#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import LaserScan
from geometry_msgs.msg import Twist
from nav_msgs.msg import Odometry
import numpy as np
import math

class ObstacleAvoidanceController(Node):
    def __init__(self, robot_name):
        super().__init__(f'{robot_name}_obstacle_avoidance')
        self.robot_name = robot_name
        
        # Parameters
        # self.linear_speed = 0.3
        # self.angular_speed = 0.5
        # self.safe_distance = 0.8  # meters
        # self.warning_distance = 1.5  # meters
        self.linear_speed = 0.5     # 中程度の速度
        self.angular_speed = 1.0     # 適度な回転速度
        self.safe_distance = 1.5     # 長めの安全距離
        self.warning_distance = 2.5  # 早期検出

        # State variables
        self.current_pose = None
        self.target_pose = None
        self.laser_data = None
        self.is_avoiding = False
        
        # Publishers and Subscribers
        self.cmd_vel_pub = self.create_publisher(
            Twist, f'/{robot_name}/cmd_vel', 10)
        
        self.laser_sub = self.create_subscription(
            LaserScan, f'/{robot_name}/scan', self.laser_callback, 10)
        
        self.odom_sub = self.create_subscription(
            Odometry, f'/{robot_name}/odom', self.odom_callback, 10)
        
        # Timer for control loop
        self.control_timer = self.create_timer(0.1, self.control_loop)
        
        self.get_logger().info(f'Obstacle avoidance controller for {robot_name} initialized')

    def laser_callback(self, msg):
        """Process laser scan data"""
        self.laser_data = msg

    def odom_callback(self, msg):
        """Process odometry data"""
        self.current_pose = msg.pose.pose

    def set_target(self, x, y):
        """Set target position"""
        self.target_pose = {'x': x, 'y': y}
        self.get_logger().info(f'Target set to ({x:.2f}, {y:.2f})')

    def get_distance_to_target(self):
        """Calculate distance to target"""
        if not self.current_pose or not self.target_pose:
            return float('inf')
        
        dx = self.target_pose['x'] - self.current_pose.position.x
        dy = self.target_pose['y'] - self.current_pose.position.y
        return math.sqrt(dx*dx + dy*dy)

    def get_angle_to_target(self):
        """Calculate angle to target"""
        if not self.current_pose or not self.target_pose:
            return 0.0
        
        dx = self.target_pose['x'] - self.current_pose.position.x
        dy = self.target_pose['y'] - self.current_pose.position.y
        target_angle = math.atan2(dy, dx)
        
        # Get current orientation
        orientation = self.current_pose.orientation
        current_yaw = math.atan2(
            2.0 * (orientation.w * orientation.z + orientation.x * orientation.y),
            1.0 - 2.0 * (orientation.y * orientation.y + orientation.z * orientation.z)
        )
        
        angle_diff = target_angle - current_yaw
        # Normalize angle to [-pi, pi]
        while angle_diff > math.pi:
            angle_diff -= 2 * math.pi
        while angle_diff < -math.pi:
            angle_diff += 2 * math.pi
            
        return angle_diff

    def detect_obstacles(self):
        """Detect obstacles using laser data"""
        if not self.laser_data:
            return False, 0.0
        
        ranges = np.array(self.laser_data.ranges)
        # Replace inf values with max range
        ranges = np.where(np.isinf(ranges), self.laser_data.range_max, ranges)
        
        # Check front sector (±45 degrees)
        front_indices = []
        angle_increment = self.laser_data.angle_increment
        angle_min = self.laser_data.angle_min
        
        for i, range_val in enumerate(ranges):
            angle = angle_min + i * angle_increment
            if -math.pi/4 <= angle <= math.pi/4:  # Front 90 degrees
                front_indices.append(i)
        
        if not front_indices:
            return False, 0.0
        
        front_ranges = ranges[front_indices]
        min_distance = np.min(front_ranges)
        
        # Find the direction with more free space
        left_ranges = ranges[:len(ranges)//4]  # Left quarter
        right_ranges = ranges[3*len(ranges)//4:]  # Right quarter
        
        left_avg = np.mean(left_ranges) if len(left_ranges) > 0 else 0
        right_avg = np.mean(right_ranges) if len(right_ranges) > 0 else 0
        
        # Prefer turning towards the side with more space
        avoidance_direction = 1.0 if left_avg > right_avg else -1.0
        
        obstacle_detected = min_distance < self.safe_distance
        return obstacle_detected, avoidance_direction

    def control_loop(self):
        """Main control loop"""
        if not self.current_pose or not self.target_pose:
            return
        
        cmd = Twist()
        
        # Check if we've reached the target
        distance_to_target = self.get_distance_to_target()
        if distance_to_target < 0.2:  # 20cm tolerance
            self.get_logger().info('Target reached!')
            self.target_pose = None
            self.cmd_vel_pub.publish(cmd)  # Stop
            return
        
        # Detect obstacles
        obstacle_detected, avoidance_direction = self.detect_obstacles()
        
        if obstacle_detected:
            # Obstacle avoidance behavior
            self.is_avoiding = True
            cmd.linear.x = 0.0  # Slow down
            cmd.angular.z = avoidance_direction * self.angular_speed
            print(f'Avoiding obstacle, turning {"left" if avoidance_direction > 0 else "right"}')
            self.get_logger().info(f'Avoiding obstacle, turning {"left" if avoidance_direction > 0 else "right"}')
        else:
            # Normal navigation towards target
            if self.is_avoiding:
                self.get_logger().info('Clear path, resuming navigation')
                self.is_avoiding = False
            
            angle_to_target = self.get_angle_to_target()
            
            # If we need to turn significantly, turn first
            if abs(angle_to_target) > 0.2:  # ~11 degrees
                cmd.angular.z = self.angular_speed if angle_to_target > 0 else -self.angular_speed
                cmd.linear.x = 0.1  # Move slowly while turning
            else:
                # Move forward towards target
                cmd.linear.x = self.linear_speed
                cmd.angular.z = 0.0
        
        self.cmd_vel_pub.publish(cmd)

def main(args=None):
    rclpy.init(args=args)
    
    # This script is meant to be imported and used by other scripts
    # For testing, you can create a controller for robot_1
    controller = ObstacleAvoidanceController('robot_1')
    controller.set_target(5.0, 5.0)  # Test target
    
    try:
        rclpy.spin(controller)
    except KeyboardInterrupt:
        pass
    finally:
        controller.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()

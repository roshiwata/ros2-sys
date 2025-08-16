#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
from nav_msgs.msg import Odometry
import math
import time
import threading

class WarehouseManager(Node):
    def __init__(self):
        super().__init__('warehouse_manager')
        
        # Robot names
        self.robot_names = ['robot_1', 'robot_2', 'robot_3', 'robot_4', 'robot_5']
        
        # Publishers for each robot
        self.cmd_vel_pubs = {}
        self.odom_subs = {}
        self.robot_poses = {}
        self.robot_targets = {}
        self.robot_moving = {}
        
        # Initialize publishers and subscribers for each robot
        for robot_name in self.robot_names:
            self.cmd_vel_pubs[robot_name] = self.create_publisher(
                Twist, 
                f'/{robot_name}/cmd_vel', 
                10
            )
            
            self.odom_subs[robot_name] = self.create_subscription(
                Odometry,
                f'/{robot_name}/odom',
                lambda msg, name=robot_name: self.odom_callback(msg, name),
                10
            )
            
            self.robot_poses[robot_name] = None
            self.robot_targets[robot_name] = None
            self.robot_moving[robot_name] = False
        
        # Control parameters
        self.linear_speed = 0.5  # m/s
        self.angular_speed = 1.0  # rad/s
        self.position_tolerance = 0.2  # meters
        self.angle_tolerance = 0.1  # radians
        
        # Timer for control loop
        self.control_timer = self.create_timer(0.1, self.control_loop)
        
        self.get_logger().info('Warehouse Manager initialized')
        
        # Wait a bit for connections to establish
        time.sleep(2.0)
        
        # Start demo sequence
        self.demo_thread = threading.Thread(target=self.run_demo)
        self.demo_thread.daemon = True
        self.demo_thread.start()
    
    def odom_callback(self, msg, robot_name):
        """Update robot pose from odometry"""
        self.robot_poses[robot_name] = msg.pose.pose
    
    def move_robot_to_goal(self, robot_name, x, y, theta=None):
        """Move specific robot to goal position"""
        if self.robot_poses[robot_name] is None:
            self.get_logger().warn(f'Pose not available for {robot_name}')
            return False
        
        self.robot_targets[robot_name] = {
            'x': x,
            'y': y,
            'theta': theta if theta is not None else 0.0
        }
        self.robot_moving[robot_name] = True
        
        self.get_logger().info(f'{robot_name} moving to: x={x:.2f}, y={y:.2f}')
        return True
    
    def control_loop(self):
        """Main control loop for all robots"""
        for robot_name in self.robot_names:
            if not self.robot_moving[robot_name]:
                continue
            if self.robot_poses[robot_name] is None:
                continue
            if self.robot_targets[robot_name] is None:
                continue
            
            # Calculate distance and angle to goal
            current_pose = self.robot_poses[robot_name]
            target = self.robot_targets[robot_name]
            
            dx = target['x'] - current_pose.position.x
            dy = target['y'] - current_pose.position.y
            distance = math.sqrt(dx**2 + dy**2)
            
            # Calculate current orientation
            current_yaw = self.quaternion_to_yaw(current_pose.orientation)
            
            # Calculate angle to goal
            angle_to_goal = math.atan2(dy, dx)
            angle_diff = self.normalize_angle(angle_to_goal - current_yaw)
            
            # Create velocity command
            cmd = Twist()
            
            if distance > self.position_tolerance:
                # First, rotate towards the goal
                if abs(angle_diff) > self.angle_tolerance:
                    cmd.angular.z = self.angular_speed if angle_diff > 0 else -self.angular_speed
                else:
                    # Move forward towards goal
                    cmd.linear.x = min(self.linear_speed, distance)
                    # Small angular correction
                    cmd.angular.z = 0.5 * angle_diff
            else:
                # Goal reached!
                self.robot_moving[robot_name] = False
                self.get_logger().info(f'{robot_name} reached goal!')
            
            # Publish velocity command
            self.cmd_vel_pubs[robot_name].publish(cmd)
    
    def stop_robot(self, robot_name):
        """Stop specific robot"""
        cmd = Twist()
        self.cmd_vel_pubs[robot_name].publish(cmd)
        self.robot_moving[robot_name] = False
    
    def stop_all_robots(self):
        """Stop all robots"""
        for robot_name in self.robot_names:
            self.stop_robot(robot_name)
        self.get_logger().info('All robots stopped')
    
    def quaternion_to_yaw(self, quaternion):
        """Convert quaternion to yaw angle"""
        siny_cosp = 2 * (quaternion.w * quaternion.z + quaternion.x * quaternion.y)
        cosy_cosp = 1 - 2 * (quaternion.y * quaternion.y + quaternion.z * quaternion.z)
        return math.atan2(siny_cosp, cosy_cosp)
    
    def normalize_angle(self, angle):
        """Normalize angle to [-pi, pi]"""
        while angle > math.pi:
            angle -= 2 * math.pi
        while angle < -math.pi:
            angle += 2 * math.pi
        return angle
    
    def wait_for_robot(self, robot_name, timeout=30.0):
        """Wait for robot to reach its goal"""
        start_time = time.time()
        while self.robot_moving[robot_name] and (time.time() - start_time) < timeout:
            time.sleep(0.1)
        return not self.robot_moving[robot_name]
    
    def get_robot_position(self, robot_name):
        """Get current robot position"""
        if self.robot_poses[robot_name] is None:
            return None
        pose = self.robot_poses[robot_name]
        return {
            'x': pose.position.x,
            'y': pose.position.y,
            'theta': self.quaternion_to_yaw(pose.orientation)
        }
    
    def run_demo(self):
        """Run a demonstration of robot movements"""
        self.get_logger().info('Starting warehouse demo in 5 seconds...')
        time.sleep(5.0)
        
        # Wait for all robots to have pose data
        while any(pose is None for pose in self.robot_poses.values()):
            self.get_logger().info('Waiting for robot pose data...')
            time.sleep(1.0)
        
        self.get_logger().info('All robots ready! Starting demo sequence...')
        
        # Demo sequence 1: Move robots to formation
        self.get_logger().info('Demo 1: Moving robots to formation')
        self.move_robot_to_goal('robot_1', -2.0, -2.0)
        self.move_robot_to_goal('robot_2', 2.0, -2.0)
        self.move_robot_to_goal('robot_3', 2.0, 2.0)
        self.move_robot_to_goal('robot_4', -2.0, 2.0)
        self.move_robot_to_goal('robot_5', 0.0, 0.0)
        
        # Wait for all robots to reach their goals
        for robot_name in self.robot_names:
            self.wait_for_robot(robot_name)
        
        self.get_logger().info('Formation complete! Waiting 3 seconds...')
        time.sleep(3.0)
        
        # Demo sequence 2: Circular movement
        self.get_logger().info('Demo 2: Circular movement pattern')
        self.move_robot_to_goal('robot_1', 0.0, -4.0)
        self.move_robot_to_goal('robot_2', 4.0, 0.0)
        self.move_robot_to_goal('robot_3', 0.0, 4.0)
        self.move_robot_to_goal('robot_4', -4.0, 0.0)
        self.move_robot_to_goal('robot_5', 1.0, 1.0)
        
        # Wait for completion
        for robot_name in self.robot_names:
            self.wait_for_robot(robot_name)
        
        self.get_logger().info('Circular pattern complete! Waiting 3 seconds...')
        time.sleep(3.0)
        
        # Demo sequence 3: Return to corners
        self.get_logger().info('Demo 3: Returning to corner positions')
        self.move_robot_to_goal('robot_1', -8.0, -8.0)
        self.move_robot_to_goal('robot_2', 8.0, -8.0)
        self.move_robot_to_goal('robot_3', 8.0, 8.0)
        self.move_robot_to_goal('robot_4', -8.0, 8.0)
        self.move_robot_to_goal('robot_5', 0.0, 0.0)
        
        # Wait for completion
        for robot_name in self.robot_names:
            self.wait_for_robot(robot_name)
        
        self.get_logger().info('Demo complete! All robots returned to starting positions.')


def main(args=None):
    rclpy.init(args=args)
    
    manager = WarehouseManager()
    
    try:
        rclpy.spin(manager)
    except KeyboardInterrupt:
        manager.get_logger().info('Shutting down warehouse manager')
    finally:
        manager.stop_all_robots()
        manager.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()

#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist, PoseStamped
from nav_msgs.msg import Odometry
from tf2_ros import TransformListener, Buffer
import math
import time

class RobotController(Node):
    def __init__(self, robot_name='robot_1'):
        super().__init__(f'{robot_name}_controller')
        self.robot_name = robot_name
        
        # Publishers and subscribers
        self.cmd_vel_pub = self.create_publisher(
            Twist, 
            f'/{robot_name}/cmd_vel', 
            10
        )
        
        self.odom_sub = self.create_subscription(
            Odometry,
            f'/{robot_name}/odom',
            self.odom_callback,
            10
        )
        
        # Robot state
        self.current_pose = None
        self.target_pose = None
        self.is_moving = False
        
        # Control parameters
        self.linear_speed = 0.5  # m/s
        self.angular_speed = 1.0  # rad/s
        self.position_tolerance = 0.1  # meters
        self.angle_tolerance = 0.1  # radians
        
        # Timer for control loop
        self.control_timer = self.create_timer(0.1, self.control_loop)
        
        self.get_logger().info(f'{robot_name} controller initialized')
    
    def odom_callback(self, msg):
        """Update current robot pose from odometry"""
        self.current_pose = msg.pose.pose
    
    def move_to_goal(self, x, y, theta=None):
        """Move robot to specified goal position"""
        if self.current_pose is None:
            self.get_logger().warn('Current pose not available yet')
            return False
        
        self.target_pose = {
            'x': x,
            'y': y,
            'theta': theta if theta is not None else 0.0
        }
        self.is_moving = True
        
        self.get_logger().info(f'Moving to goal: x={x:.2f}, y={y:.2f}, theta={theta:.2f}')
        return True
    
    def control_loop(self):
        """Main control loop for robot movement"""
        if not self.is_moving or self.current_pose is None or self.target_pose is None:
            return
        
        # Calculate distance and angle to goal
        dx = self.target_pose['x'] - self.current_pose.position.x
        dy = self.target_pose['y'] - self.current_pose.position.y
        distance = math.sqrt(dx**2 + dy**2)
        
        # Calculate current orientation
        current_yaw = self.quaternion_to_yaw(self.current_pose.orientation)
        
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
            # Reached position, now adjust final orientation if specified
            if self.target_pose['theta'] is not None:
                final_angle_diff = self.normalize_angle(self.target_pose['theta'] - current_yaw)
                if abs(final_angle_diff) > self.angle_tolerance:
                    cmd.angular.z = self.angular_speed if final_angle_diff > 0 else -self.angular_speed
                else:
                    # Goal reached!
                    self.is_moving = False
                    self.get_logger().info('Goal reached!')
            else:
                # Goal reached!
                self.is_moving = False
                self.get_logger().info('Goal reached!')
        
        # Publish velocity command
        self.cmd_vel_pub.publish(cmd)
    
    def stop(self):
        """Stop the robot"""
        cmd = Twist()
        self.cmd_vel_pub.publish(cmd)
        self.is_moving = False
        self.get_logger().info('Robot stopped')
    
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
    
    def get_current_position(self):
        """Get current robot position"""
        if self.current_pose is None:
            return None
        return {
            'x': self.current_pose.position.x,
            'y': self.current_pose.position.y,
            'theta': self.quaternion_to_yaw(self.current_pose.orientation)
        }
    
    def is_goal_reached(self):
        """Check if robot has reached its goal"""
        return not self.is_moving


def main(args=None):
    rclpy.init(args=args)
    
    # Get robot name from command line arguments
    import sys
    robot_name = 'robot_1'
    if len(sys.argv) > 1:
        robot_name = sys.argv[1]
    
    controller = RobotController(robot_name)
    
    try:
        rclpy.spin(controller)
    except KeyboardInterrupt:
        controller.get_logger().info('Shutting down robot controller')
    finally:
        controller.stop()
        controller.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()

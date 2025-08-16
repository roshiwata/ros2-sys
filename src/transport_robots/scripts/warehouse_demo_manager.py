#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist, PoseStamped
from nav_msgs.msg import Odometry
from sensor_msgs.msg import LaserScan
import math
import time
import threading

class RobotController:
    def __init__(self, node, robot_name):
        self.node = node
        self.robot_name = robot_name
        self.current_pose = None
        self.target_pose = None
        self.is_moving = False
        
        # Publishers and subscribers
        self.cmd_vel_pub = node.create_publisher(
            Twist, f'/{robot_name}/cmd_vel', 10
        )
        
        self.odom_sub = node.create_subscription(
            Odometry, f'/{robot_name}/odom', self.odom_callback, 10
        )
        
        # Movement parameters
        self.linear_speed = 0.5
        self.angular_speed = 1.0
        self.position_tolerance = 0.3
        self.angle_tolerance = 0.1
        
    def odom_callback(self, msg):
        self.current_pose = msg.pose.pose
        
    def move_to_goal(self, target_x, target_y):
        """Move robot to target position"""
        if self.current_pose is None:
            self.node.get_logger().warn(f'{self.robot_name}: No pose data available')
            return False
            
        self.target_pose = (target_x, target_y)
        self.is_moving = True
        
        self.node.get_logger().info(
            f'{self.robot_name}: Moving to ({target_x:.2f}, {target_y:.2f})'
        )
        
        # Start movement in separate thread
        movement_thread = threading.Thread(target=self._move_to_target)
        movement_thread.start()
        
        return True
        
    def _move_to_target(self):
        """Internal method to handle movement"""
        rate = self.node.create_rate(10)  # 10 Hz
        
        while self.is_moving and rclpy.ok():
            if self.current_pose is None:
                continue
                
            # Calculate distance and angle to target
            dx = self.target_pose[0] - self.current_pose.position.x
            dy = self.target_pose[1] - self.current_pose.position.y
            distance = math.sqrt(dx*dx + dy*dy)
            
            if distance < self.position_tolerance:
                # Reached target
                self._stop_robot()
                self.is_moving = False
                self.node.get_logger().info(f'{self.robot_name}: Reached target!')
                break
                
            # Calculate target angle
            target_angle = math.atan2(dy, dx)
            
            # Get current orientation
            current_quat = self.current_pose.orientation
            current_angle = math.atan2(
                2.0 * (current_quat.w * current_quat.z + current_quat.x * current_quat.y),
                1.0 - 2.0 * (current_quat.y * current_quat.y + current_quat.z * current_quat.z)
            )
            
            # Calculate angle difference
            angle_diff = target_angle - current_angle
            while angle_diff > math.pi:
                angle_diff -= 2 * math.pi
            while angle_diff < -math.pi:
                angle_diff += 2 * math.pi
                
            # Create movement command
            cmd = Twist()
            
            if abs(angle_diff) > self.angle_tolerance:
                # Need to rotate
                cmd.angular.z = self.angular_speed if angle_diff > 0 else -self.angular_speed
                cmd.linear.x = 0.1  # Slow forward movement while turning
            else:
                # Move forward
                cmd.linear.x = min(self.linear_speed, distance)
                cmd.angular.z = 0.0
                
            self.cmd_vel_pub.publish(cmd)
            
            try:
                rate.sleep()
            except:
                break
                
    def _stop_robot(self):
        """Stop the robot"""
        cmd = Twist()
        self.cmd_vel_pub.publish(cmd)
        
    def stop(self):
        """Stop robot movement"""
        self.is_moving = False
        self._stop_robot()

class WarehouseDemoManager(Node):
    def __init__(self):
        super().__init__('warehouse_demo_manager')
        
        self.get_logger().info('Warehouse Demo Manager initialized')
        
        # Robot names
        self.robot_names = ['robot_1', 'robot_2', 'robot_3', 'robot_4', 'robot_5']
        
        # Create robot controllers
        self.robots = {}
        for robot_name in self.robot_names:
            self.robots[robot_name] = RobotController(self, robot_name)
            
        # Demo waypoints for each robot (avoiding obstacles)
        self.demo_waypoints = {
            'robot_1': [
                (-12.0, -12.0),  # Start position
                (-6.0, -12.0),   # Move right
                (-6.0, -6.0),    # Move up
                (-12.0, -6.0),   # Move left
                (-12.0, -12.0)   # Return to start
            ],
            'robot_2': [
                (-12.0, 12.0),   # Start position
                (-6.0, 12.0),    # Move right
                (-6.0, 6.0),     # Move down
                (-12.0, 6.0),    # Move left
                (-12.0, 12.0)    # Return to start
            ],
            'robot_3': [
                (12.0, -12.0),   # Start position
                (6.0, -12.0),    # Move left
                (6.0, -6.0),     # Move up
                (12.0, -6.0),    # Move right
                (12.0, -12.0)    # Return to start
            ],
            'robot_4': [
                (12.0, 12.0),    # Start position
                (6.0, 12.0),     # Move left
                (6.0, 6.0),      # Move down
                (12.0, 6.0),     # Move right
                (12.0, 12.0)     # Return to start
            ],
            'robot_5': [
                (-6.0, 12.0),    # Start position
                (6.0, 12.0),     # Move right
                (6.0, -12.0),    # Move down
                (-6.0, -12.0),   # Move left
                (-6.0, 12.0)     # Return to start
            ]
        }
        
        # Current waypoint index for each robot
        self.current_waypoint = {robot: 0 for robot in self.robot_names}
        
        # Start demo after delay
        self.demo_timer = self.create_timer(5.0, self.start_demo)
        self.demo_started = False
        
    def start_demo(self):
        """Start the warehouse demo"""
        if self.demo_started:
            return
            
        self.demo_started = True
        self.demo_timer.cancel()
        
        self.get_logger().info('Starting warehouse demo in 5 seconds...')
        
        # Wait for robot pose data
        self.pose_check_timer = self.create_timer(1.0, self.check_poses_and_start)
        
    def check_poses_and_start(self):
        """Check if all robots have pose data and start movement"""
        all_ready = True
        for robot_name, robot in self.robots.items():
            if robot.current_pose is None:
                all_ready = False
                self.get_logger().info(f'Waiting for {robot_name} pose data...')
                break
                
        if all_ready:
            self.pose_check_timer.cancel()
            self.get_logger().info('All robots ready! Starting movement demo...')
            self.start_movement_demo()
            
    def start_movement_demo(self):
        """Start the movement demonstration"""
        # Move all robots to their first waypoints
        for robot_name in self.robot_names:
            waypoints = self.demo_waypoints[robot_name]
            if len(waypoints) > 1:  # Skip start position, go to first waypoint
                target_x, target_y = waypoints[1]
                self.robots[robot_name].move_to_goal(target_x, target_y)
                self.current_waypoint[robot_name] = 1
                
        # Create timer to check progress and move to next waypoints
        self.movement_timer = self.create_timer(2.0, self.check_movement_progress)
        
    def check_movement_progress(self):
        """Check movement progress and assign next waypoints"""
        for robot_name in self.robot_names:
            robot = self.robots[robot_name]
            
            # If robot is not moving, assign next waypoint
            if not robot.is_moving:
                waypoints = self.demo_waypoints[robot_name]
                current_idx = self.current_waypoint[robot_name]
                
                # Move to next waypoint
                next_idx = (current_idx + 1) % len(waypoints)
                target_x, target_y = waypoints[next_idx]
                
                self.get_logger().info(
                    f'{robot_name}: Moving to waypoint {next_idx} ({target_x:.1f}, {target_y:.1f})'
                )
                
                robot.move_to_goal(target_x, target_y)
                self.current_waypoint[robot_name] = next_idx
                
    def shutdown(self):
        """Shutdown all robots"""
        for robot in self.robots.values():
            robot.stop()

def main(args=None):
    rclpy.init(args=args)
    
    warehouse_manager = WarehouseDemoManager()
    
    try:
        rclpy.spin(warehouse_manager)
    except KeyboardInterrupt:
        warehouse_manager.get_logger().info('Demo interrupted by user')
    finally:
        warehouse_manager.shutdown()
        warehouse_manager.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()

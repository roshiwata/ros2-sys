#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from obstacle_avoidance_controller import ObstacleAvoidanceController
import threading
import time

class EnhancedWarehouseDemo(Node):
    def __init__(self):
        super().__init__('enhanced_warehouse_demo')
        
        # Create obstacle avoidance controllers for all robots
        self.controllers = {}
        self.robot_names = ['robot_1', 'robot_2', 'robot_3', 'robot_4', 'robot_5']
        
        for robot_name in self.robot_names:
            self.controllers[robot_name] = ObstacleAvoidanceController(robot_name)
        
        # Define waypoints for each robot (avoiding initial collisions)
        self.waypoints = {
            'robot_1': [(-6.0, -6.0), (6.0, -6.0), (6.0, 6.0), (-6.0, 6.0)],
            'robot_2': [(6.0, -6.0), (6.0, 6.0), (-6.0, 6.0), (-6.0, -6.0)],
            'robot_3': [(6.0, 6.0), (-6.0, 6.0), (-6.0, -6.0), (6.0, -6.0)],
            'robot_4': [(-6.0, 6.0), (-6.0, -6.0), (6.0, -6.0), (6.0, 6.0)],
            'robot_5': [(0.0, 0.0), (8.0, 0.0), (0.0, 8.0), (-8.0, 0.0)]
        }
        
        self.current_waypoint_index = {robot: 0 for robot in self.robot_names}
        self.demo_active = False
        
        self.get_logger().info('Enhanced Warehouse Demo with Obstacle Avoidance initialized')

    def start_demo(self):
        """Start the enhanced demo with obstacle avoidance"""
        self.demo_active = True
        self.get_logger().info('Starting enhanced warehouse demo with obstacle avoidance...')
        
        # Set initial targets for all robots
        for robot_name in self.robot_names:
            waypoint = self.waypoints[robot_name][0]
            self.controllers[robot_name].set_target(waypoint[0], waypoint[1])
            self.get_logger().info(f'{robot_name}: Moving to waypoint 1 {waypoint}')
        
        # Start monitoring thread
        self.monitor_thread = threading.Thread(target=self.monitor_progress)
        self.monitor_thread.daemon = True
        self.monitor_thread.start()

    def monitor_progress(self):
        """Monitor robot progress and assign new waypoints"""
        while self.demo_active:
            time.sleep(2.0)  # Check every 2 seconds
            
            for robot_name in self.robot_names:
                controller = self.controllers[robot_name]
                
                # Check if robot has reached its target
                if controller.target_pose is None:  # Target reached
                    # Move to next waypoint
                    self.current_waypoint_index[robot_name] = (
                        self.current_waypoint_index[robot_name] + 1
                    ) % len(self.waypoints[robot_name])
                    
                    next_waypoint = self.waypoints[robot_name][
                        self.current_waypoint_index[robot_name]
                    ]
                    
                    controller.set_target(next_waypoint[0], next_waypoint[1])
                    self.get_logger().info(
                        f'{robot_name}: Moving to waypoint '
                        f'{self.current_waypoint_index[robot_name] + 1} {next_waypoint}'
                    )

    def stop_demo(self):
        """Stop the demo"""
        self.demo_active = False
        self.get_logger().info('Stopping enhanced warehouse demo')

def main(args=None):
    rclpy.init(args=args)
    
    # Create the demo manager
    demo = EnhancedWarehouseDemo()
    
    # Start the demo after a short delay
    def delayed_start():
        time.sleep(5.0)
        demo.start_demo()
    
    start_thread = threading.Thread(target=delayed_start)
    start_thread.daemon = True
    start_thread.start()
    
    try:
        # Spin all controllers
        executor = rclpy.executors.MultiThreadedExecutor()
        executor.add_node(demo)
        
        for controller in demo.controllers.values():
            executor.add_node(controller)
        
        executor.spin()
        
    except KeyboardInterrupt:
        demo.get_logger().info('Demo interrupted by user')
    finally:
        demo.stop_demo()
        demo.destroy_node()
        
        for controller in demo.controllers.values():
            controller.destroy_node()
        
        rclpy.shutdown()

if __name__ == '__main__':
    main()

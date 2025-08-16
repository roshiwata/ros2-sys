#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
from nav_msgs.msg import Odometry
import math
import time

class ProductManager(Node):
    def __init__(self):
        super().__init__('product_manager')
        
        # Simple product management demo
        self.products = {
            'A': {'location': (-7.0, -7.0), 'robot': 'robot_1'},
            'B': {'location': (7.0, -7.0), 'robot': 'robot_2'},
            'C': {'location': (7.0, 7.0), 'robot': 'robot_3'},
            'D': {'location': (-7.0, 7.0), 'robot': 'robot_4'},
            'E': {'location': (0.0, 0.0), 'robot': 'robot_5'},
        }
        
        # Robot command publishers
        self.robot_names = ['robot_1', 'robot_2', 'robot_3', 'robot_4', 'robot_5']
        self.cmd_vel_pubs = {}
        
        for robot_name in self.robot_names:
            self.cmd_vel_pubs[robot_name] = self.create_publisher(
                Twist, 
                f'/{robot_name}/cmd_vel', 
                10
            )
        
        self.get_logger().info('Product Manager initialized')
        self.get_logger().info('Available products: A, B, C, D, E')
        self.get_logger().info('Use move_robot_to_product(robot_name, product_id) to move robots')
    
    def move_robot_to_product(self, robot_name, product_id):
        """Move robot to product location"""
        if product_id not in self.products:
            self.get_logger().error(f'Product {product_id} not found')
            return False
        
        if robot_name not in self.robot_names:
            self.get_logger().error(f'Robot {robot_name} not found')
            return False
        
        location = self.products[product_id]['location']
        self.get_logger().info(f'Moving {robot_name} to product {product_id} at {location}')
        
        # This is a simplified version - in a real system, you would use
        # the warehouse manager or robot controller to handle the movement
        return True
    
    def get_product_info(self, product_id):
        """Get product information"""
        if product_id in self.products:
            return self.products[product_id]
        return None
    
    def list_products(self):
        """List all available products"""
        self.get_logger().info('Available products:')
        for product_id, info in self.products.items():
            self.get_logger().info(f'  {product_id}: {info["location"]} (assigned to {info["robot"]})')


def main(args=None):
    rclpy.init(args=args)
    
    manager = ProductManager()
    
    try:
        rclpy.spin(manager)
    except KeyboardInterrupt:
        manager.get_logger().info('Shutting down product manager')
    finally:
        manager.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()

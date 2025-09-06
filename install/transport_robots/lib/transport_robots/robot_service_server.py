#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
from nav_msgs.msg import Odometry
import math
import threading
import time

# カスタムサービスメッセージをインポート
from transport_robots.srv import SetGoal, GetPosition


class RobotController:
    """個別ロボットの制御クラス"""
    def __init__(self, node, robot_name):
        self.node = node
        self.robot_name = robot_name
        self.current_pose = None
        self.current_twist = None
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
        """オドメトリデータのコールバック"""
        self.current_pose = msg.pose.pose
        self.current_twist = msg.twist.twist
        
    def set_goal(self, x, y, yaw=None):
        """目標座標を設定"""
        if self.current_pose is None:
            return False, "No pose data available"
            
        self.target_pose = {'x': x, 'y': y, 'yaw': yaw}
        self.is_moving = True
        
        # 移動スレッドを開始
        movement_thread = threading.Thread(target=self._move_to_target)
        movement_thread.daemon = True
        movement_thread.start()
        
        return True, f"Goal set to ({x:.2f}, {y:.2f})"

    def get_position(self):
        """現在の位置情報を取得"""
        if self.current_pose is None:
            return False, "No pose data available", {}
            
        # クォータニオンからオイラー角に変換
        orientation = self.current_pose.orientation
        roll, pitch, yaw = self._quaternion_to_euler(
            orientation.x, orientation.y, orientation.z, orientation.w
        )
        
        position_data = {
            'x': self.current_pose.position.x,
            'y': self.current_pose.position.y,
            'z': self.current_pose.position.z,
            'roll': roll,
            'pitch': pitch,
            'yaw': yaw,
            'linear_x': self.current_twist.linear.x if self.current_twist else 0.0,
            'linear_y': self.current_twist.linear.y if self.current_twist else 0.0,
            'angular_z': self.current_twist.angular.z if self.current_twist else 0.0
        }
        
        return True, "Position data retrieved", position_data
        
    def _quaternion_to_euler(self, x, y, z, w):
        """クォータニオンをオイラー角に変換"""
        # Roll (x-axis rotation)
        sinr_cosp = 2 * (w * x + y * z)
        cosr_cosp = 1 - 2 * (x * x + y * y)
        roll = math.atan2(sinr_cosp, cosr_cosp)
        
        # Pitch (y-axis rotation)
        sinp = 2 * (w * y - z * x)
        if abs(sinp) >= 1:
            pitch = math.copysign(math.pi / 2, sinp)
        else:
            pitch = math.asin(sinp)
            
        # Yaw (z-axis rotation)
        siny_cosp = 2 * (w * z + x * y)
        cosy_cosp = 1 - 2 * (y * y + z * z)
        yaw = math.atan2(siny_cosp, cosy_cosp)
        
        return roll, pitch, yaw
        
    def _move_to_target(self):
        """目標座標への移動処理"""
        rate = self.node.create_rate(10)  # 10 Hz
        
        while self.is_moving and rclpy.ok():
            if self.current_pose is None:
                continue
                
            # 目標までの距離と角度を計算
            dx = self.target_pose['x'] - self.current_pose.position.x
            dy = self.target_pose['y'] - self.current_pose.position.y
            distance = math.sqrt(dx*dx + dy*dy)

            if distance < self.position_tolerance:
                # 目標に到達
                self._stop_robot()
                self.is_moving = False
                self.node.get_logger().info(f'{self.robot_name}: Reached target!')
                break

            # 目標角度を計算
            target_angle = math.atan2(dy, dx)

            # 現在の姿勢を取得
            _, _, current_yaw = self._quaternion_to_euler(
                self.current_pose.orientation.x,
                self.current_pose.orientation.y,
                self.current_pose.orientation.z,
                self.current_pose.orientation.w
            )
            
            # 角度差を計算
            angle_diff = target_angle - current_yaw
            while angle_diff > math.pi:
                angle_diff -= 2 * math.pi
            while angle_diff < -math.pi:
                angle_diff += 2 * math.pi
                
            # 移動コマンドを作成
            cmd = Twist()
            
            if abs(angle_diff) > self.angle_tolerance:
                # 回転が必要
                cmd.angular.z = self.angular_speed if angle_diff > 0 else -self.angular_speed
                cmd.linear.x = 0.1  # 回転中は低速前進
            else:
                # 前進
                cmd.linear.x = min(self.linear_speed, distance)
                cmd.angular.z = 0.0
            
            self.cmd_vel_pub.publish(cmd)
            
            try:
                rate.sleep()
            except:
                break
                
    def _stop_robot(self):
        """ロボットを停止"""
        cmd = Twist()
        self.cmd_vel_pub.publish(cmd)

    def stop(self):
        """移動を停止"""
        self.is_moving = False
        self._stop_robot()


class RobotServiceServer(Node):
    """ロボット制御サービスサーバー"""
    
    def __init__(self):
        super().__init__('robot_service_server')
        
        # ロボットコントローラーを初期化
        self.robot_names = ['robot_1', 'robot_2', 'robot_3', 'robot_4', 'robot_5']
        self.robots = {}
        
        for robot_name in self.robot_names:
            self.robots[robot_name] = RobotController(self, robot_name)
            
        # サービスサーバーを作成
        self.set_goal_service = self.create_service(
            SetGoal, 'set_robot_goal', self.set_goal_callback
        )
        
        self.get_position_service = self.create_service(
            GetPosition, 'get_robot_position', self.get_position_callback
        )
        
        self.get_logger().info('Robot Service Server initialized')
        self.get_logger().info(f'Available robots: {", ".join(self.robot_names)}')
        self.get_logger().info('Services:')
        self.get_logger().info('  - /set_robot_goal (SetGoal)')
        self.get_logger().info('  - /get_robot_position (GetPosition)')
        
    def set_goal_callback(self, request, response):
        """目標座標設定サービスのコールバック"""
        robot_name = request.robot_name
        
        if robot_name not in self.robots:
            response.success = False
            response.message = f"Robot '{robot_name}' not found. Available: {', '.join(self.robot_names)}"
            return response
            
        try:
            success, message = self.robots[robot_name].set_goal(
                request.x, request.y, request.yaw
            )
            response.success = success
            response.message = message

            if success:
                self.get_logger().info(
                    f"Goal set for {robot_name}: ({request.x:.2f}, {request.y:.2f})"
                )
            else:
                self.get_logger().warn(f"Failed to set goal for {robot_name}: {message}")
                
        except Exception as e:
            response.success = False
            response.message = f"Error setting goal: {str(e)}"
            self.get_logger().error(f"Exception in set_goal_callback: {str(e)}")
            
        return response
        
    def get_position_callback(self, request, response):
        """位置情報取得サービスのコールバック"""
        robot_name = request.robot_name
        
        if robot_name not in self.robots:
            response.success = False
            response.message = f"Robot '{robot_name}' not found. Available: {', '.join(self.robot_names)}"
            return response
            
        try:
            success, message, position_data = self.robots[robot_name].get_position()
            
            response.success = success
            response.message = message
            
            if success:
                response.x = position_data['x']
                response.y = position_data['y']
                response.z = position_data['z']
                response.roll = position_data['roll']
                response.pitch = position_data['pitch']
                response.yaw = position_data['yaw']
                response.linear_x = position_data['linear_x']
                response.linear_y = position_data['linear_y']
                response.angular_z = position_data['angular_z']
                
                self.get_logger().info(
                    f"Position for {robot_name}: ({position_data['x']:.2f}, {position_data['y']:.2f})"
                )
            else:
                self.get_logger().warn(f"Failed to get position for {robot_name}: {message}")
                
        except Exception as e:
            response.success = False
            response.message = f"Error getting position: {str(e)}"
            self.get_logger().error(f"Exception in get_position_callback: {str(e)}")
            
        return response


def main(args=None):
    rclpy.init(args=args)
    
    service_server = RobotServiceServer()
    
    try:
        rclpy.spin(service_server)
    except KeyboardInterrupt:
        service_server.get_logger().info('Service server interrupted by user')
    finally:
        # 全ロボットを停止
        for robot in service_server.robots.values():
            robot.stop()
            
        service_server.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()

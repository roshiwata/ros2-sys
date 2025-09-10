#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
from nav_msgs.msg import Odometry
from sensor_msgs.msg import LaserScan
import math
import threading
import time
import numpy as np

# カスタムサービスメッセージをインポート
from transport_robots.srv import SetGoal, GetPosition


class RobotControllerWithAvoidance:
    """障害物回避機能付きロボットコントローラー"""
    def __init__(self, node, robot_name, initial_position=None):
        self.node = node
        self.robot_name = robot_name
        self.initial_position = initial_position  # launchファイルからの初期位置
        self.current_pose = None
        self.current_twist = None
        self.laser_data = None
        self.target_pose = None
        self.is_moving = False
        self.is_avoiding = False
        
        # オドメトリ補正用の変数
        self.odom_offset = None  # 初期オドメトリと初期位置の差分
        self.first_odom_received = False

        # Publishers and subscribers
        self.cmd_vel_pub = node.create_publisher(
            Twist, f'/{robot_name}/cmd_vel', 10
        )
        
        self.odom_sub = node.create_subscription(
            Odometry, f'/{robot_name}/odom', self.odom_callback, 10
        )
        
        self.laser_sub = node.create_subscription(
            LaserScan, f'/{robot_name}/scan', self.laser_callback, 10
        )
        
        # Movement parameters
        self.linear_speed = 0.5
        self.angular_speed = 0.3
        self.position_tolerance = 0.02
        self.angle_tolerance_max = 0.5
        self.angle_tolerance_min = 0.1

        # Obstacle avoidance parameters
        self.safe_distance = 0.8  # meters
        self.warning_distance = 1.5  # meters
        
        # Control timer
        self.control_timer = node.create_timer(0.1, self.control_loop)
        
        # 初期位置情報をログ出力
        if self.initial_position:
            self.node.get_logger().info(
                f'{self.robot_name}: Initial position set to '
                f'({self.initial_position["x"]:.2f}, {self.initial_position["y"]:.2f}, '
                f'yaw={self.initial_position["yaw"]:.2f})'
            )
        
    def odom_callback(self, msg):
        """オドメトリデータのコールバック（初期位置補正付き）"""
        self.current_twist = msg.twist.twist
        
        # 初回オドメトリ受信時にオフセットを計算
        if not self.first_odom_received and self.initial_position:
            # 初期オドメトリ位置を取得
            initial_odom_x = msg.pose.pose.position.x
            initial_odom_y = msg.pose.pose.position.y
            initial_odom_z = msg.pose.pose.position.z
            
            # 初期オドメトリの姿勢を取得
            initial_odom_orientation = msg.pose.pose.orientation
            _, _, initial_odom_yaw = self._quaternion_to_euler(
                initial_odom_orientation.x,
                initial_odom_orientation.y,
                initial_odom_orientation.z,
                initial_odom_orientation.w
            )
            
            # オフセットを計算（初期位置 - 初期オドメトリ）
            self.odom_offset = {
                'x': self.initial_position['x'] - initial_odom_x,
                'y': self.initial_position['y'] - initial_odom_y,
                'z': self.initial_position['z'] - initial_odom_z,
                'yaw': self.initial_position['yaw'] - initial_odom_yaw
            }
            
            self.first_odom_received = True
            self.node.get_logger().info(
                f'{self.robot_name}: Odometry offset calculated: '
                f'({self.odom_offset["x"]:.3f}, {self.odom_offset["y"]:.3f}, '
                f'yaw={self.odom_offset["yaw"]:.3f})'
            )
        
        # オドメトリデータを補正して保存
        if self.odom_offset:
            # 補正された位置を計算
            corrected_pose = type(msg.pose.pose)()
            corrected_pose.position.x = msg.pose.pose.position.x + self.odom_offset['x']
            corrected_pose.position.y = msg.pose.pose.position.y + self.odom_offset['y']
            corrected_pose.position.z = msg.pose.pose.position.z + self.odom_offset['z']
            
            # 姿勢の補正（yaw角度のみ）
            current_orientation = msg.pose.pose.orientation
            _, _, current_yaw = self._quaternion_to_euler(
                current_orientation.x,
                current_orientation.y,
                current_orientation.z,
                current_orientation.w
            )
            corrected_yaw = current_yaw + self.odom_offset['yaw']
            
            # 補正されたyawをクォータニオンに変換
            corrected_pose.orientation.x = 0.0
            corrected_pose.orientation.y = 0.0
            corrected_pose.orientation.z = math.sin(corrected_yaw / 2.0)
            corrected_pose.orientation.w = math.cos(corrected_yaw / 2.0)
            
            self.current_pose = corrected_pose
        else:
            # オフセットが未計算の場合は生のオドメトリを使用
            self.current_pose = msg.pose.pose
        
    def laser_callback(self, msg):
        """LiDARデータのコールバック"""
        self.laser_data = msg
        
    def set_goal(self, x, y, yaw=None):
        """目標座標を設定"""
        if self.current_pose is None:
            return False, "No pose data available"
            
        self.target_pose = {'x': x, 'y': y, 'yaw': yaw}
        self.is_moving = True
        
        self.node.get_logger().info(
            f'{self.robot_name}: Goal set to ({x:.2f}, {y:.2f}) with obstacle avoidance'
        )
        
        return True, f"Goal set to ({x:.2f}, {y:.2f}) with obstacle avoidance"
    
    def set_goal_to_initial_position(self):
        """初期位置に戻る"""
        if not self.initial_position:
            return False, "No initial position data available"
        
        return self.set_goal(
            self.initial_position['x'], 
            self.initial_position['y'], 
            self.initial_position['yaw']
        )
    
    def get_initial_position(self):
        """初期位置情報を取得"""
        if not self.initial_position:
            return False, "No initial position data available", {}
        
        return True, "Initial position data retrieved", self.initial_position
        
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
        
    def detect_obstacles(self):
        """LiDARを使用した障害物検知"""
        if not self.laser_data:
            return False, 0.0
        
        ranges = np.array(self.laser_data.ranges)
        # 無限値を最大範囲で置換
        ranges = np.where(np.isinf(ranges), self.laser_data.range_max, ranges)
        ranges = np.where(np.isnan(ranges), self.laser_data.range_max, ranges)
        
        # 前方セクター（±45度）をチェック
        num_samples = len(ranges)
        angle_min = self.laser_data.angle_min
        angle_increment = self.laser_data.angle_increment
        
        front_indices = []
        for i in range(num_samples):
            angle = angle_min + i * angle_increment
            if -math.pi/4 <= angle <= math.pi/4:  # 前方90度
                front_indices.append(i)
        
        if not front_indices:
            return False, 0.0
        
        front_ranges = ranges[front_indices]
        min_distance = np.min(front_ranges)
        
        # 左右の自由空間を比較
        left_half = ranges[:num_samples//2]
        right_half = ranges[num_samples//2:]
        
        left_avg = np.mean(left_half)
        right_avg = np.mean(right_half)
        
        # より空いている方向を選択
        avoidance_direction = 1.0 if left_avg > right_avg else -1.0
        
        obstacle_detected = min_distance < self.safe_distance
        return obstacle_detected, avoidance_direction
        
    def control_loop(self):
        """メイン制御ループ（障害物回避機能付き）"""
        if not self.current_pose or not self.target_pose:
            return
        
        cmd = Twist()
        
        # 目標到達チェック
        distance_to_target = self.get_distance_to_target()
        if distance_to_target < self.position_tolerance:
            self.node.get_logger().info(f'{self.robot_name}: Target reached!')
            self.target_pose = None
            self.is_moving = False
            self.cmd_vel_pub.publish(cmd)  # 停止
            return
        
        # 障害物検知
        obstacle_detected, avoidance_direction = self.detect_obstacles()
        print(f"{obstacle_detected=}, {avoidance_direction=}, {self.is_avoiding=}")

        if obstacle_detected:
            # 障害物回避動作
            self.is_avoiding = True
            cmd.linear.x = 0.1  # 減速
            cmd.angular.z = avoidance_direction * self.angular_speed
            self.node.get_logger().info(
                f'{self.robot_name}: Avoiding obstacle, turning {"left" if avoidance_direction > 0 else "right"}'
            )
        else:
            # 通常のナビゲーション
            if self.is_avoiding:
                self.node.get_logger().info(f'{self.robot_name}: Clear path, resuming navigation')
                self.is_avoiding = False

            angle_to_target = self.get_angle_to_target()
            print(f"{angle_to_target=}")

            # 大きく回転が必要な場合は回転優先
            if abs(angle_to_target) > self.angle_tolerance_max:
                print("大回転")
                cmd.angular.z = self.angular_speed if angle_to_target > 0 else -self.angular_speed
                cmd.linear.x = 0.0  # 回転中は低速前進
            # ちょっとだけ方向ずれてる時
            elif self.angle_tolerance_max > abs(angle_to_target) and abs(angle_to_target) > self.angle_tolerance_min:
                print("小回転")
                cmd.angular.z = self.angular_speed if angle_to_target > 0 else -self.angular_speed
                cmd.linear.x = 0.1  # 回転中は低速前進
            else:
                print("ゼロ回転")
                # 目標に向かって前進
                cmd.linear.x = min(self.linear_speed, distance_to_target)
                cmd.angular.z = 0.0

        print(f"{cmd=}")
        self.cmd_vel_pub.publish(cmd)
        
    def get_distance_to_target(self):
        """目標までの距離を計算"""
        if not self.current_pose or not self.target_pose:
            return float('inf')

        dx = self.target_pose['x'] - self.current_pose.position.x
        dy = self.target_pose['y'] - self.current_pose.position.y
        return math.sqrt(dx*dx + dy*dy)

    def get_angle_to_target(self):
        """目標への角度を計算"""
        if not self.current_pose or not self.target_pose:
            return 0.0

        dx = self.target_pose['x'] - self.current_pose.position.x
        dy = self.target_pose['y'] - self.current_pose.position.y
        # dx = -1 * (self.target_pose['x'] + self.current_pose.position.x)
        # dy = -1 * (self.target_pose['y'] + self.current_pose.position.y)
        # dx = self.current_pose.position.x - self.target_pose['x']
        # dy = self.current_pose.position.y - self.target_pose['y']
        target_angle = math.atan2(dy, dx)
        print(f"{self.target_pose['x']=}, {self.current_pose.position.x=}")
        print(f"{self.target_pose['y']=}, {self.current_pose.position.y=}")
        print(f"{dx=}, {dy=}, {target_angle=}")

        # 現在の姿勢を取得
        _, _, current_yaw = self._quaternion_to_euler(
            self.current_pose.orientation.x,
            self.current_pose.orientation.y,
            self.current_pose.orientation.z,
            self.current_pose.orientation.w
        )
        print(f"{current_yaw=}")

        # 角度差を計算
        angle_diff = target_angle - current_yaw
        while angle_diff > math.pi:
            angle_diff -= 2 * math.pi
        while angle_diff < -math.pi:
            angle_diff += 2 * math.pi
            
        return angle_diff
        
    def stop(self):
        """移動を停止"""
        self.is_moving = False
        self.target_pose = None
        cmd = Twist()
        self.cmd_vel_pub.publish(cmd)


class RobotServiceServerWithAvoidance(Node):
    """障害物回避機能付きロボット制御サービスサーバー"""
    
    def __init__(self):
        super().__init__('robot_service_server_with_avoidance')
        
        # ロボットの初期位置（launchファイルと同じ設定）
        self.robot_initial_positions = {
            'robot_1': {'x': -8.0, 'y': -8.0, 'z': 0.1, 'yaw': 0.0},
            'robot_2': {'x': 8.0, 'y': -8.0, 'z': 0.1, 'yaw': 1.57},
            'robot_3': {'x': 8.0, 'y': 8.0, 'z': 0.1, 'yaw': 3.14},
            'robot_4': {'x': -8.0, 'y': 8.0, 'z': 0.1, 'yaw': -1.57},
            'robot_5': {'x': 0.0, 'y': 0.0, 'z': 0.1, 'yaw': 0.0},
        }
        
        # ロボットコントローラーを初期化
        self.robot_names = list(self.robot_initial_positions.keys())
        self.robots = {}
        
        for robot_name in self.robot_names:
            initial_pos = self.robot_initial_positions[robot_name]
            self.robots[robot_name] = RobotControllerWithAvoidance(
                self, robot_name, initial_pos
            )
            
        # サービスサーバーを作成
        self.set_goal_service = self.create_service(
            SetGoal, 'set_robot_goal', self.set_goal_callback
        )
        
        self.get_position_service = self.create_service(
            GetPosition, 'get_robot_position', self.get_position_callback
        )

        self.get_logger().info('Robot Service Server with Obstacle Avoidance initialized')
        self.get_logger().info(f'Available robots: {", ".join(self.robot_names)}')
        self.get_logger().info('Robot initial positions:')
        for robot_name, pos in self.robot_initial_positions.items():
            self.get_logger().info(f'  - {robot_name}: ({pos["x"]:.1f}, {pos["y"]:.1f}, yaw={pos["yaw"]:.2f})')
        self.get_logger().info('Services:')
        self.get_logger().info('  - /set_robot_goal (SetGoal) - with obstacle avoidance')
        self.get_logger().info('  - /get_robot_position (GetPosition)')
        self.get_logger().info('Features:')
        self.get_logger().info('  - LiDAR-based obstacle detection')
        self.get_logger().info('  - Dynamic obstacle avoidance')
        self.get_logger().info('  - Multi-robot coordination')
        self.get_logger().info('  - Initial position tracking from launch file')
        
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
                    f"Goal set for {robot_name}: ({request.x:.2f}, {request.y:.2f}) with obstacle avoidance"
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
    
    service_server = RobotServiceServerWithAvoidance()
    
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

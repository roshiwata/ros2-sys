#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
import sys
import time

# カスタムサービスメッセージをインポート
from transport_robots.srv import SetGoal, GetPosition


class RobotClientApp(Node):
    """ロボット制御クライアントアプリケーション"""
    
    def __init__(self):
        super().__init__('robot_client_app')
        
        # サービスクライアントを作成
        self.set_goal_client = self.create_client(SetGoal, 'set_robot_goal')
        self.get_position_client = self.create_client(GetPosition, 'get_robot_position')
        
        # サービスが利用可能になるまで待機
        self.get_logger().info('Waiting for services...')
        
        if not self.set_goal_client.wait_for_service(timeout_sec=10.0):
            self.get_logger().error('set_robot_goal service not available')
            return
            
        if not self.get_position_client.wait_for_service(timeout_sec=10.0):
            self.get_logger().error('get_robot_position service not available')
            return
            
        self.get_logger().info('Services are ready!')
        
    def set_robot_goal(self, robot_name, x, y, yaw=0.0):
        """ロボットの目標座標を設定"""
        request = SetGoal.Request()
        request.robot_name = robot_name
        request.x = float(x)
        request.y = float(y)
        request.yaw = float(yaw)
        
        self.get_logger().info(f'Setting goal for {robot_name}: ({x}, {y}, {yaw})')
        
        future = self.set_goal_client.call_async(request)
        rclpy.spin_until_future_complete(self, future)
        
        if future.result() is not None:
            response = future.result()
            if response.success:
                self.get_logger().info(f'✅ Success: {response.message}')
                return True
            else:
                self.get_logger().error(f'❌ Failed: {response.message}')
                return False
        else:
            self.get_logger().error('Service call failed')
            return False
            
    def get_robot_position(self, robot_name):
        """ロボットの位置情報を取得"""
        request = GetPosition.Request()
        request.robot_name = robot_name
        
        self.get_logger().info(f'Getting position for {robot_name}')
        
        future = self.get_position_client.call_async(request)
        rclpy.spin_until_future_complete(self, future)
        
        if future.result() is not None:
            response = future.result()
            if response.success:
                self.get_logger().info(f'✅ Position data for {robot_name}:')
                self.get_logger().info(f'   Position: ({response.x:.3f}, {response.y:.3f}, {response.z:.3f})')
                self.get_logger().info(f'   Orientation: (roll={response.roll:.3f}, pitch={response.pitch:.3f}, yaw={response.yaw:.3f})')
                self.get_logger().info(f'   Velocity: (linear_x={response.linear_x:.3f}, linear_y={response.linear_y:.3f}, angular_z={response.angular_z:.3f})')
                return response
            else:
                self.get_logger().error(f'❌ Failed: {response.message}')
                return None
        else:
            self.get_logger().error('Service call failed')
            return None
            
    def get_all_positions(self):
        """全ロボットの位置情報を取得"""
        robot_names = ['robot_1', 'robot_2', 'robot_3', 'robot_4', 'robot_5']
        
        self.get_logger().info('Getting positions for all robots:')
        print("\n" + "="*80)
        print("🤖 ALL ROBOT POSITIONS")
        print("="*80)
        
        for robot_name in robot_names:
            response = self.get_robot_position(robot_name)
            if response:
                print(f"\n📍 {robot_name.upper()}:")
                print(f"   Position: ({response.x:8.3f}, {response.y:8.3f}, {response.z:8.3f}) m")
                print(f"   Rotation: ({response.roll:6.3f}, {response.pitch:6.3f}, {response.yaw:6.3f}) rad")
                print(f"   Velocity: ({response.linear_x:6.3f}, {response.linear_y:6.3f}, {response.angular_z:6.3f}) m/s,rad/s")
            else:
                print(f"\n❌ {robot_name.upper()}: Failed to get position")
                
        print("="*80)
        
    def interactive_mode(self):
        """インタラクティブモード"""
        self.get_logger().info('Starting interactive mode...')
        
        print("\n" + "="*60)
        print("🤖 ROBOT CONTROL CLIENT APPLICATION")
        print("="*60)
        print("Available commands:")
        print("  1. set <robot_name> <x> <y> [yaw]  - Set robot goal")
        print("  2. get <robot_name>               - Get robot position")
        print("  3. all                            - Get all robot positions")
        print("  4. demo                           - Run demo sequence")
        print("  5. help                           - Show this help")
        print("  6. quit                           - Exit application")
        print("\nAvailable robots: robot_1, robot_2, robot_3, robot_4, robot_5")
        print("="*60)
        
        while True:
            try:
                command = input("\n🔧 Enter command: ").strip().split()
                
                if not command:
                    continue
                    
                if command[0] == 'quit' or command[0] == 'q':
                    print("👋 Goodbye!")
                    break
                    
                elif command[0] == 'help' or command[0] == 'h':
                    print("\nCommands:")
                    print("  set robot_1 5.0 3.0 1.57  - Move robot_1 to (5,3) with yaw=1.57")
                    print("  get robot_2               - Get robot_2 position")
                    print("  all                       - Get all positions")
                    print("  demo                      - Run demo sequence")
                    
                elif command[0] == 'set':
                    if len(command) < 4:
                        print("❌ Usage: set <robot_name> <x> <y> [yaw]")
                        continue
                    
                    robot_name = command[1]
                    try:
                        x = float(command[2])
                        y = float(command[3])
                        yaw = float(command[4]) if len(command) > 4 else 0.0
                        self.set_robot_goal(robot_name, x, y, yaw)
                    except ValueError:
                        print("❌ Invalid coordinates. Use numbers.")
                        
                elif command[0] == 'get':
                    if len(command) < 2:
                        print("❌ Usage: get <robot_name>")
                        continue
                    
                    robot_name = command[1]
                    self.get_robot_position(robot_name)
                    
                elif command[0] == 'all':
                    self.get_all_positions()
                    
                elif command[0] == 'demo':
                    self.run_demo()
                    
                else:
                    print(f"❌ Unknown command: {command[0]}")
                    print("Type 'help' for available commands")
                    
            except KeyboardInterrupt:
                print("\n👋 Goodbye!")
                break
            except Exception as e:
                print(f"❌ Error: {str(e)}")
                
    def run_demo(self):
        """デモシーケンスを実行"""
        print("\n🎬 Running demo sequence...")
        
        # デモシーケンス
        demo_goals = [
            ('robot_1', -5.0, -5.0, 0.0),
            ('robot_2', 5.0, -5.0, 1.57),
            ('robot_3', 5.0, 5.0, 3.14),
            ('robot_4', -5.0, 5.0, -1.57),
            ('robot_5', 0.0, 0.0, 0.0),
        ]
        
        print("Setting goals for all robots...")
        for robot_name, x, y, yaw in demo_goals:
            success = self.set_robot_goal(robot_name, x, y, yaw)
            if not success:
                print(f"❌ Failed to set goal for {robot_name}")
            time.sleep(0.5)  # 少し待機
            
        print("\n⏳ Waiting 3 seconds before checking positions...")
        time.sleep(3)
        
        print("\n📍 Current positions after demo start:")
        self.get_all_positions()


def main(args=None):
    rclpy.init(args=args)
    
    client_app = RobotClientApp()
    
    if len(sys.argv) > 1:
        # コマンドライン引数がある場合
        command = sys.argv[1]
        
        if command == 'demo':
            client_app.run_demo()
        elif command == 'all':
            client_app.get_all_positions()
        elif command == 'set' and len(sys.argv) >= 5:
            robot_name = sys.argv[2]
            x = float(sys.argv[3])
            y = float(sys.argv[4])
            yaw = float(sys.argv[5]) if len(sys.argv) > 5 else 0.0
            client_app.set_robot_goal(robot_name, x, y, yaw)
        elif command == 'get' and len(sys.argv) >= 3:
            robot_name = sys.argv[2]
            client_app.get_robot_position(robot_name)
        else:
            print("Usage:")
            print("  python3 robot_client_app.py demo")
            print("  python3 robot_client_app.py all")
            print("  python3 robot_client_app.py set robot_1 5.0 3.0 [yaw]")
            print("  python3 robot_client_app.py get robot_1")
            print("  python3 robot_client_app.py  (interactive mode)")
    else:
        # インタラクティブモード
        try:
            client_app.interactive_mode()
        except KeyboardInterrupt:
            client_app.get_logger().info('Client app interrupted by user')
    
    client_app.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()

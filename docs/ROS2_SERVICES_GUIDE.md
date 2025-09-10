# ROS2サービス機能ガイド

## 概要

このドキュメントでは、搬送ロボットシステムで新しく追加されたROS2サービス機能について説明します。これらのサービスにより、ロボットの目標座標設定と位置情報取得をプログラマティックに行うことができます。

## 提供されるサービス

### 1. 移動目標座標指定サービス (`SetGoal`)
- **サービス名**: `/set_robot_goal`
- **サービス型**: `transport_robots/srv/SetGoal`
- **機能**: 指定したロボットに目標座標を設定し、移動を開始

### 2. 位置情報取得サービス (`GetPosition`)
- **サービス名**: `/get_robot_position`
- **サービス型**: `transport_robots/srv/GetPosition`
- **機能**: 指定したロボットの現在位置・姿勢・速度情報を取得

## サービス定義

### SetGoal.srv
```
# Request: 目標座標の設定
string robot_name    # ロボット名 (robot_1, robot_2, etc.)
float64 x           # 目標X座標 (m)
float64 y           # 目標Y座標 (m)
float64 yaw         # 目標姿勢角 (rad) - オプション
---
# Response: 設定結果
bool success        # 成功/失敗
string message      # 結果メッセージ
```

### GetPosition.srv
```
# Request: 位置情報の取得
string robot_name    # ロボット名 (robot_1, robot_2, etc.)
---
# Response: 位置情報
bool success        # 成功/失敗
string message      # 結果メッセージ
float64 x          # 現在X座標 (m)
float64 y          # 現在Y座標 (m)
float64 z          # 現在Z座標 (m)
float64 roll       # ロール角 (rad)
float64 pitch      # ピッチ角 (rad)
float64 yaw        # ヨー角 (rad)
float64 linear_x   # 線形速度X (m/s)
float64 linear_y   # 線形速度Y (m/s)
float64 angular_z  # 角速度Z (rad/s)
```

## 使用方法

### 1. サービスサーバーの起動

```bash
# コンテナに入る
docker-compose exec ros2-transport-robots bash

# 環境設定
source /opt/ros/humble/setup.bash
source /workspace/install/setup.bash

# サービスサーバーを起動
python3 /workspace/src/transport_robots/scripts/robot_service_server.py
```

### 2. クライアントアプリケーションの使用

#### インタラクティブモード
```bash
python3 /workspace/src/transport_robots/scripts/robot_client_app.py
```

**利用可能なコマンド**:
- `set robot_1 5.0 3.0 1.57` - robot_1を座標(5,3)、姿勢1.57radに移動
- `get robot_2` - robot_2の位置情報を取得
- `all` - 全ロボットの位置情報を取得
- `demo` - デモシーケンスを実行
- `help` - ヘルプ表示
- `quit` - 終了

#### コマンドライン実行
```bash
# 全ロボットの位置取得
python3 robot_client_app.py all

# 特定ロボットの目標設定
python3 robot_client_app.py set robot_1 5.0 3.0 0.0

# 特定ロボットの位置取得
python3 robot_client_app.py get robot_1

# デモ実行
python3 robot_client_app.py demo
```

### 3. 直接的なサービス呼び出し

#### 目標座標設定
```bash
ros2 service call /set_robot_goal transport_robots/srv/SetGoal \
  "{robot_name: 'robot_1', x: 5.0, y: 3.0, yaw: 0.0}"
```

#### 位置情報取得
```bash
ros2 service call /get_robot_position transport_robots/srv/GetPosition \
  "{robot_name: 'robot_1'}"
```

## 自動テストスクリプト

### 実行方法
```bash
./test_robot_services.sh
```

### テスト内容
1. **パッケージビルド**: 新しいサービス定義を含むビルド
2. **Gazebo起動**: シミュレーション環境の開始
3. **サービスサーバー起動**: ロボット制御サービスの開始
4. **位置情報取得テスト**: 全ロボットの初期位置確認
5. **目標設定テスト**: 複数ロボットへの目標座標設定
6. **移動確認テスト**: 移動後の位置確認
7. **デモシーケンステスト**: 自動デモの実行

## プログラミングインターフェース

### Python API例

```python
import rclpy
from transport_robots.srv import SetGoal, GetPosition

# ノード初期化
rclpy.init()
node = rclpy.create_node('my_robot_controller')

# サービスクライアント作成
set_goal_client = node.create_client(SetGoal, 'set_robot_goal')
get_position_client = node.create_client(GetPosition, 'get_robot_position')

# サービス待機
set_goal_client.wait_for_service()
get_position_client.wait_for_service()

# 目標設定
request = SetGoal.Request()
request.robot_name = 'robot_1'
request.x = 5.0
request.y = 3.0
request.yaw = 1.57

future = set_goal_client.call_async(request)
rclpy.spin_until_future_complete(node, future)

if future.result().success:
    print("Goal set successfully!")

# 位置取得
request = GetPosition.Request()
request.robot_name = 'robot_1'

future = get_position_client.call_async(request)
rclpy.spin_until_future_complete(node, future)

response = future.result()
if response.success:
    print(f"Position: ({response.x}, {response.y})")
    print(f"Orientation: {response.yaw} rad")
```

## 高度な使用例

### 1. 複数ロボットの協調制御

```python
def coordinate_robots():
    """複数ロボットの協調制御例"""
    
    # 全ロボットの現在位置を取得
    positions = {}
    for i in range(1, 6):
        robot_name = f'robot_{i}'
        response = get_robot_position(robot_name)
        if response:
            positions[robot_name] = (response.x, response.y)
    
    # 衝突を避けた目標座標を計算
    goals = calculate_safe_goals(positions)
    
    # 全ロボットに目標を設定
    for robot_name, (x, y) in goals.items():
        set_robot_goal(robot_name, x, y)
```

### 2. 動的経路計画

```python
def dynamic_path_planning(robot_name, final_goal):
    """動的経路計画の例"""
    
    current_pos = get_robot_position(robot_name)
    if not current_pos:
        return False
    
    # 中間ウェイポイントを計算
    waypoints = calculate_waypoints(
        (current_pos.x, current_pos.y), 
        final_goal
    )
    
    # ウェイポイントを順次実行
    for waypoint in waypoints:
        set_robot_goal(robot_name, waypoint[0], waypoint[1])
        
        # 到達まで待機
        while True:
            pos = get_robot_position(robot_name)
            distance = calculate_distance(pos, waypoint)
            if distance < 0.5:  # 50cm以内で到達とみなす
                break
            time.sleep(1)
```

### 3. リアルタイム監視システム

```python
def monitor_robots():
    """ロボット監視システムの例"""
    
    while True:
        print("\n=== Robot Status ===")
        
        for i in range(1, 6):
            robot_name = f'robot_{i}'
            pos = get_robot_position(robot_name)
            
            if pos:
                status = "Moving" if abs(pos.linear_x) > 0.01 else "Stopped"
                print(f"{robot_name}: ({pos.x:.2f}, {pos.y:.2f}) - {status}")
            else:
                print(f"{robot_name}: No data")
        
        time.sleep(2)
```

## トラブルシューティング

### よくある問題と解決方法

#### 1. サービスが見つからない
```bash
# サービス一覧を確認
ros2 service list | grep robot

# サービスサーバーが起動しているか確認
ros2 node list | grep robot_service_server
```

#### 2. サービス呼び出しが失敗する
```bash
# サービスの型を確認
ros2 service type /set_robot_goal

# サービスの詳細を確認
ros2 service info /set_robot_goal
```

#### 3. ロボットが応答しない
```bash
# ロボットのオドメトリデータを確認
ros2 topic echo /robot_1/odom --once

# ロボットの制御トピックを確認
ros2 topic info /robot_1/cmd_vel
```

### デバッグ用コマンド

```bash
# サービスサーバーのログ確認
ros2 run transport_robots robot_service_server.py

# 手動でのサービステスト
ros2 service call /set_robot_goal transport_robots/srv/SetGoal \
  "{robot_name: 'robot_1', x: 0.0, y: 0.0, yaw: 0.0}"

# ノード間の通信確認
ros2 node info /robot_service_server
```

## パフォーマンス考慮事項

### 1. サービス呼び出し頻度
- 推奨: 1秒に1回以下
- 理由: ロボットの物理的な応答時間を考慮

### 2. 同時移動制御
- 推奨: 最大5台まで同時制御可能
- 注意: 衝突回避は各ロボットが個別に実行

### 3. ネットワーク負荷
- 位置情報取得: 軽量（約100バイト/回）
- 目標設定: 軽量（約50バイト/回）

## セキュリティ考慮事項

### 1. 入力検証
- 座標範囲: -10.0m ～ 10.0m（倉庫境界内）
- ロボット名: robot_1 ～ robot_5のみ有効
- 角度範囲: -π ～ π rad

### 2. エラーハンドリング
- 無効なロボット名の拒否
- 範囲外座標の警告
- サービス呼び出し失敗の適切な処理

## 関連ファイル

- **サービス定義**: `src/transport_robots/srv/`
- **サービスサーバー**: `src/transport_robots/scripts/robot_service_server.py`
- **クライアントアプリ**: `src/transport_robots/scripts/robot_client_app.py`
- **テストスクリプト**: `test_robot_services.sh`
- **ビルド設定**: `src/transport_robots/CMakeLists.txt`
- **パッケージ設定**: `src/transport_robots/package.xml`

---

**最終更新**: 2025年9月6日  
**対象ROS2バージョン**: Humble Hawksbill

# 完全セットアップ・実行ガイド

## 概要

このドキュメントでは、Gazeboシミュレータの起動からROS2サービスによるロボット制御まで、システム全体の完全な実行手順を詳しく説明します。

## 🚀 完全実行手順

### ステップ1: 環境準備

#### 1.1 プロジェクトディレクトリへの移動
```bash
cd /home/tatsu/ros2-sys
```


```bash
docker stop ros2-transport-robots && docker rm ros2-transport-robots
docker-compose down
```

#### 1.2 Dockerコンテナの状態確認
```bash
# コンテナの状態を確認
docker-compose ps
```

**期待される出力**:
```
Name                    Command           State   Ports
---------------------------------------------------------------
ros2-transport-robots   /ros_entrypoint.sh bash   Up
```

#### 1.3 コンテナが停止している場合の起動
```bash
# コンテナを起動
docker-compose up -d

# 起動完了まで待機
sleep 5
```

#### 1.4 GUI環境の設定（必要に応じて）
```bash
# X11権限の設定
./setup_gui.sh

# または手動で設定
xhost +local:docker
export DISPLAY=:0
```

### ステップ2: パッケージビルド

#### 2.1 新しいサービス定義を含むビルド
```bash
docker-compose exec ros2-transport-robots bash -c "source /opt/ros/humble/setup.bash && cd /workspace && colcon build --packages-select transport_robots"
```

**期待される出力**:
```
Starting >>> transport_robots
Finished <<< transport_robots [2.34s]

Summary: 1 package finished [2.45s]
```

### ステップ3: Gazeboシミュレーション起動

#### 3.1 ターミナル1: Gazebo起動
```bash
# 新しいターミナルを開く
docker-compose exec ros2-transport-robots bash

# 環境設定
source /opt/ros/humble/setup.bash
source /workspace/install/setup.bash

# Gazeboシミュレーションを起動
ros2 launch transport_robots warehouse_simulation.launch.py
```

**期待される出力**:
```
[INFO] [launch]: All log files can be found below /root/.ros/log/...
[INFO] [gzserver-1]: process started with pid [1234]
[INFO] [gzclient-2]: process started with pid [1235]
[INFO] [spawn_robot_1-4]: Spawn status: SpawnEntity: Successfully spawned entity [robot_1]
[INFO] [spawn_robot_2-6]: Spawn status: SpawnEntity: Successfully spawned entity [robot_2]
...
```

### ステップ4: ロボットノード確認

#### 4.1 ターミナル2: ノード確認
```bash
# 新しいターミナルを開く
docker-compose exec ros2-transport-robots bash
source /opt/ros/humble/setup.bash
source /workspace/install/setup.bash

# ロボットノードの確認
ros2 node list
```

**期待される出力**:
```
/gazebo
/robot_1/differential_drive_controller
/robot_1/gazebo_ros_lidar_controller
/robot_1/robot_1_state_publisher
/robot_2/differential_drive_controller
...
/robot_5/robot_5_state_publisher
```

### ステップ5: サービスサーバー起動

#### 5.1 ターミナル3: サービスサーバー起動
```bash
# 新しいターミナルを開く
docker-compose exec ros2-transport-robots bash
source /opt/ros/humble/setup.bash
source /workspace/install/setup.bash

# サービスサーバーを起動
python3 /workspace/src/transport_robots/scripts/robot_service_server.py
python3 /workspace/src/transport_robots/scripts/robot_service_server_with_avoidance.py
```

**期待される出力**:
```
[INFO] [robot_service_server]: Robot Service Server initialized
[INFO] [robot_service_server]: Available robots: robot_1, robot_2, robot_3, robot_4, robot_5
[INFO] [robot_service_server]: Services:
[INFO] [robot_service_server]:   - /set_robot_goal (SetGoal)
[INFO] [robot_service_server]:   - /get_robot_position (GetPosition)
```

### ステップ6: サービス動作確認

#### 6.1 ターミナル4: サービス確認
```bash
# 新しいターミナルを開く
docker-compose exec ros2-transport-robots bash
source /opt/ros/humble/setup.bash
source /workspace/install/setup.bash

# 利用可能なサービスを確認
ros2 service list | grep robot
```

**期待される出力**:
```
/get_robot_position
/set_robot_goal
```

### ステップ7: 位置情報取得テスト

#### 7.1 全ロボットの初期位置確認
```bash
python3 /workspace/src/transport_robots/scripts/robot_client_app.py all
```

**期待される出力**:
```
🤖 ALL ROBOT POSITIONS
================================================================================

📍 ROBOT_1:
   Position: (  -8.000,   -8.000,    0.100) m
   Rotation: ( -0.000,   -0.000,    0.000) rad
   Velocity: (  0.000,    0.000,    0.000) m/s,rad/s

📍 ROBOT_2:
   Position: (   8.000,   -8.000,    0.100) m
   Rotation: ( -0.000,   -0.000,    1.570) rad
   Velocity: (  0.000,    0.000,    0.000) m/s,rad/s
...
```

### ステップ8: 目標座標設定テスト

#### 8.1 robot_1の移動テスト
```bash
# robot_1に目標座標を設定
python3 /workspace/src/transport_robots/scripts/robot_client_app.py set robot_1 -0.3 -0.3 0.0
```

**期待される出力**:
```
[INFO] [robot_client_app]: Setting goal for robot_1: (-3.0, -3.0, 0.0)
[INFO] [robot_client_app]: ✅ Success: Goal set to (-3.00, -3.00)
```

#### 8.2 Gazeboでの移動確認
- Gazeboウィンドウでrobot_1が目標座標(-3, -3)に向かって移動することを確認

#### 8.3 移動後の位置確認
```bash
# 5秒待機してから位置を確認
sleep 5
python3 /workspace/src/transport_robots/scripts/robot_client_app.py get robot_1
```

**期待される出力**:
```
[INFO] [robot_client_app]: ✅ Position data for robot_1:
[INFO] [robot_client_app]:    Position: (-3.123, -3.045, 0.100)
[INFO] [robot_client_app]:    Orientation: (roll=-0.000, pitch=-0.000, yaw=0.123)
[INFO] [robot_client_app]:    Velocity: (linear_x=0.000, linear_y=0.000, angular_z=0.000)
```

### ステップ9: 複数ロボット制御テスト

#### 9.1 複数ロボットに目標設定
```bash
# robot_2の移動
python3 /workspace/src/transport_robots/scripts/robot_client_app.py set robot_2 3.0 -3.0 1.57

# robot_3の移動
python3 /workspace/src/transport_robots/scripts/robot_client_app.py set robot_3 3.0 3.0 3.14
```

#### 9.2 全ロボットの状態確認
```bash
# 全ロボットの現在位置を確認
python3 /workspace/src/transport_robots/scripts/robot_client_app.py all
```

### ステップ10: インタラクティブ制御

#### 10.1 インタラクティブモードの起動
```bash
python3 /workspace/src/transport_robots/scripts/robot_client_app.py
```

#### 10.2 インタラクティブセッション例
```
🤖 ROBOT CONTROL CLIENT APPLICATION
============================================================
Available commands:
  1. set <robot_name> <x> <y> [yaw]  - Set robot goal
  2. get <robot_name>               - Get robot position
  3. all                            - Get all robot positions
  4. demo                           - Run demo sequence
  5. help                           - Show this help
  6. quit                           - Exit application

Available robots: robot_1, robot_2, robot_3, robot_4, robot_5
============================================================

🔧 Enter command: set robot_4 -5.0 5.0 -1.57
[INFO] [robot_client_app]: ✅ Success: Goal set to (-5.00, 5.00)

🔧 Enter command: get robot_4
[INFO] [robot_client_app]: ✅ Position data for robot_4:
[INFO] [robot_client_app]:    Position: (-6.234, 3.456, 0.100)
[INFO] [robot_client_app]:    Velocity: (0.420, 0.000, -0.850)

🔧 Enter command: all
🤖 ALL ROBOT POSITIONS
================================================================================
📍 ROBOT_1: (-3.001, -2.998, 0.100) m
📍 ROBOT_2: (2.876, -3.123, 0.100) m
📍 ROBOT_3: (3.045, 2.987, 0.100) m
📍 ROBOT_4: (-4.567, 4.234, 0.100) m
📍 ROBOT_5: (0.000, 0.000, 0.100) m
================================================================================

🔧 Enter command: demo
🎬 Running demo sequence...
Setting goals for all robots...
✅ Success: Goal set to (-5.00, -5.00)
✅ Success: Goal set to (5.00, -5.00)
✅ Success: Goal set to (5.00, 5.00)
✅ Success: Goal set to (-5.00, 5.00)
✅ Success: Goal set to (0.00, 0.00)

🔧 Enter command: quit
👋 Goodbye!
```

### ステップ11: 直接的なサービス呼び出し

#### 11.1 ROS2コマンドでの直接呼び出し
```bash
# 目標座標設定
ros2 service call /set_robot_goal transport_robots/srv/SetGoal \
  "{robot_name: 'robot_5', x: 2.0, y: 4.0, yaw: 1.57}"
```

**期待される出力**:
```
requester: making request: transport_robots.srv.SetGoal_Request(robot_name='robot_5', x=2.0, y=4.0, yaw=1.57)

response:
transport_robots.srv.SetGoal_Response(success=True, message='Goal set to (2.00, 4.00)')
```

#### 11.2 位置情報の直接取得
```bash
# 位置情報取得
ros2 service call /get_robot_position transport_robots/srv/GetPosition \
  "{robot_name: 'robot_5'}"
```

**期待される出力**:
```
requester: making request: transport_robots.srv.GetPosition_Request(robot_name='robot_5')

response:
transport_robots.srv.GetPosition_Response(
  success=True, 
  message='Position data retrieved', 
  x=1.234, y=3.567, z=0.1, 
  roll=0.0, pitch=0.0, yaw=1.234, 
  linear_x=0.350, linear_y=0.0, angular_z=0.785
)
```

## 🎯 自動テスト実行

### 全自動テスト
```bash
# 全手順を自動実行
./test_robot_services.sh
```

このスクリプトが以下を自動実行：
1. パッケージビルド
2. Gazebo起動
3. サービスサーバー起動
4. 位置情報取得テスト
5. 目標設定テスト
6. 移動確認テスト
7. デモシーケンステスト

## 🔧 トラブルシューティング

### よくある問題と解決方法

#### 問題1: Gazeboが起動しない
```bash
# 解決策1: コンテナ再起動
docker-compose down
docker-compose up -d

# 解決策2: GUI設定確認
echo $DISPLAY
xhost +local:docker
```

#### 問題2: サービスが見つからない
```bash
# 原因確認: サービスサーバーが起動しているか
ros2 node list | grep robot_service_server

# 解決策: サービスサーバーを再起動
python3 /workspace/src/transport_robots/scripts/robot_service_server.py
```

#### 問題3: ロボットが動かない
```bash
# 原因確認1: オドメトリデータの確認
ros2 topic echo /robot_1/odom --once

# 原因確認2: 制御コマンドの確認
ros2 topic echo /robot_1/cmd_vel

# 解決策: Gazeboを再起動
pkill gazebo
ros2 launch transport_robots warehouse_simulation.launch.py
```

#### 問題4: ビルドエラー
```bash
# 詳細エラーログの確認
docker-compose exec ros2-transport-robots bash -c "
    cd /workspace && 
    colcon build --packages-select transport_robots --event-handlers console_direct+
"

# 依存関係の確認
rosdep update
rosdep install --from-paths src --ignore-src -r -y
```

## 📋 チェックリスト

実行前の確認事項：

- [ ] Dockerが起動している
- [ ] コンテナが起動している (`docker-compose ps`)
- [ ] GUI環境が設定されている (`echo $DISPLAY`)
- [ ] パッケージがビルドされている
- [ ] Gazeboが正常に起動している
- [ ] 5台のロボットがスポーンされている
- [ ] サービスサーバーが起動している
- [ ] サービスが利用可能である (`ros2 service list`)

## 🎮 実用的な使用例

### 例1: 単一ロボットの制御
```bash
# 1. 現在位置を確認
python3 robot_client_app.py get robot_1

# 2. 目標座標を設定
python3 robot_client_app.py set robot_1 5.0 3.0 1.57

# 3. 移動完了まで待機
sleep 10

# 4. 到達確認
python3 robot_client_app.py get robot_1
```

### 例2: 複数ロボットの協調制御
```bash
# 1. 全ロボットの初期位置確認
python3 robot_client_app.py all

# 2. 各ロボットに異なる目標を設定
python3 robot_client_app.py set robot_1 -6.0 -6.0 0.0
python3 robot_client_app.py set robot_2 6.0 -6.0 1.57
python3 robot_client_app.py set robot_3 6.0 6.0 3.14
python3 robot_client_app.py set robot_4 -6.0 6.0 -1.57
python3 robot_client_app.py set robot_5 0.0 0.0 0.0

# 3. 移動状況を監視
while true; do
    python3 robot_client_app.py all
    sleep 3
done
```

### 例3: デモシーケンス実行
```bash
# 事前定義されたデモを実行
python3 robot_client_app.py demo
```

## 🔍 デバッグ・監視

### リアルタイム監視
```bash
# ノードの監視
watch -n 2 'ros2 node list'

# トピックの監視
watch -n 2 'ros2 topic list | grep robot'

# サービスの監視
watch -n 2 'ros2 service list | grep robot'
```

### ログ確認
```bash
# サービスサーバーのログ
ros2 run transport_robots robot_service_server.py

# 特定ロボットのオドメトリ監視
ros2 topic echo /robot_1/odom

# 制御コマンドの監視
ros2 topic echo /robot_1/cmd_vel
```

## 📊 パフォーマンス監視

### システム負荷確認
```bash
# CPU使用率
docker stats ros2-transport-robots

# メモリ使用量
docker exec ros2-transport-robots free -h

# ネットワーク使用量
docker exec ros2-transport-robots netstat -i
```

### ROS2通信監視
```bash
# トピック頻度確認
ros2 topic hz /robot_1/odom

# サービス応答時間確認
time ros2 service call /get_robot_position transport_robots/srv/GetPosition \
  "{robot_name: 'robot_1'}"
```

## 🚨 緊急停止手順

### 全システム停止
```bash
# 1. 全ロボット停止（各ターミナルでCtrl+C）
# 2. コンテナ停止
docker-compose down

# 3. 強制停止（必要に応じて）
docker kill ros2-transport-robots
```

### 個別ロボット停止
```bash
# 特定ロボットの停止
ros2 topic pub /robot_1/cmd_vel geometry_msgs/msg/Twist \
  '{linear: {x: 0.0, y: 0.0, z: 0.0}, angular: {x: 0.0, y: 0.0, z: 0.0}}' --once
```

## 📚 関連ドキュメント

- [ROS2サービス機能ガイド](ROS2_SERVICES_GUIDE.md) - サービスAPI詳細
- [ROS2ノードアーキテクチャ解説](ROS2_NODE_ARCHITECTURE.md) - システム構成
- [障害物回避パラメータ設定ガイド](OBSTACLE_AVOIDANCE_PARAMETERS.md) - 高度な制御

---

**最終更新**: 2025年9月6日  
**対象環境**: Docker + ROS2 Humble + Gazebo 11


ros2 topic pub /robot_2/cmd_vel geometry_msgs/msg/Twist '{linear: {x: 0.0, y: 0.0, z: 0.0}, angular: {x: 0.0, y: 0.0, z: 1.0}}'

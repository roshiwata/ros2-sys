# ROS2 搬送ロボット倉庫シミュレーション

このプロジェクトは、ROS2とGazeboを使用した5台の搬送ロボットによる倉庫シミュレーションシステムです。

## 機能

- **ROS2 Humble**: Robot Operating System 2を使用
- **Docker環境**: 完全にコンテナ化された開発環境
- **Gazeboシミュレーション**: 物理シミュレーションエンジンによるリアルな動作
- **5台の搬送ロボット**: 4輪差動駆動による安定した移動
- **障害物環境**: 倉庫内の棚、柱、壁などの障害物
- **Python制御**: 簡単なPythonコードでロボットの目標座標を指定
- **自動デモ**: 事前定義されたウェイポイントでの自動移動デモ

## システム要件

- Docker
- Docker Compose
- X11サーバー（GUI表示用）
- Linux環境（推奨）

## セットアップ

### 1. リポジトリのクローン

```bash
git clone <repository-url>
cd ros2-sys
```

### 2. GUI環境の設定

```bash
./setup_gui.sh
```

### 3. Dockerコンテナの起動

```bash
docker-compose up -d
```

### 4. ワークスペースのビルド

```bash
docker-compose exec ros2-transport-robots bash -c "source /opt/ros/humble/setup.bash && cd /workspace && colcon build --packages-select transport_robots"
```

## デモの実行

### 基本デモ（障害物付き倉庫環境）

1. **Gazeboシミュレーションの起動**
   ```bash
   docker-compose exec ros2-transport-robots bash -c "source /opt/ros/humble/setup.bash && source /workspace/install/setup.bash && ros2 launch transport_robots simple_demo.launch.py"
   ```

2. **ロボット制御デモの実行**（別ターミナルで）
   ```bash
   docker-compose exec ros2-transport-robots bash -c "source /opt/ros/humble/setup.bash && source /workspace/install/setup.bash && python3 /workspace/src/transport_robots/scripts/warehouse_demo_manager.py"
   ```

### 自動デモスクリプト

全自動でデモを実行する場合：

```bash
./test_warehouse_demo.sh
```

## ロボット制御

### 個別ロボットの制御

各ロボットは独立して制御できます：

```bash
# robot_1を前進させる
ros2 topic pub /robot_1/cmd_vel geometry_msgs/msg/Twist '{linear: {x: 0.5, y: 0.0, z: 0.0}, angular: {x: 0.0, y: 0.0, z: 0.0}}' --once

# robot_2を回転させる
ros2 topic pub /robot_2/cmd_vel geometry_msgs/msg/Twist '{linear: {x: 0.0, y: 0.0, z: 0.0}, angular: {x: 0.0, y: 0.0, z: 1.0}}' --once
```

### Pythonスクリプトでの制御

`src/transport_robots/scripts/robot_controller.py`を参考に、独自の制御スクリプトを作成できます：

```python
from robot_controller import RobotController
import rclpy

rclpy.init()
node = rclpy.create_node('my_controller')
robot = RobotController(node, 'robot_1')

# 目標座標への移動
robot.move_to_goal(5.0, 3.0)
```

## プロジェクト構造

```
ros2-sys/
├── docker-compose.yml          # Docker Compose設定
├── Dockerfile                  # Docker環境定義
├── setup_gui.sh               # GUI環境セットアップスクリプト
├── test_warehouse_demo.sh      # 自動デモスクリプト
├── README.md                   # このファイル
└── src/transport_robots/       # ROS2パッケージ
    ├── launch/                 # Launch files
    │   ├── simple_demo.launch.py
    │   └── warehouse_demo.launch.py
    ├── worlds/                 # Gazebo world files
    │   ├── simple_warehouse.world
    │   └── warehouse_with_obstacles.world
    ├── urdf/                   # ロボットモデル定義
    │   └── transport_robot.urdf.xacro
    ├── scripts/                # Python制御スクリプト
    │   ├── robot_controller.py
    │   ├── warehouse_manager.py
    │   └── warehouse_demo_manager.py
    └── models/                 # 追加モデル
        └── simple_robot.sdf
```

## 技術仕様

### ロボット仕様

- **駆動方式**: 4輪差動駆動
- **サイズ**: 0.8m × 0.6m × 0.2m
- **車輪径**: 0.2m
- **車輪間距離**: 0.6m
- **最大速度**: 0.5 m/s
- **最大角速度**: 1.0 rad/s

### 環境仕様

- **倉庫サイズ**: 30m × 30m
- **障害物**: 棚（15個）、柱（4個）、壁
- **ロボット配置**: 障害物を避けた5箇所の初期位置

### ROS2トピック

各ロボット（robot_1 ～ robot_5）について：

- **制御**: `/robot_X/cmd_vel` (geometry_msgs/Twist)
- **オドメトリ**: `/robot_X/odom` (nav_msgs/Odometry)
- **ロボット状態**: `/robot_X/robot_description` (std_msgs/String)

## トラブルシューティング

### GUI表示の問題

```bash
# X11権限の確認
xhost +local:docker

# DISPLAY環境変数の確認
echo $DISPLAY
```

### Gazeboが起動しない場合

```bash
# コンテナの再起動
docker-compose down
docker-compose up -d

# ログの確認
docker-compose logs ros2-transport-robots
```

### ロボットが動かない場合

```bash
# トピックの確認
ros2 topic list | grep cmd_vel
ros2 topic list | grep odom

# ノードの確認
ros2 node list
```

## カスタマイズ

### 新しいロボットの追加

1. `simple_demo.launch.py`でロボット位置を追加
2. `warehouse_demo_manager.py`でウェイポイントを定義
3. ワークスペースを再ビルド

### 環境の変更

1. `worlds/`ディレクトリに新しい`.world`ファイルを作成
2. Launch fileで新しいワールドファイルを指定
3. 必要に応じてロボットの初期位置を調整

## ライセンス

このプロジェクトはMITライセンスの下で公開されています。

## 貢献

プルリクエストやイシューの報告を歓迎します。

## 開発者向けドキュメント

### アーキテクチャ解説
- [warehouse_demo_manager.py アーキテクチャ解説](docs/warehouse_demo_manager_architecture.md) - 制御スクリプトの詳細な構成とアルゴリズム解説

## 参考資料

- [ROS2 Documentation](https://docs.ros.org/en/humble/)
- [Gazebo Documentation](http://gazebosim.org/documentation)
- [Docker Documentation](https://docs.docker.com/)

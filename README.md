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


### 2. 過去に立ち上げたコンテナを停止＆削除
```bash
docker stop ros2-transport-robots && docker rm ros2-transport-robots
```

### 3. コンテナを新たに起動
```bash
# コンテナを起動
docker-compose up -d
```

### 4. GUI環境の設定

```bash
./setup_gui.sh
```

#### 5. 新しいサービス定義を含むビルド
```bash
docker-compose exec ros2-transport-robots bash -c "source /opt/ros/humble/setup.bash && cd /workspace && colcon build --packages-select transport_robots"
```


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

#### 3.2 リクエストサーバ起動
```bash
# 新しいターミナルを開く
docker-compose exec ros2-transport-robots bash

# 環境設定
source /opt/ros/humble/setup.bash
source /workspace/install/setup.bash

python3 /workspace/src/transport_robots/scripts/robot_service_server_with_avoidance.py
```

#### 3.3 サーバへのリクエスト例
```bash
# 新しいターミナルを開く
docker-compose exec ros2-transport-robots bash

# 環境設定
source /opt/ros/humble/setup.bash
source /workspace/install/setup.bash

# 全ロボットの位置確認
python3 /workspace/src/transport_robots/scripts/robot_client_app.py all
# ロボット１に目標座標を設定
python3 /workspace/src/transport_robots/scripts/robot_client_app.py set robot_1 2.0 2.0 0.0
```


#### その他
- ドキュメントへの追加予定項目
   - フィールドの変更方法（障害物設定など）
   - ロボットの台数追加方法
   - オドメトリ精度向上

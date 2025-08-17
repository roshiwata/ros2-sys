# 障害物回避パラメータ設定ガイド

## 概要

このドキュメントでは、搬送ロボットの障害物回避機能で使用されるパラメータの詳細説明と設定方法について説明します。

## 1. LiDARセンサー設定

### 1.1 ハードウェア設定（URDF）

LiDARセンサーの物理的特性は `src/transport_robots/urdf/transport_robot.urdf.xacro` で定義されています。

```xml
<!-- LiDAR設定パラメータ -->
<gazebo reference="lidar_link">
  <sensor type="ray" name="lidar_sensor">
    <pose>0 0 0 0 0 0</pose>
    <visualize>true</visualize>
    <update_rate>10</update_rate>
    <ray>
      <scan>
        <horizontal>
          <samples>360</samples>
          <resolution>1</resolution>
          <min_angle>-3.14159</min_angle>
          <max_angle>3.14159</max_angle>
        </horizontal>
      </scan>
      <range>
        <min>0.1</min>
        <max>10.0</max>
        <resolution>0.01</resolution>
      </range>
    </ray>
  </sensor>
</gazebo>
```

#### 主要パラメータ：

| パラメータ | 現在値 | 説明 | 推奨範囲 |
|-----------|--------|------|----------|
| `samples` | 360 | 1回転あたりのレーザー測定点数 | 180-720 |
| `update_rate` | 10 | センサー更新頻度（Hz） | 5-30 |
| `min_angle` | -3.14159 | 最小スキャン角度（ラジアン） | -π |
| `max_angle` | 3.14159 | 最大スキャン角度（ラジアン） | π |
| `min` (range) | 0.1 | 最小検出距離（m） | 0.05-0.5 |
| `max` (range) | 10.0 | 最大検出距離（m） | 5.0-30.0 |
| `resolution` (range) | 0.01 | 距離分解能（m） | 0.001-0.1 |

### 1.2 設定変更方法

LiDARセンサーの設定を変更するには：

1. `src/transport_robots/urdf/transport_robot.urdf.xacro` を編集
2. パッケージを再ビルド：
   ```bash
   cd /workspace && colcon build --packages-select transport_robots
   ```
3. シミュレーションを再起動

## 2. 障害物回避アルゴリズム設定

### 2.1 基本パラメータ

`src/transport_robots/scripts/obstacle_avoidance_controller.py` で定義されている主要パラメータ：

```python
class ObstacleAvoidanceController(Node):
    def __init__(self, robot_namespace):
        # 移動速度設定
        self.linear_speed = 0.3      # 直進速度 (m/s)
        self.angular_speed = 0.5     # 回転速度 (rad/s)
        
        # 安全距離設定
        self.safe_distance = 0.8     # 緊急回避距離 (m)
        self.warning_distance = 1.5  # 警告距離 (m)
        
        # 検出範囲設定
        self.front_angle_range = 90  # 前方検出角度範囲 (度)
```

#### パラメータ詳細：

| パラメータ | 現在値 | 説明 | 推奨範囲 | 影響 |
|-----------|--------|------|----------|------|
| `linear_speed` | 0.3 m/s | ロボットの直進速度 | 0.1-1.0 | 高いほど高速移動、低いほど安全 |
| `angular_speed` | 0.5 rad/s | ロボットの回転速度 | 0.2-2.0 | 高いほど素早い回避、低いほど滑らか |
| `safe_distance` | 0.8 m | 緊急停止・回避開始距離 | 0.3-2.0 | 短いほど効率的、長いほど安全 |
| `warning_distance` | 1.5 m | 警告・減速開始距離 | 0.5-3.0 | 早期警告による滑らかな回避 |
| `front_angle_range` | 90° | 前方監視角度範囲 | 60-180 | 広いほど安全、狭いほど効率的 |

### 2.2 回避方向決定アルゴリズム

```python
def find_best_direction(self, laser_data):
    """最適な回避方向を決定"""
    # 左右の自由空間を分析
    left_free_space = self.calculate_free_space(laser_data, 'left')
    right_free_space = self.calculate_free_space(laser_data, 'right')
    
    # より広い自由空間がある方向を選択
    if left_free_space > right_free_space:
        return 'left'
    else:
        return 'right'
```

#### 自由空間計算パラメータ：

| パラメータ | 説明 | 調整可能範囲 |
|-----------|------|-------------|
| `left_sector` | 左側検出セクター（45°-135°） | 30°-150° |
| `right_sector` | 右側検出セクター（225°-315°） | 210°-330° |
| `free_space_threshold` | 自由空間判定閾値 | 1.0-5.0 m |

## 3. パラメータ調整ガイド

### 3.1 環境別推奨設定

#### 狭い倉庫環境：
```python
self.linear_speed = 0.2      # 低速で安全重視
self.angular_speed = 0.3     # ゆっくりとした回転
self.safe_distance = 0.6     # 短い安全距離
self.warning_distance = 1.2  # 早期警告
```

#### 広い倉庫環境：
```python
self.linear_speed = 0.5      # 高速移動
self.angular_speed = 0.8     # 素早い回避
self.safe_distance = 1.0     # 長い安全距離
self.warning_distance = 2.0  # 余裕のある警告距離
```

#### 高密度ロボット環境：
```python
self.linear_speed = 0.25     # 中程度の速度
self.angular_speed = 0.6     # 適度な回転速度
self.safe_distance = 1.0     # 長めの安全距離
self.warning_distance = 1.8  # 早期検出
self.front_angle_range = 120 # 広い監視範囲
```

### 3.2 パラメータ変更手順

1. **ファイル編集**：
   ```bash
   nano src/transport_robots/scripts/obstacle_avoidance_controller.py
   ```

2. **パラメータ変更例**：
   ```python
   # __init__メソッド内で値を変更
   self.linear_speed = 0.4      # 新しい値
   self.safe_distance = 1.0     # 新しい値
   ```

3. **変更の適用**：
   ```bash
   # パッケージ再ビルド
   cd /workspace && colcon build --packages-select transport_robots
   
   # 環境設定の再読み込み
   source /workspace/install/setup.bash
   ```

4. **テスト実行**：
   ```bash
   python3 /workspace/src/transport_robots/scripts/enhanced_warehouse_demo.py
   ```

## 4. 動的パラメータ調整

### 4.1 実行時パラメータ変更

ROSパラメータサーバーを使用した動的調整（将来の拡張）：

```python
# パラメータ宣言
self.declare_parameter('linear_speed', 0.3)
self.declare_parameter('safe_distance', 0.8)

# パラメータ取得
self.linear_speed = self.get_parameter('linear_speed').value
self.safe_distance = self.get_parameter('safe_distance').value
```

### 4.2 コマンドライン設定

```bash
# 起動時にパラメータを指定
ros2 run transport_robots obstacle_avoidance_controller \
  --ros-args -p linear_speed:=0.4 -p safe_distance:=1.0
```

## 5. デバッグとモニタリング

### 5.1 ログレベル設定

```python
# ログレベルの調整
self.get_logger().set_level(rclpy.logging.LoggingSeverity.DEBUG)
```

### 5.2 パフォーマンス監視

重要な監視項目：

- **回避頻度**：`Avoiding obstacle` メッセージの頻度
- **クリアパス率**：`Clear path, resuming navigation` の割合
- **平均移動速度**：目標到達時間の測定
- **衝突回数**：ゼロが理想

### 5.3 トラブルシューティング

#### 問題：ロボットが頻繁に立ち往生する
**解決策**：
- `safe_distance` を短くする（0.6m程度）
- `angular_speed` を上げる（0.8 rad/s程度）
- `front_angle_range` を狭くする（60°程度）

#### 問題：ロボット同士が衝突する
**解決策**：
- `safe_distance` を長くする（1.2m程度）
- `warning_distance` を長くする（2.0m程度）
- `linear_speed` を下げる（0.2m/s程度）

#### 問題：移動が遅すぎる
**解決策**：
- `linear_speed` を上げる（0.5m/s程度）
- `safe_distance` を最適化する（0.7m程度）
- `front_angle_range` を狭くする（75°程度）

## 6. 高度な設定

### 6.1 適応的パラメータ調整

環境に応じた自動調整機能の実装例：

```python
def adaptive_parameter_adjustment(self, laser_data):
    """環境密度に応じてパラメータを動的調整"""
    obstacle_density = self.calculate_obstacle_density(laser_data)
    
    if obstacle_density > 0.7:  # 高密度環境
        self.linear_speed = 0.2
        self.safe_distance = 1.0
    elif obstacle_density < 0.3:  # 低密度環境
        self.linear_speed = 0.4
        self.safe_distance = 0.6
    else:  # 中密度環境
        self.linear_speed = 0.3
        self.safe_distance = 0.8
```

### 6.2 マルチレイヤー回避

複数の回避レイヤーによる高度な制御：

```python
# レイヤー1：緊急回避（0.5m以内）
# レイヤー2：予防回避（0.5-1.0m）
# レイヤー3：計画回避（1.0-1.5m以上）
```

## 7. 設定ファイルテンプレート

### 7.1 保守的設定（安全重視）

```python
# 保守的設定 - 安全性を最優先
CONSERVATIVE_CONFIG = {
    'linear_speed': 0.2,
    'angular_speed': 0.4,
    'safe_distance': 1.2,
    'warning_distance': 2.0,
    'front_angle_range': 120
}
```

### 7.2 効率的設定（速度重視）

```python
# 効率的設定 - 速度を重視
EFFICIENT_CONFIG = {
    'linear_speed': 0.5,
    'angular_speed': 0.8,
    'safe_distance': 0.6,
    'warning_distance': 1.2,
    'front_angle_range': 75
}
```

### 7.3 バランス設定（推奨）

```python
# バランス設定 - 安全性と効率のバランス
BALANCED_CONFIG = {
    'linear_speed': 0.3,
    'angular_speed': 0.5,
    'safe_distance': 0.8,
    'warning_distance': 1.5,
    'front_angle_range': 90
}
```

## 8. 実装例

### 8.1 設定ファイルからの読み込み

```python
import yaml

class ConfigurableObstacleAvoidance(ObstacleAvoidanceController):
    def __init__(self, robot_namespace, config_file=None):
        super().__init__(robot_namespace)
        
        if config_file:
            self.load_config(config_file)
    
    def load_config(self, config_file):
        """設定ファイルからパラメータを読み込み"""
        with open(config_file, 'r') as f:
            config = yaml.safe_load(f)
        
        self.linear_speed = config.get('linear_speed', 0.3)
        self.angular_speed = config.get('angular_speed', 0.5)
        self.safe_distance = config.get('safe_distance', 0.8)
        self.warning_distance = config.get('warning_distance', 1.5)
        self.front_angle_range = config.get('front_angle_range', 90)
```

### 8.2 設定ファイル例（YAML）

```yaml
# config/robot_config.yaml
obstacle_avoidance:
  linear_speed: 0.3
  angular_speed: 0.5
  safe_distance: 0.8
  warning_distance: 1.5
  front_angle_range: 90
  
# 環境別設定
environments:
  warehouse:
    linear_speed: 0.4
    safe_distance: 0.7
  narrow_corridor:
    linear_speed: 0.2
    safe_distance: 1.0
    front_angle_range: 120
```

## 9. パフォーマンス最適化

### 9.1 計算効率の改善

```python
# NumPy配列操作の最適化
def optimized_obstacle_detection(self, laser_data):
    """最適化された障害物検出"""
    ranges = np.array(laser_data.ranges)
    
    # 無効値の処理
    ranges = np.where(np.isinf(ranges), laser_data.range_max, ranges)
    ranges = np.where(np.isnan(ranges), laser_data.range_max, ranges)
    
    # ベクトル化された距離チェック
    front_indices = self.get_front_sector_indices(len(ranges))
    front_ranges = ranges[front_indices]
    
    return np.any(front_ranges < self.safe_distance)
```

### 9.2 メモリ使用量の最適化

```python
# 配列サイズの事前確保
self.range_buffer = np.zeros(360)  # 事前にメモリ確保
self.angle_buffer = np.zeros(360)
```

## 10. 実際の運用での調整例

### 10.1 段階的調整プロセス

1. **初期設定**：デフォルト値で開始
2. **観察期間**：30分間の動作ログを収集
3. **問題特定**：衝突、立ち往生、効率性の問題を特定
4. **パラメータ調整**：1つずつパラメータを変更
5. **効果測定**：変更後の性能を測定
6. **最適化完了**：満足のいく性能が得られるまで繰り返し

### 10.2 調整記録テンプレート

```
日付: 2024/XX/XX
環境: 倉庫シミュレーション
ロボット数: 5台

変更前:
- linear_speed: 0.3
- safe_distance: 0.8

変更後:
- linear_speed: 0.4
- safe_distance: 0.7

結果:
- 平均移動時間: 15%短縮
- 衝突回数: 0回
- 立ち往生回数: 2回減少

次回調整予定: angular_speedを0.6に増加
```

## 11. よくある質問（FAQ）

### Q1: ロボットが壁に近づきすぎる
**A**: `safe_distance` を 1.0m 以上に増加してください。

### Q2: ロボットの動きが遅い
**A**: `linear_speed` を 0.4-0.5m/s に増加し、`safe_distance` を 0.6-0.7m に調整してください。

### Q3: ロボット同士が頻繁に衝突する
**A**: `warning_distance` を 2.0m 以上に設定し、`front_angle_range` を 120° に拡大してください。

### Q4: 回避動作がぎこちない
**A**: `angular_speed` を 0.3-0.4 rad/s に下げて、より滑らかな動作にしてください。

## 12. 参考資料

- ROS2 Navigation Stack: https://navigation.ros.org/
- Gazebo Sensor Plugins: http://gazebosim.org/tutorials?tut=ros_gzplugins
- LiDAR データ処理: https://docs.ros.org/en/humble/p/sensor_msgs/

---

**注意**: パラメータ変更後は必ずテスト環境で動作確認を行ってから本番環境に適用してください。

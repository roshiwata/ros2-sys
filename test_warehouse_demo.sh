#!/bin/bash

echo "=== ROS2 Transport Robots Warehouse Demo ==="
echo "This demo will show 5 transport robots moving in a warehouse with obstacles"
echo ""

# Setup GUI for Docker
echo "Setting up GUI for Docker..."
./setup_gui.sh

# Start Docker containers
echo "Starting Docker containers..."
docker-compose up -d

# Wait for containers to be ready
echo "Waiting for containers to initialize..."
sleep 5

# Build the workspace
echo "Building ROS2 workspace..."
docker-compose exec ros2-transport-robots bash -c "
    source /opt/ros/humble/setup.bash && 
    cd /workspace && 
    colcon build --packages-select transport_robots
"

# Source the workspace
echo "Sourcing workspace..."
docker-compose exec ros2-transport-robots bash -c "
    source /opt/ros/humble/setup.bash && 
    source /workspace/install/setup.bash
"

echo ""
echo "=== Starting Warehouse Demo ==="
echo "1. Launching Gazebo with warehouse environment and 5 robots..."
echo "2. You should see a warehouse with shelves, pillars, and walls as obstacles"
echo "3. 5 transport robots will be spawned at different positions"
echo "4. After a few seconds, robots will start moving in predefined patterns"
echo ""
echo "Press Ctrl+C to stop the demo"
echo ""

# Launch the warehouse demo
docker-compose exec ros2-transport-robots bash -c "
    source /opt/ros/humble/setup.bash && 
    source /workspace/install/setup.bash && 
    ros2 launch transport_robots warehouse_demo.launch.py
" &

# Wait a bit for Gazebo to start
sleep 10

# Start the demo manager in a separate terminal
echo "Starting robot movement demo manager..."
docker-compose exec ros2-transport-robots bash -c "
    source /opt/ros/humble/setup.bash && 
    source /workspace/install/setup.bash && 
    python3 /workspace/src/transport_robots/scripts/warehouse_demo_manager.py
"

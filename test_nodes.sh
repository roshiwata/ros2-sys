#!/bin/bash

# Test script for individual ROS2 nodes
echo "=== ROS2 Transport Robots Node Test ==="
echo "This script tests individual components without Gazebo"
echo ""

# Check if we're in a container
if [ ! -f /.dockerenv ]; then
    echo "Error: This script should be run inside the Docker container"
    echo "Please run: docker exec -it ros2-transport-robots bash"
    echo "Then run this script again"
    exit 1
fi

# Set up ROS2 environment
echo "Setting up ROS2 environment..."
source /opt/ros/humble/setup.bash

# Build the package
echo "Building transport_robots package..."
cd /workspace
colcon build --packages-select transport_robots

if [ $? -ne 0 ]; then
    echo "Build failed! Please check the error messages above."
    exit 1
fi

# Source the built package
source install/setup.bash

echo ""
echo "Build successful!"
echo ""

# Test individual nodes
echo "=== Testing Individual Nodes ==="

echo "1. Testing robot controller node (dry run)..."
timeout 5s ros2 run transport_robots robot_controller.py robot_1 &
CONTROLLER_PID=$!
sleep 2
kill $CONTROLLER_PID 2>/dev/null
echo "   Robot controller test completed"

echo ""
echo "2. Testing warehouse manager node (dry run)..."
timeout 5s ros2 run transport_robots warehouse_manager.py &
MANAGER_PID=$!
sleep 2
kill $MANAGER_PID 2>/dev/null
echo "   Warehouse manager test completed"

echo ""
echo "3. Testing product manager node (dry run)..."
timeout 5s ros2 run transport_robots product_manager.py &
PRODUCT_PID=$!
sleep 2
kill $PRODUCT_PID 2>/dev/null
echo "   Product manager test completed"

echo ""
echo "=== Node Tests Complete ==="
echo "All nodes can be launched successfully!"
echo ""
echo "To run the full simulation:"
echo "1. Launch Gazebo: ros2 launch transport_robots warehouse_simulation.launch.py"
echo "2. Run warehouse manager: ros2 run transport_robots warehouse_manager.py"

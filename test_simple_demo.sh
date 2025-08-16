#!/bin/bash

# Simple ROS2 Transport Robots Test Script
echo "=== Simple ROS2 Transport Robots Test ==="
echo "This script will test basic functionality"
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

# Test basic ROS2 functionality
echo "=== Testing ROS2 Setup ==="
echo "ROS2 version:"
ros2 --version

echo ""
echo "Available packages:"
ros2 pkg list | grep transport_robots

echo ""
echo "Package executables:"
ros2 pkg executables transport_robots

echo ""
echo "=== Testing Launch File ==="
echo "Checking launch file syntax..."
ros2 launch transport_robots warehouse_simulation.launch.py --show-args

echo ""
echo "=== Test Complete ==="
echo "If no errors appeared above, the system is ready!"
echo ""
echo "To run the full demo:"
echo "1. Run: ./test_demo.sh"
echo "2. Or manually: ros2 launch transport_robots warehouse_simulation.launch.py"

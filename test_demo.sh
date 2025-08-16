#!/bin/bash

# ROS2 Transport Robots Demo Script
echo "=== ROS2 Transport Robots Demo ==="
echo "This script will build and run the transport robots demo"
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
echo "=== Demo Instructions ==="
echo "1. First, launch Gazebo simulation:"
echo "   ros2 launch transport_robots warehouse_simulation.launch.py"
echo ""
echo "2. In a new terminal, run the warehouse manager for automatic demo:"
echo "   docker exec -it ros2-transport-robots bash"
echo "   cd /workspace && source install/setup.bash"
echo "   ros2 run transport_robots warehouse_manager.py"
echo ""
echo "3. Or control individual robots:"
echo "   ros2 run transport_robots robot_controller.py robot_1"
echo ""
echo "=== Starting Gazebo Simulation ==="
echo "Press Ctrl+C to stop the simulation"
echo ""

# Launch the simulation
ros2 launch transport_robots warehouse_simulation.launch.py

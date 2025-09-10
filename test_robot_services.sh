#!/bin/bash

# Test script for robot services

echo "🚀 Testing Robot Services..."
echo "This script will test the robot service functionality."
echo ""

# Check if Docker is running
if ! docker info > /dev/null 2>&1; then
    echo "❌ Error: Docker is not running. Please start Docker first."
    exit 1
fi

# Check if the container is running
if ! docker-compose ps | grep -q "ros2-transport-robots.*Up"; then
    echo "⚠️  Warning: ROS2 container is not running. Starting it now..."
    docker-compose up -d
    echo "⏳ Waiting for container to be ready..."
    sleep 5
fi

echo "🔧 Building the package with new services..."
docker-compose exec ros2-transport-robots bash -c "
    source /opt/ros/humble/setup.bash && 
    cd /workspace && 
    colcon build --packages-select transport_robots
"

if [ $? -ne 0 ]; then
    echo "❌ Build failed. Please check the error messages above."
    exit 1
fi

echo "✅ Build completed successfully!"
echo ""

echo "🎯 Starting Gazebo simulation..."
# Start Gazebo in background
docker-compose exec -d ros2-transport-robots bash -c "
    source /opt/ros/humble/setup.bash && 
    source /workspace/install/setup.bash && 
    ros2 launch transport_robots warehouse_simulation.launch.py
"

echo "⏳ Waiting for Gazebo to start..."
sleep 10

echo "🔧 Starting robot service server..."
# Start service server in background
docker-compose exec -d ros2-transport-robots bash -c "
    source /opt/ros/humble/setup.bash && 
    source /workspace/install/setup.bash && 
    python3 /workspace/src/transport_robots/scripts/robot_service_server.py
"

echo "⏳ Waiting for services to be ready..."
sleep 5

echo "🧪 Testing services..."
echo ""

# Test 1: Get all robot positions
echo "📍 Test 1: Getting all robot positions"
docker-compose exec ros2-transport-robots bash -c "
    source /opt/ros/humble/setup.bash && 
    source /workspace/install/setup.bash && 
    python3 /workspace/src/transport_robots/scripts/robot_client_app.py all
"

echo ""
echo "🎯 Test 2: Setting goals for robots"

# Test 2: Set goals
docker-compose exec ros2-transport-robots bash -c "
    source /opt/ros/humble/setup.bash && 
    source /workspace/install/setup.bash && 
    python3 /workspace/src/transport_robots/scripts/robot_client_app.py set robot_1 -3.0 -3.0 0.0
"

sleep 2

docker-compose exec ros2-transport-robots bash -c "
    source /opt/ros/humble/setup.bash && 
    source /workspace/install/setup.bash && 
    python3 /workspace/src/transport_robots/scripts/robot_client_app.py set robot_2 3.0 -3.0 1.57
"

echo ""
echo "⏳ Waiting 5 seconds for robots to move..."
sleep 5

echo "📍 Test 3: Checking positions after movement"
docker-compose exec ros2-transport-robots bash -c "
    source /opt/ros/humble/setup.bash && 
    source /workspace/install/setup.bash && 
    python3 /workspace/src/transport_robots/scripts/robot_client_app.py all
"

echo ""
echo "🎬 Test 4: Running demo sequence"
docker-compose exec ros2-transport-robots bash -c "
    source /opt/ros/humble/setup.bash && 
    source /workspace/install/setup.bash && 
    python3 /workspace/src/transport_robots/scripts/robot_client_app.py demo
"

echo ""
echo "✅ Service tests completed!"
echo ""
echo "💡 To run interactive mode:"
echo "   docker-compose exec ros2-transport-robots bash"
echo "   source /opt/ros/humble/setup.bash && source /workspace/install/setup.bash"
echo "   python3 /workspace/src/transport_robots/scripts/robot_client_app.py"
echo ""
echo "💡 To check available services:"
echo "   ros2 service list | grep robot"
echo ""
echo "💡 To call services directly:"
echo "   ros2 service call /set_robot_goal transport_robots/srv/SetGoal \"{robot_name: 'robot_1', x: 5.0, y: 3.0, yaw: 0.0}\""
echo "   ros2 service call /get_robot_position transport_robots/srv/GetPosition \"{robot_name: 'robot_1'}\""

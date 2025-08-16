#!/usr/bin/env python3

import os
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription, ExecuteProcess
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    # Package directories
    pkg_transport_robots = get_package_share_directory('transport_robots')
    pkg_gazebo_ros = get_package_share_directory('gazebo_ros')
    
    # Launch configuration variables
    use_sim_time = LaunchConfiguration('use_sim_time', default='true')
    world_file = LaunchConfiguration('world_file', default=os.path.join(pkg_transport_robots, 'worlds', 'warehouse.world'))
    
    # Declare launch arguments
    declare_use_sim_time_cmd = DeclareLaunchArgument(
        'use_sim_time',
        default_value='true',
        description='Use simulation (Gazebo) clock if true'
    )
    
    declare_world_cmd = DeclareLaunchArgument(
        'world_file',
        default_value=os.path.join(pkg_transport_robots, 'worlds', 'warehouse.world'),
        description='Full path to world model file to load'
    )
    
    # Start Gazebo server
    start_gazebo_server_cmd = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(os.path.join(pkg_gazebo_ros, 'launch', 'gzserver.launch.py')),
        launch_arguments={'world': world_file}.items()
    )
    
    # Start Gazebo client
    start_gazebo_client_cmd = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(os.path.join(pkg_gazebo_ros, 'launch', 'gzclient.launch.py'))
    )
    
    # Robot positions
    robot_positions = [
        {'name': 'robot_1', 'x': '-8.0', 'y': '-8.0', 'z': '0.1', 'yaw': '0.0'},
        {'name': 'robot_2', 'x': '8.0', 'y': '-8.0', 'z': '0.1', 'yaw': '1.57'},
        {'name': 'robot_3', 'x': '8.0', 'y': '8.0', 'z': '0.1', 'yaw': '3.14'},
        {'name': 'robot_4', 'x': '-8.0', 'y': '8.0', 'z': '0.1', 'yaw': '-1.57'},
        {'name': 'robot_5', 'x': '0.0', 'y': '0.0', 'z': '0.1', 'yaw': '0.0'},
    ]
    
    # URDF file path
    urdf_file = os.path.join(pkg_transport_robots, 'urdf', 'transport_robot.urdf.xacro')
    
    # Create launch description
    ld = LaunchDescription()
    
    # Add launch arguments
    ld.add_action(declare_use_sim_time_cmd)
    ld.add_action(declare_world_cmd)
    
    # Add Gazebo launch
    ld.add_action(start_gazebo_server_cmd)
    ld.add_action(start_gazebo_client_cmd)
    
    # Spawn robots
    for robot in robot_positions:
        robot_name = robot['name']
        
        # Process URDF with xacro
        import subprocess
        robot_description_content = subprocess.check_output([
            'xacro', urdf_file, f'robot_name:={robot_name}'
        ]).decode('utf-8')
        
        # Robot state publisher
        robot_state_publisher = Node(
            package='robot_state_publisher',
            executable='robot_state_publisher',
            name=f'{robot_name}_state_publisher',
            namespace=robot_name,
            output='screen',
            parameters=[{
                'use_sim_time': use_sim_time,
                'robot_description': robot_description_content
            }]
        )
        
        # Spawn robot in Gazebo
        spawn_robot = Node(
            package='gazebo_ros',
            executable='spawn_entity.py',
            name=f'spawn_{robot_name}',
            arguments=[
                '-entity', robot_name,
                '-topic', f'/{robot_name}/robot_description',
                '-x', robot['x'],
                '-y', robot['y'],
                '-z', robot['z'],
                '-Y', robot['yaw']
            ],
            output='screen'
        )
        
        # Joint state publisher
        joint_state_publisher = Node(
            package='joint_state_publisher',
            executable='joint_state_publisher',
            name=f'{robot_name}_joint_state_publisher',
            namespace=robot_name,
            parameters=[{'use_sim_time': use_sim_time}]
        )
        
        ld.add_action(robot_state_publisher)
        ld.add_action(spawn_robot)
        ld.add_action(joint_state_publisher)
    
    return ld

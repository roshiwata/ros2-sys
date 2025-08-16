#!/usr/bin/env python3

import os
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription, ExecuteProcess
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution, Command
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    # Package directories
    pkg_transport_robots = get_package_share_directory('transport_robots')
    pkg_gazebo_ros = get_package_share_directory('gazebo_ros')
    
    # Launch configuration variables
    use_sim_time = LaunchConfiguration('use_sim_time')
    world_file = LaunchConfiguration('world_file')
    gui = LaunchConfiguration('gui')
    
    # Declare launch arguments
    declare_use_sim_time_cmd = DeclareLaunchArgument(
        'use_sim_time',
        default_value='true',
        description='Use simulation (Gazebo) clock if true'
    )
    
    declare_world_cmd = DeclareLaunchArgument(
        'world_file',
        default_value=os.path.join(pkg_transport_robots, 'worlds', 'warehouse_with_obstacles.world'),
        description='Full path to world file to load'
    )
    
    declare_gui_cmd = DeclareLaunchArgument(
        'gui',
        default_value='true',
        description='Set to "false" to run headless.'
    )
    
    # Gazebo launch
    gazebo_cmd = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_gazebo_ros, 'launch', 'gazebo.launch.py')
        ),
        launch_arguments={
            'world': world_file,
            'gui': gui,
            'server': 'true',
            'verbose': 'true'
        }.items()
    )
    
    # Robot spawn positions (avoiding obstacles)
    robot_positions = [
        {'name': 'robot_1', 'x': '-12.0', 'y': '-12.0', 'z': '0.1', 'yaw': '0.0'},
        {'name': 'robot_2', 'x': '-12.0', 'y': '12.0', 'z': '0.1', 'yaw': '0.0'},
        {'name': 'robot_3', 'x': '12.0', 'y': '-12.0', 'z': '0.1', 'yaw': '0.0'},
        {'name': 'robot_4', 'x': '12.0', 'y': '12.0', 'z': '0.1', 'yaw': '0.0'},
        {'name': 'robot_5', 'x': '-6.0', 'y': '12.0', 'z': '0.1', 'yaw': '0.0'},
    ]
    
    # URDF/xacro file path
    urdf_file = os.path.join(pkg_transport_robots, 'urdf', 'transport_robot.urdf.xacro')
    
    # Create spawn commands for each robot
    spawn_commands = []
    for robot in robot_positions:
        spawn_cmd = Node(
            package='gazebo_ros',
            executable='spawn_entity.py',
            arguments=[
                '-entity', robot['name'],
                '-file', urdf_file,
                '-x', robot['x'],
                '-y', robot['y'],
                '-z', robot['z'],
                '-Y', robot['yaw'],
                '-robot_namespace', robot['name']
            ],
            output='screen'
        )
        spawn_commands.append(spawn_cmd)
    
    # Robot state publishers for each robot
    robot_state_publishers = []
    for robot in robot_positions:
        robot_state_publisher = Node(
            package='robot_state_publisher',
            executable='robot_state_publisher',
            name=f'{robot["name"]}_state_publisher',
            namespace=robot['name'],
            parameters=[
                {'use_sim_time': use_sim_time},
                {'robot_description': 
                    Command(['xacro ', urdf_file, ' robot_name:=', robot['name']])
                }
            ],
            output='screen'
        )
        robot_state_publishers.append(robot_state_publisher)
    
    # Create launch description and populate
    ld = LaunchDescription()
    
    # Add launch arguments
    ld.add_action(declare_use_sim_time_cmd)
    ld.add_action(declare_world_cmd)
    ld.add_action(declare_gui_cmd)
    
    # Add Gazebo
    ld.add_action(gazebo_cmd)
    
    # Add robot state publishers
    for rsp in robot_state_publishers:
        ld.add_action(rsp)
    
    # Add spawn commands
    for spawn_cmd in spawn_commands:
        ld.add_action(spawn_cmd)
    
    return ld

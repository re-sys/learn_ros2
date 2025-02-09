import os
import yaml

from ament_index_python.packages import get_package_share_directory
import launch
from launch import LaunchDescription, event_handlers
from launch.actions import IncludeLaunchDescription, DeclareLaunchArgument, GroupAction, TimerAction, RegisterEventHandler, ExecuteProcess
from launch_ros.actions import Node
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution, Command
from launch.conditions import LaunchConfigurationEquals, LaunchConfigurationNotEquals, IfCondition

def generate_launch_description():

    # 获取当前包的目录
    fishbot_navigation2_dir = get_package_share_directory('fishbot_navigation2')
    demo_description_dir = get_package_share_directory('demo_description')
    print(demo_description_dir)
    print(fishbot_navigation2_dir)
    print(os.path.join(demo_description_dir, 'launch', 'gazebo_sim.launch.py'))

    start_nav2_bringup = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(os.path.join(fishbot_navigation2_dir, 'launch', 'navigation2.launch.py')),
        launch_arguments={'use_sim_time': 'true'}.items()
    )
    start_gazebo_sim = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(os.path.join(demo_description_dir, 'launch', 'gazebo_sim.launch.py')),
        launch_arguments={'use_sim_time': 'true'}.items()
    )
    action_start_gazebo_sim = ExecuteProcess(
        cmd='ros2 launch demo_description gazebo_sim.launch.py'.split(),
        output='screen'
    )
    action_start_nav2_bringup = ExecuteProcess(
        cmd='ros2 launch fishbot_navigation2 navigation2.launch.py'.split(),
        output='screen'
    )

    
    
    ld = LaunchDescription()
    ld.add_action(action_start_gazebo_sim)
    ld.add_action(action_start_nav2_bringup)
    
    
    return ld


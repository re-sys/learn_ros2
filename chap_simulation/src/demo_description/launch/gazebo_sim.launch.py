import launch
import launch_ros
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
   #获取默认urdf路径 
    default_xacro_path = os.path.join(get_package_share_directory('demo_description'), 'urdf', 'fishbot/fishbot.urdf.xacro')
    # default_rviz_config_path = os.path.join(get_package_share_directory('demo_description'), 'config', 'display_robot_model.rviz')
    default_gazebo_path = os.path.join(get_package_share_directory('demo_description'), 'world', 'custom_room.world')
   #声明一个Urdf的参数，方便修改
    action_declare_arg_model_path = launch.actions.DeclareLaunchArgument(
        'model',
        default_value=default_xacro_path,
        description='Absolute path to the urdf file'
    )
    #通过文件路径，获取内容，并转换成参数值对象，以供传入 robot_state_publisher 节点

    urdf_content = launch.substitutions.Command(['xacro ',launch.substitutions.LaunchConfiguration('model')])
    # 将urdf_content 作为参数传入 robot_state_publisher 节点
    robot_description_value = launch_ros.parameter_descriptions.ParameterValue(urdf_content, value_type=str)

    action_robot_state_publisher = launch_ros.actions.Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        parameters=[{'robot_description': robot_description_value}]
    )
    # action_joint_state_publisher = launch_ros.actions.Node(
    #     package='joint_state_publisher',
    #     executable='joint_state_publisher',
    # )
    # action_rviz_node = launch_ros.actions.Node(
    #     package='rviz2',
    #     executable='rviz2',
    #     name='rviz2',         
    #     arguments=['-d', default_rviz_config_path]
    # )
    action_launch_gazebo = launch.actions.IncludeLaunchDescription(
        launch_description_source=launch.launch_description_sources.PythonLaunchDescriptionSource(
            os.path.join(get_package_share_directory('gazebo_ros'), 'launch', 'gazebo.launch.py')
        ),
        launch_arguments=[('world', default_gazebo_path),('verbose', 'true')]
    )
    action_spawn_entity = launch_ros.actions.Node(
        package='gazebo_ros',
        executable='spawn_entity.py',
        name='spawn_entity',
        arguments=['-entity', 'fishbot', '-topic', '/robot_description']
    )
    return launch.LaunchDescription([
        action_declare_arg_model_path,
        action_robot_state_publisher,
        # action_joint_state_publisher,
        # action_rviz_node,
        action_launch_gazebo,
        action_spawn_entity
    ])
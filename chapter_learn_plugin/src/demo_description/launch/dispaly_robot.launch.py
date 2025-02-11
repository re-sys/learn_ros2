import launch
import launch_ros
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
   #获取默认urdf路径 
    urdf_path = os.path.join(get_package_share_directory('demo_description'), 'urdf', 'first_robot.urdf')
    default_rviz_config_path = os.path.join(get_package_share_directory('demo_description'), 'config', 'display_robot_model.rviz')
   #声明一个Urdf的参数，方便修改
    action_declare_arg_model_path = launch.actions.DeclareLaunchArgument(
        'urdf_path',
        default_value=urdf_path,
        description='Absolute path to the urdf file'
    )
    #通过文件路径，获取内容，并转换成参数值对象，以供传入 robot_state_publisher 节点

    urdf_content = launch.substitutions.Command(['xacro ',launch.substitutions.LaunchConfiguration('urdf_path')])
    # 将urdf_content 作为参数传入 robot_state_publisher 节点
    robot_description_value = launch_ros.parameter_descriptions.ParameterValue(urdf_content, value_type=str)

    action_robot_state_publisher = launch_ros.actions.Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        parameters=[{'robot_description': robot_description_value}]
    )
    action_joint_state_publisher = launch_ros.actions.Node(
        package='joint_state_publisher',
        executable='joint_state_publisher',
    )
    action_rviz_node = launch_ros.actions.Node(
        package='rviz2',
        executable='rviz2',
        name='rviz2',         
        arguments=['-d', default_rviz_config_path]
    )
    return launch.LaunchDescription([
        action_declare_arg_model_path,
        action_robot_state_publisher,
        action_joint_state_publisher,
        action_rviz_node
    ])
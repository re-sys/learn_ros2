import launch
import launch_ros

def generate_launch_description():
    #1.声明launch参数
    action_declare_arg_k = launch.actions.DeclareLaunchArgument(
        "k",
        default_value="1.0",
        description="The k parameter for the turtle control"
    )
    action_declare_arg_background_g = launch.actions.DeclareLaunchArgument(
        "background_g",
        default_value="150",
        description="The background color for the turtlesim"
    )
    #2.把launch参数传递给某个节点
    
    action_node_turtlesim_node = launch_ros.actions.Node(
        package="turtlesim",
        executable="turtlesim_node",
        parameters=[{
            "background_g": launch.substitutions.LaunchConfiguration("background_g",default="150")
        }],
        output="screen",
       
    )
    action_node_patrol_client = launch_ros.actions.Node(
        package="demo_cpp_service",
        executable="patrol_client",
        output="log"
    )
    action_node_patrol_server = launch_ros.actions.Node(
        package="demo_cpp_service",
        executable="turtle_control",
        output="log"
    )   
    return launch.LaunchDescription([
        action_node_turtlesim_node,
        action_node_patrol_client,
        action_node_patrol_server
    ])
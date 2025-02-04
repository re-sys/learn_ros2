import launch
import launch_ros
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    launch.actions.DeclareLaunchArgument(
        "start_rqt",
        default_value="false",
        description="Whether to start rqt"
    )
    action_node_start_rqt = launch.actions.ExecuteProcess(
        condition=launch.conditions.IfCondition(launch.substitutions.LaunchConfiguration("start_rqt")),
        cmd=["rqt"],
    )
    #1.启动其他launch文件
    demo_launch_dir = get_package_share_directory("turtlesim")
    demo_launch_file = os.path.join(demo_launch_dir,"launch","multisim.launch.py")
    demo_launch = launch.actions.IncludeLaunchDescription(
        launch_description_source=demo_launch_file
    )
    #2.打印数据
    action_node_print_data = launch.actions.LogInfo(msg=str(demo_launch_file))

    #3.执行进程，命令行ros2 topic list
    action_node_execute_process = launch.actions.ExecuteProcess(
        cmd=["rqt"],
        # output="log"
    )

    #4.组织动作成组
    action_group = launch.actions.GroupAction([
        #5.定时器
        launch.actions.TimerAction(
            period=2.0,
            actions=[demo_launch]
        ),
        
        launch.actions.TimerAction(
            period=4.0,
            actions=[action_node_start_rqt]
        )
    ])

    return launch.LaunchDescription([
        action_node_print_data,
        action_group
    ])
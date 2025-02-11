import rclpy
from rclpy.node import Node
from geometry_msgs.msg import PoseStamped
from nav2_simple_commander.robot_navigator import BasicNavigator

def main():
    rclpy.init()
    nav = BasicNavigator()
    nav.waitUntilNav2Active()

    goal_poses = []
    goal_pose = PoseStamped()
    goal_pose.header.frame_id = 'map'
    goal_pose.header.stamp = nav.get_clock().now().to_msg()
    goal_pose.pose.position.x = 2.0
    goal_pose.pose.position.y = 0.0
    goal_pose.pose.orientation.w = 1.0
    goal_poses.append(goal_pose)
    goal_pose = PoseStamped()
    goal_pose.header.frame_id = 'map'
    goal_pose.header.stamp = nav.get_clock().now().to_msg()
    goal_pose.pose.position.x = 0.0
    goal_pose.pose.position.y = 1.0
    goal_pose.pose.orientation.w = 1.0
    goal_poses.append(goal_pose)
    goal_pose = PoseStamped()
    goal_pose.header.frame_id = 'map'
    goal_pose.header.stamp = nav.get_clock().now().to_msg()
    goal_pose.pose.position.x = 0.0
    goal_pose.pose.position.y = 3.0
    goal_pose.pose.orientation.w = 1.0
    goal_poses.append(goal_pose)
    nav.followWaypoints(goal_poses)
    while not nav.isTaskComplete():
        feedback = nav.getFeedback()
        nav.get_logger().info(f'目标点{feedback.current_waypoint}')
        # nav.cancelTask()
    result = nav.getResult()
    nav.get_logger().info(f'导航结果: {result}')


    # rclpy.spin(nav)
    # rclpy.shutdown()


#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from nav2_simple_commander.robot_navigator import BasicNavigator
from geometry_msgs.msg import PoseStamped
from std_srvs.srv import Trigger
import yaml
import os
from ament_index_python.packages import get_package_share_directory
import math
from tf_transformations import quaternion_from_euler
import time
class PatrolNode(Node):
    def __init__(self):
        super().__init__('patrol_node')
        
        # 创建导航器
        self.navigator = BasicNavigator()
        
        # 等待导航器准备就绪
        self.navigator.waitUntilNav2Active()
        
        # 创建图像触发服务客户端
        self.trigger_client = self.create_client(Trigger, 'trigger_image')
        while not self.trigger_client.wait_for_service(timeout_sec=1.0):
            self.get_logger().info('等待图像服务可用...')
        print('图像服务可用')
        
        # 读取配置文件
        config_path = os.path.join(
            get_package_share_directory('auto_patrol'),
            'config',
            'waypoints.yaml'
        )
        print(config_path)
        with open(config_path, 'r') as f:
            self.waypoints = yaml.safe_load(f)['waypoints']
        print(self.waypoints)
        self.current_waypoint = 0
        # self.create_timer(1.0, self.patrol_callback)
        while rclpy.ok():
            self.patrol_callback()
            time.sleep(1.0)
        
    def trigger_image_save(self):
        request = Trigger.Request()
        print('触发图像保存')
        future = self.trigger_client.call_async(request)
        rclpy.spin_until_future_complete(self, future)
        response = future.result()
        print('触发图像保存完成')
        print(future.result())
       
        
    def patrol_callback(self):
        # 如果导航还未完成，直接返回
        if not self.navigator.isTaskComplete():
            print('导航未完成')
            return
            
        # 如果导航完成，先触发图像保存
        self.trigger_image_save()
        print('触发图像保存完成')
        
        # 获取下一个导航点
        waypoint = self.waypoints[self.current_waypoint]
        
        # 创建目标姿态
        goal_pose = PoseStamped()
        goal_pose.header.frame_id = 'map'
        goal_pose.header.stamp = self.get_clock().now().to_msg()
        goal_pose.pose.position.x = waypoint['x']
        goal_pose.pose.position.y = waypoint['y']
        
        # 使用tf_transformations来处理方向
        q = quaternion_from_euler(0, 0, waypoint['yaw'])
        goal_pose.pose.orientation.x = q[0]
        goal_pose.pose.orientation.y = q[1]
        goal_pose.pose.orientation.z = q[2]
        goal_pose.pose.orientation.w = q[3]
        
        # 发送导航目标
        self.navigator.goToPose(goal_pose)
        
        self.get_logger().info(f'导航至点 {self.current_waypoint + 1}/{len(self.waypoints)}')
        
        # 更新下一个导航点索引
        self.current_waypoint = (self.current_waypoint + 1) % len(self.waypoints)

def main():
    rclpy.init()
    node = PatrolNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main() 
#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from std_srvs.srv import Trigger
from cv_bridge import CvBridge
import cv2
import os
from datetime import datetime

class ImageSafeNode(Node):
    def __init__(self):
        super().__init__('image_safe_node')
        
        # 创建图像订阅器
        self.subscription = self.create_subscription(
            Image,
            '/camera_sensor/image_raw',
            self.image_callback,
            10
        )
        
        # 创建服务
        self.srv = self.create_service(
            Trigger,
            'trigger_image',
            self.trigger_callback
        )
        
        self.bridge = CvBridge()
        self.latest_image = None
        
        # 创建保存图像的目录
        self.save_dir = os.path.join(os.getcwd(), 'saved_images')
        os.makedirs(self.save_dir, exist_ok=True)
        
        self.get_logger().info('图像存储节点已启动')
        
    def image_callback(self, msg):
        """保存最新的图像消息"""
        self.latest_image = msg
        
    def trigger_callback(self, request, response):
        """处理触发保存图像的服务请求"""
        if self.latest_image is None:
            response.success = False
            response.message = "没有可用的图像"
            self.get_logger().error(response.message)
            return response
            
        try:
            # 将ROS图像消息转换为OpenCV格式
            cv_image = self.bridge.imgmsg_to_cv2(self.latest_image, "bgr8")
            
            # 生成文件名（使用时间戳）
            timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
            filename = os.path.join(self.save_dir, f'image_{timestamp}.jpg')
            
            # 保存图像
            cv2.imwrite(filename, cv_image)
            
            response.success = True
            response.message = f'成功保存图像到 {filename}'
            self.get_logger().info(response.message)
            return response
            
        except Exception as e:
            response.success = False
            response.message = f'保存图像时出错: {str(e)}'
            self.get_logger().error(response.message)
            
        return response

def main():
    rclpy.init()
    node = ImageSafeNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main() 
import cv2
from cv_bridge import CvBridge
import rclpy
from rclpy.node import Node
from interfaces.srv import FaceDetector
from ament_index_python.packages import get_package_share_directory
import os
import time
import face_recognition

class FaceDetectClient(Node):

    def __init__(self):
        super().__init__('face_detect_client')
        self.bridge = CvBridge()
        self.default_image_path = os.path.join(get_package_share_directory('demo_python_pkg'), 'resource', 'default.jpg')
        self.get_logger().info('节点初始化完毕')
        self.cli = self.create_client(FaceDetector, 'face_detect')
        self.image = cv2.imread(self.default_image_path)
        


    def send_request(self):
        while self.cli.wait_for_service(timeout_sec=1.0) is False:
            self.get_logger().info('服务未就绪, 重试...')
        # 2.构造Request
        request = FaceDetector.Request()
        request.image = self.bridge.cv2_to_imgmsg(self.image)
        # 3.发送请求等待处理
        future = self.client.call_async(request)# 异步调用服务，立刻返回future对象，等待服务端处理完成才会把结果放在future对象中
        # while future.done() is False:
        #     time.sleep(1.0)#休眠当前线程，等待服务完成,造成当前线程无法接收来自服务端的返回，futuredone 没有返回True
        rclpy.spin_until_future_complete(self, future)#等待服务端返回响应
        
        response = future.result()# 获取服务端返回的结果
        self.get_logger().info('接收到响应，共有%d个人脸'%len(response.number))
        self.show_response(response)
    def show_response(self, response):
        for i in range(response.number):
            top = response.top[i]
            bottom = response.bottom[i]
            left = response.left[i]
            right = response.right[i]
            cv2.rectangle(self.image, (left, top), (right, bottom), (0, 255, 0), 2)
            cv2.putText(self.image, 'face', (left, top - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)
        cv2.imshow('image', self.image)
        cv2.waitKey(0)#会导致阻塞线程，导致spin无法正常使用
        cv2.destroyAllWindows()

def main(args=None):
    rclpy.init(args=args)
    face_detect_client = FaceDetectClient()
    face_detect_client.send_request()
    rclpy.spin(face_detect_client)
    face_detect_client.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
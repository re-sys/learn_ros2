import cv2
from cv_bridge import CvBridge
import rclpy
from rclpy.node import Node
from rcl_interfaces.msg import SetParametersResult
from interfaces.srv import FaceDetector
from ament_index_python.packages import get_package_share_directory
import os
import time
import face_recognition

class FaceDetectNode(Node):
    def __init__(self):
        super().__init__('face_detect_node')
        
        self.bridge = CvBridge()
        self.declare_parameter('number_of_times_to_upsample', 1)    
        self.declare_parameter('model', 'hog')
        self.number_of_times_to_upsample = self.get_parameter('number_of_times_to_upsample').value
        self.model = self.get_parameter('model').value
        self.default_image_path = os.path.join(get_package_share_directory('demo_python_pkg'), 'resource', 'default.jpg')
        self.get_logger().info('人脸检测节点初始化完成')
        self.srv = self.create_service(FaceDetector, 'face_detect', self.face_detect_callback)
        self.add_on_set_parameters_callback(self.parameters_callback)
        
    def parameters_callback(self, parameters):
        for parameter in parameters:
            self.get_logger().info('参数名：{}，参数值：{}'.format(parameter.name, parameter.value))
            if parameter.name == 'number_of_times_to_upsample':
                self.number_of_times_to_upsample = parameter.value
            elif parameter.name == 'model':
                self.model = parameter.value
        return SetParametersResult(successful=True)
    
    def face_detect_callback(self, request, response):
        if request.image.data:
            cv_image = self.bridge.imgmsg_to_cv2(request.image)
        else:
            cv_image = cv2.imread(self.default_image_path)
            self.get_logger().info('No image data received, using default image')
        start_time = time.time()
        self.get_logger().info('Detecting faces in the image')
        face_locations = face_recognition.face_locations(cv_image,number_of_times_to_upsample=self.number_of_times_to_upsample,model=self.model)
        response.used_time = time.time() - start_time
        response.number = len(face_locations)
        for (top, right, bottom, left) in face_locations:
            response.top.append(top)
            response.right.append(right)
            response.bottom.append(bottom)
            response.left.append(left)
        self.get_logger().info('完成人脸检测，检测到{}个人脸'.format(response.number))
            #cv_image是cv格式的图像
        return response #必须返回response，否则会报错



def main():
    rclpy.init()
    node = FaceDetectNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()
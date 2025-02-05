import rclpy
from rclpy.node import Node
from tf2_ros import StaticTransformBroadcaster # 静态坐标变换广播器
from geometry_msgs.msg import TransformStamped # 坐标变换消息
from tf_transformations import quaternion_from_euler # 欧拉角转换为四元数
import math # 角度转弧度

class StaticTFBroadcaster(Node):
    def __init__(self):
        super().__init__('static_tf_broadcaster')
        # 创建静态坐标变换广播器
        self.broadcaster = StaticTransformBroadcaster(self)
        self.publish_static_tf()

    def publish_static_tf(self):
        '''
        发布静态坐标变换
        从base_link 到camera_link 的坐标变换
        '''
        # 创建坐标变换消息
        tfs = TransformStamped()
        # 设置坐标变换消息的参考坐标系
        tfs.header.stamp = self.get_clock().now().to_msg()
        tfs.header.frame_id = 'base_link'
        # 设置坐标变换消息的目标坐标系
        tfs.child_frame_id = 'camera_link'
        # 设置坐标变换消息的位置
        tfs.transform.translation.x = 0.5
        tfs.transform.translation.y = 0.3
        tfs.transform.translation.z = 0.6
        # 欧拉角转换为四元数
        quaternion = quaternion_from_euler(math.radians(180), 0, 0) 
        # 旋转部分赋值
        tfs.transform.rotation.x = quaternion[0]
        tfs.transform.rotation.y = quaternion[1]
        tfs.transform.rotation.z = quaternion[2]
        tfs.transform.rotation.w = quaternion[3]
        # 发布坐标变换消息
        self.broadcaster.sendTransform(tfs)
        self.get_logger().info(f'Static TF broadcasted: {tfs}')

def main(args=None):
    rclpy.init(args=args)
    static_tf_broadcaster = StaticTFBroadcaster()
    rclpy.spin(static_tf_broadcaster)
    static_tf_broadcaster.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
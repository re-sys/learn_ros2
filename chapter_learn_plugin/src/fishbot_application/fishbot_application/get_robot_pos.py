import rclpy
from rclpy.node import Node
from geometry_msgs.msg import TransformStamped # 坐标变换消息
from tf2_ros import TransformListener # 坐标变换监听器
from tf2_ros import Buffer # 坐标变换缓存
import math # 角度转弧度
from tf_transformations import euler_from_quaternion # 四元数转换为欧拉角

class DynamicTFBroadcaster(Node):
    def __init__(self):
        super().__init__('dynamic_tf_broadcaster')
        # 创建坐标变换缓存
        self.buffer = Buffer()
        # 创建坐标变换监听器
        self.listener = TransformListener(self.buffer, self)
        self.timer = self.create_timer(1.0, self.get_transform)

    def get_transform(self):
        '''
        获取坐标变换
        '''
        try:
            # 获取坐标变换
            tfs = self.buffer.lookup_transform('map', 'base_link', rclpy.time.Time(seconds=0.0), rclpy.time.Duration(seconds=1.0))
            transform = tfs.transform
            self.get_logger().info(f'平移: {transform.translation}')
            self.get_logger().info(f'旋转: {transform.rotation}')
            # 四元数转换为欧拉角
            euler = euler_from_quaternion([
                transform.rotation.x, 
                transform.rotation.y, 
                transform.rotation.z, 
                transform.rotation.w
            ])
            self.get_logger().info(f'欧拉角: {euler}')
        except Exception as e:
            self.get_logger().error(f'Error: {e}')

def main(args=None):
    rclpy.init(args=args)
    dynamic_tf_broadcaster = DynamicTFBroadcaster()
    rclpy.spin(dynamic_tf_broadcaster)
    dynamic_tf_broadcaster.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
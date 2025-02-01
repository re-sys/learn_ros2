import rclpy
from status_interfaces.msg import SystemStatus
from rclpy.node import Node
import psutil
import platform

class SystemStatusPublisher(Node):

    def __init__(self):
        super().__init__('system_status_publisher')
        self.publisher_ = self.create_publisher(SystemStatus, 'system_status', 10)
        self.timer_ = self.create_timer(1.0, self.timer_callback)
    
    def timer_callback(self):
        """
        builtin_interfaces/Time time # recored the time when the status is updated
        string hostname # the hostname of the system
        float32 cpu_usage # the percentage of CPU usage
        float32 memory_usage # the percentage of memory usage
        float32 memory_total # the total memory of the system
        float32 memory_available # the available memory of the system
        float64 net_sent # the amount of data sent through the network
        float64 net_recv # the amount of data received through the network
        """
        cpu_percent = psutil.cpu_percent()
        memory_info = psutil.virtual_memory()
        net_io_counters = psutil.net_io_counters()

        msg = SystemStatus()
        msg.time = self.get_clock().now().to_msg()
        msg.hostname = platform.node()
        msg.cpu_usage = cpu_percent
        msg.memory_usage = memory_info.percent
        msg.memory_total = memory_info.total/1024**2
        msg.memory_available = memory_info.available/1024**2
        msg.net_sent = net_io_counters.bytes_sent / 1024**2
        msg.net_recv = net_io_counters.bytes_recv / 1024**2

        self.publisher_.publish(msg)
        self.get_logger().info('System status published: %s' % msg)

def main(args=None):
    rclpy.init(args=args)
    node = SystemStatusPublisher()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()    

if __name__ == '__main__':
    main()
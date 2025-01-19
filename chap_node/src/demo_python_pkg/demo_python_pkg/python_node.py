# This is a simple Python node that publishes a message to the topic "chatter" every 5 seconds.

import rclpy
from rclpy.node import Node
from std_msgs.msg import String

class PythonNode(Node):

    def __init__(self):
        super().__init__('python_node')
        self.publisher_ = self.create_publisher(String, 'chatter', 10)
        timer_period = 5.0  # seconds
        self.timer = self.create_timer(timer_period, self.timer_callback)
        self.i = 0

    def timer_callback(self):
        msg = String()
        msg.data = 'Hello World: %d' % self.i
        self.publisher_.publish(msg)
        self.get_logger().info('Publishing: "%s"' % msg.data)
        self.i += 1

def main(args=None):
    rclpy.init(args=args)
    node = PythonNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
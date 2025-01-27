# This is the subscriber node for the "novel" topic

import rclpy
from rclpy.node import Node
from std_msgs.msg import String
import threading
import espeak
# This is the subscriber node for the "novel" topic using threading

class NovelSubscriber(Node):

    def __init__(self):
        super().__init__('novel_subscriber')
        self.subscription = self.create_subscription(String, 'novel', self.listener_callback, 10)
        self.subscription  # prevent unused variable warning
        self.speech_thread = threading.Thread(target=self.spin)
        self.speech_thread.start()
    def listener_callback(self, msg):
        self.get_logger().info('Received novel: "%s"' % msg.data)
    def spin(self):
        speaker = espeak.Speaker()
        speaker.say("I have received a new novel!")
        while rclpy.ok():
            sleep(1)
            

def main(args=None):
    rclpy.init(args=args)

    novel_subscriber = NovelSubscriber()

    rclpy.spin(novel_subscriber)

    # Destroy the node explicitly
    # (optional - otherwise it will be done automatically
    # when the garbage collector destroys the node object)
    novel_subscriber.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
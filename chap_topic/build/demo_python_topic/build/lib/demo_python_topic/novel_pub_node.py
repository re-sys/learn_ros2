# This is the publisher node for the novel_topic download by requests library.

import rclpy
from rclpy.node import Node
from std_msgs.msg import String
import requests
from queue import Queue

class NovelPublisher(Node):

    def __init__(self,url):
        super().__init__('novel_publisher')
        self.publisher_ = self.create_publisher(String, 'novel_topic', 10)
        timer_period = 1 # seconds
        self.text_queue = Queue(maxsize=10)
        self.timer = self.create_timer(timer_period, self.timer_callback)
        
        self.url = url
        self.download_novel()
        

    def timer_callback(self):
        msg = String()
        if not self.text_queue.empty():
            text = self.text_queue.get()
            msg.data = text
            self.publisher_.publish(msg)
            self.get_logger().info('Publishing: "%s"' % msg.data)
        
    
    def download_novel(self):
        response = requests.get(self.url)
        response.encoding = 'utf-8'
        text = response.text
        for line in text.splitlines():
            self.text_queue.put(line)
        self.get_logger().info('Downloaded novel')

def main(args=None):

    rclpy.init(args=args)
    node = NovelPublisher('http://0.0.0.0:8080/novel1.txt')
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
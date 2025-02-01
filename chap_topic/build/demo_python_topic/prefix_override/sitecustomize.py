import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/wufy/learn_ros2/learn_ros2/chap_topic/install/demo_python_topic'

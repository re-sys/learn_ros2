import rclpy
from rclpy.node import Node
class PersonNode(Node):
    def __init__(self,name_val:str,age_val:int,node_name:str='person_node')->None:
        super().__init__(node_name)
        self.name = name_val
        self.age = age_val

    def eat(self,food_name:str):
        """
        This is a function that allows a person to eat a certain food.
        """
        print(f"{self.name} is eating {food_name}.")
        node.get_logger().info(f"{self.name} is eating {food_name}.")

def main():
    rclpy.init()
    node = PersonNode("John",25)
    node.eat("apple")
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()
    

if __name__ == '__main__':
    main()
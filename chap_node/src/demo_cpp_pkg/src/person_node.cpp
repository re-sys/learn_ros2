#include "rclcpp/rclcpp.hpp"

class PersonNode : public rclcpp::Node
{
private:
    std::string name_;
    int age_;
public:
    PersonNode(const std::string& node_name, const std::string name, int age) : Node(node_name), name_(name), age_(age)
    {
        
        RCLCPP_INFO(this->get_logger(), "Hello, ROS2!");
    }

    void eat(const std::string& foodname )
    {
        RCLCPP_INFO(this->get_logger(), "I am eating %s,my name is %s, and I am %d years old.", foodname.c_str(), name_.c_str(), age_);
    }
};
int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<PersonNode>("person_node", "wufy", 25);
    node->eat("apple");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
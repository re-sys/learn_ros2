// This is a simple C++ node that publishes a message to the topic "chatter"

#include <rclcpp/rclcpp.hpp>
// #include <std_msgs/msg/string.hpp>

class CppNode : public rclcpp::Node
{
public:
    CppNode() : Node("cpp_node")
    {
        // publisher_ = this->create_publisher<std_msgs::msg::String>("chatter", 10);
        // timer_ = this->create_timer(std::chrono::seconds(1), std::bind(&CppNode::publishMessage, this));
        // rosinfo("Hello, world!");
        RCLCPP_INFO(this->get_logger(), "Hello, world!");
    }

    void publishMessage()
    {
        // auto message = std_msgs::msg::String();
        // message.data = "Hello, world!";
        // RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
        // publisher_->publish(message);
    }

private:
    rclcpp::TimerBase::SharedPtr timer_;
    // rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<CppNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
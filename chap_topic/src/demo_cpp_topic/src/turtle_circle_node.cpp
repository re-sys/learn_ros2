// This code  makes tutle1 move in a circle with timer

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
// #include <turtlesim/msg/pose.hpp>
#include <chrono>

using namespace std::chrono_literals;

class TurtleCircle : public rclcpp::Node
{
public:
  TurtleCircle() : Node("turtle_circle")
  {
    // Create a publisher to control the turtle's movement
    turtle_publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", 10);
    turtle_timer = this->create_wall_timer(500ms, std::bind(&TurtleCircle::timer_callback, this));
  }

  void timer_callback()
  {
    // Create a message to control the turtle's movement
    geometry_msgs::msg::Twist msg;
    msg.linear.x = 1.0;
    msg.angular.z = 1.0;

    // Publish the message to control the turtle's movement
    turtle_publisher_->publish(msg);
  }

private:
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr turtle_publisher_;
  rclcpp::TimerBase::SharedPtr turtle_timer;

};
    
int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);

    rclcpp::spin(std::make_shared<TurtleCircle>());
    rclcpp::shutdown();
    return 0;
}


#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <chrono>
#include "turtlesim/msg/pose.hpp"
#include "interfaces/srv/patrol.hpp"
#include "rcl_interfaces/msg/set_parameters_result.hpp"

using Patrol = interfaces::srv::Patrol;
using namespace std::chrono_literals;
using SetParametersResult = rcl_interfaces::msg::SetParametersResult;

class TurtleControl : public rclcpp::Node
{
public:
  TurtleControl() : Node("turtle_control")
  {
    //声明参数
    this->declare_parameter("k", 1.0);
    this->declare_parameter("max_speed", 1.0);
    this->get_parameter("k", k_);
    this->get_parameter("max_speed", max_speed_);
    // this->set_parameter(rclcpp::Parameter("k", 2.0));
    parameters_callback_handle_ = this->add_on_set_parameters_callback([&](const std::vector<rclcpp::Parameter> &parameters)->
     SetParametersResult{
      SetParametersResult result;
      result.successful = true;
      for(const auto &parameter : parameters){
        RCLCPP_INFO(this->get_logger(), "Parameter name: %s, value: %f", parameter.get_name().c_str(), parameter.as_double());
        if(parameter.get_name() == "k"){
          k_ = parameter.as_double();
        }
        if(parameter.get_name() == "max_speed"){
          max_speed_ = parameter.as_double();
        }
      }
      return result;
    });
    patrol_service_ = this->create_service<Patrol>("patrol", [&](const std::shared_ptr<Patrol::Request> request, const std::shared_ptr<Patrol::Response> response){
        if(
            (request->target_x>0 && request->target_x<12.0f)&&
            (request->target_y>0 && request->target_y<12.0f)
        )
        {
            this->target_x_= request->target_x;
            this->target_y_ = request->target_y;
            response->result = Patrol::Response::SUCCESS;
            // RCLCPP_INFO(this->get_logger(), "New target set: x=%f, y=%f", this->target_x__, this->target_y__);
        }
        else
        {
            response->result = Patrol::Response::FAIL;
        }
    });
    // Create a publisher to control the turtle's movement
    turtle_publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", 10);
    // Create a subscriber to get the turtle's current position
    turtle_pose_subscriber_ = this->create_subscription<turtlesim::msg::Pose>("turtle1/pose", 10, std::bind(&
    TurtleControl::pose_callback, this, std::placeholders::_1));
    // turtle_timer = this->create_wall_timer(500ms, std::bind(&TurtleControl::timer_callback, this));
  }

  void pose_callback(const turtlesim::msg::Pose::SharedPtr pose)
  {
    auto msg = geometry_msgs::msg::Twist();
    // Get the turtle's current position
    auto x = pose->x;
    auto y = pose->y;
    auto theta = pose->theta;
    RCLCPP_INFO(this->get_logger(), "Turtle pose: x=%f, y=%f, theta=%f", x, y, theta);

    // Calculate the distance and angle to the target position
    auto distance = sqrt(pow(x - target_x_, 2) + pow(y - target_y_, 2));
    auto angle = atan2(target_y_ - y, target_x_ - x) - theta;

    // Create a message to control the turtle's movement
    if(distance > 0.1)
    {
      if(fabs(angle) > 0.1){
        msg.angular.z = angle * k_;
      }else{
        msg.linear.x = distance * k_;
      }
    }

    if(msg.linear.x > max_speed_)
    {
      msg.linear.x = max_speed_;
    }

    turtle_publisher_->publish(msg);
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
  rclcpp::Service<Patrol>::SharedPtr patrol_service_;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr turtle_publisher_;
  rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr turtle_pose_subscriber_;
  OnSetParametersCallbackHandle::SharedPtr parameters_callback_handle_;
  double target_x_{1.0};
  double target_y_{1.0};
  double k_{1.0};
  double max_speed_{1.0};
  // rclcpp::TimerBase::SharedPtr turtle_timer;

};
    
int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);

    rclcpp::spin(std::make_shared<TurtleControl>());
    rclcpp::shutdown();
    return 0;
}


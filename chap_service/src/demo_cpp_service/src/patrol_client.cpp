#include <rclcpp/rclcpp.hpp>
#include "interfaces/srv/patrol.hpp"
#include <chrono>
#include <ctime>
#include "rcl_interfaces/msg/set_parameters_result.hpp"
#include "rcl_interfaces/srv/set_parameters.hpp"
#include "rcl_interfaces/msg/parameter.hpp"
#include "rcl_interfaces/msg/parameter_value.hpp"
#include "rcl_interfaces/msg/parameter_type.hpp"

using Patrol = interfaces::srv::Patrol;
using namespace std::chrono_literals;//使用10s,100ms表示时间
using SetParametersResult = rcl_interfaces::msg::SetParametersResult;
using SetParameters = rcl_interfaces::srv::SetParameters;
using Parameter = rcl_interfaces::msg::Parameter;
using ParameterValue = rcl_interfaces::msg::ParameterValue;
using ParameterType = rcl_interfaces::msg::ParameterType;

class PatrolClient : public rclcpp::Node
{
public:
  PatrolClient() : Node("turtle_circle")
  {
    srand(time(NULL));
    client_ = this->create_client<Patrol>("patrol");
    timer_ = this->create_wall_timer(10s,[&](){
        //等待服务
        while(!this->client_->wait_for_service(1s)){
            if(!rclcpp::ok()){
                RCLCPP_ERROR(this->get_logger(), "Interrupted while waiting for service");
                return;
            }
            RCLCPP_INFO(this->get_logger(), "service not available, waiting again...");
            
        }
        //构造request对象
        auto request = std::make_shared<Patrol::Request>();
        request->target_x = rand()%15;
        request->target_y = rand()%15;
        RCLCPP_INFO(this->get_logger(), "Sending request to patrol turtle to (%f,%f)",request->target_x,request->target_y);
        //发送请求
        this->client_->async_send_request(request,[&](rclcpp::Client<Patrol>::SharedFuture future){
            auto response = future.get();
            if(response->result==Patrol::Response::SUCCESS){
                RCLCPP_INFO(this->get_logger(), "请求成功");
            }
            if(response->result==Patrol::Response::FAIL){
                RCLCPP_INFO(this->get_logger(), "请求失败");
            }
        });
        //等待结果        
    });

  }
     // Create a publisher to control the turtle's movement
  //创建客户端发送请求,返回结果
  SetParameters::Response::SharedPtr call_set_parameters(Parameter parameter){
    //1.创建客户端
    auto client = this->create_client<SetParameters>("/turtle_control/set_parameters");
    //2.等待服务
    while(!client->wait_for_service(1s)){
        if(!rclcpp::ok()){
            RCLCPP_ERROR(this->get_logger(), "Interrupted while waiting for service");
            return nullptr;
        }
        RCLCPP_INFO(this->get_logger(), "service not available, waiting again...");
    }
    //3.创建请求
    auto request = std::make_shared<SetParameters::Request>();
    request->parameters.push_back(parameter);
    //4.发送请求,异步发送请求
    auto future = client->async_send_request(request);
    //5.等待结果
    if(rclcpp::spin_until_future_complete(this->get_node_base_interface(), future) == rclcpp::FutureReturnCode::SUCCESS){
        return future.get();
    }else{
        RCLCPP_ERROR(this->get_logger(), "Failed to call service");
        return nullptr;
    }
  }
  //更新参数
  void update_parameter_k(double k){
    Parameter parameter;
    parameter.name = "k";
    parameter.value.type = ParameterType::PARAMETER_DOUBLE;
    parameter.value.double_value = k;
    auto result = call_set_parameters(parameter);
    if(result==NULL){
        RCLCPP_ERROR(this->get_logger(), "Failed to update parameter k");
        return;
    }
    for(const auto &result : result->results){
        if(result.successful){
            RCLCPP_INFO(this->get_logger(), "Parameter k updated to %f", k);
        }else{
            RCLCPP_ERROR(this->get_logger(), "Failed to update parameter k, %s", result.reason.c_str());
        }
    }

  }
private:
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Client<Patrol>::SharedPtr client_;
  // rclcpp::TimerBase::SharedPtr turtle_timer;

};
    
int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<PatrolClient>();   
    node->update_parameter_k(2.0);
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}


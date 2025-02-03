#include <rclcpp/rclcpp.hpp>
#include "interfaces/srv/patrol.hpp"
#include <chrono>
#include <ctime>

using Patrol = interfaces::srv::Patrol;
using namespace std::chrono_literals;//使用10s,100ms表示时间

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
    // Create a publisher to control the turtle's movement
  
  }
 
private:
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Client<Patrol>::SharedPtr client_;
  // rclcpp::TimerBase::SharedPtr turtle_timer;

};
    
int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<PatrolClient>());
    rclcpp::shutdown();
    return 0;
}


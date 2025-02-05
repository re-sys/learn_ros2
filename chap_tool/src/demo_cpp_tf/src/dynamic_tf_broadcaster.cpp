#include "tf2_ros/transform_broadcaster.h"//广播类
#include "geometry_msgs/msg/transform_stamped.hpp"//提供消息接口
#include "rclcpp/rclcpp.hpp"
#include "tf2/LinearMath/Quaternion.h"//提供四元数接口
#include "tf2_geometry_msgs/tf2_geometry_msgs.hpp"//消息类型转换函数
#include "chrono"
using namespace std::chrono_literals;


class DynamicTFBroadcaster : public rclcpp::Node
{
private:
    // 广播器
    std::shared_ptr<tf2_ros::TransformBroadcaster> broadcaster_;
    rclcpp::TimerBase::SharedPtr timer_;
public:
    // 构造函数
    DynamicTFBroadcaster():Node("dynamic_tf_broadcaster"){
        // 创建广播器
        broadcaster_ = std::make_shared<tf2_ros::TransformBroadcaster>(this);
        timer_ = this->create_wall_timer(100ms, std::bind(&DynamicTFBroadcaster::publish_dynamic_tf, this));
    };
    void publish_dynamic_tf(){
        // 创建坐标变换
        geometry_msgs::msg::TransformStamped tfs;
        tfs.header.stamp = this->get_clock()->now();
        tfs.header.frame_id = "map";
        tfs.child_frame_id = "base_link";
        // 设置平移
        tfs.transform.translation.x = 2.0;
        tfs.transform.translation.y = 3.0;
        tfs.transform.translation.z = 0.0;
        // 设置旋转
        tf2::Quaternion qtn;
        qtn.setRPY(0, 0, 30*M_PI/180.0);
        tfs.transform.rotation = tf2::toMsg(qtn);
        // 发布坐标变换
        broadcaster_->sendTransform(tfs);
    }
};

int main(int argc, char *argv[]){
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<DynamicTFBroadcaster>());
    rclcpp::shutdown();
    return 0;
}


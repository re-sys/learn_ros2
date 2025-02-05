#include "tf2_ros/transform_listener.h"//广播类
#include "geometry_msgs/msg/transform_stamped.hpp"//提供消息接口
#include "rclcpp/rclcpp.hpp"
#include "tf2/LinearMath/Quaternion.h"//提供四元数接口
#include "tf2_geometry_msgs/tf2_geometry_msgs.hpp"//消息类型转换函数
#include "tf2_ros/buffer.h"
#include "tf2/utils.h"//提供四元数转换函数
#include "chrono"
using namespace std::chrono_literals;


class TfListener : public rclcpp::Node
{
private:
    // 广播器
    std::shared_ptr<tf2_ros::TransformListener> listener_;
    rclcpp::TimerBase::SharedPtr timer_;
    std::shared_ptr<tf2_ros::Buffer> buffer_;
public:
    // 构造函数
    TfListener():Node("tf_listener"){
        // 创建广播器
        buffer_ = std::make_shared<tf2_ros::Buffer>(this->get_clock());
        listener_ = std::make_shared<tf2_ros::TransformListener>(*buffer_,this);
        timer_ = this->create_wall_timer(1s, std::bind(&TfListener::get_transform, this));

    };
    void get_transform(){
        geometry_msgs::msg::TransformStamped tfs;
        try{
            //查询坐标关系
            tfs = buffer_->lookupTransform("base_link", "target_point", this->get_clock()->now(),rclcpp::Duration::from_seconds(1.0));
            //打印坐标关系
            auto translation = tfs.transform.translation;
            auto rotation = tfs.transform.rotation;
            double roll,pitch,yaw;
            tf2::getEulerYPR(rotation,yaw,pitch,roll);

            RCLCPP_INFO(this->get_logger(),"坐标关系:平移(%f,%f,%f),旋转(%f,%f,%f)",
            translation.x,translation.y,translation.z,
            yaw,pitch,roll);
        }
        catch(const std::exception& e){
            RCLCPP_ERROR(this->get_logger(),"查询失败:%s",e.what());
            return;
        }
    }
    // void publish_dynamic_tf(){
    //     // 创建坐标变换
    //     geometry_msgs::msg::TransformStamped tfs;
    //     tfs.header.stamp = this->get_clock()->now();
    //     tfs.header.frame_id = "map";
    //     tfs.child_frame_id = "base_link";
    //     // 设置平移
    //     tfs.transform.translation.x = 2.0;
    //     tfs.transform.translation.y = 3.0;
    //     tfs.transform.translation.z = 0.0;
    //     // 设置旋转
    //     tf2::Quaternion qtn;
    //     qtn.setRPY(0, 0, 30*M_PI/180.0);
    //     tfs.transform.rotation = tf2::toMsg(qtn);
    //     // 发布坐标变换
    //     broadcaster_->sendTransform(tfs);
    // }
};

int main(int argc, char *argv[]){
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<TfListener>());
    rclcpp::shutdown();
    return 0;
}


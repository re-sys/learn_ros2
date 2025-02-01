#include <QApplication>
#include <QLabel>
#include <QString>
#include <rclcpp/rclcpp.hpp>
#include <status_interfaces/msg/system_status.hpp>

using SystemStatus = status_interfaces::msg::SystemStatus;

class SystemStatusDisplay : public rclcpp::Node
{
private:
    rclcpp::Subscription<SystemStatus>::SharedPtr sub_;
    QLabel *label_;
public:
    SystemStatusDisplay() : Node("system_status_display")
    {
        label_ = new QLabel();
        sub_ = this->create_subscription<SystemStatus>(
            "system_status", 10, [&](const SystemStatus::SharedPtr msg)->void
            {
                label_->setText(get_qstr_from_msg(msg));
            }
        );
        label_->setText(get_qstr_from_msg( std::make_shared<SystemStatus>() ));
        label_->show();
    }
    QString get_qstr_from_msg(const SystemStatus::SharedPtr msg)
    {
        std::stringstream ss;
        ss<<"==============提供可视化系统状态==============\n"<<
        "数据时间: "<<msg->time.sec<<"."<<msg->time.nanosec/1000000<<"\ts\n"<<
        "CPU使用率: "<<msg->cpu_usage<<"\t%\n"<<
        "内存使用率: "<<msg->memory_usage<<"\t%\n"<<
        "内存总量: "<<msg->memory_total<<"\tMB\n"<<
        "内存可用量: "<<msg->memory_available<<"\tMB\n"<<
        "网络发送量"<<msg->net_sent<<"\tMB\n"<<
        "网络接收量"<<msg->net_recv<<"\tMB\n"<<
        "===============================================\n";
        return QString::fromStdString(ss.str());
    }
    
};
                


int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    QApplication app(argc, argv);
    auto node = std::make_shared<SystemStatusDisplay>();
    
    std::thread spinthread([&]()->void 
                        {             
                            rclcpp::spin(node);
                        });
    spinthread.detach();
    
    app.exec();
    return 0;
};
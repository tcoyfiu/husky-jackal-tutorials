#include "rclcpp/rclcpp.hpp"
#include "tf2_msgs/msg/tf_message.hpp"
class TFRemapper : public rclcpp::Node
{

public:
TFRemapper():Node("tf_remapper_node")
{
rclcpp::QoS qos_tf(100);
qos_tf.reliable();
qos_tf.durability_volatile();

rclcpp::QoS qos_tf_static(10);
qos_tf_static.reliable();
qos_tf_static.transient_local();

rclcpp::QoS qos_odom(100);
qos_odom.reliable();
qos_odom.durability_volatile();

printf("Remapping /j100_1439/tf and /j100_1439/tf_static\n");

// Remap /j100_1439/tf → /tf
printf("Subscribing to /j100_1439/tf\n");
tf_sub_ = this->create_subscription<tf2_msgs::msg::TFMessage>("/j100_1439/tf", qos_tf, [this](const tf2_msgs::msg::TFMessage::SharedPtr msg)
{
tf_pub_->publish(*msg);
});
printf("Publishing /tf\n");
tf_pub_ = this->create_publisher<tf2_msgs::msg::TFMessage>("/tf", qos_tf);

// Remap /j100_1439/tf_static → /tf_static
printf("Subscribing to /j100_1439/tf_static\n");
tf_static_sub_ = this->create_subscription<tf2_msgs::msg::TFMessage>("/j100_1439/tf_static", qos_tf_static, [this](const tf2_msgs::msg::TFMessage::SharedPtr msg)
{
tf_static_pub_->publish(*msg);
});
printf("Publishing /tf_static\n");
tf_static_pub_ = this->create_publisher<tf2_msgs::msg::TFMessage>("/tf_static", qos_tf_static);


}


private:
rclcpp::Subscription<tf2_msgs::msg::TFMessage>::SharedPtr tf_sub_;
rclcpp::Publisher<tf2_msgs::msg::TFMessage>::SharedPtr tf_pub_;
rclcpp::Subscription<tf2_msgs::msg::TFMessage>::SharedPtr tf_static_sub_;
rclcpp::Publisher<tf2_msgs::msg::TFMessage>::SharedPtr tf_static_pub_;
};


int main(int argc, char **argv)
{
rclcpp::init(argc, argv);
printf("Initializing");
rclcpp::spin(std::make_shared<TFRemapper>());
rclcpp::shutdown();
return 0;
}
#include <nav_msgs/Odometry.h>
#include <ros/ros.h>
#include <std_msgs/Int32.h>

/*void counterCallback(const std_msgs::Int32::ConstPtr& msg)
{
  ROS_INFO("%d", msg->data);
}*/

void odomCallback(const nav_msgs::Odometry::ConstPtr &var) {
  ROS_INFO("%f", var->pose.pose.position.x);
  ROS_INFO("%f", var->twist.twist.linear.x);
  // ROS_INFO("%s", msg->header.frame_id.c_str());
}

int main(int argc, char **argv) {

  ros::init(argc, argv, "odom_subscriber");
  ros::NodeHandle nh;

  // ros::Subscriber sub = nh.subscribe("counter", 1000, counterCallback);
  ros::Subscriber sub = nh.subscribe("odom", 1000, odomCallback);

  ros::spin();

  return 0;
}
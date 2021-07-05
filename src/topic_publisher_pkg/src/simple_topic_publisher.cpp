#include <geometry_msgs/Twist.h>
#include <ros/ros.h>
#include <std_msgs/Int32.h>

int main(int argc, char **argv) {

  // ros::init(argc, argv, "topic_publisher");
  ros::init(argc, argv, "topic_publisher");
  ros::NodeHandle nh;

  // ros::Publisher pub = nh.advertise<std_msgs::Int32>("counter", 1000);
  ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
  ros::Rate loop_rate(2);

  // std_msgs::Int32 count;
  // count.data = 0;
  geometry_msgs::Twist mov;
  mov.linear.x = 0.1;
  mov.angular.z = 0.1;

  while (ros::ok()) {
    // pub.publish(count);
    pub.publish(mov);
    ros::spinOnce();
    loop_rate.sleep();
    //++count.data;
  }

  return 0;
}
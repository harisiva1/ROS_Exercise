#include "my_custom_srv_msg_pkg/MyCustomServiceMessage.h"
#include "ros/ros.h"
#include <geometry_msgs/Twist.h>

ros::Publisher pub;
geometry_msgs::Twist mov;
bool my_callback(my_custom_srv_msg_pkg::MyCustomServiceMessage::Request &req,
                 my_custom_srv_msg_pkg::MyCustomServiceMessage::Response &res) {
  // res.some_variable = req.some_variable + req.other_variable;
  ROS_INFO("Request Data==> duration=%i", req.duration);
  mov.linear.x = 0.2;
  mov.angular.z = 0.2;
  ros::Time startTime = ros::Time::now();
  ros::Duration loopDuration(req.duration);
  ros::Rate loopRate(10.0);
  while (ros::Time::now() < startTime + loopDuration) {
    pub.publish(mov);
    ros::spinOnce();
    loopRate.sleep();
    // ROS_INFO("counting");
  }
  mov.linear.x = 0;
  mov.angular.z = 0;
  pub.publish(mov);
  res.success = true;
  ROS_INFO("sending back response:true");
  return true;
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "service_server");
  ros::NodeHandle nh;

  pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1000);

  ros::ServiceServer my_service = nh.advertiseService(
      "/custom_my_service_ex35",
      my_callback); // create the Service called // my_service
                    // with the defined // callback
  pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
  ros::spin();

  return 0;
}

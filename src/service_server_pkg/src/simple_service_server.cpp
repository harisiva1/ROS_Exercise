#include "ros/ros.h"
#include "std_srvs/Empty.h"
#include <geometry_msgs/Twist.h>
// Import the service message header file generated from the Empty.srv message

// We define the callback function of the service

ros::Publisher pub;
geometry_msgs::Twist mov;
bool my_callback(std_srvs::Empty::Request &req,
                 std_srvs::Empty::Response &res) {
  // res.some_variable = req.some_variable + req.other_variable;
  ROS_INFO("My_callback has been called"); // We print an string whenever the
                                           // Service gets called
  mov.linear.x = 0.2;
  mov.angular.z = 0.2;
  ros::Rate loop_rate(2);
  pub.publish(mov);
  ROS_INFO("done");
  return true;
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "service_server");
  ros::NodeHandle nh;

  pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1000);

  ros::ServiceServer my_service = nh.advertiseService(
      "/my_service", my_callback); // create the Service called // my_service
                                   // with the defined // callback
  pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
  ros::spin();

  return 0;
}
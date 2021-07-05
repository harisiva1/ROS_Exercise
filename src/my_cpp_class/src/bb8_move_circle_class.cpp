#include "services_quiz/BB8CustomServiceMessage.h"
#include <geometry_msgs/Twist.h>
#include <ros/ros.h>
#include <std_srvs/Empty.h>
#include <unistd.h>

class MoveBB8 {

public:
  // ROS Objects
  ros::NodeHandle nh_;

  // ROS Services
  // ros::ServiceServer my_service;
  ros::ServiceServer my_custom_service;

  // ROS Publishers
  ros::Publisher vel_pub;

  // ROS Messages
  geometry_msgs::Twist vel_msg;

  int time;

  int i = 0;

  MoveBB8() {
    /*my_service = nh_.advertiseService("/move_bb8_in_circle",
                                      &MoveBB8::my_callback, this);*/
    my_custom_service = nh_.advertiseService(
        "/move_bb8_in_circle_class", &MoveBB8::my_callback_custom, this);
    ROS_INFO("The Service /move_bb8_in_circle is READY");
    vel_pub = nh_.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
  }

  void move_in_circle(int time) {
    vel_msg.linear.x = 0.2;
    vel_msg.angular.z = 0.2;
    while (i < time) {
      vel_pub.publish(vel_msg);
      usleep(1000000);
      i++;
    }
  }

  void stop() {
    vel_msg.linear.x = 0.0;
    vel_msg.angular.z = 0.0;
    vel_pub.publish(vel_msg);
  }

  bool my_callback(std_srvs::Empty::Request &req,
                   std_srvs::Empty::Response &res) {
    ROS_INFO("The Service /move_bb8_in_circle has been called");
    
    move_in_circle(5);
    stop();
    ROS_INFO("Finished service /move_bb8_in_circle");
    return true;
  }
  bool
  my_callback_custom(services_quiz::BB8CustomServiceMessage::Request &req,
                     services_quiz::BB8CustomServiceMessage::Response &res) {
    // res.some_variable = req.some_variable + req.other_variable;
    ROS_INFO("Request Data==> side=%f, repetitions=%i", req.side,
             req.repetitions);
    ROS_INFO("The Service /move_bb8_in_circle has been called");
    move_in_circle(req.side);
    stop();
    ROS_INFO("Finished service /move_bb8_in_circle");
    res.success = true;
    ROS_INFO("sending back response:true");
    return true;
  }
};

int main(int argc, char **argv) {
  ros::init(argc, argv, "move_bb8_node");

  MoveBB8 moveBB8;

  ros::spin();

  return 0;
}
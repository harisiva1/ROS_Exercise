/*
#include "my_custom_srv_msg_pkg/MyCustomServiceMessage.h"
#include "ros/ros.h"

bool my_callback(my_custom_srv_msg_pkg::MyCustomServiceMessage::Request &req,
                 my_custom_srv_msg_pkg::MyCustomServiceMessage::Response &res) {
  ROS_INFO("Request Data==> radius=%f, repetitions=%d", req.radius,
           req.repetitions);
  if (req.radius > 5.0) {
    res.success = true;
    ROS_INFO("sending back response:true");
  } else {
    res.success = false;
    ROS_INFO("sending back response:false");
  }

  return true;
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "custom_service_server");
  ros::NodeHandle nh;

  ros::ServiceServer my_service =
      nh.advertiseService("/custom_my_service", my_callback);
  ros::spin();

  return 0;
}*/
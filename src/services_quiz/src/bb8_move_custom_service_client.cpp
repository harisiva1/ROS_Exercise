#include "ros/ros.h"
#include "services_quiz/BB8CustomServiceMessage.h"

int main(int argc, char **argv) {
  ros::init(argc, argv, "quiz_service_client"); // Initialise a ROS node
  ros::NodeHandle nh;

  // Create the connection to the service /move_bb8_in_circle_custom
  ros::ServiceClient move_bb8_in_square_service_client =
      nh.serviceClient<services_quiz::BB8CustomServiceMessage>(
          "/move_bb8_in_square_custom");

  services_quiz::BB8CustomServiceMessage srv;
  srv.request.side = 5; // Create an object of type MyCustomServiceMessage
  srv.request.repetitions = 2;
  // ros::Rate rate();
  move_bb8_in_square_service_client.call(srv);
  ros::Duration(10).sleep();
  services_quiz::BB8CustomServiceMessage srv1;
  srv1.request.side = 10; // Create an object of type MyCustomServiceMessage
  srv1.request.repetitions = 2;
  move_bb8_in_square_service_client.call(srv1);
  ros::Duration(10).sleep();
  services_quiz::BB8CustomServiceMessage srv2;
  srv2.request.side = 20; // Create an object of type MyCustomServiceMessage
  srv2.request.repetitions = 1;
  move_bb8_in_square_service_client.call(srv2);
  /*if (move_bb8_in_square_service_client.call(srv)) {
    ROS_INFO("Service successfully called. Moving BB8 in a square.");
  } else if (move_bb8_in_square_service_client.call(srv1)) {
    ROS_INFO(
        "Service successfully called for second case. Moving BB8 in a square.");
  } else if (move_bb8_in_square_service_client.call(srv2)) {
    ROS_INFO(
        "Service successfully called for third case. Moving BB8 in a square.");
  } else {
    ROS_ERROR("Failed to call service /move_bb8_in_square_custom");
    return 1;
  }*/

  return 0;
}

//<include file="$(find
 services_quiz)/launch/start_bb8_move_custom_service_server.launch"/>
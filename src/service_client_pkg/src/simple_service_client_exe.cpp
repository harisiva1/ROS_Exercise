
#include "iri_wam_reproduce_trajectory/ExecTraj.h"
#include "ros/ros.h"
#include <ros/package.h>
// Import the service message used by the service /trajectory_by_name

int main(int argc, char **argv) {
  ros::init(argc, argv,
            "service_client_exe"); // Initialise a ROS node with the name
                                   // service_client
  ros::NodeHandle nh;

  // Create the connection to the service /trajectory_by_name
  ros::ServiceClient traj_by_name_service =
      nh.serviceClient<iri_wam_reproduce_trajectory::ExecTraj>(
          "/execute_trajectory");
  iri_wam_reproduce_trajectory::ExecTraj
      srv; // Create an object of type exectraj
  srv.request.file = ros::package::getPath("iri_wam_reproduce_trajectory") +
                     "/config/get_food.txt";

  if (traj_by_name_service.call(srv)) // Send through the connection the name of
                                      // the trajectory to execute
  {
    ROS_INFO("%s", "success"); // Print the result given by the service called
  } else {
    ROS_ERROR("Failed to call service /iri_wam_reproduce_trajectory");
    return 1;
  }

  return 0;
}
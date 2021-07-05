#include <ros/console.h>
#include <ros/ros.h>
#include <stdlib.h>

int main(int argc, char **argv) {

  if (ros::console::set_logger_level(ROSCONSOLE_DEFAULT_NAME,
                                     ros::console::levels::Warn)) {
    ros::console::notifyLoggerLevelsChanged();
  }

  ros::init(argc, argv, "log_demo");
  ros::NodeHandle nh;
  ros::Rate loop_rate(0.5); // We create a Rate object of 2Hz

  while (ros::ok()) // Endless loop until Ctrl + C
  {
    ROS_DEBUG("There is a missing droid");
    ROS_INFO("The Emperors Capuchino is done");
    ROS_WARN("Help me Obi-Wan Kenobi, you're my only hope");
    int exhaust_number = rand() % 100 + 1;
    int port_number = rand() % 100 + 1;
    ROS_ERROR("The thermal exhaust port %d, right below the main port %d",
              exhaust_number, port_number);
    ROS_FATAL("The DeathStar Is EXPLODING");
    loop_rate.sleep();
    ros::spinOnce();
  }

  return 0;
}
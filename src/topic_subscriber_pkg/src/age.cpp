#include <ros/ros.h>
#include <topic_subscriber_pkg/Age.h>

int main(int argc, char **argv) {

  // ros::init(argc, argv, "topic_publisher");
  ros::init(argc, argv, "age_publisher");
  ros::NodeHandle nh;

  
  ros::Publisher pub = nh.advertise<topic_subscriber_pkg::Age>("age_topic", 1000);
  ros::Rate loop_rate(2);

  topic_subscriber_pkg::Age var;
  var.years = 1992;
  var.months = 01;
  var.days = 19;

  while (ros::ok()) {
    pub.publish(var);
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
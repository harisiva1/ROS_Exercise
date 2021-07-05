#include <geometry_msgs/Twist.h>
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <std_msgs/Int32.h>

ros::Publisher pub;
ros::Subscriber sub;

float st, left, right;

void laserCallback(const sensor_msgs::LaserScan::ConstPtr &msg) {
  // ROS_INFO("%f", var->pose.pose.position.x);
  st = msg->ranges[360];
  left = msg->ranges[719];
  right = msg->ranges[1];
}

int main(int argc, char **argv) {

  ros::init(argc, argv, "pub_sub_node");
  ros::NodeHandle nh;

  pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);
  sub = nh.subscribe("/kobuki/laser/scan", 1000, laserCallback);

  geometry_msgs::Twist mov;

  ros::Rate rate(2);

  while (ros::ok()) {

    if (st > 1) {
      mov.linear.x = 0.2;
      mov.angular.z = 0;
    } else if (st < 1 || left < 0.3) {
      mov.linear.x = 0;
      mov.angular.z = -0.4;
    } else if (st < 1 || right < 0.3) {
      mov.linear.x = 0;
      mov.angular.z = 0.4;
    }

    pub.publish(mov);

    rate.sleep();
    ros::spinOnce();
  }

  // ros::spin();

  return 0;
}
#include "ros/ros.h"
#include "services_quiz/BB8CustomServiceMessage.h"
#include <geometry_msgs/Twist.h>
#include <unistd.h>

ros::Publisher pub;
geometry_msgs::Twist mov;
const double PI = 3.14159265358979323846;
float targ_ang = 90 * 2 * PI / 360;
float ang_speed = 12 * 2 * PI / 360;

bool my_callback(services_quiz::BB8CustomServiceMessage::Request &req,
                 services_quiz::BB8CustomServiceMessage::Response &res) {
  // res.some_variable = req.some_variable + req.other_variable;
  ROS_INFO("Request Data==> side=%f, repetitions=%i", req.side,
           req.repetitions);
  int i = 0;
  int j = 0;
  int s = 0;
  while (j < req.repetitions) {
    int s = 0;
    while (s < 4) {
      int i = 0;
      while (i < req.side) {
        mov.linear.x = 0.2;
        mov.angular.z = 0.0;
        pub.publish(mov);
        usleep(1000000);
        i++;
      }
      ROS_INFO("moved straight");
      mov.linear.x = 0.0;
      mov.angular.z = 0.0;
      pub.publish(mov);
      float time = 0.0;
      while (time < 10) {
        mov.linear.x = 0.0;
        mov.angular.z = -0.2;
        pub.publish(mov);
        usleep(1000000);
        // loopRate.sleep();
        time++;
      }
      mov.linear.x = 0.0;
      mov.angular.z = 0.0;
      pub.publish(mov);
      ROS_INFO("one loop completed");
      s++;
    }
    ROS_INFO("one repetition completed");

    j++;
    ROS_INFO("%i", j);
  }

  mov.linear.x = 0;
  mov.angular.z = 0;
  pub.publish(mov);
  res.success = true;
  ROS_INFO("sending back response:true");
  return true;
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "quiz_service_server");
  ros::NodeHandle nh;

  pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1000);

  ros::ServiceServer my_service = nh.advertiseService(
      "/move_bb8_in_square_custom",
      my_callback); // create the Service called // my_service
                    // with the defined // callback
  ros::spin();

  return 0;
}

/*ros::Time startTime = ros::Time::now();
ros::Duration loopDuration(req.duration);
ros::Rate loopRate(10.0);
ros::Time::now() < startTime + loopDuration
ros::spinOnce();
loopRate.sleep();

    while (i < req.side) {
      pub.publish(mov);
      usleep(1000000);
      i++;
    }
*/

/*while (j < req.repetitions) {
  int s = 0;
  while (s < 4) {
    int i = 0;
    float curr_angle = 0.0;
    while (i < req.side) {
      mov.linear.x = 0.2;
      mov.angular.z = 0;
      pub.publish(mov);
      usleep(1000000);
      i++;
    }
    ROS_INFO("moved straight");
    mov.linear.x = 0;
    pub.publish(mov);
    ros::Rate loopRate(2.0);
    double t0 = ros::Time::now().toSec();
    while (curr_angle < targ_ang) {
      mov.angular.z = -0.2;
      pub.publish(mov);
      loopRate.sleep();
      double t1 = ros::Time::now().toSec();
      curr_angle = ang_speed * (t1 - t0);
      ROS_INFO("%f", curr_angle);
    }
    ROS_INFO("one loop completed");
    s++;
  }
  ROS_INFO("one repetition completed");

  j++;
  ROS_INFO("%i", j);
}*/
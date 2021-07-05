#include <actionlib/client/simple_action_client.h>
#include <ardrone_as/ArdroneAction.h> // Note: "Action" is appended
#include <geometry_msgs/Twist.h>
#include <ros/ros.h>
#include <std_msgs/Empty.h>
#include <unistd.h>

int nImage = 0;

void doneCb(const actionlib::SimpleClientGoalState &state,
            const ardrone_as::ArdroneResultConstPtr &result) {
  ROS_INFO("[State Result]: %s", state.toString().c_str());
  ROS_INFO("The Action has been completed");
  // ros::shutdown();
}

// Called once when the goal becomes active
void activeCb() { ROS_INFO("Goal just went active"); }

void feedbackCb(const ardrone_as::ArdroneFeedbackConstPtr &feedback) {
  ROS_INFO("[Feedback] image n.%d received", nImage);
  ++nImage;
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "drone_action_client");
  ros::NodeHandle nh;

  ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);
  geometry_msgs::Twist mov;

  ros::Publisher takeoff =
      nh.advertise<std_msgs::Empty>("/drone/takeoff", 1000);

  std_msgs::Empty takeoff_msg;

  ros::Publisher land = nh.advertise<std_msgs::Empty>("/drone/land", 1000);
  std_msgs::Empty land_msg;

  actionlib::SimpleActionClient<ardrone_as::ArdroneAction> client(
      "ardrone_action_server", true);
  client.waitForServer();

  ardrone_as::ArdroneGoal goal;
  goal.nseconds = 10;

  client.sendGoal(goal, &doneCb, &activeCb, &feedbackCb);
  // client.waitForResult();

  ros::Rate loop_rate(2);
  actionlib::SimpleClientGoalState state_result = client.getState();
  ROS_INFO("[State Result]: %s", state_result.toString().c_str());
  // takeoff.publish(takeoff_msg);
  // usleep(1000000);

  while (state_result == actionlib::SimpleClientGoalState::ACTIVE ||
         state_result == actionlib::SimpleClientGoalState::PENDING) {
    takeoff.publish(takeoff_msg);
    mov.linear.x = 1.0;
    mov.angular.z = 1.0;
    pub.publish(mov);
    ROS_INFO("moved quadcopter");
    loop_rate.sleep();
    state_result = client.getState();
    ROS_INFO("[State Result]: %s", state_result.toString().c_str());
  }
  if (state_result == actionlib::SimpleClientGoalState::SUCCEEDED) {
    mov.linear.x = 0.0;
    mov.angular.z = 0.0;
    pub.publish(mov);
    ROS_INFO("stopped quadcopter");
    land.publish(land_msg);
  }
  return 0;
}
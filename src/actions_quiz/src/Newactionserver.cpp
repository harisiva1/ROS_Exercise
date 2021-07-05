#include <actionlib/server/simple_action_server.h>
#include <actions_quiz/CustomActionMsgAction.h>
//#include <geometry_msgs/Twist.h>
#include <ros/ros.h>
#include <std_msgs/Empty.h>

class TakeoffLand {
protected:
  ros::NodeHandle nh_;
  // NodeHandle instance must be created before this line. Otherwise strange
  // error occurs.
  actionlib::SimpleActionServer<actions_quiz::CustomActionMsgAction> as_;
  std::string action_name_;
  // create messages that are used to publish feedback
  actions_quiz::CustomActionMsgFeedback feedback_;
  // actionlib::TestResult result_;

  // Create needed messages
  int rate_hz_;

  ros::Rate *rate_;
  bool success_;
  ros::Publisher takeoff_pub_;
  std_msgs::Empty takeoff_msg_;
  ros::Publisher land_pub_;
  std_msgs::Empty land_msg_;

public:
  TakeoffLand(std::string name)
      : as_(nh_, name, boost::bind(&TakeoffLand::executeCB, this, _1), false),
        action_name_(name) {
    as_.start();
    rate_hz_ = 1;

    rate_ = new ros::Rate(rate_hz_);
    success_ = true;
    takeoff_pub_ = nh_.advertise<std_msgs::Empty>("/drone/takeoff", 1000);
    land_pub_ = nh_.advertise<std_msgs::Empty>("/drone/land", 1000);
  }

  ~TakeoffLand(void) {}

  void executeCB(const actions_quiz::CustomActionMsgGoalConstPtr &goal) {

    feedback_.feedback = goal->goal;
    // publish the feedback
    as_.publishFeedback(feedback_);

    // Takeoff the drone
    if (goal->goal == "TAKEOFF") {
      this->takeoff_drone();
    } else if (goal->goal == "LAND") {
      this->land_drone();
    }

    // check that preempt has not been requested by the client
    if (as_.isPreemptRequested() || !ros::ok()) {
      ROS_INFO("%s: Preempted", action_name_.c_str());
      // set the action state to preempted
      as_.setPreempted();
      success_ = false;
    }

    feedback_.feedback = goal->goal;
    // publish the feedback
    as_.publishFeedback(feedback_);

    if (success_) {

      ROS_INFO("%s: Succeeded", action_name_.c_str());
      // set the action state to succeeded
      as_.setSucceeded();
    }
  }

  // Functions to control the drone

  void takeoff_drone(void) {
    ROS_INFO("Taking Off Drone...");
    int i = 0;
    while (i < 4) {
      takeoff_pub_.publish(takeoff_msg_);

      i++;
      rate_->sleep();
    }
  }

  void land_drone(void) {
    ROS_INFO("Landing Drone...");
    int i = 0;
    while (i < 4) {
      land_pub_.publish(land_msg_);
      i++;
      rate_->sleep();
    }
  }
};

int main(int argc, char **argv) {
  ros::init(argc, argv, "newas");

  TakeoffLand tkld("action_custom_msg_as");
  ros::spin();

  return 0;
}
#include <actionlib/TestAction.h>
#include <actionlib/server/simple_action_server.h>
#include <geometry_msgs/Twist.h>
#include <ros/ros.h>
#include <std_msgs/Empty.h>
#include <unistd.h>

class Movesquare {
protected:
  ros::NodeHandle nh_;
  // NodeHandle instance must be created before this line. Otherwise strange
  // error occurs.
  actionlib::SimpleActionServer<actionlib::TestAction> as_;
  std::string action_name_;
  // create messages that are used to publish feedback and result
  actionlib::TestFeedback feedback_;
  actionlib::TestResult result_;

  ros::Rate *rate;
  int rate_hz_;
  int turnsec;
  int sidesec;
  bool success_;
  ros::Publisher pub;
  geometry_msgs::Twist mov;
  ros::Publisher takeoff;
  std_msgs::Empty takeoff_msg;
  ros::Publisher land;
  std_msgs::Empty land_msg;

public:
  Movesquare(std::string name)
      : as_(nh_, name, boost::bind(&Movesquare::executeCB, this, _1), false),
        action_name_(name) {
    as_.start();
    pub = nh_.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);

    takeoff = nh_.advertise<std_msgs::Empty>("/drone/takeoff", 1000);

    land = nh_.advertise<std_msgs::Empty>("/drone/land", 1000);
    rate_hz_ = 1;
    turnsec = 4;
    success_ = true;

    rate = new ros::Rate(rate_hz_);
  }

  ~Movesquare(void) {}

  void executeCB(const actionlib::TestGoalConstPtr &goal) {

    // start executing the action
    this->takeoffdrone();
    for (int i = 0; i < 4; i++) {
      // check that preempt has not been requested by the client
      if (as_.isPreemptRequested() || !ros::ok()) {
        ROS_INFO("%s: Preempted", action_name_.c_str());
        // set the action state to preempted
        as_.setPreempted();
        success_ = false;
        break;
      }
      sidesec = goal->goal;

      this->movefwd(sidesec);
      this->stop();
      this->turn(turnsec);

      feedback_.feedback = i;
      as_.publishFeedback(feedback_);
      rate->sleep();
    }
    if (success_) {
      result_.result = (4 * turnsec) + (4 * sidesec);
      ROS_INFO("The total seconds it took the drone to perform the square "
               "was %i seconds",
               result_.result);
      ROS_INFO("%s: Succeeded", action_name_.c_str());
      // set the action state to succeeded
      as_.setSucceeded(result_);
      this->stop();
      this->landdrone();
    }
  }
  void takeoffdrone() {
    ROS_INFO("Taking off");
    takeoff.publish(takeoff_msg);
    usleep(3000000);
  }
  void movefwd(int sec) {
    ROS_INFO("moving straight");
    int i = 0;
    while (i < sec) {
      mov.linear.x = 1;
      mov.angular.z = 0;
      pub.publish(mov);
      rate->sleep();
      i++;
    }
  }
  void stop() {
    ROS_INFO("stopping");
    mov.linear.x = 0;
    mov.angular.z = 0;
    pub.publish(mov);
    usleep(2000000);
  }
  void turn(int sec) {
    ROS_INFO("turning");
    int i = 0;
    while (i < sec) {
      mov.linear.x = 0;
      mov.angular.z = 0.55;
      pub.publish(mov);
      rate->sleep();
      i++;
    }
  }
  void landdrone() {
    ROS_INFO("landing");
    land.publish(land_msg);
    usleep(3000000);
  }
};

int main(int argc, char **argv) {
  ros::init(argc, argv, "movesquarenode");

  Movesquare ms("movesquaredrone");
  ros::spin();

  return 0;
}
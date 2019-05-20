#include "ros/ros.h"
#include "arlocal/AlvarMarker.h"
#include "arlocal/getLoc.h"
#include "arlocal/frontierExplorer.h"
#include "arlocal/ROSINFOPoseRecipient.h"
#include "arlocal/TFBroadcastPR.h"
#include <move_base_msgs/MoveBaseAction.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <cmath>
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char **argv) {
  ros::init(argc, argv, "driver");
  ros::NodeHandle n;
  MoveBaseClient ac("move_base", true);

  ros::Publisher setInitialPose= n.advertise<geometry_msgs::PoseWithCovarianceStamped>("initialpose", 5, true);

  geometry_msgs::PoseWithCovarianceStamped initialPose;
  initialPose.header.frame_id = "base_link";
  initialPose.header.stamp = ros::Time::now();
  initialPose.pose.pose.position.x = 0;
  initialPose.pose.pose.position.y = 0;
  initialPose.pose.pose.position.z = 0;
  
  initialPose.pose.pose.orientation = tf::createQuaternionFromYaw((30.0*M_PI)/180.0);

  setInitialPose.publish(initialPose);

  tf::TransformListener tf_l;
  getLoc getLoc(tf_l, ac);
  ROS_INFO("Started program.");
  AlvarMarker am(n, tf_l, getLoc, "nav_kinect_rgb_optical_frame");  //Kinect on robot

  frontierExplorer explorer(tf_l, ac);
  explorer.move(getLoc);
  
  setFinalPose(getLoc

  ros::AsyncSpinner spinner(1);
  spinner.start();
  ros::waitForShutdown();

  return 0;
}

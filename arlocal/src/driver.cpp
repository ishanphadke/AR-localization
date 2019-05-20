#include "ros/ros.h"
#include "arlocal/AlvarMarker.h"
#include "arlocal/getLoc.h"
#include "arlocal/frontierExplorer.h"
#include "arlocal/ROSINFOPoseRecipient.h"
#include "arlocal/TFBroadcastPR.h"
#include <move_base_msgs/MoveBaseAction.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <cmath>
#include <fstream>
#include <actionlib/client/simple_action_client.h> 
#include <map> 

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char **argv)
{
  std::ifstream inFile("ar_tag_locations.txt", std::ios::in);
  if (!inFile) 
  {
    cerr << "Unable to open file ar_tag_locations.txt";
    exit(1);
  }
  
  // Populate AR Tag location map
  map<int, geometry_msgs::Pose> markers; 
  
  while (inFile >> x) 
  {
    int id= x;
    inFile >> x;
    double xPos= x;
    
    inFile >> x;
    double yPos= z;
    
    inFile >> x;
    double zPos= x;
    
    geometry_msgs::Pose markerP;
    
    markerP.position.x = 0;
    markerP.position.y = 0;
    markerP.position.z = 0;
    
    markers.insert(pair<int, geometry_msgs::Pose markerP>(id, markerP)); 
  }
  
  inFile.close();
  
  // Start processes
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
  
  initialPose.pose.pose.orientation.w= 1;;

  setInitialPose.publish(initialPose);

  tf::TransformListener tf_l;
  getLoc getLoc(tf_l, ac);
  ROS_INFO("Started program.");
  AlvarMarker am(n, tf_l, getLoc, "nav_kinect_rgb_optical_frame");  //Kinect on robot

  frontierExplorer explorer(tf_l, ac);
  explorer.move(getLoc);
  
  // reverse transformation
  setFinalPose(getLoc.getMarkerID, getLoc.getMarkerPose, markers, setInitialPose);

  ros::AsyncSpinner spinner(1);
  spinner.start();
  ros::waitForShutdown();

  return 0;
}

void setFinalPose(int markerID, geometry_msgs::Pose markerPoseInRelation, map<int, geometry_msgs::Pose> markers, ros::Publisher setInitialPose)
{
  geometry_msgs::Pose realMarkerPose= markers.find(markerID)->second;
  
  geometry_msgs::Pose realRobotPose;
  
  realRobotPose.position.x= markerPoseInRelation.position.x+ realMarkerPose.position.x;
  realRobotPose.position.y= markerPoseInRelation.position.y+ realMarkerPose.position.y;
  realRobotPose.position.z= markerPoseInRelation.position.z+ realMarkerPose.position.z;
  
  geometry_msgs::PoseWithCovarianceStamped finalPose;
  initialPose.header.frame_id= "base_link";
  initialPose.header.stamp= ros::Time::now();
  initialPose.pose.pose.position.x= markerPoseInRelation.position.x+ realMarkerPose.position.x;
  initialPose.pose.pose.position.y= markerPoseInRelation.position.y+ realMarkerPose.position.y;
  initialPose.pose.pose.position.z= markerPoseInRelation.position.z+ realMarkerPose.position.z; 
  
  initialPose.pose.pose.orientation.w= 1;

  setInitialPose.publish(finalPose);
}







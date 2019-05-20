#include "arlocal/getLoc.h"
#include <fstream>
#include <iostream>

  getLoc::getLoc(tf::TransformListener &tfL, MoveBaseClient &ac) : _tfL(tfL), _ac(ac) {}

  geometry_msgs::Pose getLoc::receivePose(geometry_msgs::Pose &pose, int markerID)
  {
  	geometry_msgs::Pose markerPos= pose;

    while(!_ac.waitForServer(ros::Duration(5.0))){
      ROS_INFO("Waiting for the move_base action server to come up");
    }

  	move_base_msgs::MoveBaseGoal goal;

  	goal.target_pose.header.frame_id= "base_link";
	  goal.target_pose.header.stamp= ros::Time::now();

    double x= markerPos.position.z;
    double y= markerPos.position.x;
    double z= markerPos.position.y;
    double distance= sqrt(pow(x, 2)+pow(y, 2));
  	goal.target_pose.pose.position.x= distance;

    double angle= atan2(y,x);
    std::cout << "Angle: "<<angle<<'\n';
    tf::Quaternion direction;
    direction.setRPY(0,0,0.8*angle);
    goal.target_pose.pose.orientation.w= direction.w();
    goal.target_pose.pose.orientation.x= direction.x();
    goal.target_pose.pose.orientation.y= direction.y();
    goal.target_pose.pose.orientation.z= direction.z();

   if(!markerFound)
    {
	   
    }
  }

  bool getLoc::seenMarker()
  {
    return markerFound;
  }

  getLoc::~getLoc() {}

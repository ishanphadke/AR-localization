#include "arlocal/frontierExplorer.h"
#include <fstream>
#include <iostream>

  frontierExplorer::frontierExplorer(tf::TransformListener &tfL, MoveBaseClient &ac) : _tfL(tfL), _ac(ac) {}

  void frontierExplorer::move(getLoc alvarSeeker)
  {
      move_base_msgs::MoveBaseGoal goal;
      goal.target_pose.header.frame_id= "base_link";
      goal.target_pose.header.stamp= ros::Time::now();
      double distance= 5;
      double angle= 0;
      while(!alvarSeeker.seenMarker())
      {
        goal.target_pose.pose.position.x= distance;

        angle= (angle*M_PI)/180;
        std::cout << "Angle: "<<angle<<'\n';
        tf::Quaternion direction;
        direction.setRPY(0,0,0.8*angle);
        goal.target_pose.pose.orientation.w= direction.w();
        goal.target_pose.pose.orientation.x= direction.x();
        goal.target_pose.pose.orientation.y= direction.y();
        goal.target_pose.pose.orientation.z= direction.z();

         ROS_INFO("Sending goal");
         _ac.sendGoal(goal);
         _ac.waitForResult();
         if(_ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
         {
           ROS_INFO("Hooray, the base moved somewhere");
           distance= 5;
           angle=0;
         }
         else
         {
           ROS_INFO("The base failed to move for some reason");
           distance-= 1;
           angle+=30;
         }
      }
  }

  frontierExplorer::~frontierExplorer() {};

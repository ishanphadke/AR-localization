#include "arlocal/getLoc.h"
#include <fstream>
#include <iostream>

  getLoc::getLoc(tf::TransformListener &tfL, MoveBaseClient &ac) : _tfL(tfL), _ac(ac) {}

  void getLoc::receivePose(geometry_msgs::Pose &pose, int markerID)
  {
  	geometry_msgs::Pose destination= pose;

    while(!_ac.waitForServer(ros::Duration(5.0))){
      ROS_INFO("Waiting for the move_base action server to come up");
    }

  	move_base_msgs::MoveBaseGoal goal;

  	goal.target_pose.header.frame_id= "base_link";
	  goal.target_pose.header.stamp= ros::Time::now();

    double x= destination.position.z;
    double y= destination.position.x;
    double z= destination.position.y;
   //  double distance= sqrt(pow(x, 2)+pow(y, 2));
  	// goal.target_pose.pose.position.x= distance;

   //  double angle= atan2(y,x);
   //  std::cout << "Angle: "<<angle<<'\n';
   //  tf::Quaternion direction;
   //  direction.setRPY(0,0,0.8*angle);
   //  goal.target_pose.pose.orientation.w= direction.w();
  	// goal.target_pose.pose.orientation.x= direction.x();
  	// goal.target_pose.pose.orientation.y= direction.y();
  	// goal.target_pose.pose.orientation.z= direction.z();

   if(!markerFound)
    {
      // ROS_INFO("Sending goal");
      // _ac.sendGoal(goal);
      // _ac.waitForResult();
      // if(_ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
      // {
      //   ROS_INFO("Hooray, the base moved somewhere");
      //   markerFound= true;
      // }
      // else
      //   ROS_INFO("The base failed to move for some reason");

      // ofstream myfile;
      // myfile.open("location.txt");
      // myfile << "markerID: "<< markerID<<" (x, y, z)-> ("<<pose.position.x+ x<<", "<<pose.position.y+ y<<", "<<pose.position.z+ z<<")";
      // myfile << "currentPosition: "<< " (x, y, z)-> ("<< x <<", "<< y <<", "<< z <<")";
      // myfile << "positionRelAR: "<< " (x, y, z)-> ("<< pose.position.x <<", "<< pose.position.y <<", "<< pose.position.z <<")";
      //
      // myfile.close();
      // markerFound= true;
    }

  }

  geometry_msgs::Pose getLoc::getDest(geometry_msgs::Pose &pose)
  {
	   Eigen::MatrixXd p(3,1);
	   p(0,0)= pose.position.x;
	   p(1,0)= pose.position.y;
	   p(2,0)= pose.position.z;

	   Eigen::MatrixXd t(3,1);
	   t(0,0)= 0;
	   t(1,0)= 0;
	   t(2,0)= 0.5;
	   Eigen::Quaterniond rotation(pose.orientation.w, pose.orientation.x, pose.orientation.y, pose.orientation.z);

	   Eigen::MatrixXd rotated= rotation.matrix() * t;

	   Eigen::MatrixXd translated = rotated+p;

	   geometry_msgs::Pose pose2;

	   pose2.position.x= translated(0,0);
	   pose2.position.y= translated(1,0);
	   pose2.position.z= translated(2,0);

	   pose2.orientation.w= pose.orientation.w;
	   pose2.orientation.x= pose.orientation.x;
	   pose2.orientation.y= pose.orientation.y;
	   pose2.orientation.z= pose.orientation.z;

	   Eigen::Quaterniond p2(pose2.orientation.w, pose2.orientation.x, pose2.orientation.y, pose2.orientation.z);
	   Eigen::Quaterniond rotation180(0,1,0,0);

	   Eigen::Quaterniond newQ= p2 * rotation180;


	   pose2.orientation.w= newQ.w();
	   pose2.orientation.x= newQ.x();
	   pose2.orientation.y= newQ.y();
	   pose2.orientation.z= newQ.z();

	   return pose2;
  }

  bool getLoc::seenMarker()
  {
    return markerFound;
  }

  getLoc::~getLoc() {}

#include "arlocal/TFBroadcastPR.h"


TFBroadcastPR::TFBroadcastPR(std::string fromFrame, std::string toFrame) : _fromFrame(fromFrame), _toFrame(toFrame) {}

void TFBroadcastPR::receivePose(geometry_msgs::Pose &pose)
{
   tf::Transform tran;
   //(tf::Quaternion(pose.orientation.x,pose.orientation.y,pose.orientation.z,pose.orientation.w),tf::Vector3(pose.position.x,pose.position.y,pose.position.z))
   tran.setOrigin(tf::Vector3(pose.position.x, pose.position.y, pose.position.z));
   tran.setRotation(tf::Quaternion(pose.orientation.x, pose.orientation.y, pose.orientation.z, pose.orientation.w));
   _br.sendTransform(tf::StampedTransform(tran, ros::Time::now(),_fromFrame, _toFrame));
}

TFBroadcastPR::~TFBroadcastPR() {}


// static tf::TransformBroadcaster br;
//   11   tf::Transform transform;
//   12   transform.setOrigin( tf::Vector3(msg->x, msg->y, 0.0) );
//   13   tf::Quaternion q;
//   14   q.setRPY(0, 0, msg->theta);
//   15   transform.setRotation(q);
//   16   br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world", turtle_name));

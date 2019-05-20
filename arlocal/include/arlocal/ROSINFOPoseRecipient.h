#ifndef ROS_INFO_POSE_RECIPIENT_H
#define ROS_INFO_POSE_RECIPIENT_H

#include "PoseRecipient.h"

class ROSINFOPoseRecipient : public PoseRecipient {
public:
  geometry_msgs::Pose receivePose(geometry_msgs::Pose &pose);
  
};

#endif

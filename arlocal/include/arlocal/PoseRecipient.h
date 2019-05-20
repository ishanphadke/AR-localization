#ifndef POSE_RECIPIENT_H
#define POSE_RECIPIENT_H

#include <geometry_msgs/Pose.h>

class PoseRecipient {
public:
  virtual geometry_msgs::Pose receivePose(geometry_msgs::Pose &pose, int markerID) = 0;
};

#endif

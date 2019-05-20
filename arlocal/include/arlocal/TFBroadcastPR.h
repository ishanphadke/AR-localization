#ifndef TF_BROADCAST_PR_H
#define TF_BROADCAST_PR_H
#include "ros/ros.h"
#include <tf/transform_broadcaster.h>
#include "PoseRecipient.h"

class TFBroadcastPR : public PoseRecipient{
public:
  TFBroadcastPR(std::string fromFrame, std::string toFrame);
  void receivePose(geometry_msgs::Pose &pose);
  ~TFBroadcastPR();

protected:
  std::string _fromFrame;
  std::string _toFrame;
  tf::TransformBroadcaster _br;
};

#endif

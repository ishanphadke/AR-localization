#ifndef GET_LOC_H
#define GET_LOC_H

#include "PoseRecipient.h"

#include <tf/tf.h>
#include <tf/transform_listener.h>

#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <cmath>
#include <Eigen/Geometry>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

class getLoc : public PoseRecipient {
public:
  getLoc(tf::TransformListener &tfL, MoveBaseClient &ac);

  void receivePose(geometry_msgs::Pose &pose, int markerID);
  
  geometry_msgs::Pose markerPose getMarkerPose();
  
  int getMarkerID();

  bool seenMarker();

  ~getLoc();
protected:
  MoveBaseClient &_ac;
  tf::TransformListener &_tfL;
  bool markerFound;
  double x;
  double y;
  double z;
  geometry_msgs::Pose markerPose;
  int markerID;
};

#endif

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

  geometry_msgs::Pose receivePose(geometry_msgs::Pose &pose, int markerID);

  bool seenMarker();

  ~getLoc();
protected:
  MoveBaseClient &_ac;
  tf::TransformListener &_tfL;
  bool markerFound;
  double x;
  double y;
  double z;
};

#endif

#ifndef ALVAR_MARKER_H
#define ALVAR_MARKER_H

#include "arlocal/PoseRecipient.h"
#include "ros/ros.h"
#include <tf/tf.h>
#include <tf/transform_listener.h>
#include <visualization_msgs/Marker.h>

class AlvarMarker {
public:
  AlvarMarker(ros::NodeHandle &n, tf::TransformListener &tf_l
    , PoseRecipient &prIn, std::string fromFrame);

  void vis_cb(const visualization_msgs::Marker::ConstPtr& msg);

protected:
  tf::TransformListener &tfL;
  ros::Subscriber vis_sub;
  PoseRecipient &pr;
  std::string _fromFrame;
};


#endif

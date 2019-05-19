#include "arlocal/AlvarMarker.h"

AlvarMarker::AlvarMarker(ros::NodeHandle &n, tf::TransformListener &tf_l
    , PoseRecipient &prIn, std::string fromFrame) : tfL(tf_l), pr(prIn), _fromFrame(fromFrame) {
  //subscriber to get tag information
  vis_sub = n.subscribe("/visualization_marker", 1, &AlvarMarker::vis_cb, this);
}

void AlvarMarker::vis_cb(const visualization_msgs::Marker::ConstPtr& msg) {
  geometry_msgs::PoseStamped tag_pose;
  geometry_msgs::PoseStamped tag_rel_pose;

  try{
    tag_pose.header = msg->header;
    tag_pose.pose = msg->pose;
    tfL.waitForTransform(_fromFrame, tag_pose.header.frame_id, ros::Time(0), ros::Duration(4));
    tfL.transformPose(_fromFrame, tag_pose, tag_rel_pose);
    pr.receivePose(tag_rel_pose.pose, msg->id);
  } catch (tf::TransformException ex) {}
}

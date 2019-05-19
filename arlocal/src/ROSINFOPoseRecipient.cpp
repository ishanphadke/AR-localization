#include "arlocal/ROSINFOPoseRecipient.h"
#include "ros/ros.h"

void ROSINFOPoseRecipient::receivePose(geometry_msgs::Pose &pose) {
    ROS_INFO("POS:  %f %f %f"
    , pose.position.x
    , pose.position.y
    , pose.position.z);
}

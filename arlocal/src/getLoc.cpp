#include "arlocal/getLoc.h"
#include <fstream>
#include <iostream>

  getLoc::getLoc(tf::TransformListener &tfL, MoveBaseClient &ac) : _tfL(tfL), _ac(ac) {}

  geometry_msgs::Pose getLoc::receivePose(geometry_msgs::Pose &pose, int mID)
  {
    geometry_msgs::Pose markerPos= pose;
    markerFound= true;
    markerID= mID;
    markerPose= pose;
  }

  bool getLoc::seenMarker()
  {
    return markerFound;
  }

  getLoc::~getLoc() {}

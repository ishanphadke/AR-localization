#ifndef FRONTIER_EXPLORER_H
#define FRONTIER_EXPLORER_H

#include "ros/ros.h"
#include "arlocal/getLoc.h"
#include <move_base_msgs/MoveBaseAction.h>
#include <cmath>
#include <actionlib/client/simple_action_client.h>
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

class frontierExplorer {
public:
  frontierExplorer(tf::TransformListener &tfL, MoveBaseClient &ac);

  void move(getLoc alvarSeeker);

  ~frontierExplorer();
protected:
  MoveBaseClient &_ac;
  tf::TransformListener &_tfL;
};

#endif

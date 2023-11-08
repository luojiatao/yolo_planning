#include <ros/ros.h>
#include "line_detector_handle.hpp"

typedef ns_line_detector::LineDetectorHandle LineDetectorHandle;

int main(int argc, char **argv) {
  ros::init(argc, argv, "line_detector");
  ros::NodeHandle nodeHandle("~");
  LineDetectorHandle myLineDetectorHandle(nodeHandle);
  ros::Rate loop_rate(myLineDetectorHandle.getNodeRate());
  while (ros::ok()) {

    myLineDetectorHandle.run();

    ros::spinOnce();                // Keeps node alive basically
    loop_rate.sleep();              // Sleep for loop_rate
  }
  return 0;
}


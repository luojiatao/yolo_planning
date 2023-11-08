#ifndef LINE_DETECTOR_HPP
#define LINE_DETECTOR_HPP

#include "nav_msgs/Path.h"
#include "std_msgs/String.h"
#include "line_detector/BoundingBoxes.h"
#include "line_detector/BoundingBox.h"
#include <geometry_msgs/Twist.h>
namespace ns_line_detector {

class LineDetector {

public:
  // Constructor
  LineDetector(ros::NodeHandle& nh);

	// Getters
  // geometry_msgs::Point gettargetPoint();
  // geometry_msgs::Twist get_cmd();
  geometry_msgs::Twist create_target();
	// Setters
  void setyolo(line_detector::BoundingBoxes msgs);

  void runAlgorithm();

private:

	ros::NodeHandle& nh_;
	
  line_detector::BoundingBoxes detection_result;
  geometry_msgs::Point red_position, blue_position, target_point;
  geometry_msgs::Twist cmd;

  bool getPath = false;
  double path_length;
  double allow_angle_error;

  // void create_target();
  // geometry_msgs::Twist create_target();
};
}

#endif //LINE_DETECTOR_HPP

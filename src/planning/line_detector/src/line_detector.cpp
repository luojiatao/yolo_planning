#include <ros/ros.h>
#include "line_detector.hpp"
#include <geometry_msgs/Point.h> // Include the Point message
#include <sstream>
#include "line_detector/BoundingBoxes.h"
#include "line_detector/BoundingBox.h"
#include <geometry_msgs/Twist.h>
#include <cmath>

namespace ns_line_detector {

// Constructor
LineDetector::LineDetector(ros::NodeHandle &nh) : nh_(nh) {
  // getPath = false; // Initialize a variable to track whether we have a path
}

// Getters
// geometry_msgs::Point LineDetector::gettargetPoint() { return target_point; }
// geometry_msgs::Twist LineDetector::get_cmd() { return cmd; }

// Setters
void LineDetector::setyolo(line_detector::BoundingBoxes msgs) {
  detection_result = msgs; 
}

void LineDetector::runAlgorithm() {
  // if(!getPath)
  //   create_target();
  // else
  //   return;
  create_target();

}

geometry_msgs::Twist LineDetector::create_target() {

  if(detection_result.header.stamp.isZero()) {
  geometry_msgs::Twist cmd;
  cmd.angular.z = 0;
  return cmd;
}


  // 遍历红蓝两个检测框
  for(const auto& box : detection_result.bounding_boxes) {

  // 检查类别
  if(box.Class == "red") {
  
    // 计算红色目标的位置
    red_position.x = (box.xmax+box.xmin)/2;
    red_position.y = (box.ymax+box.ymin)/2;

  } else if (box.Class == "blue") {

    // 同理,计算蓝色目标的位置
    blue_position.x = (box.xmax+box.xmin)/2;
    blue_position.y = (box.ymax+box.ymin)/2;
  }
  }

  target_point.x = (red_position.x+blue_position.x)/2 - 320;
  target_point.y = 480 - (red_position.y+blue_position.y)/2;

  // ROS_INFO("目标坐标: %f,%f", target_point.x,target_point.y);
  std::cout << "目标坐标为: " << target_point.x << "," << target_point.y << std::endl;

  // 后续可以根据这个点来规划路径
  double hypotenuse = std::hypot(target_point.x, target_point.y);
  double angle = std::asin(target_point.x / hypotenuse);
  double angle1 = -angle;
  double angle2 = angle1 * 180 / M_PI; 

  // ROS_INFO("目标角度: %f", angle2);
  std::cout << "目标角度为: " << angle2 << " 度" << std::endl;
  // 创建Twist消息
  geometry_msgs::Twist cmd;

  // 将角度赋值给角速度
  
  cmd.angular.z = angle1;

  return cmd;

}

} // namespace ns_line_detector

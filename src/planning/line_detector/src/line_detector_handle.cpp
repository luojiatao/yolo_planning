#include <ros/ros.h>
#include "line_detector_handle.hpp"
#include "line_detector/BoundingBoxes.h"
#include "line_detector/BoundingBox.h"
#include <geometry_msgs/Twist.h>

namespace ns_line_detector {

// Constructor
LineDetectorHandle::LineDetectorHandle(ros::NodeHandle &nodeHandle) :
    nodeHandle_(nodeHandle),
    line_detector_(nodeHandle) {
  ROS_INFO("Constructing Handle");
  loadParameters();
  subscribeToTopics();
  publishToTopics();
}

// Getters
int LineDetectorHandle::getNodeRate() const { return node_rate_; }

// Methods
void LineDetectorHandle::loadParameters() {
  ROS_INFO("loading handle parameters");
  if (!nodeHandle_.param<std::string>("yolo_result_topic_name",
                                      yolo_result_topic_name_,
                                      "/darknet_ros/bounding_boxes")) {
    ROS_WARN_STREAM("Did not load yolo_result_topic_name. Standard value is: " << yolo_result_topic_name_);
  }
  // if (!nodeHandle_.param<std::string>("target_point_topic_name",
  //                                     target_point_topic_name_,
  //                                     "/planning/target_point")) {
  //   ROS_WARN_STREAM("Did not load target_point_topic_name. Standard value is: " << target_point_topic_name_);
  // }
   if (!nodeHandle_.param<std::string>("cmd_vel_topic_name",
                                      cmd_vel_topic_name_,
                                      "/cmd_vel")) {
    ROS_WARN_STREAM("Did not load cmd_vel_topic_name. Standard value is: " << cmd_vel_topic_name_);
  }
  if (!nodeHandle_.param("node_rate", node_rate_, 50)) {
    ROS_WARN_STREAM("Did not load node_rate. Standard value is: " << node_rate_);
  }
}

void LineDetectorHandle::subscribeToTopics() {
  ROS_INFO("subscribe to topics");
  yoloSubscriber_ = nodeHandle_.subscribe(yolo_result_topic_name_, 1, &LineDetectorHandle::yoloCallback, this);
}

void LineDetectorHandle::publishToTopics() {
  ROS_INFO("publish to topics");
  // targetPointPublisher_ = nodeHandle_.advertise<geometry_msgs::Point>(target_point_topic_name_, 1);
  twist_pub_ = nodeHandle_.advertise<geometry_msgs::Twist>(cmd_vel_topic_name_, 1);
}

void LineDetectorHandle::run() {
	line_detector_.runAlgorithm();
  sendMsg();
}

void LineDetectorHandle::sendMsg() {
  // targetPointPublisher_.publish(line_detector_.gettargetPoint());
  twist_pub_.publish(line_detector_.create_target());
}

void LineDetectorHandle::yoloCallback(const line_detector::BoundingBoxes &msg) {
  line_detector_.setyolo(msg);
}

}
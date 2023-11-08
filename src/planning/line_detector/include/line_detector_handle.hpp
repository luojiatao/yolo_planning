#ifndef LINE_DETECTOR_HANDLE_HPP
#define LINE_DETECTOR_HANDLE_HPP

#include "line_detector.hpp"
#include "line_detector/BoundingBoxes.h"
#include "line_detector/BoundingBox.h"
namespace ns_line_detector {

class LineDetectorHandle {

 public:
  // Constructor
  LineDetectorHandle(ros::NodeHandle &nodeHandle);

//  // Getters
  int getNodeRate() const;

  // Methods
  void loadParameters();
  void subscribeToTopics();
  void publishToTopics();
  void run();
  void sendMsg();

 private:
  ros::NodeHandle nodeHandle_;
  ros::Subscriber yoloSubscriber_;
  ros::Publisher targetPointPublisher_;
  ros::Publisher twist_pub_; 

  void yoloCallback(const line_detector::BoundingBoxes &msg);

  std::string yolo_result_topic_name_;
  // std::string target_point_topic_name_;
  std::string cmd_vel_topic_name_;

  int node_rate_;

  LineDetector line_detector_;

};
}

#endif //LINE_DETECTOR_HANDLE_HPP

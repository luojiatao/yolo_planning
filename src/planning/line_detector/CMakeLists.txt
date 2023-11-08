cmake_minimum_required(VERSION 2.8.3)
project(line_detector)

set(CMAKE_BUILD_TYPE "Release")
add_compile_options(-std=c++11)

set(PROJECT_DEPS
  roscpp
  std_msgs
  )

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  geometry_msgs
  message_generation
  )
## 配置 msg 源文件
add_message_files(
  FILES
  BoundingBox.msg
  BoundingBoxes.msg
)

# 生成消息时依赖于 std_msgs
generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
  INCLUDE_DIRS
  LIBRARIES
  CATKIN_DEPENDS
  DEPENDS
  roscpp 
  rospy 
  std_msgs 
  message_runtime
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${roscpp_INCLUDE_DIRS}
)

# Each node in the package must be declared like this
add_executable(${PROJECT_NAME}
  src/line_detector_handle.cpp
  src/line_detector.cpp
  src/main.cpp
  )
target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
  )

  #这儿是为了避免先编译cpp文件时，cpp文件中使用了自定义的消息类型还未编译。导致编译失败
add_dependencies(line_detector ${PROJECT_NAME}_generate_messages_cpp)
add_dependencies(line_detector ${PROJECT_NAME}_generate_messages_cpp)
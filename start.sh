#!/bin/bash

gnome-terminal --tab -- bash -c "\
source devel/setup.bash; \
roslaunch line_detector line_detector.launch; \
exec bash"

sleep 3s  

gnome-terminal --tab -- bash -c "\
source devel/setup.bash; \
roslaunch darknet_ros fsac_darknet_ros.launch; \
exec bash"

# 两个roslauch之间需要间隔一段时间，否则会相互抢占roscore

echo “successfully started!”

#include <stdio.h>
#include "/u/mansi/catkin_ws/src/opencv_hw/include/opencv_hw/ROSInterface.h"
#include <ros/ros.h>
#include "/u/mansi/catkin_ws/src/opencv_hw/include/opencv_hw/ColorFilter.h"

int main(int argc, char **argv) {
    ros::init(argc, argv, "opencv_hw");
    ros::NodeHandle handle; 
    ColorFilter cf;
    ROSInterface ri(cf, handle);
    ros::spin();
    return 0;
}
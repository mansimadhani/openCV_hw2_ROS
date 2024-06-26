#ifndef ROS_INTERFACE_H
#define ROS_INTERFACE_H

#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include "ColorFilter.h"
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>

#include <string>
#include <vector>

using namespace std;

class ROSInterface {

protected:
    ros::NodeHandle nh;
    ColorFilter  &_filter;
    image_transport::ImageTransport it;
    image_transport::Publisher bluePub;
    image_transport::Publisher greenPub;
    image_transport::Publisher redPub;
    image_transport::Publisher bgrPub;
    image_transport::Subscriber sub;

public:
    ROSInterface(ColorFilter &cf, ros::NodeHandle &handle);
    void imageCallBack(const sensor_msgs::ImageConstPtr& msg);
};

#endif
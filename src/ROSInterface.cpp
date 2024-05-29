// Use the image_transport classes instead.
#include <ros/ros.h>
#include <image_transport/image_transport.h>

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
  // ...
}

ros::NodeHandle nh;
image_transport::ImageTransport it(nh);

image_transport::Subscriber sub = it.subscribe("in_image_base_topic", 1, imageCallback);

image_transport::Publisher pub = it.advertise("blue", 1);
image_transport::Publisher pub = it.advertise("green", 1);
image_transport::Publisher pub = it.advertise("red", 1);
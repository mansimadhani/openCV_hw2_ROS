#include "ROSInterface.h"

ROSInterface::ROSInterface(ColorFilter *cf) {
  _filter = *cf;
  image_transport::ImageTransport it(nh);

  //advertise output topics
  bluePub = it.advertise("/color_filter/blue_cup", 1);
  greenPub = it.advertise("/color_filter/green_cup", 1);
  redPub = it.advertise("/color_filter/red_cup", 1);
  bgrPub = it.advertise("/color_filter/cups", 1);


  //subscribe to input topic
  sub = it.subscribe("/kinect2/hd/image_-color", 1, imageCallback);
}

void ROSInterface::imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
  
  cv_bridge::CvImagePtr img_ptr = toCvCopy(msg, const std::string& encoding = std::string());

  
  _filter.processImage(_img);

  cv::Mat _blue = _filter.getBlueImage();
  cv::Mat _green = _filter.getGreenImage();
  cv::Mat _red = _filter.getRedImage();
  cv::Mat _bgr = _filter.getBGRImage();

  cv_bridge::CvImage img_bridge;
  sensor_msgs::Image blue_msg;
  sensor_msgs::Image green_msg;
  sensor_msgs::Image red_msg;
  sensor_msgs::Image bgr_msg;
  
}


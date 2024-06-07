#include "/u/mansi/catkin_ws/src/opencv_hw/include/opencv_hw/ROSInterface.h"

ROSInterface::ROSInterface(ColorFilter &cf, ros::NodeHandle &handle) : _filter(cf), nh(handle), it(nh) {
  
  //image_transport::ImageTransport it(nh);

  //advertise output topics
  bluePub = it.advertise("blue", 1);
  greenPub = it.advertise("green", 1);
  redPub = it.advertise("red", 1);
  bgrPub = it.advertise("bgr", 1);


  //subscribe to input topic
  sub = it.subscribe("/kinect2/hd/image_color", 1, &ROSInterface::imageCallBack, this);
}

void ROSInterface::imageCallBack(const sensor_msgs::ImageConstPtr& msg)
{
  try {
    cv_bridge::CvImagePtr img_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
  //not sure if this works
  //cv::Mat _img = Mat(const IplImage *img_ptr, bool copyData = false);

  _filter.processImage(img_ptr->image);

  sensor_msgs::ImagePtr blue_ptr;
 sensor_msgs::ImagePtr green_ptr;
 sensor_msgs::ImagePtr red_ptr;
 sensor_msgs::ImagePtr bgr_ptr;

   
  blue_ptr = cv_bridge::CvImage(std_msgs::Header(), "mono8", _filter.getBlueImage()).toImageMsg();
  bluePub.publish(blue_ptr);
  green_ptr = cv_bridge::CvImage(std_msgs::Header(), "mono8", _filter.getGreenImage()).toImageMsg();
  greenPub.publish(green_ptr);
  red_ptr = cv_bridge::CvImage(std_msgs::Header(), "mono8", _filter.getRedImage()).toImageMsg();
  redPub.publish(red_ptr);
  bgr_ptr = cv_bridge::CvImage(std_msgs::Header(), "bgr8", _filter.getBGRImage()).toImageMsg();
  bgrPub.publish(bgr_ptr);
  } catch (cv_bridge::Exception& e){
    ROS_ERROR("could not convert from %s to bgr8", msg->encoding.c_str());
  }
  
  


}


#include <stdio.h>
#include "ROSInterface.h"

int main(int argc, char **argv) {
    ros::init();
    ColorFilter *cf = new ColorFilter();
    ROSInterface *ri = new ROSInterface(cf);
    ros::spin();
}
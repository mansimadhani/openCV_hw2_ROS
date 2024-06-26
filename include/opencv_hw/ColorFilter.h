#ifndef COLOR_FILTER_H
#define COLOR_FILTER_H

#include <opencv2/opencv.hpp>

#include <string>
#include <vector>

class ColorFilter {
protected:
    cv::Mat _frame;
    std::vector<cv::Mat> _chans;

    //variables added to store masks
    cv::Mat _blueMask;
    cv::Mat _greenMask;
    cv::Mat _redMask;

public:
    void processImage(cv::Mat img);

    void split();

    void findBlue();
    void findGreen();
    void findRed();
    void findBGR();

    cv::Mat getBlueImage();
    cv::Mat getGreenImage();
    cv::Mat getRedImage();
    cv::Mat getBGRImage();
    cv::Mat getMask(int c1, int c2);

    void showResult();
};

#endif
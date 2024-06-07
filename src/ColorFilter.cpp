#include "/u/mansi/catkin_ws/src/opencv_hw/include/opencv_hw/ColorFilter.h"

using namespace std;
using namespace cv;

void ColorFilter::processImage(cv::Mat img) {
    _frame = img;
    split();
    findBlue();
    findGreen();
    findRed();
    findBGR();
    showResult();
}

void ColorFilter::split() {
    cv::split(_frame, _chans);
}

void ColorFilter::showResult() {

    //PROBLEM 1
    //imshow("result", _frame);


    //PROBLEM 2: B
    //imshow("blue", _chans[0]);

    //PROBLEM 2: G
    //imshow("green", _chans[1]);

    //PROBLEM 2: R
    //imshow("red", _chans[2]);


    //PROBLEM 3: Blue Subtraction
    //imshow("blue subtraction", _chans[0]);

    //PROBLEM 3: Blue Threshold
    //imshow("blue threshold", _chans[0]);

    //PROBLEM 3: Largest Blue Blob
    //imshow("largest blue blob", _chans[0]);

    //PROBLEM 3: Blue Cup
    //imshow("blue cup", _chans[0]);


    //PROBLEM 4: Green Subtraction
    //imshow("green subtraction", _chans[1]);

    //PROBLEM 4: Green Threshold
    //imshow("green threshold", _chans[1]);

    ////PROBLEM 4: Largest Green Blob
    //imshow("largest green blob", _chans[1]);

    //PROBLEM 4: Green Cup
    //imshow("green cup", _chans[1]);


    //PROBLEM 5: Red Subtraction
    //imshow("red subtraction", _chans[2]);

    //PROBLEM 5: Red Threshold
    //imshow("red threshold", _chans[2]);

    ////PROBLEM 5: Largest Red Blob
    //imshow("largest red blob", _chans[2]);

    //PROBLEM 5: Red Cup
    //imshow("red cup", _chans[2]);
    

    //PROBLEM 6: ALL THREE
    //imshow("all three", _chans[0]);
    //waitKey(100);
}

void ColorFilter::findBlue() {
    //4.3.1
    subtract(_chans[0], _chans[2], _chans[0]); //bMinusR

    //4.3.2
    threshold(_chans[0], _chans[0], 50, 255, cv::THRESH_BINARY);

    //4.3.3
    vector<vector<cv::Point>> contours;
    vector<cv::Vec4i> hierarchy;
    findContours(_chans[0], contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);
    int highest = 0;

    for (int i = 0; i < contours.size(); i++) {
        if (contourArea(contours[i]) > contourArea(contours[highest])) {
            highest = i;
        }
    }
    _blueMask = cv::Mat::zeros(_frame.size(), CV_8UC1);
    drawContours(_blueMask, contours, highest, cv::Scalar(255), cv::FILLED, 8, hierarchy);
    
    //display blue cup
    copyTo(_frame, _chans[0], _blueMask);

    split(); 
    
}

void ColorFilter::findGreen() {
    subtract(_chans[1], _chans[0], _chans[1]); //gMinusB

    threshold(_chans[1], _chans[1], 50, 255, cv::THRESH_BINARY);

    vector<vector<cv::Point>> contours;
    vector<cv::Vec4i> hierarchy;
    findContours(_chans[1], contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);
    int highest = 0;

    for (int i = 0; i < contours.size(); i++) {
        if (contourArea(contours[i]) > contourArea(contours[highest])) {
            highest = i;
        }
    }
    _greenMask = cv::Mat::zeros(_frame.size(), CV_8UC1);
    drawContours(_greenMask, contours, highest, cv::Scalar(255), cv::FILLED, 8, hierarchy);

    //display green cup
    copyTo(_frame, _chans[1], _greenMask);

    split();

}

void ColorFilter::findRed() {
    
    subtract(_chans[2], _chans[1], _chans[2]); //rMinusG

    threshold(_chans[2], _chans[2], 50, 255, cv::THRESH_BINARY);

    vector<vector<cv::Point>> contours;
    vector<cv::Vec4i> hierarchy;
    findContours(_chans[2], contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
    int highest = 0;

    for (int i = 0; i < contours.size(); i++) {
        if (contourArea(contours[i]) > contourArea(contours[highest])) {
            highest = i;
        }
    }
    _redMask = cv::Mat::zeros(_frame.size(), CV_8UC1);
    drawContours(_redMask, contours, highest, cv::Scalar(255), cv::FILLED, 8, hierarchy);

    //display red cup
    copyTo(_frame, _chans[2], _redMask);

    split();
}

void ColorFilter::findBGR() {
    cv::Mat _finalMask = cv::Mat::zeros(_frame.size(), CV_8UC1);
    cv::Mat _bMask = getMask(0, 2);
    cv::Mat _gMask = getMask(1, 0);
    cv::Mat _rMask = getMask(2, 1);
    cv::bitwise_or(_bMask, _gMask, _finalMask);
    cv::bitwise_or(_finalMask, _rMask, _finalMask);
    copyTo(_frame, _chans[0], _finalMask);

}

cv::Mat ColorFilter::getBlueImage() {
    cv::Mat _bMask = getMask(0, 2);
    cv::Mat _blueImg = cv::Mat::zeros(_frame.size(), CV_8UC1);
    copyTo(_frame, _blueImg, _bMask);
    return _blueImg;
}

cv::Mat ColorFilter::getGreenImage() {
    cv::Mat _gMask = getMask(1, 0);
    cv::Mat _greenImg = cv::Mat::zeros(_frame.size(), CV_8UC1);
    copyTo(_frame, _greenImg, _gMask);
    return _greenImg;
}

cv::Mat ColorFilter::getRedImage() {
    cv::Mat _rMask = getMask(2, 1);
    cv::Mat _redImg = cv::Mat::zeros(_frame.size(), CV_8UC1);
    copyTo(_frame, _redImg, _rMask);
    return _redImg;
}

cv::Mat ColorFilter::getBGRImage() {
    cv:Mat _bgrImage = cv::Mat::zeros(_frame.size(), CV_8UC1);
    cv::Mat _finalMask = cv::Mat::zeros(_frame.size(), CV_8UC1);
    cv::Mat _bMask = getMask(0, 2);
    cv::Mat _gMask = getMask(1, 0);
    cv::Mat _rMask = getMask(2, 1);
    cv::bitwise_or(_bMask, _gMask, _finalMask);
    cv::bitwise_or(_finalMask, _rMask, _finalMask);
    copyTo(_frame, _bgrImage, _finalMask);
    return _bgrImage;
}

cv::Mat ColorFilter::getMask(int c1, int c2) {
    subtract(_chans[c1], _chans[c2], _chans[c1]); //bMinusR

    //4.3.2
    threshold(_chans[c1], _chans[c1], 50, 255, cv::THRESH_BINARY);

    //4.3.3
    vector<vector<cv::Point>> contours;
    vector<cv::Vec4i> hierarchy;
    findContours(_chans[c1], contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
    int highest = 0;

    for (int i = 0; i < contours.size(); i++) {
        if (contourArea(contours[i]) > contourArea(contours[highest])) {
            highest = i;
        }
    }
    cv::Mat _Mask = cv::Mat::zeros(_frame.size(), CV_8UC1);
    drawContours(_Mask, contours, highest, cv::Scalar(255), cv::FILLED, 8, hierarchy);
    
    //display blue cup
    //copyTo(_frame, _chans[c1], _Mask);

    split();  
    return _Mask;
}
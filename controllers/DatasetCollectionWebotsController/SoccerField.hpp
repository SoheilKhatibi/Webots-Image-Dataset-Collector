#ifndef SOCCERFIELD_HPP
#define SOCCERFIELD_HPP

#include <opencv2/opencv.hpp>

class SoccerField {
public:
    SoccerField();
    cv::Mat fieldMat;
    cv::Mat drawField();
    cv::Point pointOnField2Pixel(cv::Point2f pointOnCourtMeter);
};

#endif // SOCCERFIELD_HPP

#ifndef DATASETCOLLECTOR_HPP
#define DATASETCOLLECTOR_HPP

#include <opencv2/opencv.hpp>

#include "SoccerField.hpp"

class DatasetCollector {
public:
    DatasetCollector();
    SoccerField soccerField;
    cv::Mat baseFigure, figure;
};

#endif // DATASETCOLLECTOR_HPP

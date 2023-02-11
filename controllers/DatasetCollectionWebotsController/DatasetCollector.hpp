#ifndef DATASETCOLLECTOR_HPP
#define DATASETCOLLECTOR_HPP

#include <opencv2/opencv.hpp>

#include "SoccerField.hpp"
#include "Node.hpp"

class DatasetCollector {
public:
    DatasetCollector();
    SoccerField soccerField;
    // std::vector<SoccerBall> soccerBalls;
    std::vector<DatasetCollection::Node> capturers;
    std::vector<DatasetCollection::Node> balls;
    cv::Mat baseFigure, figure;
    void addCapturerRobot(DatasetCollection::Node robot);
    void addBall(DatasetCollection::Node ball);
    void illustrateCapturersInfo();
    void rePoseObjects();
    void drawCapturers();
    // void drawRobots();
    // void update();
    // void drawRobotFOVs();
    // void drawBalls();
    // void drawScaleOverviewer();
    // void addBall(float x, float y);  // will add a ball to the court
    // void deleteAllBalls();  // will delete all balls from the court
    // void addRobot(float x, float y, float theta); // will add a robot to the court
    // void deleteAllRobots(); // will delete all robots from the court
};

#endif // DATASETCOLLECTOR_HPP

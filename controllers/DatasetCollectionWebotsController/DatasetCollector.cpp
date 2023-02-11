#include "DatasetCollector.hpp"

DatasetCollector::DatasetCollector() {
    baseFigure = soccerField.fieldMat.clone();

    // Create directory for images
    std::string stringpath = "../../Pics/";
    mkdir(stringpath.c_str(), 0777);

    imgCount = 0;
}

void DatasetCollector::addCapturerRobot(DatasetCollection::Node robot) {
    capturers.push_back(robot);
}

void DatasetCollector::addBall(DatasetCollection::Node ball) {
    balls.push_back(ball);
}

void DatasetCollector::illustrateCapturersInfo() {
    int i = 0;
    for (auto &capturer : capturers) {
        const double *trans = capturer.getPosition();
        std::cout << "MY_ROBOT is at position: " << trans[0] << ' '
                    << trans[1] << ' ' << trans[2] << std::endl;
        capturer.getRotation();
        const double *rot = capturer.getRotation();
        std::cout << "MY_ROBOT is at rotation: "
                    << rot[2] * rot[3] << std::endl;
        //           << rot[0] << ' ' << rot[1] << ' ' << rot[2] << ' ' << rot[3] << std::endl;

        // Get and show robot image
        cv::imshow("capturer " + std::to_string(i), capturers[0].getImage());

        // Draw robot on field
        figure = baseFigure.clone();
        drawCapturers();
        cv::imshow("Field", figure);
    }
    cv::waitKey(1);
}

void DatasetCollector::rePoseObjects() {
    for (auto &capturer : capturers) {
        capturer.rePose();
    }

    for (auto &ball : balls) {
        ball.rePose();
    }
}

void DatasetCollector::drawCapturers() {
    for (auto &capturer : capturers) {
        const double *robotPose = capturer.getPosition();
        const double *robotRot = capturer.getRotation();
        cv::Point robotPixels = soccerField.pointOnField2Pixel(cv::Point2f(robotPose[0], robotPose[1]));

        // putText(figure, std::to_string(robotPose[0]), cv::Point(20, 20), 1, 1, cv::Scalar(0, 0, 0), 1);
        // putText(figure, std::to_string(robotPose[1]), cv::Point(20, 40), 1, 1, cv::Scalar(0, 0, 0), 1);
        // // putText(figure, std::to_string(simulationTime), cv::Point(20, 60), 1, 1, cv::Scalar(0, 0, 0), 1);
        cv::circle(figure, cv::Point(robotPixels.x, robotPixels.y), 13, cv::Scalar(0, 0, 255), 0.2 * 5);
        double r = 25;
        double x = r * cos(robotRot[2] * robotRot[3]);
        double y = r * sin(robotRot[2] * robotRot[3]);
        cv::line(figure, cv::Point(robotPixels.x, robotPixels.y), cv::Point(robotPixels.x - x, robotPixels.y + y), cv::Scalar(0, 0, 255), 0.5 * 5);
    }
}

bool DatasetCollector::shouldImageBeSaved() {
    int objectNumber = capturers[0].wb_cam->getRecognitionNumberOfObjects();
    for (int j = 0; j < objectNumber; j++){
        if (capturers[0].wb_cam->getRecognitionObjects()[j].id == balls[0].wb_node->getId()) {
            // if (isBallSizeValid(cam->getRecognitionObjects()[j])) {
            return true;
            // }
        }
    }
    return false;
}

void DatasetCollector::saveImage() {
    // capturers[0].wb_cam->saveRecognitionSegmentationImage("../../Pics/Image" + std::to_string(k) + "_mask.png", 100);
    capturers[0].wb_cam->saveImage("../../Pics/Image" + std::to_string(imgCount) + ".jpeg", 100);
    imgCount++;
}

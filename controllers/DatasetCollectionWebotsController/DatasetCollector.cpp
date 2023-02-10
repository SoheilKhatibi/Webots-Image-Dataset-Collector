#include "DatasetCollector.hpp"

DatasetCollector::DatasetCollector() {
    baseFigure = soccerField.fieldMat.clone();
}

void DatasetCollector::addCapturerRobot(DatasetCollection::Robot robot) {
    capturers.push_back(robot);
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
    }
    cv::waitKey(1);
}

void DatasetCollector::rePoseObjects() {
    for (auto &capturer : capturers) {
        capturer.rePose();
    }
}

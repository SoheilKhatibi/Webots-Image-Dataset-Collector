#include "DatasetCollector.hpp"

DatasetCollector::DatasetCollector() {
    baseFigure = soccerField.fieldMat.clone();
}

void DatasetCollector::addRobot(DatasetCollection::Robot robot) {
    robots.push_back(robot);
}

#include "Robot.hpp"

// using namespace DatasetCollection;

DatasetCollection::Robot::Robot() {

}

DatasetCollection::Robot::Robot(webots::Node *node) {
    setNode(node);
}

DatasetCollection::Robot::Robot(webots::Node *node, webots::Camera *cam) {
    setNode(node);
    setCamera(cam);
}

void DatasetCollection::Robot::setCamera(webots::Camera *cam) {
    wb_cam = cam;
}

void DatasetCollection::Robot::setNode(webots::Node *node) {
    wb_node = node;
}

cv::Mat DatasetCollection::Robot::getImage() {
    // Get and show robot image
    cv::Mat image(wb_cam->getHeight(), wb_cam->getWidth(), CV_8UC3);
    uint8_t* bgra = (uint8_t *) wb_cam->getImage();
    // bgra = (uint8_t *) cam->getRecognitionSegmentationImage();
    for (int i = 0; i < wb_cam->getHeight(); i++) {
        for (int j = 0; j < wb_cam->getWidth(); j++) {
            image.at<cv::Vec3b>(i, j)[0] = *bgra++;
            image.at<cv::Vec3b>(i, j)[1] = *bgra++;
            image.at<cv::Vec3b>(i, j)[2] = *bgra++;
            bgra++;
        }
    }
    // cv::imshow("preview", image);
    // cv::waitKey(0);
    return image;
}

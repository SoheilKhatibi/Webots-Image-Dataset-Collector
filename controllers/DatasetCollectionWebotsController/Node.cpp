#include "Node.hpp"

// using namespace DatasetCollection;

DatasetCollection::Node::Node() {

}

DatasetCollection::Node::Node(webots::Node *node) {
    setNode(node);
}

DatasetCollection::Node::Node(webots::Node *node, float bpHeight) {
    setNode(node);
    setOnFloorBasePointHeight(bpHeight);
}

DatasetCollection::Node::Node(webots::Node *node, webots::Camera *cam) {
    setNode(node);
    setCamera(cam);
}

DatasetCollection::Node::Node(webots::Node *node, webots::Camera *cam, float bpHeight) {
    setNode(node);
    setCamera(cam);
    setOnFloorBasePointHeight(bpHeight);
}

void DatasetCollection::Node::setCamera(webots::Camera *cam) {
    wb_cam = cam;
}

void DatasetCollection::Node::setNode(webots::Node *node) {
    wb_node = node;
}

void DatasetCollection::Node::setOnFloorBasePointHeight(float bpHeight) {
    onFloorBasePointHeight = bpHeight;
}

cv::Mat DatasetCollection::Node::getImage() {
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

void DatasetCollection::Node::rePose() {
    double randx, randy;
    double randrot;
    randx = ((double)rand()) / RAND_MAX * 9 - 4.5;
    randy = ((double)rand()) / RAND_MAX * 6 - 3;
    randrot = ((double)rand()) / RAND_MAX * (2 * M_PI);
    double translation[3] = {randx , randy , onFloorBasePointHeight};

    cv::Vec3f euler;
    euler[0] = 0.0;
    euler[1] = 0.0;
    euler[2] = randrot;
    double rotation[4];
    calculateRotationFromEulerAngles(euler, rotation);

    wb_node->getField("translation")->setSFVec3f(translation);
    wb_node->getField("rotation")->setSFRotation(rotation);

    // reset robot physics
    wb_node->resetPhysics();
}

const double *DatasetCollection::Node::getPosition() {
    return wb_node->getField("translation")->getSFVec3f();
}

const double *DatasetCollection::Node::getRotation() {
    return wb_node->getField("rotation")->getSFRotation();
}

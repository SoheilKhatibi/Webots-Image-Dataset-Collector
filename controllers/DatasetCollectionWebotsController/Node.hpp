#ifndef DATASETCOLLECTION_NODE_HPP
#define DATASETCOLLECTION_NODE_HPP

#include <opencv2/opencv.hpp>
#include <webots/Node.hpp>
#include <webots/Camera.hpp>

#include "Utils.hpp"

namespace DatasetCollection {
    class Node {
    public:
        Node();
        Node(webots::Node *node);
        Node(webots::Node *node, float bpHeight);
        Node(webots::Node *node, webots::Camera *cam);
        Node(webots::Node *node, webots::Camera *cam, float bpHeight);
        void setCamera(webots::Camera *cam);
        void setNode(webots::Node *node);
        void setOnFloorBasePointHeight(float bpHeight);
        cv::Mat getImage();
        cv::Mat getRecognitionSegmentationImage();
        void rePose();
        const double *getPosition();
        const double *getRotation();
        webots::Node *wb_node;
        webots::Camera *wb_cam;
        float onFloorBasePointHeight;
    };
}

#endif // DATASETCOLLECTION_NODE_HPP

#ifndef DATASETCOLLECTION_ROBOT_HPP
#define DATASETCOLLECTION_ROBOT_HPP

#include <opencv2/opencv.hpp>
#include <webots/Node.hpp>
#include <webots/Camera.hpp>

#include "Utils.hpp"

namespace DatasetCollection {
    class Robot {
    public:
        Robot();
        Robot(webots::Node *node);
        Robot(webots::Node *node, webots::Camera *cam);
        void setCamera(webots::Camera *cam);
        void setNode(webots::Node *node);
        cv::Mat getImage();
        void rePose();
        const double *getPosition();
        const double *getRotation();
        webots::Node *wb_node;
        webots::Camera *wb_cam;
    };
}

#endif // DATASETCOLLECTION_ROBOT_HPP

#ifndef DATASETCOLLECTION_ROBOT_HPP
#define DATASETCOLLECTION_ROBOT_HPP

#include <opencv2/opencv.hpp>
#include <webots/Node.hpp>
#include <webots/Camera.hpp>

namespace DatasetCollection {
    class Robot {
    public:
        Robot();
        Robot(webots::Node *node);
        Robot(webots::Node *node, webots::Camera *cam);
        void setCamera(webots::Camera *cam);
        void setNode(webots::Node *node);
        cv::Mat getImage();
        webots::Node *wb_node;
        webots::Camera *wb_cam;
    };
}

#endif // DATASETCOLLECTION_ROBOT_HPP

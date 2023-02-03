#include <webots/Robot.hpp>
#include <webots/Supervisor.hpp>
#include <webots/Camera.hpp>

// OpenCV
#include <opencv2/opencv.hpp>


#include "DatasetCollector.hpp"


int main(int argc, char **argv) {
    srand (time(NULL));
    DatasetCollector datasetCollector;
    // create the Supervisor instance.
    webots::Supervisor *supervisor = new webots::Supervisor();

    // get the time step of the current world.
    int timeStep = (int)supervisor->getBasicTimeStep();

    webots::Node *robot_node = supervisor->getFromDef("MY_ROBOT");
    if (robot_node == NULL) {
        std::cerr << "No DEF MY_ROBOT node found in the current world file" << std::endl;
        exit(1);
    }
    webots::Field *trans_field = robot_node->getField("translation");

    // Get and enable Camera
    webots::Camera *cam = supervisor->getCamera("Camera");
    cam->enable(timeStep);

    int simulationTime = 0;
    while (supervisor->step(timeStep) != -1) {
        simulationTime += timeStep;
        std::cout << "simulation time: " << simulationTime << std::endl;

        const double *values = trans_field->getSFVec3f();
        std::cout << "MY_ROBOT is at position: " << values[0] << ' '
                  << values[1] << ' ' << values[2] << std::endl;

        // Get and show robot image
        cv::Mat image(cam->getHeight(), cam->getWidth(), CV_8UC3);
        uint8_t* bgra = (uint8_t *) cam->getImage();
        // bgra = (uint8_t *) cam->getRecognitionSegmentationImage();
        for (int i = 0; i < cam->getHeight(); i++) {
            for (int j = 0; j < cam->getWidth(); j++) {
                image.at<cv::Vec3b>(i, j)[0] = *bgra++;
                image.at<cv::Vec3b>(i, j)[1] = *bgra++;
                image.at<cv::Vec3b>(i, j)[2] = *bgra++;
                bgra++;
            }
        }
        cv::imshow("preview", image);
        cv::waitKey(0);


        // Reposition robot
        double randx, randy;
        // double randrot;
        randx = ((double)rand()) / RAND_MAX * 9 - 4.5;
        randy = ((double)rand()) / RAND_MAX * 6 - 3;
        // randrot = ((double)rand()) / RAND_MAX * 6.283185;

        const double INITIAL[3] = {randx, randy, 0.279};
        trans_field->setSFVec3f(INITIAL);

        // reset robot physics
        robot_node->resetPhysics();

    };

    delete supervisor;
    return 0;
}

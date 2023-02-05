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


    // Get robot node
    webots::Node *robot_node = supervisor->getFromDef("MY_ROBOT");
    if (robot_node == NULL) {
        std::cerr << "No DEF MY_ROBOT node found in the current world file" << std::endl;
        exit(1);
    }
    webots::Field *trans_field = robot_node->getField("translation");
    webots::Field *rot_field = robot_node->getField("rotation");

    // Get and enable Camera
    webots::Camera *cam = supervisor->getCamera("Camera");
    cam->enable(timeStep);

    // Add robot to datasetCollector
    DatasetCollection::Robot robot(robot_node, cam);
    datasetCollector.addRobot(robot);

    int simulationTime = 0;
    while (supervisor->step(timeStep) != -1) {
        simulationTime += timeStep;
        std::cout << "simulation time: " << simulationTime << std::endl;

        const double *trans = trans_field->getSFVec3f();
        std::cout << "MY_ROBOT is at position: " << trans[0] << ' '
                  << trans[1] << ' ' << trans[2] << std::endl;

        const double *rot = rot_field->getSFRotation();
        std::cout << "MY_ROBOT is at rotation: "
                  << rot[2] * rot[3] << std::endl;
        //           << rot[0] << ' ' << rot[1] << ' ' << rot[2] << ' ' << rot[3] << std::endl;

        // Get and show robot image
        cv::imshow("preview", datasetCollector.robots[0].getImage());
        cv::waitKey(1);

        // Reposition robot
        datasetCollector.robots[0].rePose();
    };

    delete supervisor;
    return 0;
}

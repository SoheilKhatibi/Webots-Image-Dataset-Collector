// Webots headers
#include <webots/Robot.hpp>
#include <webots/Supervisor.hpp>
#include <webots/Camera.hpp>

//External headers
// OpenCV
#include <opencv2/opencv.hpp>

// Local headers
#include "DatasetCollector.hpp"


int main(int argc, char **argv) {
    srand (time(NULL));
    DatasetCollector datasetCollector;
    // create the Supervisor instance.
    webots::Supervisor *supervisor = new webots::Supervisor();

    // get the time step of the current world.
    int timeStep = (int)supervisor->getBasicTimeStep();


    // Get robot node
    webots::Node *robot_node = supervisor->getFromDef("capturer");
    if (robot_node == NULL) {
        std::cerr << "No DEF of your robot node found in the current world file" << std::endl;
        exit(1);
    }

    // Get camera name and raise error if no camera is found
    std::string cameraName = "";
    int n_devices = supervisor->getNumberOfDevices();
    for (int i = 0; i < n_devices; i++) {
        webots::Device *dev = supervisor->getDeviceByIndex(i);

        const std::string name = dev->getName();
        int type = dev->getNodeType();

        if (type == webots::Node::CAMERA) {
            cameraName = name;
            break;
        }
    }
    if (cameraName == "") {
        std::cerr << "No cameras found in the robot" << std::endl;
        exit(1);
    }

    // Get and enable Camera
    webots::Camera *cam = supervisor->getCamera(cameraName);
    cam->enable(timeStep);
    cam->recognitionEnable(timeStep);

    // Add robot to datasetCollector
    DatasetCollection::Node robot(robot_node, cam);
    datasetCollector.addCapturerRobot(robot);

    int simulationTime = 0;
    while (supervisor->step(timeStep) != -1) {
        simulationTime += timeStep;
        std::cout << "simulation time: " << simulationTime << std::endl;

        datasetCollector.illustrateCapturersInfo();

        // Reposition the objects in th field
        datasetCollector.rePoseObjects();
    };

    delete supervisor;
    return 0;
}

// File:          DatasetCollectionWebotsController.cpp
// Date:
// Description:
// Author:
// Modifications:

// You may need to add webots include files such as
// <webots/DistanceSensor.hpp>, <webots/Motor.hpp>, etc.
// and/or to add some other includes
#include <webots/Robot.hpp>
#include <webots/Supervisor.hpp>
#include <webots/Camera.hpp>

// OpenCV
#include <opencv2/opencv.hpp>

// All the webots classes are defined in the "webots" namespace
using namespace webots;

// This is the main program of your controller.
// It creates an instance of your Robot instance, launches its
// function(s) and destroys it at the end of the execution.
// Note that only one instance of Robot should be created in
// a controller program.
// The arguments of the main function can be specified by the
// "controllerArgs" field of the Robot node
int main(int argc, char **argv) {
    srand (time(NULL));
    // create the Robot instance.
    Supervisor *supervisor = new Supervisor();

    // get the time step of the current world.
    int timeStep = (int)supervisor->getBasicTimeStep();

    // do this once only
    Node *robot_node = supervisor->getFromDef("MY_ROBOT");
    if (robot_node == NULL) {
        std::cerr << "No DEF MY_ROBOT node found in the current world file" << std::endl;
        exit(1);
    }
    Field *trans_field = robot_node->getField("translation");

    // Get and enable Camera
    Camera *cam = supervisor->getCamera("Camera");
    cam->enable(timeStep);
    // You should insert a getDevice-like function in order to get the
    // instance of a device of the robot. Something like:
    //  Motor *motor = robot->getMotor("motorname");
    //  DistanceSensor *ds = robot->getDistanceSensor("dsname");
    //  ds->enable(timeStep);

    // Main loop:
    // - perform simulation steps until Webots is stopping the controller
    int simulationTime = 0;
    while (supervisor->step(timeStep) != -1) {
        simulationTime += timeStep;
        std::cout << "simulation time: " << simulationTime << std::endl;

        // this is done repeatedly
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


        // reset robot position and physics
        double randx, randy;
        // double randrot;
        randx = ((double)rand()) / RAND_MAX * 9 - 4.5;
        randy = ((double)rand()) / RAND_MAX * 6 - 3;
        // randrot = ((double)rand()) / RAND_MAX * 6.283185;

        const double INITIAL[3] = {randx, randy, 0.279};
        trans_field->setSFVec3f(INITIAL);
        robot_node->resetPhysics();

        // Read the sensors:
        // Enter here functions to read sensor data, like:
        //  double val = ds->getValue();

        // Process sensor data here.

        // Enter here functions to send actuator commands, like:
        //  motor->setPosition(10.0);
    };

    // Enter here exit cleanup code.

    delete supervisor;
    return 0;
}

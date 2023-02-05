#ifndef UTILS_HPP
#define UTILS_HPP

#include <opencv2/opencv.hpp>
#include <math.h>
#include <vector>

std::vector<double> pose_global(std::vector<double> pRelative, std::vector<double> pose);
double mod_angle(double a);
void calculateRotationFromEulerAngles(cv::Vec3f euler, double *rotation);
cv::Mat eulerAnglesToRotationMatrix(cv::Vec3f &theta);
std::vector<double> toEuler(double x,double y,double z,double angle);

#endif // UTILS_HPP

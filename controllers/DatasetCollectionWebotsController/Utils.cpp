#include "Utils.hpp"

std::vector<double> pose_global(std::vector<double> pRelative, std::vector<double> pose) {
  double ca = cos(pose[2]);
  double sa = sin(pose[2]);
  std::vector<double> GlobalPose(3, 0);
  GlobalPose[0] = pose[0] + ca*pRelative[0] - sa*pRelative[1];
  GlobalPose[1] = pose[1] + sa*pRelative[0] + ca*pRelative[1];
  GlobalPose[2] = pose[2] + pRelative[2];
  return GlobalPose;
}

double mod_angle(double a) {
  // Reduce angle to [-pi, pi)
  a = remainder(a, 2 * M_PI);

  if (a >= M_PI) {
    a = a - 2 * M_PI;
  }
  return a;
}

void calculateRotationFromEulerAngles(cv::Vec3f euler, double *rotation) {
    cv::Mat R(3, 3, CV_64F);
    double m[3];
    double theta;
    double Length;

    R = eulerAnglesToRotationMatrix(euler);

    theta = acos((R.at<double>(0, 0) + R.at<double>(1, 1) + R.at<double>(2, 2) - 1) / 2);

    m[0] = (R.at<double>(2, 1) - R.at<double>(1, 2)) * (1.0 / 2.0 * sin(theta));
    m[1] = (R.at<double>(0, 2) - R.at<double>(2, 0)) * (1.0 / 2.0 * sin(theta));
    m[2] = (R.at<double>(1, 0) - R.at<double>(0, 1)) * (1.0 / 2.0 * sin(theta));

    rotation[0] = m[0];
    rotation[1] = m[1];
    rotation[2] = m[2];
    rotation[3] = theta;

    Length = sqrt(pow(rotation[0], 2) + pow(rotation[1], 2) + pow(rotation[2], 2));

    rotation[0] = rotation[0] / Length;
    rotation[1] = rotation[1] / Length;
    rotation[2] = rotation[2] / Length;
}

cv::Mat eulerAnglesToRotationMatrix(cv::Vec3f &theta) {
    cv::Mat R_x = (cv::Mat_<double>(3, 3) <<
            1,      0,                  0,
            0,      cos(theta[0]),      -sin(theta[0]),
            0,      sin(theta[0]),      cos(theta[0])
            );

    cv::Mat R_y = (cv::Mat_<double>(3, 3) <<
            cos(theta[1]),      0,      sin(theta[1]),
            0,                  1,      0,
            -sin(theta[1]),     0,      cos(theta[1])
            );

    cv::Mat R_z = (cv::Mat_<double>(3, 3) <<
            cos(theta[2]),      -sin(theta[2]),      0,
            sin(theta[2]),      cos(theta[2]),       0,
            0,                  0,                   1);

    cv::Mat R = R_z * R_y * R_x;
    return R;
}

std::vector<double> toEuler(double x, double y, double z, double angle) {
    double heading, attitude, bank;
    double s = sin(angle);
    double c = cos(angle);
    double t = 1 - c;

    //  if axis is not already normalised then uncomment this
    // double magnitude = Math.sqrt(x*x + y*y + z*z);
    // if (magnitude==0) throw error;
    // x /= magnitude;
    // y /= magnitude;
    // z /= magnitude;
    // if ((x*y*t + z*s) > 0.998) { // north pole singularity detected
    // 	heading = 2*atan2(x*sin(angle/2),cos(angle/2));
    // 	attitude = M_PI/2;
    // 	bank = 0;
    // 	return;
    // }
    // if ((x*y*t + z*s) < -0.998) { // south pole singularity detected
    // 	heading = -2*atan2(x*sin(angle/2),cos(angle/2));
    // 	attitude = -M_PI/2;
    // 	bank = 0;
    // 	return;
    // }

    heading = atan2(y * s - x * z * t , 1 - (y * y + z * z) * t);
    attitude = asin(x * y * t + z * s);
    bank = atan2(x * s - y * z * t , 1 - (x * x + z * z) * t);
    return {heading, attitude, bank};
}

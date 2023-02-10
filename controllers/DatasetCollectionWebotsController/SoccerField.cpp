#include "SoccerField.hpp"

float FieldWidth = 9.0;
float FieldHeight = 6.0;
float FieldPading = 1.0;
int PixelPerMeter = 100;
float WindowWidth = FieldWidth + 2 * FieldPading;
float WindowHeight = FieldHeight + 2 * FieldPading;
float Half = 0.5;

SoccerField::SoccerField() {
    fieldMat = drawField();
}

cv::Mat SoccerField::drawField() {
    cv::Mat fieldMatrix(WindowHeight * PixelPerMeter, WindowWidth * PixelPerMeter, CV_8UC3, cv::Scalar(0, 255, 0));

    // Corner points
    cv::Point CUL(FieldPading * PixelPerMeter, FieldPading * PixelPerMeter);
    cv::Point CUR((FieldWidth + FieldPading) * PixelPerMeter, FieldPading * PixelPerMeter);
    cv::Point CDL(FieldPading * PixelPerMeter, (FieldHeight + FieldPading) * PixelPerMeter);
    cv::Point CDR((FieldWidth + FieldPading) * PixelPerMeter, (FieldHeight + FieldPading) * PixelPerMeter);

    // Center line points
    cv::Point CLineU((CUR.x + CUL.x) / 2, CUR.y);
    cv::Point CLineD((CUR.x + CUL.x) / 2, CDR.y);

    // Connect corner points
    cv::line(fieldMatrix, CUL, CUR, cv::Scalar(255, 255, 255), 0.05 * PixelPerMeter);
    cv::line(fieldMatrix, CUL, CDL, cv::Scalar(255, 255, 255), 0.05 * PixelPerMeter);
    cv::line(fieldMatrix, CDL, CDR, cv::Scalar(255, 255, 255), 0.05 * PixelPerMeter);
    cv::line(fieldMatrix, CDR, CUR, cv::Scalar(255, 255, 255), 0.05 * PixelPerMeter);

    // Connect center line points
    cv::line(fieldMatrix, CLineU, CLineD, cv::Scalar(255, 255, 255), 0.05 * PixelPerMeter);


    // Right penalty area
    cv::line(fieldMatrix, cv::Point(CUR.x, CUR.y + (0.5 * PixelPerMeter)), cv::Point(CUR.x - (1.0 * PixelPerMeter), CUR.y + (0.5 * PixelPerMeter)), cv::Scalar(255, 255, 255), 0.05 * PixelPerMeter);
    cv::line(fieldMatrix, cv::Point(CDR.x, CDR.y - (0.5 * PixelPerMeter)), cv::Point(CDR.x - (1.0 * PixelPerMeter), CDR.y - (0.5 * PixelPerMeter)), cv::Scalar(255, 255, 255), 0.05 * PixelPerMeter);
    cv::line(fieldMatrix, cv::Point(CDR.x - (1.0 * PixelPerMeter), CDR.y - (0.5 * PixelPerMeter)), cv::Point(CUR.x - (1.0 * PixelPerMeter), CUR.y + (0.5 * PixelPerMeter)), cv::Scalar(255, 255, 255), 0.05 * PixelPerMeter);

    // Left penalty area
    cv::line(fieldMatrix, cv::Point(CUL.x , CUL.y + (0.5 * PixelPerMeter)), cv::Point(CUL.x + (1.0 * PixelPerMeter), CUL.y + (0.5 * PixelPerMeter)), cv::Scalar(255, 255, 255), 0.05 * PixelPerMeter);
    cv::line(fieldMatrix, cv::Point(CDL.x , CDL.y - (0.5 * PixelPerMeter)), cv::Point(CDL.x + (1.0 * PixelPerMeter), CDL.y - (0.5 * PixelPerMeter)), cv::Scalar(255, 255, 255), 0.05 * PixelPerMeter);
    cv::line(fieldMatrix, cv::Point(CDL.x + (1.0 * PixelPerMeter), CDL.y - (0.5 * PixelPerMeter)), cv::Point(CUL.x + (1.0 * PixelPerMeter), CUL.y + (0.5 * PixelPerMeter)), cv::Scalar(255, 255, 255), 0.05 * PixelPerMeter);

    // Penalty marks
    cv::line(fieldMatrix, cv::Point(CUR.x - 2.2 * PixelPerMeter, (CUR.y + CDR.y) / 2), cv::Point(CUR.x - 2.2 * PixelPerMeter, (CUR.y + CDR.y) / 2), cv::Scalar(255, 255, 255), 0.15 * PixelPerMeter);
    cv::line(fieldMatrix, cv::Point(CUL.x + 2.2 * PixelPerMeter, (CUL.y + CDL.y) / 2), cv::Point(CUL.x + 2.2 * PixelPerMeter, (CUL.y + CDL.y) / 2), cv::Scalar(255, 255, 255), 0.15 * PixelPerMeter);

    // Center circle and mark
    cv::circle(fieldMatrix, cv::Point(CLineU.x, (CLineD.y + CLineU.y) / 2), 0.75 * PixelPerMeter, cv::Scalar(255, 255, 255), 0.05 * PixelPerMeter);
    cv::circle(fieldMatrix, cv::Point(CLineU.x, (CLineD.y + CLineU.y) / 2), 0.05 * PixelPerMeter, cv::Scalar(255, 255, 255), 0.05 * PixelPerMeter);

    return fieldMatrix;
}

cv::Point SoccerField::pointOnField2Pixel(cv::Point2f pointOnCourtMeter) {
    return cv::Point(((WindowHeight * Half) - pointOnCourtMeter.x) * PixelPerMeter, ((WindowWidth * Half) + pointOnCourtMeter.y) * PixelPerMeter);
}

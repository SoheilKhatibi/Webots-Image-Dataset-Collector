#include "SoccerField.hpp"

int FieldWidth = 90;
int FieldHeight = 60;
int FieldPading = 15;
int ScaleToPixel = 5;

SoccerField::SoccerField() {

}

cv::Mat SoccerField::drawField() {
    cv::Mat fieldMat((FieldHeight + 2 * FieldPading) * ScaleToPixel, (FieldWidth + 2 * FieldPading) * ScaleToPixel, CV_8UC3, cv::Scalar(0, 255, 0));

    cv::Point CUL(FieldPading * ScaleToPixel, FieldPading * ScaleToPixel);
    cv::Point CUR((FieldWidth + FieldPading) * ScaleToPixel, FieldPading * ScaleToPixel);
    cv::Point CDL(FieldPading * ScaleToPixel, (FieldHeight + FieldPading) * ScaleToPixel);
    cv::Point CDR((FieldWidth + FieldPading) * ScaleToPixel, (FieldHeight + FieldPading) * ScaleToPixel);

    cv::Point CLineU((CUR.x + CUL.x) / 2, CUR.y);
    cv::Point CLineD((CUR.x + CUL.x) / 2, CDR.y);

    cv::line(fieldMat, CUL, CUR, cv::Scalar(255, 255, 255), 0.5 * ScaleToPixel);
    cv::line(fieldMat, CUL, CDL, cv::Scalar(255, 255, 255), 0.5 * ScaleToPixel);
    cv::line(fieldMat, CDL, CDR, cv::Scalar(255, 255, 255), 0.5 * ScaleToPixel);
    cv::line(fieldMat, CDR, CUR, cv::Scalar(255, 255, 255), 0.5 * ScaleToPixel);

    cv::line(fieldMat, cv::Point(CUR.x, CUR.y + (5*ScaleToPixel)), cv::Point(CUR.x - (10*ScaleToPixel), CUR.y + (5 * ScaleToPixel)), cv::Scalar(255, 255, 255), 0.5 * ScaleToPixel);
    cv::line(fieldMat, cv::Point(CDR.x, CDR.y - (5*ScaleToPixel)), cv::Point(CDR.x - (10*ScaleToPixel), CDR.y - (5 * ScaleToPixel)), cv::Scalar(255, 255, 255), 0.5 * ScaleToPixel);
    cv::line(fieldMat, cv::Point(CDR.x - (10 * ScaleToPixel), CDR.y - (5 * ScaleToPixel)), cv::Point(CUR.x - (10 * ScaleToPixel), CUR.y + (5 * ScaleToPixel)), cv::Scalar(255, 255, 255), 0.5 * ScaleToPixel);

    cv::line(fieldMat, cv::Point(CUL.x , CUL.y + (5 * ScaleToPixel)), cv::Point(CUL.x + (10 * ScaleToPixel), CUL.y + (5 * ScaleToPixel)), cv::Scalar(255, 255, 255), 0.5 * ScaleToPixel);
    cv::line(fieldMat, cv::Point(CDL.x , CDL.y - (5 * ScaleToPixel)), cv::Point(CDL.x + (10 * ScaleToPixel), CDL.y - (5 * ScaleToPixel)), cv::Scalar(255, 255, 255), 0.5 * ScaleToPixel);
    cv::line(fieldMat, cv::Point(CDL.x + (10 * ScaleToPixel), CDL.y - (5 * ScaleToPixel)), cv::Point(CUL.x + (10 * ScaleToPixel), CUL.y + (5 * ScaleToPixel)), cv::Scalar(255, 255, 255), 0.5 * ScaleToPixel);
    cv::line(fieldMat, CLineU,CLineD, cv::Scalar(255, 255, 255), 0.5 * ScaleToPixel);

    cv::line(fieldMat, cv::Point(CUR.x - 22 * ScaleToPixel, (CUR.y + CDR.y) / 2), cv::Point(CUR.x - 22 * ScaleToPixel, (CUR.y + CDR.y) / 2), cv::Scalar(255, 255, 255), 1.5 * ScaleToPixel);
    cv::line(fieldMat, cv::Point(CUL.x + 22 * ScaleToPixel, (CUL.y + CDL.y) / 2), cv::Point(CUL.x + 22 * ScaleToPixel, (CUL.y + CDL.y) / 2), cv::Scalar(255, 255, 255), 1.5 * ScaleToPixel);
    cv::circle(fieldMat, cv::Point(CLineU.x, (CLineD.y + CLineU.y) / 2), 7.5 * ScaleToPixel, cv::Scalar(255, 255, 255), 0.5 * ScaleToPixel);
    cv::circle(fieldMat, cv::Point(CLineU.x, (CLineD.y + CLineU.y) / 2), 0.5 * ScaleToPixel, cv::Scalar(255, 255, 255), 0.5 * ScaleToPixel);

    return fieldMat;
}

cv::Point2f SoccerField::pointOnField2Pixel(cv::Point2f pointOnCourtMeter) {

}

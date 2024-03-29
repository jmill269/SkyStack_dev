#include "opencv2/core.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/aruco.hpp"
#include "opencv2/calib3d.hpp"

#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;

const float calSquareDim = 0.025f;
//const float arucoSquareDim =
const Size boardDimensions = Size(6,9);


void createArucoMarkers() {
    Mat outputMarker;

    Ptr<aruco::Dictionary> markerDictionary = aruco::getPredefinedDictionary(aruco::PREDEFINED_DICTIONARY_NAME::DICT_4X4_50);

    for (int i = 0; i < 50; i++) {
        aruco::drawMarker(markerDictionary, i, 500, outputMarker, 1);
        ostringstream convert;
        string imageName = "4x4Marker_";
        convert << imageName << i << ".jpg";
        imwrite(convert.str(), outputMarker);
    }
}

void createKnownBoardPos(Size boardSize, float sqEdgeLen, vector<Point3f>& corners) {
    for (int i = 0; i < boardSize.height; i++) {
        for (int j = 0; j < boardSize.width; j++) {
            corners.push_back(Point3f(j*sqEdgeLen, i*sqEdgeLen, 0.0f));
        }
    }
}

void getBoardCorners(vector<Mat> imgs, vector<vector<Point2f>>& allFoundCorners, bool showResults = false) {
    for (vector<Mat>::iterator it = imgs.begin(); it != imgs.end(); it++) {
        vector<Point2f> pointBuf;
        bool found = findChessboardCorners(*it, Size(boardDimensions), pointBuf, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_NORMALIZE_IMAGE);

        if (found) {
            allFoundCorners.push_back(pointBuf);
        }
        if (showResults) {
            drawChessboardCorners(*it, Size(boardDimensions), pointBuf, found);
            imshow("Looking for Corners", *it);
            waitKey(0);
        }
    }
}


int main(int agrgv, char** argc) {
    //createArucoMarkers();
    Mat frame;
    Mat drawToFrame;
    Mat cameraMatrix = Mat::eye(3,3, CV_64F);
    Mat distanceCoeff;
    vector<Mat> savedImages;

    vector<vector<Point2f>> markerCorners, rejectedMarkers;

    VideoCapture vid(0);

    if (!vid.isOpened()) {
        cerr << "Failed to open video feed.\n";
        return 1;
    }

    int FPS = 20;   // frames per second

    namedWindow("Webcam", CV_WINDOW_AUTOSIZE);

    while (true) {
        if (!vid.read(frame)) {
            break;
        }

        vector<Vec2f> foundPoints;
        bool found = false;

        found = findChessboardCorners(frame, boardDimensions, foundPoints, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_NORMALIZE_IMAGE);
        frame.copyTo(drawToFrame);
        drawChessboardCorners(drawToFrame, boardDimensions, foundPoints, found);
        if (found) {
            imshow("Webcam", drawToFrame);
            } else {
                imshow("Webcam", frame);
            }

            char key = waitKey(1000/FPS);   // store key user presses for later
    }

    return 0;
}



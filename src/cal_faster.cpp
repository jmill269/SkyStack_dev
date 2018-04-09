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

void cameraCalibration(vector<Mat> calImages, Size boardSize, float sqEdgeLen, Mat& cameraMatrix, Mat& distanceCoeff) {
    vector<vector<Point2f>> checkerboardImgSpacePoints;
    getBoardCorners(calImages, checkerboardImgSpacePoints, false);

    vector<vector<Point3f>> worldSpaceCornerPoints(1);
    createKnownBoardPos(boardSize, sqEdgeLen, worldSpaceCornerPoints[0]);
    worldSpaceCornerPoints.resize(checkerboardImgSpacePoints.size(), worldSpaceCornerPoints[0]);

    vector<Mat> rVecs, tVecs;
    distanceCoeff = Mat::zeros(8,1, CV_64F);

    calibrateCamera(worldSpaceCornerPoints, checkerboardImgSpacePoints, boardSize, cameraMatrix, distanceCoeff, rVecs, tVecs);
}


bool loadCameraCalibration(string filename, Mat& cameraMatrix, Mat& distanceCoeff) {
    ifstream in(filename);

    if (in) {
        uint16_t rows;
        uint16_t cols;

        in >> rows;
        in >> cols;

        cameraMatrix = Mat(Size(cols, rows), CV_64F);

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                double read = 0.0f;
                in >> read;
                cameraMatrix.at<double>(r,c) = read;
                cout << cameraMatrix.at<double>(r,c) << "\n";
            }
        }

        in >> rows;
        in >> cols;

        distanceCoeff = Mat::zeros(rows, cols, CV_64F);

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                double read = 0.0f;
                in >> read;
                distanceCoeff.at<double>(r,c) = read;
                cout << distanceCoeff.at<double>(r,c) << "\n";
            }
        }

        in.close();
        return true;
    }
    return false;
}






bool saveCameraCalibration(string filename, Mat cameraMatrix, Mat distanceCoeff) {
    ofstream out(filename);
    if (out) {
        uint16_t rows = cameraMatrix.rows;
        uint16_t cols = cameraMatrix.cols;

        out << rows << endl;
        out << cols << endl;

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                double value = cameraMatrix.at<double>(r,c);
                out << value << endl;
            }
        }

        rows = distanceCoeff.rows;
        cols = distanceCoeff.cols;

        out << rows << endl;
        out << cols << endl;

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                double value = distanceCoeff.at<double>(r,c);
                out << value << endl;
            }
        }

        out.close();
        return true;
    }
    return false;
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

        found = findChessboardCorners(frame, boardDimensions, foundPoints, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_NORMALIZE_IMAGE | CV_CALIB_CB_FAST_CHECK);
        frame.copyTo(drawToFrame);
        drawChessboardCorners(drawToFrame, boardDimensions, foundPoints, found);
        if (found) {
            imshow("Webcam", drawToFrame);
            } else {
                imshow("Webcam", frame);
            }

            char key = waitKey(1000/FPS);   // store key user presses for later

            switch (key) {
                case ' ':   // saving image, space key
                    if (found) {
                        Mat temp;
                        frame.copyTo(temp);
                        savedImages.push_back(temp);
                    }
                    break;
                case 13:    // enter key, start calibration after enough images have been taken
                    if (savedImages.size() > 15) {
                        cameraCalibration(savedImages, boardDimensions, calSquareDim, cameraMatrix, distanceCoeff);
                        saveCameraCalibration("CameraCalibration", cameraMatrix, distanceCoeff);
                    }
                    break;
                case 27:    // esc key, close the window
                    return 0;
                    break;
            }
    }
    return 0;
}







#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    VideoCapture cap(0);
    if(!cap.isOpened())
        return -1;

    Mat imgA, imgB;
    int win_size = 15;
    int maxCorners = 10;
    double qualityLevel = 0.01;
    double minDistance = 5.0;

    std::vector<cv::Point2f> cornersA;
    cornersA.reserve(maxCorners);

    cap >> imgA;
    flip(imgB, imgB, 1);
    cvtColor(imgA, imgA, COLOR_BGR2GRAY);

    goodFeaturesToTrack(imgA, cornersA, maxCorners, qualityLevel, minDistance, cv::Mat());

    while(true) {
        std::vector<cv::Point2f> cornersB;
        cornersB.reserve(maxCorners);

        cap >> imgA;
        flip(imgA, imgA, 1);
        cvtColor(imgA, imgA, COLOR_BGR2GRAY);

        Size img_sz = imgA.size();
        Mat imgC(img_sz, 1);

        cap >> imgB;
        flip(imgB, imgB, 1);
        cvtColor(imgB, imgB, COLOR_BGR2GRAY);

        cv::Size pyr_sz(img_sz.width + 8, img_sz.height / 3);

        std::vector<uchar> features_found;
        features_found.reserve(maxCorners);

        std::vector<float> feature_errors;
        feature_errors.reserve(maxCorners);

        calcOpticalFlowPyrLK(imgA, imgB, cornersA, cornersB, features_found, feature_errors,
                             Size(win_size, win_size), 5,
                             cvTermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 10, 0.5), 0);

        for (int i = 0; i < features_found.size(); i++) {
            Point p0(ceil(cornersA[i].x), ceil(cornersA[i].y));
            Point p1(ceil(cornersB[i].x), ceil(cornersB[i].y));
            line(imgC, p0, p1, CV_RGB(255, 255, 255), 2);
        }

        namedWindow("ImageA", 0);
        namedWindow("ImageB", 0);
        namedWindow("LKpyr_OpticalFlow", 0);

        imshow("ImageA", imgA);
        imshow("ImageB", imgB);
        imshow("LKpyr_OpticalFlow", imgC);

        cornersA = cornersB;
    }

    return 0;
}

#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, const char * argv[])
{
    cv::VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    cv::namedWindow("video",1);
    while(true)
    {
        cv::Mat frame;
        cap >> frame; // get a new frame from camera
        cv::imshow("video", frame);
        if(cv::waitKey(30) == 'q') break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
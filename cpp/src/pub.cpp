#include <iostream>

#include <zmq.hpp>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main() {
    cout << "C++: Camera publisher!" << endl;

    VideoCapture cap(0);
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
    Mat frame;

    zmq::context_t context(1);
    zmq::socket_t publisher(context, ZMQ_PUB);
    publisher.bind("tcp://*:5555");

    while(cap.isOpened()){
        cap >> frame;

        imshow("C++ Publisher", frame);
        int len = frame.total() * frame.channels();
        zmq::message_t message(len);
        memcpy (message.data(), frame.data, len);
        bool rc = publisher.send (message);

        int k = waitKey(10);
        if(k == 'q'){
            break;
        }
    }

    return 0;
}
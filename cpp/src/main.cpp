#include <iostream>
#include <opencv2/opencv.hpp>
#include <zmq.hpp>

using namespace std;

void my_free(void *data, void *hint)
{
    free(data);
}

int main(int argc, const char * argv[])
{
    cv::VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    cv::Mat frame;

    // Open ZMQ Connection
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_PUB);
    socket.bind ("tcp://*:5555");

    // video info
    while(true){
        cap >> frame;
        if(frame.cols != 0 && frame.rows!=0) break;        
    }
    int32_t  info[3];
    info[0] = (int32_t)frame.rows;
    info[1] = (int32_t)frame.cols;
    info[2] = (int32_t)frame.type();

    cout << "rows: " << info[0] << endl;
    cout << "cols: " << info[1] << endl;
    cout << "type: " << info[2] << endl;

    /*
    // Send Rows, Cols, Type
    for(int i=0; i<3; i++){
        zmq::message_t msg_info ( (void*)&info[i], sizeof(int32_t), NULL  );
        socket.send(msg_info, ZMQ_SNDMORE);
    }
    */

    cv::namedWindow("video",1);
    while(true)
    {
        cv::Mat frame;
        cap >> frame; // get a new frame from camera
        
        // Pixel data
        void* data = malloc(frame.total() * frame.elemSize());
        memcpy(data, frame.data, frame.total() * frame.elemSize());
        
        // Send Pixel data
        zmq::message_t msg(data, frame.total() * frame.elemSize(), my_free, NULL);
        socket.send(msg, ZMQ_SNDMORE);

        cv::imshow("video", frame);
        if(cv::waitKey(30) == 'q') break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
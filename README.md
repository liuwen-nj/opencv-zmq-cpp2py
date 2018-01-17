# opencv-zmq-cpp2py

example of c++ and python opencv pipe using ZeroMQ  
send c++ cv::Mat sequence captured by cv::VideoCapture to python  

## tested environment
- Ubuntu 16.04
- python 2.7

## requirement
- opencv (both c++ & python)
- zmq (cppzmq & pyzmq)

## how to use

### build
```
./build.sh
```

### run c++ publisher
```
cpp/build/pub
```

### run python subscriber
```
python py/sub.py
```

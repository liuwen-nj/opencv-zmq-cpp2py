import struct
import zmq
import numpy as np
import cv2

# Open ZMQ Connection
context = zmq.Context()
socket = context.socket(zmq.SUB)
socket.connect("tcp://localhost:5555")
socket.setsockopt(zmq.SUBSCRIBE, "")
print("komi")

# Receve Data from C++ Program
data =  socket.recv_unicode()
print("komi")

# Convert byte to integer
rows = 480
cols = 640
mat_type = 16

if mat_type == 0:
    # Gray Scale
    image = np.frombuffer(data, dtype=np.uint8).reshape((rows,cols));
else:
    # BGR Color
    image = np.frombuffer(data, dtype=np.uint8).reshape((rows,cols,3));

# Write BMP Image
cv2.imwrite("recv.bmp", image);
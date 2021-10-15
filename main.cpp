#include "opencv2/opencv.hpp"
#include <iostream>
#include <glog/logging.h>
#include <iostream>
#include <memory>
#include <chrono>
#include <vitis/ai/demo.hpp>
#include <vitis/ai/facedetect.hpp>
using namespace cv;
int main(int argc, char** argv)
{
    VideoCapture cap(0);
    // open the default camera, use something different from 0 otherwise;
    // Check VideoCapture documentation.
       auto network = vitis::ai::FaceDetect::create(
                  "densebox_320_320",
                  true);
        
    while(true)
    {
          Mat frame;
          cap >> frame;
          //Resizing for densebox 320 by 360
          resize(frame, frame, Size(320,320));
          //The VITIS-AI MAGIC
	      auto face_results = network->run(frame);
          //Drawing boxes around results
	    for (const auto &r : face_results.rects) {
            int x1 = r.x * frame.cols;
            int y1 = r.y * frame.rows;
            int x2 = x1 + (r.width * frame.cols);
            int y2 = y1 + (r.height * frame.rows);
          Point pt1(x1, y1);
          // and its bottom right corner.
          Point pt2(x2, y2);
          cv::rectangle(frame, pt1, pt2, cv::Scalar(0, 255, 0));
        }


          imshow("this is you, smile! :)", frame);
          if( waitKey(10) == 27 ) break; // stop capturing by pressing ESC 
         
    // the camera will be closed automatically upon exit
    // cap.close();
    return 0;
}
}
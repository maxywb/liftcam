#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <boost/thread.hpp>
#include <vector>
using namespace std;

class VidQueue{
public:
  VidQueue(int size){
    size_ = size;
    ptr_ = 0;
    imgs_ = new vector<IplImage>();
  }
private:
  vector<IplImage> *imgs_;
  int size_;
  int ptr_;
};

class VidGrabber{
public:
  VidGrabber(string output, int queue_size){
    queue_ = new VidQueue(queue_size);
  }

  // The entry point for a thread
  void operator()(){
    // grab images
    // write image
  }
private:
  VidQueue *queue_;
  
};

 


int main(int argc, char ** argv){
  CvCapture *cam = cvCaptureFromCAM(0);
  if (!cam){
    cout << "camera not found" << endl;
  }
  IplImage *img;
  IplImage *cur = cvCreateImage(cvSize(640,480),IPL_DEPTH_8U,3);;
  double t1,t2;
  cvNamedWindow("liftcam", 0);

  while(true){
    t1 = (double) cvGetTickCount();//timing

    img = cvQueryFrame(cam);
    cvCopy(img,cur);
    cvShowImage("liftcam", cur);
    cvWaitKey(1);

    t2 = (double) cvGetTickCount();//timing

    cout << "fps: " <<1000./((t2-t1)/(cvGetTickFrequency() * 1000.)) << endl;

  }

  cvReleaseCapture(&cam);
}

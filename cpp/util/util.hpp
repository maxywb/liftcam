#ifndef _UTIL_H_
#define _UTIL_H_
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <boost/thread.hpp>
#include <vector>
using namespace std;

template<class T> 
class SafeQueue{
public:
  SafeQueue(int const max_items, boost::mutex * const mutex){
    max_items_ = max_items;
    mutex_ = mutex;
    size_ = 0;
  }
  bool isFull(){
    boost::mutex::scoped_lock lock(*mutex_);
    return size_ == max_items_;
  }
  void force_push(T item){
    boost::mutex::scoped_lock lock(*mutex_);
    if(size_ >= max_items_){
      items_.erase(items_.begin());
    } else{
      size_++;
    }
    items_.push_back(item);
  }
  bool push(T item){
    boost::mutex::scoped_lock lock(*mutex_);
    // check if queue is full
    if(size_ >= max_items_){
      return false;
    }
    items_.push_back(item);
    size_++;
    return true;
  }  
  T pop(){
    boost::mutex::scoped_lock lock(*mutex_);
    // deal with empty queue
    if(size_ == 0){
      return NULL;
    } else{
      T front = items_.front();
      items_.erase(items_.begin());
      return front;
    }
  }
private:
  size_t max_items_;
  size_t size_;
  vector<T> items_;
  boost::mutex* mutex_;
};

class VidGrabber{
public:
  VidGrabber(string output, int queue_size,boost::mutex *mutex){
    queue_ = new SafeQueue(queue_size,mutex);
  }
  void operator()(){
    CvCapture *cam = cvCaptureFromCAM(0);
    if (!cam){
      cout << "camera not found" << endl;
      return;
    }
    IplImage *img;
    IplImage *copy = cvCreateImage(cvSize(640,480),IPL_DEPTH_8U,3);;
    cvNamedWindow("liftcam", 0);

    while(true){
      // get and copy image
      img = cvQueryFrame(cam);
      cvCopy(img,copy);

      // enqueue the copy
      queue_.force_push(copy);

      // write image
      
    }

    cvReleaseCapture(&cam);

  }
private:
  SafeQueue<IplImage> queue_;
  
};

#endif

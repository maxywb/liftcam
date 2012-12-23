#!/usr/bin/python
import sys, time
import cv



mine = "http://192.168.1.10:8080/videofeed"
print "opening capture"
capture =cv.CaptureFromFile(mine)
print "moving on"
cv.NamedWindow('Video Stream', 1 )
while True:
    # capture the current frame
    frame = cv.QueryFrame(capture)
    print "frame:",frame
    #detect(frame)
    cv.ShowImage('Video Stream', frame)
    k = cv.WaitKey(1)
    if k == 0x1b: # ESC
        print 'ESC pressed. Exiting ...'
        break

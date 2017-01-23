//
//  main.cpp
//  CharBP
//
//  Created by 唐伟伦 on 2017/1/23.
//  Copyright © 2017年 唐伟伦. All rights reserved.
//

#include <iostream>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
using namespace cv;

int main(int argc, const char * argv[]) {
    // insert code here...
    /*CBP bp;
     bp.readData("a");
     bp.initBPNework();
     bp.trainNetwork();
     bp.writeData("b");*/
    
    IplImage* imgSrc = cvLoadImage("./Images/img001-001.png", CV_LOAD_IMAGE_COLOR);
    IplImage* img_gray = cvCreateImage(cvGetSize(imgSrc), IPL_DEPTH_8U, 1);
    //灰度处理
    cvCvtColor(imgSrc, img_gray, CV_BGR2GRAY);
    
    //二值化处理，CV_THRESH_BINARY_INV使得背景为黑色，字符为白色，这样找到的最外层才是字符的最外层
    cvThreshold(img_gray, img_gray, 100, 255, CV_THRESH_BINARY_INV);//
    //cvShowImage("ThresholdImg", img_gray);
    
    //找到图中数字的外接矩形
    CvSeq* contours = NULL;
    CvMemStorage* storage = cvCreateMemStorage(0);
    int count = cvFindContours(img_gray, storage, &contours, sizeof(CvContour), CV_RETR_EXTERNAL);
    if (count != 1) {	//应该只能找到一个连通区域
        return 1;
    }
    CvSeq* c = contours;
    CvRect rc = cvBoundingRect(c, 0);
    cvDrawRect(imgSrc, cvPoint(rc.x, rc.y), cvPoint(rc.x + rc.width, rc.y + rc.height), CV_RGB(255, 0, 0));
    
    //裁剪出数字并二值化
    IplImage* imgNo = cvCreateImage(cvSize(rc.width, rc.height), IPL_DEPTH_8U, 3);
    cvSetImageROI(imgSrc, rc);
    cvCopy(imgSrc, imgNo);
    cvThreshold(imgNo, imgNo, 100, 255, CV_THRESH_BINARY_INV);//
    //cvShowImage("cut", imgNo);
    cvReleaseMemStorage(&storage);
    cvReleaseImage(&imgSrc);
    cvReleaseImage(&img_gray);
    
    //归一化大小
    IplImage *imgNor = 0;	//目标图像指针
    CvSize dstCvsize;	//目标图像尺寸
    dstCvsize.height = dstCvsize.width = 100;
    imgNor = cvCreateImage(dstCvsize, imgNo->depth, imgNo->nChannels);	//构造目标图象
    cvResize(imgNo, imgNor, CV_INTER_LINEAR);	//缩放源图像到目标图像
    cvShowImage("nor", imgNor);
    
    cvWaitKey(0);
    cvReleaseImage(&imgNo);
    cvReleaseImage(&imgNor);
    return 0;
}


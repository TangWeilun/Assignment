//
//  ImagePro.cpp
//  CharBP
//
//  Created by 唐伟伦 on 2017/1/25.
//  Copyright © 2017年 唐伟伦. All rights reserved.
//

#include "ImagePro.hpp"

CImagePro::CImagePro() {
    strcpy(imageFile, "./tests/0-0.png");
}

void CImagePro::imagePro() {
    
    int i, j;
    dataFile = fopen("test.bin", "wb");
    for(i=0; i<10; i++) {
        imageFile[8] = '0' + i;
        for(j=0; j<10; j++) {
            imageFile[10] = '0' + j;
            //std::cout<<imageFile<<std::endl;
            oneImagePro();
            fwrite(data,sizeof(double),feaSize,dataFile);
        }
    }
    fclose(dataFile);
    
}

bool CImagePro::oneImagePro() {
    IplImage* imgSrc = cvLoadImage(imageFile, CV_LOAD_IMAGE_COLOR);
    IplImage* imgGray = cvCreateImage(cvGetSize(imgSrc), IPL_DEPTH_8U, 1);
    //灰度处理
    cvCvtColor(imgSrc, imgGray, CV_BGR2GRAY);
    
    //二值化处理，CV_THRESH_BINARY_INV使得背景为黑色，字符为白色，这样找到的最外层才是字符的最外层
    cvThreshold(imgGray, imgGray, 100, 255, CV_THRESH_BINARY_INV);//
    //cvShowImage("ThresholdImg", img_gray);
    
    //找到图中数字的外接矩形
    CvSeq* contours = NULL;
    CvMemStorage* storage = cvCreateMemStorage(0);
    int count = cvFindContours(imgGray, storage, &contours, sizeof(CvContour), CV_RETR_EXTERNAL);
    if (count != 1) {	//应该只能找到一个连通区域
        return false;
    }
    CvSeq* c = contours;
    CvRect rc = cvBoundingRect(c, 0);
    //ßcvDrawRect(imgSrc, cvPoint(rc.x, rc.y), cvPoint(rc.x + rc.width, rc.y + rc.height), CV_RGB(255, 0, 0));
    
    //裁剪出数字并灰度、二值化处理
    IplImage* imgNo = cvCreateImage(cvSize(rc.width, rc.height), imgSrc->depth, imgSrc->nChannels);
    IplImage* imgNoG = cvCreateImage(cvSize(rc.width, rc.height), IPL_DEPTH_8U, 1);
    cvSetImageROI(imgSrc, rc);
    cvCopy(imgSrc, imgNo);
    cvCvtColor(imgNo, imgNoG, CV_BGR2GRAY);
    cvThreshold(imgNoG, imgNoG, 100, 255, CV_THRESH_BINARY_INV);//
    //cvShowImage("cut", imgNo);
    cvReleaseMemStorage(&storage);
    cvReleaseImage(&imgNo);
    cvReleaseImage(&imgSrc);
    cvReleaseImage(&imgGray);
    
    //归一化大小
    IplImage *imgNor = 0;	//目标图像指针
    CvSize dstCvsize;	//目标图像尺寸
    dstCvsize.height = dstCvsize.width = norSize;
    imgNor = cvCreateImage(dstCvsize, imgNoG->depth, imgNoG->nChannels);	//构造目标图象
    cvResize(imgNoG, imgNor, CV_INTER_LINEAR);	//缩放源图像到目标图像
    //cvShowImage("nor", imgNor);
    //cvWaitKey(0);
    for( int i=0; i<imgNor->imageSize; i++ ) {
        data[i] = imgNor->imageData[i];
        //std::cout<< data[i] <<std::endl;
        if(data[i]>-1) {
            data[i] = 1;
        } else {
            data[i] = 0;
        }
    }
    
    cvReleaseImage(&imgNoG);
    cvReleaseImage(&imgNor);
    return true;
}

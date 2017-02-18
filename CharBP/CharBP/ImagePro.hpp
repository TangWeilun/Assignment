//
//  ImagePro.hpp
//  CharBP
//
//  Created by 唐伟伦 on 2017/1/25.
//  Copyright © 2017年 唐伟伦. All rights reserved.
//

#ifndef ImagePro_hpp
#define ImagePro_hpp

#include <stdio.h>

#endif /* ImagePro_hpp */
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
using namespace cv;

class CImagePro {
private:
    //归一化后图像的高和宽
    const static int norSize = 20;
    //储存提取的特征，等于长乘以宽
    int feaSize = 400;
    double data[400];
    
    char imageFile[15];
    FILE* dataFile;
    
    
    bool oneImagePro();
public:
    CImagePro();
    void imagePro();
};

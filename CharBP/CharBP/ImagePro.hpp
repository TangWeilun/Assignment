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
    int norSize;
    
    char imageFile[18];
    FILE* dataFile;
    
    bool oneImagePro();
public:
    CImagePro();
    bool imagePro();
};

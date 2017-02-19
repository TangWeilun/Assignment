//
//  main.cpp
//  CharBP
//
//  Created by 唐伟伦 on 2017/1/23.
//  Copyright © 2017年 唐伟伦. All rights reserved.
//

#include "ImagePro.hpp"
#include"BPNet.hpp"
#include<cstdlib>
#include<ctime>
#include<iostream>
using std::cout;
using std::cin;
using std::endl;




int main()
{
    
    /*
     原始图像处理、需要手动修改要处理的文件名和写入的文件名，分别在CImagePro()函数和imagePro(）函数中修改。
     由于本系统文件已经生成，故注释掉。
     */
    //CImagePro ip;
    //ip.imagePro();
    
    
    /*
     提取特征并添加标签
    */
    //原始数据
    double Data[trainsample][400];
    
    //输入样本
    double X[trainsample][innode];
    //期望输出样本
    double Y[trainsample][outnode];
    
    //读取训练文件
    FILE *fp = fopen("train.bin", "rb");
    for(int i=0; i<trainsample; i++ ) {
        fread(Data[i], sizeof(double), 400, fp);
        Y[i][0] = i/10;
        Y[i][0] /= 10;
    }
    
    fclose(fp);
    //特征提取
    int count;
    for(int k=0; k<trainsample; k++) {
        for(int i=0; i<20; i++) {
            count = 0;
            for(int j=1; j<20; j++) {
                if(Data[k][i*20+j] != Data[k][i*20+j-1]) {
                    count++;
                }
            }
            X[k][i] = count*0.1;
        }
    }
    
    /*
     BP网络训练
     */
    CBpNet bp;
    bp.init();
    int times=0;
    while(bp.error>0.001 && times < 200000)
    {
        bp.e=0.0;
        times++;
        bp.train(X,Y);
        cout<<"Times="<<times<<" error="<<bp.error<<endl;
    }
    cout<<"trainning complete..."<<endl;
    //写入权值文件
    bp.writetrain();
    
    /*
     BP网络测试
     */
    //读取测试文件
    fp = fopen("train.bin", "rb");
    for(int i=0; i<trainsample; i++ ) {
        fread(Data[i], sizeof(double), 400, fp);
        Y[i][0] = i/10;
        Y[i][0] /= 10;
    }
    
    fclose(fp);
    
    for(int k=0; k<trainsample; k++) {
        for(int i=0; i<20; i++) {
            count = 0;
            for(int j=1; j<20; j++) {
                if(Data[k][i*20+j] != Data[k][i*20+j-1]) {
                    count++;
                }
            }
            X[k][i] = count*0.1;
        }
    }
    
    
    //读取权值文件
    bp.readtrain();
    //测试
    count = 0;
    for(int i=0; i<trainsample; i++) {
        bp.recognize(X[i]);
        cout<< bp.result[0] << " "  << Y[i][0] << endl;
        if(fabs(bp.result[0]-Y[i][0])>0.01) {
            count++;
        }
    }
    
    for(int i=0; i<outnode; i++)
        cout<< "error:" << count << endl;
    return 0;
}

//
//  main.cpp
//  CharBP
//
//  Created by 唐伟伦 on 2017/1/23.
//  Copyright © 2017年 唐伟伦. All rights reserved.
//

/*#include "ImagePro.hpp"
#include "BP.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...

    CImagePro ip;
    ip.imagePro();
    CBP bp;
    char dataFile[10];
    strcpy(dataFile, "train.bin");
    bp.readData(dataFile);
    bp.initBPNework();
    bp.trainNetwork();
    strcpy(dataFile, "test.bin");
    bp.readData(dataFile);
    bp.testNetwork();
    
    
    return 0;
}*/

#include"BPNet.hpp"
#include<cstdlib>
#include<ctime>
#include<iostream>
using std::cout;
using std::cin;
using std::endl;




int main()
{
    
    //原始数据
    double Data[trainsample][400];
    
    
    //输入样本
    double X[trainsample][innode];
    //期望输出样本
    double Y[trainsample][outnode];
    
    
    FILE *fp = fopen("train.bin", "rb");
    for(int i=0; i<trainsample; i++ ) {
        fread(Data[i], sizeof(double), innode, fp);
        Y[i][0] = i/10;
        Y[i][0] /= 10;
    }
    
    fclose(fp);
    
    int count;
    for(int k=0; k<trainsample; k++) {
        for(int i=0; i<20; i++) {
            count = 0;
            for(int j=1; j<20; j++) {
                if(fabs(Data[i][j] - Data[i][j-1])>0.5) {
                    count++;
                }
            }
            X[k][i] = count*0.1;
        }
    }
    
    
    
    /*//输入样本
    double X[trainsample][innode]= {
        {0,0,0},{0,0,1},{0,1,0},{0,1,1},{1,0,0},{1,0,1},{1,1,0},{1,1,1}
    };
    //期望输出样本
    double Y[trainsample][outnode]={
        {0},{0.1429},{0.2857},{0.4286},{0.5714},{0.7143},{0.8571},{1.0000}
    };*/
    
    
    CBpNet bp;
    bp.init();
    int times=0;
    while(bp.error>0.0001)
    {
        bp.e=0.0;
        times++;
        bp.train(X,Y);
        cout<<"Times="<<times<<" error="<<bp.error<<endl;
    }
    cout<<"trainning complete..."<<endl;
    double m[innode]={1,1,1};
    bp.recognize(m);
    for(int i=0;i<outnode;++i)
        cout<<bp.result[i]<<" ";
    double cha[trainsample][outnode];
    double mi=100;
    int index = 0;
    for(int i=0;i<trainsample;i++)
    {
        for(int j=0;j<outnode;j++)
        {
            //找差值最小的那个样本
            cha[i][j]=(double)(fabs(Y[i][j]-bp.result[j]));
            if(cha[i][j]<mi)
            {
                mi=cha[i][j];
                index=i;
            }
        }
    }
    for(int i=0;i<innode;++i)
        cout<<m[i];
    cout<<" is "<<index<<endl;
    cout<<endl;
    return 0;
}

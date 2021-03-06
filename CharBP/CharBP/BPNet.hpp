//
//  BPNet.hpp
//  CharBP
//
//  Created by 唐伟伦 on 2017/2/18.
//  Copyright © 2017年 唐伟伦. All rights reserved.
//

#include<iostream>
#include<cmath>
using namespace std;

#define  innode 20  //输入结点数
#define  hidenode 30//隐含结点数
#define  outnode 1 //输出结点数
#define  trainsample 100//BP训练样本数
class CBpNet
{
public:
    void train(double p[trainsample][innode ],double t[trainsample][outnode]);//Bp训练
    double p[trainsample][innode];     //输入的样本
    double t[trainsample][outnode];    //样本要输出的
    
    double *recognize(double *p);//Bp识别
    
    void writetrain(); //写训练完的权值
    void readtrain(); //读训练好的权值，这使的不用每次去训练了，只要把训练最好的权值存下来就OK
    
    CBpNet();
    virtual ~CBpNet();
    
public:
    void init();
    double w[innode][hidenode];//隐含结点权值
    double w1[hidenode][outnode];//输出结点权值
    double b1[hidenode];//隐含结点阀值
    double b2[outnode];//输出结点阀值
    
    double rate_w; //权值学习率（输入层-隐含层)
    double rate_w1;//权值学习率 (隐含层-输出层)
    double rate_b1;//隐含层阀值学习率
    double rate_b2;//输出层阀值学习率
    
    double e;//误差计算
    double error;//允许的最大误差
    double result[outnode];// Bp输出
};

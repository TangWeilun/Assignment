//
//  BP.hpp
//  CharBP
//
//  Created by 唐伟伦 on 2017/1/23.
//  Copyright © 2017年 唐伟伦. All rights reserved.
//

#ifndef BP_hpp
#define BP_hpp

#include <stdio.h>

#endif /* BP_hpp */

#pragma once
#include<stdlib.h>
#include<math.h>
#include <time.h>

#define Data  100		//总训练样本的数量
#define In 400			//每个样本有多少个输入变量
#define Out 10			//每个样本有多少个输出变量
#define sData 10        //每种样本的数量
#define Neuron 500		//神经元的数量
#define TrainC 1000		//训练的次数
class CBP {
private:
    int d_in[Data][In];		//样本输入
    int d_out[Data][Out];	//样本输出
    double w[Neuron][In];	//某个输入对某个神经元的权重
    double dw[Neuron][In];	//修正量的数组
    double v[Out][Neuron];	//某个神经元对某个输出的权重
    double dv[Out][Neuron];	//修正量的数组
    double o[Neuron];		//神经元通过激活函数对外的输出
    double OutputData[Out];	//BP神经网络的输出
    
    double ErrorThresholds = 0.1;	//允许误差
    /*
     学习率
     */
    double A = 0.002;
    double B = 0.004;
    double a = 0.002;
    double b = 0.003;
    
    
public:
    bool readData(char* dataFile);		//读取样本数据
    void initBPNework();	//初始化BP神经网络
    void trainNetwork();	//训练BP神经网络
    void testNetwork();     //测试BP神经网络
    void computO(int var);	//计算BP神经网络预测第 var 个样本的输出
    void backUpdate(int var);	//根据预测的第 i 个样本输出对神经网络的权重进行更新
    void writeData(char* dataFile);	//写入训练后所得的w,v
};


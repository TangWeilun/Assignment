//
//  BP.cpp
//  CharBP
//
//  Created by 唐伟伦 on 2017/1/23.
//  Copyright © 2017年 唐伟伦. All rights reserved.
//

#include "BP.hpp"

bool CBP::readData(char* dataFile)
{
    return false;
}

void CBP::initBPNework()
{
    int i, j;
    /*
     　　　　找到数据最小、最大值
     
     for (i = 0; i<In; i++) {
     Minin[i] = Maxin[i] = d_in[0][i];
     for (j = 0; j<Data; j++)
     {
     Maxin[i] = Maxin[i]>d_in[j][i] ? Maxin[i] : d_in[j][i];
     Minin[i] = Minin[i]<d_in[j][i] ? Minin[i] : d_in[j][i];
     }
     }
     for (i = 0; i<Out; i++) {
     Minout[i] = Maxout[i] = d_out[0][i];
     for (j = 0; j<Data; j++)
     {
     Maxout[i] = Maxout[i]>d_out[j][i] ? Maxout[i] : d_out[j][i];
     Minout[i] = Minout[i]<d_out[j][i] ? Minout[i] : d_out[j][i];
     }
     }
     
     　　　　归一化处理
     
     for (i = 0; i < In; i++)
     for (j = 0; j < Data; j++)
     d_in[j][i] = (d_in[j][i] - Minin[i] + 1) / (Maxin[i] - Minin[i] + 1);
     for (i = 0; i < Out; i++)
     for (j = 0; j < Data; j++)
     d_out[j][i] = (d_out[j][i] - Minout[i] + 1) / (Maxout[i] - Minout[i] + 1);
     /*
     　　　　初始化神经元
     */
    for (i = 0; i < Neuron; ++i)
        for (j = 0; j < In; ++j) {
            w[i][j] = (rand()*2.0 / RAND_MAX - 1) / 2;
            dw[i][j] = 0;
        }
    for (i = 0; i < Neuron; ++i)
        for (j = 0; j < Out; ++j) {
            v[j][i] = (rand()*2.0 / RAND_MAX - 1) / 2;
            dv[j][i] = 0;
        }
}

void CBP::trainNetwork()
{
    int i, c = 0;
    double e;
    do {
        e = 0;
        for (i = 0; i < Data; ++i) {
            computO(i);
            e += fabs((OutputData[0] - d_out[i][0]) / d_out[i][0]);
            backUpdate(i);
        }
        //printf("%d  %lf\n",c,e/Data);
        c++;
    } while (c<TrainC && e / Data>ErrorThresholds);
}

void CBP::computO(int var)
{
    int i, j;
    double sum;
    
    /*
     神经元输出
     */
    
    for (i = 0; i < Neuron; ++i) {
        sum = 0;
        for (j = 0; j < In; ++j)
            sum += w[i][j] * d_in[var][j];
        o[i] = 1 / (1 + exp(-1 * sum));
    }
    
    /*  隐藏层到输出层输出 */
    
    for (i = 0; i < Out; ++i) {
        sum = 0;
        for (j = 0; j < Neuron; ++j)
            sum += v[i][j] * o[j];
        
        OutputData[i] = sum;
    }
}

void CBP::backUpdate(int var)
{
    int i, j;
    double t;
    for (i = 0; i < Neuron; ++i)
    {
        t = 0;
        for (j = 0; j < Out; ++j) {
            t += (OutputData[j] - d_out[var][j])*v[j][i];
            
            dv[j][i] = A*dv[j][i] + B*(OutputData[j] - d_out[var][j])*o[i];
            v[j][i] -= dv[j][i];
        }
        
        for (j = 0; j < In; ++j) {
            dw[i][j] = a*dw[i][j] + b*t*o[i] * (1 - o[i])*d_in[var][j];
            w[i][j] -= dw[i][j];
        }
    }
}

void CBP::writeData(char * dataFile)
{
    
}

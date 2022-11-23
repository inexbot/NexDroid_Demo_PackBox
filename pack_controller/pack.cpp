/*
 * pack.cpp
 *
 *  Created on: 2022年3月8日
 *      Author: anders
 */
#include "pack.h"
#include <iostream>
#include <pthread.h>
#include <cmath>
#include "nrcAPI.h"
#include <stdio.h>
#include <string>
#include <fstream>
#include "json/json.h"
#include <vector>
#include <time.h>
using namespace std;
#include<time.h>
#include <unistd.h>
unsigned sleep(unsigned seconds);
using namespace std;

extern Pack  pack;

void Pack::set_timeParam(double absorb_Time,double lengthways_Time,
															double across_Time,double pushing_Time)
{
	pack_timeParam.absorb_Time = absorb_Time;
	pack_timeParam.lengthways_Time = lengthways_Time;
	pack_timeParam.across_Time = across_Time;
	pack_timeParam.pushing_Time = pushing_Time;
}

//周期监控
double Pack::period_time_funtion()
{
	return period_param.period_time;
}
void Pack::open_period()
{
	pthread_t mytime;
	if(pthread_create(&mytime, NULL, call_period, (void*)&pack) == 0)//启动信号监控
	{
		printf("get_period thread create success_!\n");
	}
}

void* Pack::call_period(void *arg)
{
	Pack* pack_period = (Pack*)arg;
	pack_period->period_function();
	return 0;
}
void Pack::period_function()
{
	while(1)
	{
		clock_t start,stop;//周期标记
		//周期时间
		if( NRC_ReadBoolVar(1) )
		{
			start=clock();/*开始计时*/
			NRC_SetBoolVar(1, false);
			cout<<"程序第一行"<<endl;
		}

		if( NRC_ReadBoolVar(2) && NRC_GetCycleCount() > 1)
		{
			stop=clock();/*停止计时*/
			period_param.period_time = ((double)(stop-start))/CLOCKS_PER_SEC;/*计算运行时间*/
			NRC_SetBoolVar(2, false);
			cout<<period_param.period_time <<endl;
			cout<<"最后循环最后一行"<<endl;
		}
		if( NRC_ReadBoolVar(3) && NRC_GetCycleCount() ==1)
		{
			stop=clock();/*停止计时*/
			period_param.period_time  = ((double)(stop-start))/CLOCKS_PER_SEC;/*计算运行时间*/

			NRC_SetBoolVar(3, false);
			cout<<period_param.period_time <<endl;
			cout<<"程序最后一行"<<endl;
		}
	}
}
//周期监控__endl
//*****************/
////运行作业文件线程
void Pack::runPackFile()
{
	pthread_t file;
	if(pthread_create(&file, NULL, call_run_file, (void*)&pack) == 0)//启动信号监控
	{
		printf("get_period thread create success_!\n");
	}
}
void* Pack::call_run_file(void* arg)
{
	Pack* runfile = (Pack*)arg;
	runfile->run_file_function();
	return 0;
}
void Pack::run_file_function()
{
	NRC_StartRunJobfile("baohe_file");
	while (NRC_GetProgramRunStatus() != 0)  //等待运行结束
	{
		NRC_Delayms(500);   //延时100ms
		printf("line=%d,time=%d\n", NRC_GetJobfileCurrentRunLine(), NRC_GetCycleTimeSec());
	}
	NRC_StopRunJobfile();
}
//运行作业文件线程__endlallPos
//************/
//试运行一次
void Pack::runOnceAllPos()
{
	pthread_t allPos;
	if(pthread_create(&allPos, NULL, call_run_once, (void*)&pack) == 0)//启动信号监控
	{
		printf("get_period thread create success_!\n");
	}
}
void* Pack::call_run_once(void* arg)
{
	Pack* runOnce = (Pack*)arg;
	runOnce->run_once_function();
	return 0;
}
void Pack::run_once_function()
{

	Json::Value root_judge;
	Json::FastWriter wt_judge;
	Json::Reader reader_judge;
	ifstream in_judge("judge_exc_pos.json", ios :: binary);
	if(reader_judge.parse(in_judge, root_judge))
	{
		NRC_RobotMoveJoint(50, btn_startPos,80,80);
		while (NRC_GetProgramRunStatus() != 0)  //等待运行结束
		{
			NRC_Delayms(100);   //延时100ms
		}
		cout<<"1"<<endl;

		NRC_Delayms(100);   //延时100ms
//			NRC_StopRunJobfile();
		if(root_judge["exc"]["1"] == 1)
		{
			NRC_RobotMoveJoint(50, exc_pos_1,80,80);
			while (NRC_GetProgramRunStatus() != 0)  //等待运行结束
			{
				NRC_Delayms(100);   //延时100ms
			}
			cout<<"2"<<endl;
		}
		NRC_Delayms(100);   //延时100ms
//			NRC_StopRunJobfile();
		if(root_judge["exc"]["2"] == 1)
		{
			NRC_RobotMoveJoint(50, exc_pos_2,80,80);
			while (NRC_GetProgramRunStatus() != 0)  //等待运行结束
			{
				NRC_Delayms(100);   //延时100ms
			}
			cout<<"3"<<endl;
		}
		NRC_Delayms(100);   //延时100ms
//			NRC_StopRunJobfile();
		NRC_RobotMoveJoint(50, _materialPos,80,80);
		while (NRC_GetProgramRunStatus() != 0)  //等待运行结束
		{
			NRC_Delayms(100);   //延时100ms
		}
		cout<<"4"<<endl;
		NRC_Delayms(100);   //延时100ms
//			NRC_StopRunJobfile();
		if(root_judge["exc"]["3"] == 1)
		{
			NRC_RobotMoveJoint(50, exc_pos_3,80,80);
			while (NRC_GetProgramRunStatus() != 0)  //等待运行结束
			{
				NRC_Delayms(100);   //延时100ms
			}

			cout<<"5"<<endl;
		}
		NRC_Delayms(100);   //延时100ms
//			NRC_StopRunJobfile();
		if(root_judge["exc"]["4"] == 1)
		{
			NRC_RobotMoveJoint(50, exc_pos_4,80,80);
			while (NRC_GetProgramRunStatus() != 0)  //等待运行结束
			{
				NRC_Delayms(100);   //延时100ms
			}
			cout<<"6"<<endl;
		}
		NRC_Delayms(100);   //延时100ms
//			NRC_StopRunJobfile();
		NRC_RobotMoveJoint(50, box_setPos,80,80);
		while (NRC_GetProgramRunStatus() != 0)  //等待运行结束
		{
			NRC_Delayms(100);   //延时100ms
		}
		cout<<"7"<<endl;
		NRC_Delayms(100);   //延时100ms
//			NRC_StopRunJobfile();
		if(root_judge["exc"]["5"] == 1)
		{
			NRC_RobotMoveJoint(50, exc_pos_5,80,80);
			while (NRC_GetProgramRunStatus() != 0)  //等待运行结束
			{
				NRC_Delayms(100);   //延时100ms
			}
			cout<<"8"<<endl;
		}
		NRC_Delayms(100);   //延时100ms
//			NRC_StopRunJobfile();
		if(root_judge["exc"]["6"] == 1)
		{
			NRC_RobotMoveJoint(50, exc_pos_6,80,80);
			while (NRC_GetProgramRunStatus() != 0)  //等待运行结束
			{
				NRC_Delayms(100);   //延时100ms
			}
			cout<<"9"<<endl;
		}
		NRC_Delayms(100);   //延时100ms
//			NRC_StopRunJobfile();
		NRC_RobotMoveJoint(50, btn_stopPos,80,80);
		while (NRC_GetProgramRunStatus() != 0)  //等待运行结束
		{
			NRC_Delayms(100);   //延时100ms
		}
		cout<<"10"<<endl;
		NRC_StopRunJobfile();
	}
	else
	{
		printf("judge_exc_pos.json  fail !");
	}
}
//试运行一次__endl


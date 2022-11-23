/*
 * pack.h
 *
 *  Created on: 2022年3月8日
 *      Author: anders
 */

#ifndef PACK_H_
#define PACK_H_
#include<string>
#include <vector>
#include "nrcAPI.h"
using namespace std;
class Pack
{
public:

		int g_run_number = 0;//开机后运行次数
		double g_run_time ;//开机后运行时间
		int g_sum = 0;//累计总产量
		int g_sum_tmp = 0;//累计总产量的中间变量
		int run_number = 0;//开机后运行次数的中间变量２
		bool judge_start_pos = false;//判断是否在起点
		bool judge_io1 = false;//调试变量1
		bool judge_io4 = false;//调试变量4
		NRC_Position btn_startPos;
		NRC_Position exc_pos_1;
		NRC_Position exc_pos_2;
		NRC_Position _materialPos;
		NRC_Position exc_pos_3;
		NRC_Position exc_pos_4;
		NRC_Position box_setPos;
		NRC_Position exc_pos_5;
		NRC_Position exc_pos_6;
		NRC_Position btn_stopPos;
	struct pack_TimeParam
	{
		double absorb_Time;
		double lengthways_Time ;
		double across_Time;
		double pushing_Time;
		pack_TimeParam()
		{
			absorb_Time = 1;
			lengthways_Time = 1;
			across_Time = 1;
			pushing_Time = 1;
		}
	};
	struct period_Param
	{
		double period_time;
		period_Param()
		{
			period_time = 0.00;
		}
	};

	void set_timeParam(double absorb_Time,double lengthways_Time,
												double across_Time,double pushing_Time);


	void open_period();
	static  void *call_period(void *arg);
	void period_function();
	double period_time_funtion();

	void runPackFile();
	static void* call_run_file(void* arg);
	void run_file_function();

	void runOnceAllPos();
	static void* call_run_once(void* arg);
	void run_once_function();

private:
	pack_TimeParam pack_timeParam;
	period_Param period_param;
};




#endif /* PACK_H_ */

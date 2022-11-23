#include <iostream>
#include "nrcAPI.h"
#include "json/json.h"
using namespace std;
#include "pack.h"
#include<stdio.h>
#include <fstream>
#include <pthread.h>
#include<string>
#include<time.h>
#include <unistd.h>
unsigned sleep(unsigned seconds);
using namespace std;
Pack  pack;
using namespace std;

 void params_access()//初始化
 {
	 //参数设定，起Ｊｓｏｎ文件保存
	 fstream screwfile;
	 screwfile.open("packParam.json", ios :: in);
	 Json::Value rootparam, root,root_sum_now,root_sum,root_judge,root_judge_exc,root_judge_exc_seed,root_file;
	 Json::Reader reader, Reader,reader_sum,reader_judge;
	 Json::StyledWriter wt,wt1, wt_judge_exc, wt_judge_exc_seed, wt_file;
	 if(!screwfile)
	 {
		 rootparam["Time"]["absorb_Time"] = 1;
		 rootparam["Time"]["lengthways_Time"] =1;
		 rootparam["Time"]["across_Time"] = 1;
		 rootparam["Time"]["pushing_Time"] = 1;
		 ofstream os;
		 os.open("packParam.json");
		 os<<wt.write(rootparam);
		 os.close();
	 }
	 else
	 {
		 screwfile.close();
		 ifstream in("packParam.json");
		 if(reader.parse(in, rootparam))
		 {
			 printf("param access succeed!\n");
			 in.close();
		 }
	 }
	 //参数从ｊｓｏｎ读出来后，参数初始化
	 double T1,T2,T3,T4;
	 T1 = rootparam["Time"]["absorb_Time"].asDouble();
	 T2 = rootparam["Time"]["lengthways_Time"].asDouble();
	 T3 = rootparam["Time"]["across_Time"].asDouble();
	 T4 = rootparam["Time"]["pushing_Time"].asDouble();
	 pack.set_timeParam(T1,T2,T3,T4);
	 //参数初始化__endl
	 //**sum，为了下电保护总产量，起Ｊｓｏｎ文件保存sum
	 fstream screwfile_sum;
	 screwfile_sum.open("sumParam.json", ios :: in);
	 if(!screwfile_sum)
	 {
		 root_sum_now["sum"] = 0;
		 ofstream os;
		 os.open("sumParam.json");
		 os.close();
	 }
	 else
	 {
		 screwfile_sum.close();
		 ifstream in("sumParam.json");
		 if(reader_sum.parse(in, root_sum))
		 {
			 //				 printf("sumparam access succeed!\n");
			 in.close();
		 }
	 }
	 pack.g_sum = root_sum["sum"].asInt();
	 pack.g_sum_tmp = pack.g_sum;
	 //**sum_endl
	 //初始化过渡点
	 fstream screwfile_judge;
	 screwfile_judge.open("judge_exc_pos.json", ios :: in);
	 if(!screwfile_judge)
	 {
		 root_judge["exc"]["1"] = 0;
		 root_judge["exc"]["2"] = 0;
		 root_judge["exc"]["3"] = 0;
		 root_judge["exc"]["4"] = 0;
		 root_judge["exc"]["5"] = 0;
		 root_judge["exc"]["6"] = 0;
		 ofstream os;
		 os.open("judge_exc_pos.json");
		 os.close();
	 }
	 else
	 {
		 screwfile_judge.close();
		 ifstream in("judge_exc_pos.json");
		 if(reader_judge.parse(in, root_judge_exc))
		 {
			 printf("judge_exc_pos access succeed!\n");
			 in.close();
		 }
		 root_judge_exc_seed["exc"]["1"] = root_judge_exc["exc"]["1"].asInt();
		 root_judge_exc_seed["exc"]["2"] = root_judge_exc["exc"]["2"].asInt();
		 root_judge_exc_seed["exc"]["3"] = root_judge_exc["exc"]["3"].asInt();
		 root_judge_exc_seed["exc"]["4"] = root_judge_exc["exc"]["4"].asInt();
		 root_judge_exc_seed["exc"]["5"] = root_judge_exc["exc"]["5"].asInt();
		 root_judge_exc_seed["exc"]["6"] = root_judge_exc["exc"]["6"].asInt();
		 NRC_SendSocketCustomProtocal(0x920b,wt_judge_exc_seed.write(root_judge_exc_seed));
	 }
	 //初始化过渡点___endl

	 //**Pos 从ｊｓｏｎ读出来后，参数初始化
	 fstream screwfile_pos;
	 screwfile_pos.open("PosParam.json", ios :: in);
	 if(!screwfile_pos)
	 {
		 ofstream os1;
		 os1.open("PosParam.json");
		 os1.close();
	 }
	 else
	 {
		 screwfile_pos.close();
		 ifstream in("PosParam.json");
		 if(Reader.parse(in, root))
		 {
			 printf("Posparam access succeed!\n");
			 in.close();
		 }
	 }
	 //把上次存在作业文件的点位拿出来，赋值给对象点
	 double pos_btn_startPos[7] = {root["btn_startPos"]["J1"].asDouble(),  root["btn_startPos"]["J2"].asDouble(), root["btn_startPos"]["J3"].asDouble(),
			 root["btn_startPos"]["J4"].asDouble(), root["btn_startPos"]["J5"].asDouble(), root["btn_startPos"]["J6"].asDouble(), 0.00 };
	 pack.btn_startPos = { NRC_ACS,0,0,0,pos_btn_startPos };

	 double exc_pos_1_pos[7] = {root["exc_pos_1"]["J1"].asDouble(),  root["exc_pos_1"]["J2"].asDouble(), root["exc_pos_1"]["J3"].asDouble(),
			 root["exc_pos_1"]["J4"].asDouble(), root["exc_pos_1"]["J5"].asDouble(), root["exc_pos_1"]["J6"].asDouble(), 0.00 };
	 pack.exc_pos_1 = { NRC_ACS,0,0,0,exc_pos_1_pos };

	 double exc_pos_2_pos[7] = {root["exc_pos_2"]["J1"].asDouble(),  root["exc_pos_2"]["J2"].asDouble(), root["exc_pos_2"]["J3"].asDouble(),
			 root["exc_pos_2"]["J4"].asDouble(), root["exc_pos_2"]["J5"].asDouble(), root["exc_pos_2"]["J6"].asDouble(), 0.00 };
	 pack.exc_pos_2 = { NRC_ACS,0,0,0,exc_pos_2_pos };

	 double _materialPos_pos[7] = {root["_materialPos"]["J1"].asDouble(),  root["_materialPos"]["J2"].asDouble(), root["_materialPos"]["J3"].asDouble(),
			 root["_materialPos"]["J4"].asDouble(), root["_materialPos"]["J5"].asDouble(), root["_materialPos"]["J6"].asDouble(), 0.00 };
	 pack._materialPos = { NRC_ACS,0,0,0,_materialPos_pos };

	 double exc_pos_3_pos[7] = {root["exc_pos_3"]["J1"].asDouble(),  root["exc_pos_3"]["J2"].asDouble(), root["exc_pos_3"]["J3"].asDouble(),
			 root["exc_pos_3"]["J4"].asDouble(), root["exc_pos_3"]["J5"].asDouble(), root["exc_pos_3"]["J6"].asDouble(), 0.00 };
	 pack.exc_pos_3 = { NRC_ACS,0,0,0,exc_pos_3_pos };

	 double exc_pos_4_pos[7] = {root["exc_pos_4"]["J1"].asDouble(),  root["exc_pos_4"]["J2"].asDouble(), root["exc_pos_4"]["J3"].asDouble(),
			 root["exc_pos_4"]["J4"].asDouble(), root["exc_pos_4"]["J5"].asDouble(), root["exc_pos_4"]["J6"].asDouble(), 0.00 };
	 pack.exc_pos_4 = { NRC_ACS,0,0,0,exc_pos_4_pos };

	 double box_setPos_pos[7] = {root["box_setPos"]["J1"].asDouble(),  root["box_setPos"]["J2"].asDouble(), root["box_setPos"]["J3"].asDouble(),
			 root["box_setPos"]["J4"].asDouble(), root["box_setPos"]["J5"].asDouble(), root["box_setPos"]["J6"].asDouble(), 0.00 };
	 pack.box_setPos = { NRC_ACS,0,0,0,box_setPos_pos };

	 double exc_pos_5_pos[7] = {root["exc_pos_5"]["J1"].asDouble(),  root["exc_pos_5"]["J2"].asDouble(), root["exc_pos_5"]["J3"].asDouble(),
			 root["exc_pos_5"]["J4"].asDouble(), root["exc_pos_5"]["J5"].asDouble(), root["exc_pos_5"]["J6"].asDouble(), 0.00 };
	 pack.exc_pos_5 = { NRC_ACS,0,0,0,exc_pos_5_pos };

	 double exc_pos_6_pos[7] = {root["exc_pos_6"]["J1"].asDouble(),  root["exc_pos_6"]["J2"].asDouble(), root["exc_pos_6"]["J3"].asDouble(),
			 root["exc_pos_6"]["J4"].asDouble(), root["exc_pos_6"]["J5"].asDouble(), root["exc_pos_6"]["J6"].asDouble(), 0.00 };
	 pack.exc_pos_6 = { NRC_ACS,0,0,0,exc_pos_6_pos };

	 double pos__btn_stopPos[7] = {root["btn_stopPos"]["J1"].asDouble(),  root["btn_stopPos"]["J2"].asDouble(), root["btn_stopPos"]["J3"].asDouble(),
			 root["btn_stopPos"]["J4"].asDouble(), root["btn_stopPos"]["J5"].asDouble(), root["btn_stopPos"]["J6"].asDouble(), 0.00 };
	 pack.btn_stopPos = { NRC_ACS,0,0,0,pos__btn_stopPos };
	 NRC_StopRunJobfile();

	 //初始化标记位
	 NRC_SetBoolVar(1, false);
	 NRC_SetBoolVar(2, false);
	 NRC_SetBoolVar(3, false);
	 NRC_SetBoolVar(4, false);
	 NRC_SetBoolVar(7, true);
}
void printffff(string str)//修改控制器参数
{
	Json::Value root, str_root, send;
	Json::Reader Reader, reader;
	Json::StyledWriter wt;
	cout<<"-----------------------------------test-----------------------------"<<endl;
	cout<<str<<endl;
	if(Reader.parse(str, str_root) && str_root.size() != 0)
	{
		if(str_root["robot_Param"] == "robot_Param")
		{
			ifstream in("packParam.json", ios :: binary);
			if(reader.parse(in,root))
			{
				printf("Param access succeed!");
				in.close();
			}
			root["Time"]["absorb_Time"] =  str_root["Time"]["absorb_Time"].asDouble();
			root["Time"]["lengthways_Time"] =  str_root["Time"]["lengthways_Time"].asDouble();
			root["Time"]["across_Time"] =  str_root["Time"]["across_Time"].asDouble();
			root["Time"]["pushing_Time"] =  str_root["Time"]["pushing_Time"].asDouble();
			root["robot"]["coormode"] = str_root["robot"]["coormode"].asInt();
			ofstream os;
			os.open("packParam.json");
			os << wt.write(root);
		}
	}
	params_access();
}
void message(string str )//发送参数给示教盒同步
{
	if(str == "参数设定")
	{
		cout << str << endl;
		Json::StyledWriter wt;
		Json::Value root,send;
		Json::Value str_root;
		Json::Reader reader;
		Json::Reader reader_str;
		ifstream in("packParam.json", ios::binary);
		if (reader.parse(in, root)) //本地Json
		{
			printf("param access succeed!\n");
			send["Time"]["absorb_Time"] =  root["Time"]["absorb_Time"].asDouble();
			send["Time"]["lengthways_Time"] =  root["Time"]["lengthways_Time"].asDouble();
			send["Time"]["across_Time"] =  root["Time"]["across_Time"].asDouble();
			send["Time"]["pushing_Time"] =  root["Time"]["pushing_Time"].asDouble();

			NRC_SendSocketCustomProtocal(0x9202,wt.write(send));
			in.close();
		}
		else
		{
			printf("param access fail !");
		}
	}
	//未保存后，可以再次把作业文件的对象点拿出来，给回中间对象点
	if(str == "点位管理")
	{
		cout<<"点位管理"<<endl;
	}
}
void get_read_time(string str)//实时时钟
{
	Json::Value send,root,root1,root2;
	Json::FastWriter wt,wt1;
	Json::Reader reader, reader1;

	pack.g_run_time = NRC_GetCycleTimeSec();//运行时间
//调试状态下同步开关
	if(NRC_GetCycleCount() > 1 && pack.judge_io1 )
	{
		NRC_SetIntVar(1, 1);
	}
	if(NRC_GetCycleCount() > 1 && pack.judge_io4)
	{
		NRC_SetIntVar(4, 1);
	}
//程序最后计数
	if(NRC_ReadBoolVar(3))
	{
		pack.g_run_number =  NRC_GetCycleCount();//获取当前作业文件已运行的次数，返回当前作业文件已运行的次数。
		pack.g_sum = pack.g_sum_tmp + pack.g_run_number;//总产量
		NRC_SetBoolVar(3, false);
	}
	//当运行状态不能修改运行模式
	if(NRC_GetProgramRunStatus() == 0)
	{
		NRC_SendSocketCustomProtocal(0x9208,"enable_rnn_mode");
		NRC_SendSocketCustomProtocal(0x9208,"enable_reset");
	}
	//当非运行状态可以修改运行模式
	if(NRC_GetProgramRunStatus() == 2)
	{
		NRC_SendSocketCustomProtocal(0x9208,"disable_rnn_mode");
		NRC_SendSocketCustomProtocal(0x9208,"disable_reset");
	}
	//***sum
	ifstream in3("sumParam.json", ios :: binary);
	if(reader.parse(in3,root1))
	{
		in3.close();
	}
	root1["sum"] = pack.g_sum;
	ofstream os1;
	os1.open("sumParam.json");
	os1 << wt1.write(root1);

	ifstream in4("sumParam.json", ios::binary);
	if (reader1.parse(in4, root2)) //本地Json
	{
		cout<< root2["sum"].asInt()<<endl;
		pack.g_sum =  root2["sum"].asInt();
	}

	send["run_number"] = pack.g_run_number;
	send["run_time"] = pack.g_run_time;
	send["cicle_time"] = pack.period_time_funtion();
	send["sum"] = pack.g_sum;

	//**IO
	//in
	send["IO1"] = NRC_ReadDigIn(1);
	send["IO2"] = NRC_ReadDigIn(2);
	send["IO3"] = NRC_ReadDigIn(3);
	send["IO4"] = NRC_ReadDigIn(4);
	send["IO5"] = NRC_ReadDigIn(5);
	//out
	send["IO1_out"] = NRC_ReadDigOut(1);
	send["IO2_out"] = NRC_ReadDigOut(2);
	send["IO5_out"] = NRC_ReadDigOut(5);
	send["IO6_out"] = NRC_ReadDigOut(6);
	send["IO7_out"] = NRC_ReadDigOut(7);
	send["IO8_out"] = NRC_ReadDigOut(8);
	send["IO9_out"] = NRC_ReadDigOut(9);

	//虚拟io输入，用于调试
	send["IO1_in"] = NRC_ReadIntVar(1);
	send["IO2_in"] = NRC_ReadIntVar(2);
	send["IO3_in"] = NRC_ReadIntVar(3);
	send["IO4_in"] = NRC_ReadIntVar(4);
	send["IO5_in"] = NRC_ReadIntVar(5);

	//实时更新坐标
	if(str == "关节")
	{
		//		cout<<"关节"<<endl;
		NRC_Position inexbot;
		inexbot.coord = NRC_ACS;
		NRC_GetCurrentPos(NRC_ACS, inexbot); //获取当前位置(关节)
		send["pos"]["1"] = inexbot.pos[0];
		send["pos"]["2"] = inexbot.pos[1];
		send["pos"]["3"] = inexbot.pos[2];
		send["pos"]["4"] = inexbot.pos[3];
		send["pos"]["5"] = inexbot.pos[4];
		send["pos"]["6"] = inexbot.pos[5];
		NRC_SendSocketCustomProtocal(0x9205,wt.write(send));
	}
	if(str == "直角")
	{
		NRC_Position inexbot;
		inexbot.coord = NRC_MCS;
		NRC_GetCurrentPos(NRC_MCS, inexbot); //获取当前位置(关节)
		send["pos"]["1"]=inexbot.pos[0];
		send["pos"]["2"]=inexbot.pos[1];
		send["pos"]["3"]=inexbot.pos[2];
		send["pos"]["4"]=inexbot.pos[3];
		send["pos"]["5"]=inexbot.pos[4];
		send["pos"]["6"]=inexbot.pos[5];
		NRC_SendSocketCustomProtocal(0x9205,wt.write(send));
	}
	if(str == "工具")
	{
		NRC_Position inexbot;
		inexbot.coord = NRC_PCS;
		NRC_GetCurrentPos(NRC_PCS, inexbot); //获取当前位置(关节)
		send["pos"]["1"]=inexbot.pos[0];
		send["pos"]["2"]=inexbot.pos[1];
		send["pos"]["3"]=inexbot.pos[2];
		send["pos"]["4"]=inexbot.pos[3];
		send["pos"]["5"]=inexbot.pos[4];
		send["pos"]["6"]=inexbot.pos[5];
		NRC_SendSocketCustomProtocal(0x9205,wt.write(send));
	}
	if(str == "用户")
	{
		NRC_Position inexbot;
		inexbot.coord = NRC_UCS;
		NRC_GetCurrentPos(NRC_UCS, inexbot); //获取当前位置(关节)
		send["pos"]["1"]=inexbot.pos[0];
		send["pos"]["2"]=inexbot.pos[1];
		send["pos"]["3"]=inexbot.pos[2];
		send["pos"]["4"]=inexbot.pos[3];
		send["pos"]["5"]=inexbot.pos[4];
		send["pos"]["6"]=inexbot.pos[5];
		NRC_SendSocketCustomProtocal(0x9205,wt.write(send));
	}
	if(NRC_ReadDigOut(9) == 1)
	{
		NRC_SendSocketCustomProtocal(0x9208,"alarm_light");
	}
	else
	{
		NRC_SendSocketCustomProtocal(0x9208,"alarm_down");
	}
	if(!NRC_GetTeachBoxConnectStatus())// 如果断开连接了示教盒, 作业文件马上停止
	{
		NRC_StopRunJobfile();
	}

}
void sign_pos_and_file_updata(string str)//标记点和更新作业文件
{
	Json::Value root_str;
	Json::Reader reader_str;
	reader_str.parse(str, root_str);
	if( NRC_GetServoStatus() != 3)//在伺服下电才可以保存
	{
		if(root_str["Point"].asString() == "起点")
		{
			NRC_GetCurrentPos(NRC_ACS, pack.btn_startPos); //获取0当前位置
		}
		if(root_str["Point"].asString() == "过渡点1")
		{
			NRC_GetCurrentPos(NRC_ACS, pack.exc_pos_1); //获取1当前位置
		}
		if(root_str["Point"].asString() == "过渡点2")
		{
			NRC_GetCurrentPos(NRC_ACS, pack.exc_pos_2); //获取2当前位置
		}
		if(root_str["Point"].asString() == "取料点")
		{
			NRC_GetCurrentPos(NRC_ACS, pack._materialPos); //获取3当前位置
		}
		if(root_str["Point"].asString() == "过渡点3")
		{
			NRC_GetCurrentPos(NRC_ACS, pack.exc_pos_3); //获取4当前位置
		}
		if(root_str["Point"].asString() == "过渡点4")
		{
			NRC_GetCurrentPos(NRC_ACS, pack.exc_pos_4); //获取5当前位置
		}
		if(root_str["Point"].asString() == "套盒点")
		{
			NRC_GetCurrentPos(NRC_ACS, pack.box_setPos); //获取6当前位置
		}
		if(root_str["Point"].asString() == "过渡点5")
		{
			NRC_GetCurrentPos(NRC_ACS, pack.exc_pos_5); //获取7当前位置
		}
		if(root_str["Point"].asString() == "过渡点6")
		{
			NRC_GetCurrentPos(NRC_ACS, pack.exc_pos_6); //获取8当前位置
		}
		if(root_str["Point"].asString() == "结束点")
		{
			NRC_GetCurrentPos(NRC_ACS, pack.btn_stopPos); //获取9当前位置
		}

		//** 将点保存在作业文件
		Json::Value root;
		Json::Reader  reader_file;
		Json::StyledWriter wt_file;
		ifstream in_file("PosParam.json", ios :: binary);
		if(reader_file.parse(in_file,root))
		{
			printf("PosParam access succeed!");
			in_file.close();
		}
		root["btn_startPos"]["J1"] = pack.btn_startPos.pos[0];
		root["btn_startPos"]["J2"] = pack.btn_startPos.pos[1];
		root["btn_startPos"]["J3"] = pack.btn_startPos.pos[2];
		root["btn_startPos"]["J4"] = pack.btn_startPos.pos[3];
		root["btn_startPos"]["J5"] = pack.btn_startPos.pos[4];
		root["btn_startPos"]["J6"] = pack.btn_startPos.pos[5];

		root["exc_pos_1"]["J1"] = pack.exc_pos_1.pos[0];
		root["exc_pos_1"]["J2"] = pack.exc_pos_1.pos[1];
		root["exc_pos_1"]["J3"] = pack.exc_pos_1.pos[2];
		root["exc_pos_1"]["J4"] = pack.exc_pos_1.pos[3];
		root["exc_pos_1"]["J5"] = pack.exc_pos_1.pos[4];
		root["exc_pos_1"]["J6"] = pack.exc_pos_1.pos[5];

		root["exc_pos_2"]["J1"] = pack.exc_pos_2.pos[0];
		root["exc_pos_2"]["J2"] = pack.exc_pos_2.pos[1];
		root["exc_pos_2"]["J3"] = pack.exc_pos_2.pos[2];
		root["exc_pos_2"]["J4"] = pack.exc_pos_2.pos[3];
		root["exc_pos_2"]["J5"] = pack.exc_pos_2.pos[4];
		root["exc_pos_2"]["J6"] = pack.exc_pos_2.pos[5];

		root["_materialPos"]["J1"] = pack._materialPos.pos[0];
		root["_materialPos"]["J2"] = pack._materialPos.pos[1];
		root["_materialPos"]["J3"] = pack._materialPos.pos[2];
		root["_materialPos"]["J4"] = pack._materialPos.pos[3];
		root["_materialPos"]["J5"] = pack._materialPos.pos[4];
		root["_materialPos"]["J6"] = pack._materialPos.pos[5];

		root["exc_pos_3"]["J1"] = pack.exc_pos_3.pos[0];
		root["exc_pos_3"]["J2"] = pack.exc_pos_3.pos[1];
		root["exc_pos_3"]["J3"] = pack.exc_pos_3.pos[2];
		root["exc_pos_3"]["J4"] = pack.exc_pos_3.pos[3];
		root["exc_pos_3"]["J5"] = pack.exc_pos_3.pos[4];
		root["exc_pos_3"]["J6"] = pack.exc_pos_3.pos[5];

		root["exc_pos_4"]["J1"] = pack.exc_pos_4.pos[0];
		root["exc_pos_4"]["J2"] = pack.exc_pos_4.pos[1];
		root["exc_pos_4"]["J3"] = pack.exc_pos_4.pos[2];
		root["exc_pos_4"]["J4"] = pack.exc_pos_4.pos[3];
		root["exc_pos_4"]["J5"] = pack.exc_pos_4.pos[4];
		root["exc_pos_4"]["J6"] = pack.exc_pos_4.pos[5];

		root["box_setPos"]["J1"] = pack.box_setPos.pos[0];
		root["box_setPos"]["J2"] = pack.box_setPos.pos[1];
		root["box_setPos"]["J3"] = pack.box_setPos.pos[2];
		root["box_setPos"]["J4"] = pack.box_setPos.pos[3];
		root["box_setPos"]["J5"] = pack.box_setPos.pos[4];
		root["box_setPos"]["J6"] = pack.box_setPos.pos[5];

		root["exc_pos_5"]["J1"] = pack.exc_pos_5.pos[0];
		root["exc_pos_5"]["J2"] = pack.exc_pos_5.pos[1];
		root["exc_pos_5"]["J3"] = pack.exc_pos_5.pos[2];
		root["exc_pos_5"]["J4"] = pack.exc_pos_5.pos[3];
		root["exc_pos_5"]["J5"] = pack.exc_pos_5.pos[4];
		root["exc_pos_5"]["J6"] = pack.exc_pos_5.pos[5];

		root["exc_pos_6"]["J1"] = pack.exc_pos_6.pos[0];
		root["exc_pos_6"]["J2"] = pack.exc_pos_6.pos[1];
		root["exc_pos_6"]["J3"] = pack.exc_pos_6.pos[2];
		root["exc_pos_6"]["J4"] = pack.exc_pos_6.pos[3];
		root["exc_pos_6"]["J5"] = pack.exc_pos_6.pos[4];
		root["exc_pos_6"]["J6"] = pack.exc_pos_6.pos[5];

		root["btn_stopPos"]["J1"] = pack.btn_stopPos.pos[0];
		root["btn_stopPos"]["J2"] = pack.btn_stopPos.pos[1];
		root["btn_stopPos"]["J3"] = pack.btn_stopPos.pos[2];
		root["btn_stopPos"]["J4"] = pack.btn_stopPos.pos[3];
		root["btn_stopPos"]["J5"] = pack.btn_stopPos.pos[4];
		root["btn_stopPos"]["J6"] = pack.btn_stopPos.pos[5];

		ofstream os_file;
		os_file.open("PosParam.json");
		os_file << wt_file.write(root);
		//** 将点保存在作业文件___End

		//解析参数数据
		Json::Value root_param;
		Json::Reader  reader_param;
		ifstream in_param("packParam.json", ios :: binary);
		if(reader_param.parse(in_param, root_param))
		{
			cout<<"成功解析packParam"<<endl;
		}
		//解析参数数据____End

		//***file操作
		NRC_DeleteJobfile("baohe_file");
		if (NRC_JudgeJobIsExist("baohe_file") == 0)
		{
			cout << "作业文件不存在" << endl;
		}
		NRC_CreateJobfile("baohe_file");//创建作业文件INEXBOT1
		NRC_OpenJobfile("baohe_file");

		NRC_JobfileInsertDOUT(1, 1, 0);//端口1输出为零
		NRC_JobfileInsertDOUT(2, 2, 0);//端口2输出为零
		NRC_JobfileInsertDOUT(3, 5, 0);//端口5输出为零
		NRC_JobfileInsertDOUT(4, 6, 0);//端口6输出为零
		NRC_JobfileInsertDOUT(5, 7, 0);//端口7输出为零
		NRC_JobfileInsertDOUT(6, 8, 0);//端口8输出为零
		NRC_JobfileInsertSETVAR(7,"GI001", 0);//定义int变量GI001;对应ｉｏ1
		NRC_JobfileInsertSETVAR(8,"GI004", 0);//定义int变量GI004;对应ｉｏ４
		NRC_JobfileInsertMOVJ(9, 100, 100, 100, pack.btn_startPos, 5);//起点
		NRC_JobfileInsertSETVAR(10, "GB002", true );//计时２
		NRC_JobfileInsertSETVAR(11, "GB001", true );//计时１
		NRC_JobfileInsertMOVJ(12, 100, 100, 100, pack.exc_pos_1, 5);//过渡点1
		NRC_JobfileInsertMOVJ(13, 100, 100, 100, pack.exc_pos_2, 5);//过渡点2
		NRC_JobfileInsertMOVL(14, 1500, 100, 100, pack._materialPos, 5);//取料点
		NRC_JobfileInsertWAIT(15, 1, 1, 0, 1);//来料检测*******************ｉｏ1
		NRC_JobfileInsertCMDNOTE(16, "wait");//
		NRC_JobfileInsertCMDNOTE(17, "endwhile");//
		NRC_JobfileInsertDOUT(18, 5, 1);//端口5输出为1
		NRC_JobfileInsertTIMER(19, 0.05);
		NRC_JobfileInsertDOUT(20, 6, 1);//端口6输出为1
		NRC_JobfileInsertTIMER(21, 0.05);
		NRC_JobfileInsertDOUT(22, 8, 1);//端口8输出为1
		NRC_JobfileInsertTIMER(23, 0.05);
		NRC_JobfileInsertDOUT(24, 7, 1);//端口7输出为1  吸盘
		NRC_JobfileInsertTIMER(25, root_param["Time"]["absorb_Time"].asDouble());
		NRC_JobfileInsertMOVJ(26, 100, 100, 100, pack.exc_pos_3, 5);//过渡点3
		NRC_JobfileInsertMOVJ(27, 100, 100, 100, pack.exc_pos_4, 5);//过渡点4
		NRC_JobfileInsertWAIT(28, 4, 1,  0, 1);//成型进入允许*************************ｉｏ4
		NRC_JobfileInsertCMDNOTE(29, "wait");//
		NRC_JobfileInsertCMDNOTE(30, "endwhile");//
		NRC_JobfileInsertMOVL(31, 1500, 100, 100, pack.box_setPos, 0);//套盒点
			NRC_JobfileInsertDOUT(32, 1, 1);//端口1输出为1   成型机启动
			NRC_JobfileInsertTIMER(33, 0.1);
			NRC_JobfileInsertDOUT(34, 1, 0);//端口1输出为1   成型机关闭
			NRC_JobfileInsertTIMER(35, root_param["Time"]["lengthways_Time"].asDouble());//套盒等待时间
			NRC_JobfileInsertDOUT(36, 7, 0);//端口7输出为0   关闭吸盘
			NRC_JobfileInsertDOUT(37, 5, 0);//端口5输出为0
			NRC_JobfileInsertDOUT(38, 6, 0);//端口6输出为0
			NRC_JobfileInsertDOUT(39, 8, 0);//端口8输出为0
		NRC_JobfileInsertMOVL(40, 1500, 100, 100, pack.exc_pos_5, 5);//过渡点5
		NRC_JobfileInsertMOVJ(41, 100, 100, 100, pack.exc_pos_6, 5);//过渡点6
		NRC_JobfileInsertMOVJ(42, 100, 100, 100, pack.btn_stopPos, 5);//结束点
		NRC_JobfileInsertSETVAR(43, "GB003", true );//计时3
		//***file操作____End
        //***切换调试作业文件
		if(root_str["check"].asInt() == 1)
		{
			NRC_OpenJobfile("baohe_file");
			NRC_JobfileEraseCmd(15);
			NRC_JobfileInsertVarWHILE(15, "GI001", NRC_EQU, 0);
			NRC_JobfileEraseCmd(16);
			NRC_JobfileInsertTIMER(16, 0.1);
			NRC_JobfileEraseCmd(17);
			NRC_JobfileInsertENDWHILE(17);

			NRC_JobfileEraseCmd(28);
			NRC_JobfileInsertVarWHILE(28, "GI004", NRC_EQU, 0);
			NRC_JobfileEraseCmd(29);
			NRC_JobfileInsertTIMER(29, 0.1);
			NRC_JobfileEraseCmd(30);
			NRC_JobfileInsertENDWHILE(30);

		}
		 //***切换调试作业文件__endl

			//保存过渡点状态
			Json::Value root_judge;
			Json::FastWriter wt_judge;
			Json::Reader reader_judge;
			ifstream in_judge("judge_exc_pos.json", ios :: binary);
			if(reader_judge.parse(in_judge, root_judge))
			{
				in_judge.close();
			}
		//过渡点操作, 是否替代对应位置
		if(root_str["unaffected_pos"].asInt() == 1)
		{

			//过渡点1
			NRC_OpenJobfile("baohe_file");
			if(root_str["judge_exc_1"].asInt() == 1)
			{
				printf("点2!");
				NRC_JobfileEraseCmd(12);
				NRC_JobfileInsertMOVJ(12, 100, 100, 100, pack.exc_pos_1, 5);//过渡点1
				root_judge["exc"]["1"] = 1;
			}
			else
			{
				printf("点2!");
				NRC_JobfileEraseCmd(12);
				NRC_JobfileInsertCMDNOTE(12, "过渡点1");//
				root_judge["exc"]["1"] = 0;
			}
			//过渡点2
			if(root_str["judge_exc_2"].asInt() == 1)
			{
				NRC_JobfileEraseCmd(13);
				NRC_JobfileInsertMOVJ(13, 100, 100, 100, pack.exc_pos_2, 5);//过渡点2
				root_judge["exc"]["2"] = 1;
			}
			else
			{
				NRC_JobfileEraseCmd(13);
				NRC_JobfileInsertCMDNOTE(13, "过渡点2");//
				root_judge["exc"]["2"] = 0;
			}
			//过渡点3
			if(root_str["judge_exc_3"].asInt() == 1)
			{
				NRC_JobfileEraseCmd(26);
				NRC_JobfileInsertMOVJ(26, 100, 100, 100, pack.exc_pos_3, 5);//过渡点3
				root_judge["exc"]["3"] = 1;
			}
			else
			{
				NRC_JobfileEraseCmd(26);
				NRC_JobfileInsertCMDNOTE(26, "过渡点3");//
				root_judge["exc"]["3"] = 0;
			}
			//过渡点4
			if(root_str["judge_exc_4"].asInt() == 1)
			{
				NRC_JobfileEraseCmd(27);
				NRC_JobfileInsertMOVJ(27, 100, 100, 100, pack.exc_pos_4, 5);//过渡点4
				root_judge["exc"]["4"] = 1;
			}
			else
			{
				NRC_JobfileEraseCmd(27);
				NRC_JobfileInsertCMDNOTE(27, "过渡点4");//
				root_judge["exc"]["4"] = 0;
			}
			//过渡点5
			if(root_str["judge_exc_5"].asInt() == 1)
			{
				NRC_JobfileEraseCmd(40);
				NRC_JobfileInsertMOVJ(40, 100, 100, 100, pack.exc_pos_5, 5);//过渡点5
				root_judge["exc"]["5"] = 1;
			}
			else
			{
				NRC_JobfileEraseCmd(40);
				NRC_JobfileInsertCMDNOTE(40, "过渡点5");//
				root_judge["exc"]["5"] = 0;
			}
			//过渡点6
			if(root_str["judge_exc_6"].asInt() == 1)
			{
				NRC_JobfileEraseCmd(41);
				NRC_JobfileInsertMOVJ(41, 100, 100, 100, pack.exc_pos_6, 5);//过渡点6
				root_judge["exc"]["6"] = 1;
			}
			else
			{
				NRC_JobfileEraseCmd(41);
				NRC_JobfileInsertCMDNOTE(41, "过渡点6");//
				root_judge["exc"]["6"] = 0;
			}
			ofstream os_judge;
			os_judge.open("judge_exc_pos.json");
			os_judge << wt_judge.write(root_judge);
			NRC_SendSocketCustomProtocal(0x920b,wt_judge.write(root_judge));
		}
		NRC_SendSocketCustomProtocal(0x9208,"yes");//发送插入文件成功
	}
	else
	{
		NRC_SendSocketCustomProtocal(0x9208,"no");//下电才能保存
	}
}
void run_pos(string str)//点位移动
{
	if(str == "起点")
	{
		NRC_RobotMoveJoint(50, pack.btn_startPos,80,80);
		while (NRC_GetProgramRunStatus() != 0)  //等待运行结束
		{
			NRC_Delayms(100);   //延时100ms
		}
		pack.judge_start_pos = true;
		cout << NRC_GetCycleCount() << endl;
		NRC_StopRunJobfile();
	}
	if(str == "过渡点1")
	{
		NRC_RobotMoveJoint(50, pack.exc_pos_1,80,80);
		while (NRC_GetProgramRunStatus() != 0)  //等待运行结束
		{
			NRC_Delayms(100);   //延时100ms
		}
		NRC_StopRunJobfile();
	}
	if(str == "过渡点2")
	{
		NRC_RobotMoveJoint(50, pack.exc_pos_2,80,80);
		while (NRC_GetProgramRunStatus() != 0)  //等待运行结束
		{
			NRC_Delayms(100);   //延时100ms
		}
		NRC_StopRunJobfile();
	}
	if(str == "取料点")
	{
		NRC_RobotMoveJoint(50, pack._materialPos,80,80);
		while (NRC_GetProgramRunStatus() != 0)  //等待运行结束
		{
			NRC_Delayms(100);   //延时100ms
		}
		NRC_StopRunJobfile();
	}
	if(str == "过渡点3")
	{
		NRC_RobotMoveJoint(50, pack.exc_pos_3,80,80);
		while (NRC_GetProgramRunStatus() != 0)  //等待运行结束
		{
			NRC_Delayms(100);   //延时100ms
		}
		NRC_StopRunJobfile();
	}
	if(str == "过渡点4")
	{
		NRC_RobotMoveJoint(50, pack.exc_pos_4,80,80);
		while (NRC_GetProgramRunStatus() != 0)  //等待运行结束
		{
			NRC_Delayms(100);   //延时100ms
		}
		NRC_StopRunJobfile();
	}
	if(str == "套盒点")
	{
		NRC_RobotMoveJoint(50, pack.box_setPos,80,80);
		while (NRC_GetProgramRunStatus() != 0)  //等待运行结束
		{
			NRC_Delayms(100);   //延时100ms
		}
		NRC_StopRunJobfile();
	}
	if(str == "过渡点5")
	{
		NRC_RobotMoveJoint(50, pack.exc_pos_5,80,80);
		while (NRC_GetProgramRunStatus() != 0)  //等待运行结束
		{
			NRC_Delayms(100);   //延时100ms
		}
		NRC_StopRunJobfile();
	}
	if(str == "过渡点6")
	{
		NRC_RobotMoveJoint(50, pack.exc_pos_6,80,80);
		while (NRC_GetProgramRunStatus() != 0)  //等待运行结束
		{
			NRC_Delayms(100);   //延时100ms
		}
		NRC_StopRunJobfile();
	}
	if(str == "结束点")
	{
		NRC_RobotMoveJoint(50, pack.btn_stopPos,80,80);
		while (NRC_GetProgramRunStatus() != 0)  //等待运行结束
		{
			NRC_Delayms(100);   //延时100ms
		}
		NRC_StopRunJobfile();
	}
}
void updata(string str)//update
{
		params_access();
}
void stop_reset_clear(string str)//停止、暂停、继续、清除
{
	if(str == "暂停")
	{
		cout<<"暂停暂停暂停暂停"<<endl;
		NRC_PauseRunJobfile();//暂停
		NRC_SendSocketCustomProtocal(0x9208,"pause_file");
	}
	if(str == "继续")
	{
		NRC_StartRunJobfile("baohe_file");
		NRC_SendSocketCustomProtocal(0x9208,"continue_file");
	}
	if(str == "停止")
	{
		NRC_StopRunJobfile();
		NRC_SendSocketCustomProtocal(0x9208,"stop_file");
	}
	if(str == "清除产量")
	{
		Json::Value root;
		Json::Reader reader;
		Json::FastWriter wt;
		//***clear_sum
		ifstream in3("sumParam.json", ios :: binary);
		if(reader.parse(in3,root))
		{
			in3.close();
		}
		pack.g_sum_tmp = 0;
		pack.g_run_number = 0;
		pack.g_sum = 0;
		root["sum"] = pack.g_sum;
		ofstream os1;
		os1.open("sumParam.json");
		os1 << wt.write(root);
		NRC_SendSocketCustomProtocal(0x9208,"clear_sum");
	}
	if(str == "复位")
	{
		if(NRC_GetOperationMode() == NRC_RUN_)//运行模式状态下才可以
		{
			NRC_DigOut(1, 0);
			NRC_DigOut(2, 0);
			NRC_DigOut(5, 0);
			NRC_DigOut(6, 0);
			NRC_DigOut(7, 0);
			pack.judge_start_pos = true;
			NRC_StopRunJobfile();
			NRC_RobotMoveJoint(50, pack.btn_startPos,80,80);
			while (NRC_GetProgramRunStatus() != 0)  //等待运行结束
			{
				NRC_Delayms(100);   //延时100ms
			}
			NRC_SendSocketCustomProtocal(0x9208,"reset_to_start");
			//		NRC_StopRunJobfile();
		}
		else
		{
			NRC_SendSocketCustomProtocal(0x9208,"No running mode");
		}
	}

}
void run_file(string str)//启动作业文件
{
	if(NRC_GetProgramRunStatus() == 0)//程序处于停止状态
	{
		if(NRC_GetOperationMode() == NRC_RUN_)//运行模式状态下才可以
		{
			//起点相同才可以
			if( pack.judge_start_pos )
			{
				pack.g_run_number =  NRC_GetCycleCount();//获取当前作业文件已运行的次数，返回当前作业文件已运行的次数。
				pack.g_sum_tmp = pack.g_sum;
				if(str == "单次运行")
				{
					NRC_SetCycleIndex(1);
				}
				else if(str == "循环运行")
				{
					NRC_SetCycleIndex(0);
				}
				NRC_SetBoolVar(5, true);
				pack.judge_start_pos = false;
				NRC_SetBoolVar(7, true);
				pack.runPackFile();//起线程运行作业文件
			}
			else
			{
				NRC_SendSocketCustomProtocal(0x9208,"No at start point");
			}
		}
		else
		{
			NRC_SendSocketCustomProtocal(0x9208,"No running mode");
		}
	}
	else
	{
		NRC_SendSocketCustomProtocal(0x9208,"No stop file");
	}
}
void set_io(string str)//io设定
{
	Json::Value root_io;
	Json::Reader  reader_io;
	if(reader_io.parse(str,root_io))
	{
		if(root_io["IO1_in"] =="IO1_in")
		{
			NRC_SetIntVar(1, root_io["IO1_in_out"].asInt());
			if(root_io["IO1_in_out"].asInt()==0)
			{
				pack.judge_io1 = false;
			}
			else if(root_io["IO1_in_out"].asInt()==1)
			{
				pack.judge_io1 = true;
			}
		}
		if(root_io["IO3_in"] =="IO3_in")
		{
			NRC_SetIntVar(3, root_io["IO3_in_out"].asInt());
		}
		if(root_io["IO4_in"] =="IO4_in")
		{
			NRC_SetIntVar(4, root_io["IO4_in_out"].asInt());
			if(root_io["IO4_in_out"].asInt()==0)
			{
				pack.judge_io4 = false;
			}
			else if(root_io["IO4_in_out"].asInt()==1)
			{
				pack.judge_io4 = true;
			}
		}
		if(root_io["IO5_in"] =="IO5_in")
		{
			NRC_SetIntVar(5, root_io["IO5_in_out"].asInt());
		}


		if(root_io["IO1"] == "IO1")
		{
			cout<<"((((((((((((((("<<endl;
			NRC_DigOut(1, root_io["IO1_out"].asInt());
		}
		if(root_io["IO2"] == "IO2")
		{
			NRC_DigOut(2, root_io["IO2_out"].asInt());
		}
		if(root_io["IO3"] == "IO3")
		{
			NRC_DigOut(3, root_io["IO2_out"].asInt());
		}
		if(root_io["IO5"] == "IO5")
		{
			NRC_DigOut(5, root_io["IO5_out"].asInt());
		}
		if(root_io["IO6"] == "IO6")
		{
			NRC_DigOut(6, root_io["IO6_out"].asInt());
		}
		if(root_io["IO7"] == "IO7")
		{
			NRC_DigOut(7, root_io["IO7_out"].asInt());
		}
		if(root_io["IO8"] == "IO8")
		{
			NRC_DigOut(8, root_io["IO8_out"].asInt());
		}
		if(root_io["IO9"] == "IO9")
		{
			NRC_DigOut(9, root_io["IO9_out"].asInt());
		}
	}
}
void try_run_allpos(string str)
{
	if(NRC_GetProgramRunStatus() == 0)//程序处于停止状态
	{
		if(NRC_GetOperationMode() == NRC_RUN_)//运行模式状态下才可以
		{
			//起点相同才可以
			if( pack.judge_start_pos )
			{
				pack.judge_start_pos = false;
				pack.runOnceAllPos();
			}
			else
			{
				NRC_SendSocketCustomProtocal(0x9208,"No at start point");
			}
		}
		else
		{
			NRC_SendSocketCustomProtocal(0x9208,"No running mode");
		}
	}
	else
	{
		NRC_SendSocketCustomProtocal(0x9208,"No stop file");
	}
}



void msgHook() {
	NRC_Messsage tmp; //定义一个消息结构体对象
	NRC_GetMesssage(1, tmp); //将消息队列中最早的消息赋值给对象tmp
	printf("msgHooklocalTime=%d:%d::%d,0x%x,0x%x,0x%x,text=%s,size=%d\n",tmp.localTime.minute,tmp.localTime.second,tmp.localTime.milliseconds,tmp.kind,tmp.code,tmp.robot,tmp.text.c_str(),NRC_GetMesssageSize());	//删除tmp.type，新增tmp.robot
	NRC_Delayms(200);
}
void  SystemStartup()
{
	std::string NRC_GetNexMotionLibVersion();//获取Nexmotion版本库信息
	cout << "库版本：" << NRC_GetNexMotionLibVersion() << endl;//输出Nexmotion版本库信息
	NRC_StartController(4);  //启动控制系统
	while (NRC_GetControlInitComplete() != 1)  //检测控制系统是否初始化完成
	{
		NRC_Delayms(100);   //延时100ms
	}
	NRC_ClearAllError();//清除所有错误
	cout << "StartController Success" << endl;
	//*********
	params_access();
	NRC_SetSocketCustomProtocalCB(0x9200,&printffff);//接收示教器参数
	NRC_SetSocketCustomProtocalCB(0x9201,&message);//修改参数后读取控制器参数
	NRC_SetSocketCustomProtocalCB(0x9204,&set_io);// io设定
	NRC_SetSocketCustomProtocalCB(0x9203,&get_read_time);//实时获取
	NRC_SetSocketCustomProtocalCB(0x9206,&sign_pos_and_file_updata);//获取点位的坐标
	NRC_SetSocketCustomProtocalCB(0x9207,&run_pos);//run点位的坐标
	NRC_SetSocketCustomProtocalCB(0x9209,&updata);//updata
	NRC_SetSocketCustomProtocalCB(0x920a,&run_file);//Run_file
	NRC_SetSocketCustomProtocalCB(0x920c,&stop_reset_clear);//stop and reset
	NRC_SetSocketCustomProtocalCB(0x920d,&try_run_allpos);//stop and reset
	NRC_Delayms(200);
	NRC_SetMsgHappenCallback(msgHook);//设置消息发生时的回调函数
	//**************
}
void SetServoMap()
{
	std::vector<int> servoMap = {0,0,0,0,0,0};//机器人映射
	 int syncGroupNum = 1;//外部轴组数
	int syncType[]={0,0,0};//外部轴类型
	std::vector<std::vector<int>> syncServoMap={{0,0},{0,0},{0,0}};//外部轴映射, 两个双轴变位机
	NRC_SetAllServoMapRelation(servoMap,syncGroupNum, syncType, syncServoMap);
}
void SettingofRobotRelatedParameters()
{
NRC_RobotDHConfig robotDHConfig = {321.5, 270,70,299, 78.5, 50, 0, 90, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};//DH参数配置
NRC_SetRobotDHConfig(robotDHConfig );//设置DH参数配置
NRC_RobotJointConfig robotJointConfig = {76.5, 17, 180, -180, 3000, -3000, 1, -1, 5, -5,1,1};//关节参数配置
for (int i=1; i<7; i++)
{
NRC_SetRobotJointConfig(i,robotJointConfig );
}//设置关节参数配置
NRC_RobotRangeLimit robotRangeLimit = { true, 1000, true, -500, false, 300, true, -1000, false, 0, false, 3000 };//范围限制配置
NRC_SetRobotRangeLimit(robotRangeLimit);//设置机器人范围限制
NRC_RobotDecareConfig robotDecareConfig = {1000, 3, -3};//笛卡尔参数配置
NRC_SetRobotDecareConfig(robotDecareConfig);//设置笛卡尔参数配置
}

void RobotMsg()
{
	int ioNum;
	vector<string> type;
	cout<<"机器人轴数："<<NRC_GetRobotAxisSum()<<endl;
	//cout<<"外部轴数"<<NRC_GetSyncAxisSum()<<endl;
	NRC_GetEthercatIOConfig(ioNum, type);
	cout<<"扩展板数："<<ioNum<<endl;
//	if(ioNum>0)
//	{
//		cout<<"扩展板类型："<<type.at(1)<<" ,"<<type.at(2)<<endl;
//	}
}


int main()
{
    SystemStartup();//系统启动，详见3.3节
    RobotMsg();//获取机器人配置，详见3.4节
//    SetServoMap();//设置伺服映射关系，见3.5节
//    SettingofRobotRelatedParameters();//机器人相关参数设置。
    NRC_SetServoReadyStatus(1);//设置伺服允许
//    NRC_SendSocketCustomProtocal(0x9208,"unaffected_pos");//初始化模式
    cout<< "设置伺服允许成功"<<endl;
    int inexbot=NRC_GetServoStatus();
    if(inexbot=0)cout<<"伺服禁止";
    else if(inexbot=1)cout<<"伺服允许(就绪)";
    else if(inexbot=2)cout<<"伺服报警";
    else cout <<"伺服运行";

    NRC_SetDoubleVar(1, 0);
    pack.open_period();//启动监控周期



    while(1)//保持程序继续运行
    {
    	NRC_Delayms(1000);
    }
}

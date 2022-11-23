/**
 * @file nrcAPI.h
 * @brief NexMotion 函数库
 * @author 纳博特科技 Inexbot
 * @date 2021-08-17
 * @version 2.1.0
 * @note 修改内容
 * 新增追加模式下支持的指令：ELSEIF、WHILE、ENDWHILE、ADD
 *
*/

#ifndef _API_NRCAPI_H_
#define _API_NRCAPI_H_

#include <string>
#include <vector>
#include <initializer_list>
/***********************************宏定义**************************************/

 /**
* @name 函数调用返回值宏定义
* @{
*/
#define NORMAL      (0)                 ///<  表示函数正常调用
#define INVALID_PARAMETER    (-101)         ///<  无效的输入参数
#define TARGET_NOT_EXIST         (-102)         ///<  目标对象不存在，一般出现在系统初始化未完成时，调用其他函数时可能返回该值
#define TARGET_NOT_OPERATE  (-103)        ///<目标对象当前处于不可操作状态
/** @} */

 /**
* @name 消息缓存大小的宏定义
* @{
*/
#define MESSAGEBUFFSIZE     (32)     ///<当缓存已满时，再有新的消息产生，将自动移除最早的消息
/** @} */

/**
 * @name 用户自定义配置文件名称
 * @attention 请勿修改文件名称
 * @{
 */
#define USER_DEFINED_PROFILE      "userDefinedProfile.json"
/** @} */

/***********************************枚举**************************************/

/**
 * @brief 操作模式
 */
enum NRC_OperationMode
{
	NRC_TEACH_ = 0,     ///< 示教模式
	NRC_REMOTE_ = 1,     ///< 远程模式
	NRC_RUN_ = 2     ///< 运行模式
};

/**
 * @brief 机器人坐标系
 */
enum NRC_COORD
{
	NRC_ACS = 0,     ///< 关节坐标
	NRC_MCS = 1,     ///< 世界坐标
	NRC_PCS = 2,     ///< 工具坐标
	NRC_UCS = 3      ///< 用户坐标
};

enum NRC_OPREATION
{
	NRC_ADD = 0,     ///< 加
	NRC_SUB = 1,     ///< 减
	NRC_MUL = 2,     ///< 乘
	NRC_DIV = 3,     ///< 除
	NRC_MOD = 4,     ///< 模
	NRC_SIN = 5,     ///< 正弦
	NRC_COS = 6,     ///< 余弦
	NRC_ATAN = 7     ///< 1反正切
};

enum NRC_JUDGE
{
	NRC_EQU = 1,     ///< 等于
	NRC_LES = 2,     ///< 小于
	NRC_GRE = 3,     ///< 大于
	NRC_LOE = 4,     ///< 小于等于
	NRC_GOE = 5,     ///< 大于等于
	NRC_NEQU = 6     ///< 不等于
};

/***********************************结构体**************************************/

/**
 * @brief 机器人位置结构体
 */
struct NRC_Position
{
	 std::vector<double> v;
	NRC_COORD coord;     ///< 位置的坐标系
	int usrNum;			///用户坐标系
	int toolNum;		///工具坐标系
	int configuration;	///形态值
	/**
	 * @brief 位置的值
	 *  - 关节坐标系下，pos[0]到pos[6]分别对于机器人的1到7轴
	 *  - 其他坐标系下，pos[0]到pos[6]分别对于机器人的x轴、y轴、z轴、A轴、B轴、C轴、臂角(七轴机器人)
	 */
	double pos[7];
	NRC_Position()
	{
		coord = NRC_ACS;
		usrNum = 0;
		toolNum = 0;
		configuration = 0;
		for(int i=0;i<7;i++)
		{
			pos[i] = 0;
		}
	};
	NRC_Position(NRC_COORD coo,double  axis_pos1,double  axis_pos2,double  axis_pos3,double  axis_pos4,double  axis_pos5,double  axis_pos6) ///兼容旧版本位置定义
	{
		coord = coo;
		usrNum = 0;
		toolNum = 0;
		configuration = 0;
		pos[0] = axis_pos1;
		pos[1] = axis_pos2;
		pos[2] = axis_pos3;
		pos[3] = axis_pos4;
		pos[4] = axis_pos5;
		pos[5] = axis_pos6;
	}
	NRC_Position(NRC_COORD coo,std::initializer_list<double> l) : v(l) ///兼容旧版本位置定义
	{
		coord = coo;
		usrNum = 0;
		toolNum = 0;
		configuration = 0;
		for(int i=0;i<6;i++)
		{
			pos[i] = v[i];
		}
	}
	NRC_Position(NRC_COORD coo,int usrnum,int toolnum,int conf,double* axis_pos)
	{
		coord = coo;
		usrNum = usrnum;
		toolNum = toolnum;
		configuration = conf;
		for(int i=0;i<7;i++)
		{
			pos[i] = axis_pos[i];
		}
	}
	NRC_Position(NRC_COORD coo,int usr,int tool,int con,double  axis_pos1,double  axis_pos2,double  axis_pos3,double  axis_pos4,double  axis_pos5,double  axis_pos6,double  axis_pos7) ///兼容旧版本位置定义
	{
		coord = coo;
		usrNum = usr;
		toolNum = tool;
		configuration = con;
		pos[0] = axis_pos1;
		pos[1] = axis_pos2;
		pos[2] = axis_pos3;
		pos[3] = axis_pos4;
		pos[4] = axis_pos5;
		pos[5] = axis_pos6;
		pos[6] = axis_pos7;
	}
};

/**
 * @brief 外部轴位置结构体
 */
struct NRC_SyncPosition
{
	NRC_COORD coord;     ///< 位置的坐标系
	 /**
	  * @brief 位置的值
	  *  - 关节坐标系下，pos[0]到pos[1]分别对于外部轴的1到2轴
	  */
	double pos[5];
};
/**
 * @brief 机器人类型枚举
 */
enum NRC_RobotType {
	NRC_R_NULL = 0, ///无
	NRC_R_GENERAL_6S = 1, ///通用六轴
	NRC_R_SCARA = 2, ///scara
	NRC_R_FOURAXIS_PALLET = 3, ///四轴码垛
	NRC_R_FOURAXIS = 4, ///四轴
	NRC_R_GENERAL_1S = 5, ///一轴
	NRC_R_GENERAL_5S = 6, ///五轴
	NRC_R_GENERAL_6S_1 = 7, ///UR
	NRC_R_SCARA_TWOAXIS = 8, ///二轴scara
	NRC_R_SCARA_THREEAXIS = 9, ///三轴scara
	NRC_R_THREE_CARTESIAN_COORDINATE = 10, ///三轴直角
	NRC_R_THREE_CARTESIAN_COORDINATE_1 = 11, ///三轴异形一
	NRC_R_GENERAL_7S_RBT = 12, ///七轴
	NRC_R_SCARA_1 = 13, ///scara异形一
	NRC_R_FOURAXIS_PALLET_1 = 14, ///四轴码垛丝杆
};
/**
 * @brief 机器人DH参数配置
 */
struct NRC_RobotDHConfig
{
	double L1; ///<L1杆长
	double L2; ///<L2杆长
	double L3; ///<L3杆长
	double L4; ///<L4杆长
	double L5; ///<L5杆长
	double L6; ///<L6杆长
	double L7; ///<L7杆长
	double theta; ///<5轴方向，仅对六轴机器人有效，参数可选：0、90
	double CoupleCoe12; ///<1/2轴耦合比
	double CoupleCoe23; ///<2/3轴耦合比
	double CoupleCoe32; ///<3/2轴耦合比
	double CoupleCoe34; ///<3/4轴耦合比
	double CoupleCoe45; ///<4/5轴耦合比
	double CoupleCoe46; ///<4/6轴耦合比
	double CoupleCoe56; ///<5/6轴耦合比
	double dynamicLimitMax; ///动态限位最大值，用于四轴码垛机器人
	double dynamicLimitMin; ///动态限位最小值，用于四轴码垛机器人
	double ConversionRatio2; ///二轴转换比
	double ConversionRatio3; ///三轴转换比
	double ConversionRatio4; ///四轴转换比
	double Pitch = 0; ///scara升降杆螺距
	NRC_RobotDHConfig(double l1, double l2,double l3,double l4, double l5, double l6, double l7, double l8, double l9, double l10,double l11, double l12, double l13, double l14, double l15)
	{
		 L1 = l1;
		 L2 = l2;
		 L3 = l3;
		 L4 = l4;
		 L5 = l5;
		 L6 = l6;
		 L7 = l7;
		 theta = l8;
		 CoupleCoe12 = l9;
		 CoupleCoe23 = l10;
		 CoupleCoe32 = l11;
		 CoupleCoe34 = l12;
		 CoupleCoe45 = l13;
		 CoupleCoe46 = l14;
		 CoupleCoe56 = l15;
		 dynamicLimitMax = 0;
		 dynamicLimitMin = 0;
		 ConversionRatio2 = 0;
		 ConversionRatio3 = 0;
		 ConversionRatio4 = 0;
		 Pitch = 0;
	}
	NRC_RobotDHConfig(double l1, double l2,double l3,double l4, double l5, double l6, double l7, double l8, double l9, double l10,double l11, double l12, double l13, double l14, double l15,
			 double l16,double l17, double l18, double l19, double l20, double l21)
	{
		 L1 = l1;
		 L2 = l2;
		 L3 = l3;
		 L4 = l4;
		 L5 = l5;
		 L6 = l6;
		 L7 = l7;
		 theta = l8;
		 CoupleCoe12 = l9;
		 CoupleCoe23 = l10;
		 CoupleCoe32 = l11;
		 CoupleCoe34 = l12;
		 CoupleCoe45 = l13;
		 CoupleCoe46 = l14;
		 CoupleCoe56 = l15;
		 dynamicLimitMax = l16;
		 dynamicLimitMin = l17;
		 ConversionRatio2 = l18;
		 ConversionRatio3 = l19;
		 ConversionRatio4 = l20;
		 Pitch = l21;
	}
};

/**
 * @brief 机器人关节参数配置
 */
struct NRC_RobotJointConfig
{
	double reducRatio; ///<减速比
	int encoderResolution; ///<编码器位数
	double posSWLimit; ///<轴正限位，单位：度
	double negSWLimit; ///<轴反限位，单位：度
	double ratedRotSpeed; ///<电机额定正转速，单位：转/分钟
	double ratedDeRotSpeed; ///<电机额定反转速，单位：转/分钟
	double maxRotSpeed; ///<电机最大正转速，为电机额定正转速的倍数，单位：倍数
	double maxDeRotSpeed; ///<电机最大反转速，为电机额定反转速的倍数，单位：倍数
	double maxAcc; ///<最大加速度，为额定正速度的倍数，单位：倍数，额定正速度 = 电机额定正转速 / 减速比 * 6
	double maxDecel; ///<最大减速度，为额定反速度的倍数，单位：倍数，额定反速度 = 电机额定反转速 / 减速比 * 6
	int direction; ///<模型方向，1：正向，-1：反向.若要改变机器人单关节运动的方向，通常修改模型方向
	int AxisDirection;///<关节实际方向
};

/**
 * @brief 机器人笛卡尔参数配置
 */
struct NRC_RobotDecareConfig
{
	double maxVel; ///<最大速度，单位：毫米/秒
	double maxAcc; ///<最大加速度，为最大速度的倍数，单位：倍数
	double maxDec; ///<最大减速度，为最大速度的倍数，单位：倍数
};

/**
 * @brief 机器人范围限制配置
 */
struct NRC_RobotRangeLimit
{
	bool enableMaxX;  ///<使能X正方向限制
	double maxX;  ///<X正方向限制
	bool enableMinX;  ///<使能X负方向限制
	double minX;  ///<X负方向限制
	bool enableMaxY;  ///<使能Y正方向限制
	double maxY;  ///<Y正方向限制
	bool enableMinY;  ///<使能Y负方向限制
	double minY;  ///<Y负方向限制
	bool enableMaxZ;  ///<使能Z正方向限制
	double maxZ;  ///<Z正方向限制
	bool enableMinZ;  ///<使能Z负方向限制
	double minZ;  ///<Z负方向限制
};

/**
 * @brief 时间数据结构体
 */
struct NRC_TIME
{
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
	int milliseconds;
};

/**
 * @brief 消息数据结构体
 * @note 用户自定义区间为0x9000之后
 */
struct NRC_Messsage
{
	NRC_TIME localTime;///<消息产生时的系统时间
	int kind; ///<消息级别：0:一般消息，1:警告消息，2:错误消息，3:重要消息
	int code;///<消息编码
	int robot;///<机器人编号
	std::vector<int> param;///<消息内容参数，根据具体编码的不同，会有不同个数，一共预留5个
	std::string text;///<消息内容
};

/***********************************函数**************************************/

/**
 * @brief 系统延时一定时间
 * @param ms 要延时的时间，单位为毫秒
 */
int NRC_Delayms(int ms);

/**
 * @brief 向NRC系统中打印日志
 * @note 使用方式同printf()
 */
void NRC_LogInfo(const char* format, ...);

/**
 * @brief 获取NexMotion库版本
 * @return 返回NexMotion库版本信息
 */
std::string NRC_GetNexMotionLibVersion();

/**
 * @brief 获取同步版本号
 * @return 返回同步版本号
 */
std::string NRC_GetSyncVersion();

/**
 * @brief 系统启动函数
 * @param netPort 连接伺服的网口的端口号,默认为4,根据具体工控机型号设置
 * @warning 启动系统需要时间，请使用 NRC_GetControlInitComplete() 函数查看系统是否初始化完成，在初始化完成前，请勿调用其他函数
 */
int NRC_StartController(int netPort = 4);

/**
 * @brief 查看系统初始化是否完成
 * @return 返回系统是否初始化完成
 *@retval 0 表示未完成
 *@retval 1 表示已完成
 */
int NRC_GetControlInitComplete();

/**
 * @brief 切换伺服准备状态
 * @param status 可选参数值：
 *  -    0  伺服禁止
 *  -    1  伺服允许
 */
int NRC_SetServoReadyStatus(int status);

/**
 * @brief 获取伺服状态
 * @return 返回伺服状态
 *@retval	0 伺服禁止
 *@retval	1 伺服允许(就绪)
 *@retval  2 伺服报警
 *@retval	3 伺服运行
 */
int NRC_GetServoStatus();

/**
 * @brief 设置操作模式
 * @param mode 将当前模式切换至该模式
 * @see NRC_OperationMode
 */
int NRC_SetOperationMode(NRC_OperationMode mode);

/**
 * @brief 获取操作模式
 * @return 返回当前模式
 * @see NRC_OperationMode
 */
NRC_OperationMode NRC_GetOperationMode();

/**
 * @brief 设置示教速度百分比
 * @param speedPer
 *    -   参数范围：0 < speedPer  <= 100
 *    -   微动参数范围  : -1，-2    (关节坐标系下：-1表示0.1度，-2表示0.01度；其他模式下：-1表示1mm/s，-2表示0.1mm/s)
 */
int NRC_SetTeachRunSpeedPer(int speedPer);

/**
 * @brief 获取示教速度百分比
 * @return 返回示教速度百分比
 * @retval	返回值范围：-2 < NRC_GetTeachRunSpeedPer()  <= 100 ,  NRC_GetTeachRunSpeedPer() != 0
 */
int NRC_GetTeachRunSpeedPer();

/**
 * @brief 设置自动速度百分比
 * @param speedPer
 *    -   参数范围：0 < speedPer  <= 100
 */
int NRC_SetAutoRunSpeedPer(int speedPer);

/**
 * @brief 获取自动速度百分比
 * @return 返回自动速度百分比
 * @retval	返回值范围：0< NRC_GetAutoRunSpeedPer()  <= 100
 */
int NRC_GetAutoRunSpeedPer();

/**
 * @brief 切换当前坐标系
 * @param coord 将当前坐标系切换至该坐标系
 * @see NRC_COORD
 */
int NRC_SetCurrentCoord(NRC_COORD coord);

/**
 * @brief 获取当前坐标系
 * @return 返回当前坐标系
 * @see NRC_COORD
 */
NRC_COORD NRC_GetCurrentCoord();

/**
 * @brief 按下deadman键
 * @note
 *   - 按下deadman键,使机器人上电
 *   - 使用此接口上电后，再调用对应接口 NRC_ServoEnable() 下电时，可以自动先停止正在运行中的机器人，再进行下电
 *   - 仅示教模式下可用，并且示教模式下推荐使用该接口
 * @pre 调用该函数前，请将伺服准备状态切换至伺服就绪，可调用 NRC_SetServoReadyStatus(int status) 函数切换伺服状态
 * @warning 成功调用该函数后，伺服将处于上电使能状态，请注意安全
 */
int NRC_ServoEnable();

/**
 * @brief 松开deadman键
 * @note
 *   - 可将通过 NRC_ServoEnable() 接口上电的机器人，进行下电
 *   - 成功调用该函数后，伺服将下电，处于未使能状态
 *   - 仅示教模式下可用，并且示教模式下推荐使用该接口
 */
int NRC_ServoDisable();
/**
 * @brief 开始点动某轴
 * @note 机器人将在 NRC_GetCurrentCoord() 坐标系下， axis 轴沿 vel 方向运动
 * @pre 调用该函数前，请将伺服上电使能，可调用 NRC_ServoEnable() 函数将伺服上电
 * @warning
 *     -   进行点动操作时，为保障安全，该函数需要每200ms调用一次，一旦超时未调用，机器人将自动停止点动
 *     -   进行微动操作时，即使连续调用该函数，也只会执行一次，需执行停止点动后，再次调用该函数，才能执行下一次
 *     -   成功调用该函数后，机器人将开始运动，请注意安全
 * @param axis 要进行点动的轴，取值范围1-6
 * @param vel 轴运动方向和速度，取值范围[-1,-0.01)U(0.01,1]
 *  -    正负号代表正反方向
 *  -    系数为速度比例，实际速度为示教速度*vel*电机速度
 */
int NRC_JogMove(int axis, double vel);

/**
 * @brief 停止某关节点动
 * @note 调用该函数后，该关节点动将会停止，机器人将减速至停止
 */
int NRC_JogMoveStop(int axis);

/**
 * @brief 停止所有关节点动
 * @note 调用该函数后，机器人点动将会停止，机器人将减速
 */
int NRC_JogMoveStopAll();
/**
 * @brief 获取当前位置下其他工具坐标系表示的位置
 * @note 该函数可以获取在工具手Num坐标系下的机器人位置，位置数据由参数引用 position 返回，坐标系类型会改为工具坐标系
 * @see ToolNum
 * @see NRC_Position
 */
int NRC_GetOtherToolPos(int ToolNum, NRC_Position& position);
/**
 * @brief 获取当前位置
 * @note 该函数可以获取在 coord 坐标系下的机器人位置，位置数据由参数引用 position 返回
 * @see NRC_COORD
 * @see NRC_Position
 */
int NRC_GetCurrentPos(NRC_COORD coord, NRC_Position& position);

/**
 * @brief 将机器人关节坐标值转换为直角坐标值
 * @param posACS 要进行转换的关节坐标值
 * @param posMCS 转换的结果通过其返回
 */
int NRC_PositionACStoMCS(NRC_Position& posACS, NRC_Position& posMCS);

/**
 * @brief 将机器人直角坐标值转换为关节坐标值
 * @param posMCS 要进行转换的直角坐标值
 * @param posACS 转换的结果通过其返回
 * @return 返回是否转换成功
 * @retval  0 转换成功
 * @retval  -1 转换失败
 */
int NRC_PositionMCStoACS(NRC_Position& posMCS, NRC_Position& posACS);

/**
 * @brief 获取当前程序运行状态
 * @return 返回机器人当前程序运行状态
 * @retval  0 程序处于停止状态
 * @retval  1 程序处于暂停状态
 * @retval  2 程序处于运行状态
 */
int NRC_GetProgramRunStatus();

/**
 * @brief 获取当前机器人运动状态
 * @return 返回当前机器人运动状态
 * @retval  0 程序处于停止状态
 * @retval  1 程序处于运动状态
 */
int NRC_GetRobotRunStatus();


/**
 * @brief 伺服上使能
 * @pre 调用该函数前，请将伺服准备状态切换至伺服就绪，可调用 NRC_SetServoReadyStatus(int status) 函数切换伺服状态
 * @warning 成功调用该函数后，伺服将处于上电使能状态，请注意安全
 */
int NRC_PowerOn();

/**
 * @brief 伺服下使能
 * @note 成功调用该函数后，伺服将下电，处于未使能状态
 * @warning 请勿在机器人运动时调用该接口，可能会导致机器人突然停止，造成剧烈抖动
 */
int NRC_PowerOff();

/**
 * @brief 机器人点到点运行
 * @note 机器人以 vel 的速度从当前位置以点到点方式运行到 target 位置
 * @pre 调用该函数前，请将伺服上电使能，可调用 NRC_ServoEnable() 函数将伺服上电
 * @warning 成功调用该函数后，机器人将开始运动，请注意安全
 * @param vel 机器人的运行速度，为机器人最大速度的百分比，参数范围：0 < vel <= 100
 * @param target 机器人运动目标位置，详见 NRC_Position
 * @param acc 机器人运行加速度，为机器人各关节最大加速度的百分比，参数范围：0 < vel <= 100
 * @param dec 机器人运行减速度，为机器人各关节最大减速度的百分比，参数范围：0 < vel <= 100
 */
int NRC_RobotMoveJoint(int vel, const NRC_Position& target, int acc, int dec);

/**
 * @brief 机器人直线运动
 * @note 机器人以 vel 的速度从当前位置以直线方式运行到 target 位置
 * @pre 调用该函数前，请将伺服上电使能，可调用 NRC_ServoEnable() 函数将伺服上电
 * @warning 成功调用该函数后，机器人将开始运动，请注意安全
 * @param vel 机器人的运行速度，为机器人末端位置点绝对运行速度，单位为 毫秒每秒（mm/s），参数范围：vel > 1
 * @param target 机器人运动目标位置，详见 NRC_Position
 * @param acc 机器人运行加速度，为机器人笛卡尔最大加速度的百分比，参数范围：0 < vel <= 100
 * @param dec 机器人运行减速度，为机器人笛卡尔最大减速度的百分比，参数范围：0 < vel <= 100
 */
int NRC_RobotMoveLinear(int vel, const NRC_Position& target, int acc, int dec);

/**
 * @brief 机器人回复位点
 * @note 调用该接口,使机器人回到复位点
 * @pre 若在示教模式下调用该函数，请先将伺服上电使能，可调用 NRC_ServoEnable() 函数将伺服上电
 * @warning 成功调用该函数后，机器人将开始运动，请注意安全
 */
int NRC_StartResetPoint();

/**
 * @brief 数字IO端口输出
 * @param port 要输出的数字IO端口，最大范围为 1 <= port <= 16，实际范围取决于所连接点IO模块上的IO端口数目
 * @param value 要输出的状态
 *    -   0  输出低电平
 *    -   1  输出高电平
 */
void NRC_DigOut(int port, int value);

/**
 * @brief 读取数字IO输出端口的状态
 * @param port 要读取的数字IO端口，最大范围为 1 <= port <= 16，实际范围取决于所连接点IO模块上的IO端口数目
 * @return 返回该端口当前状态
 * @retval  0  当前处于低电平
 * @retval  1  当前处于高电平
 * @retval  -1  该端口不存在
 */
int NRC_ReadDigOut(int port);

/**
 * @brief 读取数字IO输入端口的状态
 * @param port 要读取的数字IO端口，最大范围为 1 <= port <= 16，实际范围取决于所连接点IO模块上的IO端口数目
 * @return 返回该端口当前状态
 * @retval  0  当前处于低电平
 * @retval  1  当前处于高电平
 * @retval  -1  该端口不存在
 */
int NRC_ReadDigIn(int port);

/**
 * @brief 模拟IO端口输出
 * @param port 要输出的模拟IO端口，最大范围为 1 <= port <= 16，实际范围取决于所连接点IO模块上的IO端口数目
 * @param value 要输出的数值
 */
void NRC_AnaOut(int port, double value);

/**
 * @brief 读取模拟IO输出端口的状态
 * @param port 要读取的模拟IO端口，最大范围为 1 <= port <= 16，实际范围取决于所连接点IO模块上的IO端口数目
 * @param value 返回该端口当前数值
 */
int NRC_ReadAnaOut(int port,double& value);

/**
 * @brief 读取模拟IO输入端口的状态
 * @param port 要读取的模拟IO端口，最大范围为 1 <= port <= 16，实际范围取决于所连接点IO模块上的IO端口数目
 * @param value 返回该端口当前数值
 */
int NRC_ReadAnaIn(int port,double& value);

/**
 * @brief 设置CAN通讯的波特率
 */
void NRC_SetCANBaudRate(unsigned int baud);
/**
 * @brief CAN通讯发送一帧数据
  * @param sendID 设置帧ID通过该变量返回
 * @param sendlen 设置发送数据长度
 * @param buff 要发送的数据
 */
void NRC_SendCANData(unsigned int sendCanID, const unsigned char buff[8], unsigned int sendLen=8);
/**
 * @brief CAN通讯读取一帧数据
 * @param recvID -R4P：读取的数据帧ID通过该变量返回
 *								  -R1/R4：接收recID发送来的数据，过滤其他ID的数据
 * @param buff 读取到的数据通过该变量返回
 * @return 返回读取到的数据字节数
 */
unsigned int NRC_ReadCANData(unsigned int & recvID ,  unsigned char buff[8]);

/**
 * @brief 读取BOOL变量的值
 * @param num BOOL变量的编号，取值范围：0 < num <= 999
 */
bool NRC_ReadBoolVar(int num);
/**
 * @brief 读取INT变量的值
 * @param num INT变量的编号，取值范围：0 < num <= 999
 */
int NRC_ReadIntVar(int num);
/**
 * @brief 读取DOUBLE变量的值
 * @param num DOUBLE变量的编号，取值范围：0 < num <= 999
 */
double NRC_ReadDoubleVar(int num);

/**
 * @brief 设置BOOL变量的值
 * @param num BOOL变量的编号，取值范围：0 < num <= 999
 * @param value 要设置的目标值
 */
int NRC_SetBoolVar(int num, bool value);
/**
 * @brief 设置INT变量的值
 * @param num INT变量的编号，取值范围：0 < num <= 999
 * @param value 要设置的目标值
 */
int NRC_SetIntVar(int num, int value);
/**
 * @brief 设置DOUBLE变量的值
 * @param num DOUBLE变量的编号，取值范围：0 < num <= 999
 * @param value 要设置的目标值
 */
int NRC_SetDoubleVar(int num, double value);
/**
 * @brief 设置全局位置变量坐标值
 * @param num 要设置的全局位置变量编号,0 < num <= 999
 * @param pos_set 要设置的全局位置变量坐标值
 *  */
int NRC_SetGlobalPositionVariable(int num, NRC_Position pos_set);
/**
 * @brief 设置全局位置变量注释
 * @param num 要设置的全局位置变量编号,0 < num <= 999
 * @param note 给全局变量设置的注释
 *  */
int NRC_SetGlobalPositionVariableNote(int num, std::string note);

/**
 * @brief 获取全局位置变量坐标值
 * @param num 要获取的全局位置变量编号,0 < num <= 999
 * @param pos_get 要获取的全局位置变量坐标值
 *  */
int NRC_GetGlobalPositionVariable(int num, NRC_Position& pos_get);
/**
 * @brief 获取全局位置变量注释
 * @param num 要获取的全局位置变量编号,0 < num <= 999
 * @param note 要获取的全局位置变量的注释
 *  */
int NRC_GetGlobalPositionVariableNote(int num, std::string& note);

/**
 * @brief 新建作业文件
 * @param jobname 要新建的作业文件名称
 */
int NRC_CreateJobfile(std::string jobname);
/**
 * @brief 打开作业文件
 * @param jobname 要打开的作业文件名称
 */
int NRC_OpenJobfile(std::string jobname);
/**
 * @brief 删除作业文件
 * @param jobname 要删除的作业文件名称
 */
int NRC_DeleteJobfile(std::string jobname);

/**
 * @brief 检测作业文件是否存在
 * @param jobname 要检测的作业文件名称
 * @retval  0  作业文件不存在
 * @retval  1  作业文件已存在
 */
int NRC_JudgeJobIsExist(std::string jobname);
/**
 * @brief 检测作业文件是否存在
 * @param jobname 要检测的作业文件名称
 * @retval  0  作业文件不存在
 * @retval  1  作业文件已存在
 */
int NRC_JudgeJobIsExist(std::string jobname);
/**
 * @brief 新建局部后台程序
 * @param jobname 要新建的局部后台程序名称
 * @note 后台程序不能插入任何运动指令，只能进行逻辑操作
 */
int NRC_CreatePthreadJobfile(std::string jobname);
/**
 * @brief 打开局部后台程序
 * @param jobname 要打开的作业文件名称
 */
int NRC_OpenPthreadJobfile(std::string jobname);
/**
 * @brief 删除局部后台程序
 * @param jobname 要删除的作业文件名称
 */
int NRC_DeletePthreadJobfile(std::string jobname);
/**
 * @brief 检测局部后台程序是否存在
 * @param jobname 要检测的局部后台程序名称
 * @retval  0  局部后台程序不存在
 * @retval  1  局部后台程序已存在
 */
int NRC_JudgePthreadJobIsExist(std::string jobname);

/**
 * @brief 当前打开的作业文件的总行数
 * @pre 调用该函数前，请先调用 NRC_CreateJobfile(std::string jobname) 或 NRC_OpenJobfile(std::string jobname) 创建或打开一个作业文件
 * @return 返回当前打开的作业文件的总行数
 */
int NRC_GetJobfileLineSum();

/**
 * @brief 开始/继续运行作业文件
 * @pre 该函数仅在运行模式下有效
 * @param jobname 要开始运行的作业文件，继续运行时该参数无效
 * @warning 成功调用该函数后，机器人将开始运动，请注意安全
 */
int NRC_StartRunJobfile(std::string jobname);
/**
 * @brief 单步运行作业文件一行指令
 * @pre 该函数仅在示教模式下有效
 * @param jobname 要单步运行的作业文件，继续运行时该参数无效
  * @param line 要单步运行的指令行号，继续运行时该参数无效
 * @warning 成功调用该函数后，机器人将开始运动，请注意安全
 */
int NRC_StepRunJobfile(std::string jobname, int line);
/**
 * @brief 暂停运行作业文件
 * @note 暂停运行作业文件，调用 NRC_StartRunJobfile() 将继续运行
 */
int NRC_PauseRunJobfile();
/**
 * @brief 停止运行作业文件
 * @note 停止运行作业文件，执行后再调用 NRC_StartRunJobfile(std::string jobname) 将从头开始运行
 */
int NRC_StopRunJobfile();

/**
 * @brief 停止运行作业文件并且不下使能
 * @note 停止运行作业文件，并且不会下使能，执行后再调用 NRC_StartRunJobfile(std::string jobname) 将从头开始运行
 */
int NRC_StopRunJobfileNotPoweroff();

/**
 * @brief 创建一个无文件运行队列
 * @note 创建一个无文件运行队列后，调用插入指令函数后，调用开始运行无文件运行队列函数，即可进行一条或多条指令运动
 */
int NRC_CreateNoFlieRunqueue();
/**
 * @brief 开始运行无文件运行队列
 * @note 开始运行后，若要添加新的运行指令，请在本次运行结束后重新重新创建一个无文件运行队列
 * @warning 成功调用该函数后，机器人将开始运动，请注意安全
 */
int NRC_StartRunNoFlieRunqueue();
/**
 * @brief 暂停运行无文件运行队列
 * @note 暂停运行无文件运行队列，调用 NRC_StartRunNoFlieRunqueue() 将继续运行
 */
int NRC_PauseRunNoFlieRunqueue();
/**
 * @brief 停止运行无文件运行队列
 * @note 停止后，若要继续运行，请重新创建一个无文件运行队列
 */
int NRC_StopRunNoFlieRunqueue();
/**
 * @brief 停止运行无文件运行队列并且不下使能
 * @note 停止后，若要继续运行，请重新创建一个无文件运行队列
 */
int NRC_StopRunNoFlieRunqueueNotPoweroff();

/**
 * @brief 删除作业文件指令
 * @param line 要删除的指令所在的行号，参数范围：0 < line <= NRC_GetJobfileLineSum()
 */
int NRC_JobfileEraseCmd(int line);

/**
 * @brief 运行队列插入MOVJ指令
 * @pre 调用该函数前，请先调用 NRC_CreateNoFlieRunqueue() 创建一个无文件运行队列
 * @param vel 机器人的运行速度，为机器人最大速度的百分比，参数范围：0 < vel <= 100
 * @param acc 机器人运行加速度，为机器人各关节最大加速度的百分比，参数范围：0 < vel <= 100
 * @param dec 机器人运行减速度，为机器人各关节最大减速度的百分比，参数范围：0 < vel <= 100
 * @param target 机器人运动目标位置，详见 NRC_Position
 * @param pl 平滑度，将和后面一条移动指令进行平滑过渡，数值越大，越平滑，轨迹偏差也越大，参数范围：0 <= pl <= 5
 */
int NRC_RunqueueInsertMOVJ(int vel, int acc, int dec, const NRC_Position& target, int pl=0,int tm = 0);
/**
 * @brief 作业文件插入MOVJ指令
 * @pre 调用该函数前，请先调用 NRC_CreateJobfile(std::string jobname) 或 NRC_OpenJobfile(std::string jobname) 创建或打开一个作业文件
 * @param line 将指令插入到第line行，参数范围：0 < line <= (NRC_GetJobfileLineSum()+1)
 * @param vel 机器人的运行速度，为机器人最大速度的百分比，参数范围：0 < vel <= 100
 * @param acc 机器人运行加速度，为机器人各关节最大加速度的百分比，参数范围：0 < vel <= 100
 * @param dec 机器人运行减速度，为机器人各关节最大减速度的百分比，参数范围：0 < vel <= 100
 * @param target 机器人运动目标位置，详见 NRC_Position
 * @param pl 平滑度，将和后面一条移动指令进行平滑过渡，数值越大，越平滑，轨迹偏差也越大，参数范围：0 <= pl <= 5
 */
int NRC_JobfileInsertMOVJ(int line, int vel, int acc, int dec, const NRC_Position& target, int pl=0,int tm = 0);

/**
 * @brief 运行队列插入MOVL指令
 * @pre 调用该函数前，请先调用 NRC_CreateNoFlieRunqueue() 创建一个无文件运行队列
 * @param vel 机器人的运行速度，为机器人末端位置点绝对运行速度，单位为 毫米每秒（mm/s），参数范围：vel > 1
 * @param acc 机器人运行加速度，为机器人笛卡尔最大加速度的百分比，参数范围：0 < vel <= 100
 * @param dec 机器人运行减速度，为机器人笛卡尔最大减速度的百分比，参数范围：0 < vel <= 100
 * @param target 机器人运动目标位置，详见 NRC_Position
 * @param pl 平滑度，将和后面一条移动指令进行平滑过渡，数值越大，越平滑，轨迹偏差也越大，参数范围：0 <= pl <= 5
 */
int NRC_RunqueueInsertMOVL(int vel, int acc, int dec, const NRC_Position& target, int pl=0,int tm = 0);
/**
 * @brief 作业文件插入MOVL指令
 * @pre 调用该函数前，请先调用 NRC_CreateJobfile(std::string jobname) 或 NRC_OpenJobfile(std::string jobname) 创建或打开一个作业文件
 * @param line 将指令插入到第line行，参数范围：0 < line < (NRC_GetJobfileLineSum()+1)
 * @param vel 机器人的运行速度，为机器人末端位置点绝对运行速度，单位为 毫米每秒（mm/s），参数范围：vel > 1
 * @param acc 机器人运行加速度，为机器人笛卡尔最大加速度的百分比，参数范围：0 < vel <= 100
 * @param dec 机器人运行减速度，为机器人笛卡尔最大减速度的百分比，参数范围：0 < vel <= 100
 * @param target 机器人运动目标位置，详见 NRC_Position
 * @param pl 平滑度，将和后面一条移动指令进行平滑过渡，数值越大，越平滑，轨迹偏差也越大，参数范围：0 <= pl <= 5
 */
int NRC_JobfileInsertMOVL(int line, int vel, int acc, int dec, const NRC_Position& target, int pl=0,int tm = 0);

/**
 * @brief 运行队列插入MOVC指令
 * @pre 调用该函数前，请先调用 NRC_CreateNoFlieRunqueue() 创建一个无文件运行队列
 * @param vel 机器人的运行速度，为机器人末端位置点绝对运行速度，单位为 毫米每秒（mm/s），参数范围：vel > 1
 * @param acc 机器人运行加速度，为机器人笛卡尔最大加速度的百分比，参数范围：0 < vel <= 100
 * @param dec 机器人运行减速度，为机器人笛卡尔最大减速度的百分比，参数范围：0 < vel <= 100
 * @param target 机器人运动目标位置，详见 NRC_Position
 * @param pl 平滑度，将和后面一条移动指令进行平滑过渡，数值越大，越平滑，轨迹偏差也越大，参数范围：0 <= pl <= 5
 * @attention MOVC指令需要两条才可执行
 * @par 示例:
 * @code
 * 		//以100mm/s的速度以圆弧插补方式经过pos1点到达pos2点
 *			NRC_RunqueueInsertMOVC(100, pos1, 0);
 *			NRC_RunqueueInsertMOVC(100, pos2, 0);
 * @endcode
 */
int NRC_RunqueueInsertMOVC(int vel, int acc, int dec, const NRC_Position& target, int pl=0,int tm = 0);
/**
 * @brief 作业文件插入MOVC指令
 * @pre 调用该函数前，请先调用 NRC_CreateJobfile(std::string jobname) 或 NRC_OpenJobfile(std::string jobname) 创建或打开一个作业文件
 * @param line 将指令插入到第line行，参数范围：0 < line < (NRC_GetJobfileLineSum()+1)
 * @param vel 机器人的运行速度，为机器人末端位置点绝对运行速度，单位为 毫米每秒（mm/s），参数范围：vel > 1
 * @param acc 机器人运行加速度，为机器人笛卡尔最大加速度的百分比，参数范围：0 < vel <= 100
 * @param dec 机器人运行减速度，为机器人笛卡尔最大减速度的百分比，参数范围：0 < vel <= 100
 * @param target 机器人运动目标位置，详见 NRC_Position
 * @param pl 平滑度，将和后面一条移动指令进行平滑过渡，数值越大，越平滑，轨迹偏差也越大，参数范围：0 <= pl <= 5
 * @attention MOVC指令需要两条才可执行
 * @par 示例:
 * @code
 * 		//以100mm/s的速度以圆弧插补方式经过pos1点到达pos2点
 *			NRC_JobfileInsertMOVC(1, 100, pos1, 0);//在第1行插入一条MOVC
 *			NRC_JobfileInsertMOVC(2, 100, pos2, 0);//在第2行插入一条MOVC
 * @endcode
 */
int NRC_JobfileInsertMOVC(int line, int vel, int acc, int dec, const NRC_Position& target, int pl=0,int tm = 0);

/**
 * @brief 运行队列插入IMOV指令
 * @pre 调用该函数前，请先调用 NRC_CreateNoFlieRunqueue() 创建一个无文件运行队列
 * @attention deviation.coord为NRC_ACS时，该指令将使用关节插补方式，deviation.coord为其他值时，使用直线插补方式
 * @param vel 机器人的运行速度
 * 		- deviation.coord为NRC_ACS时，为机器人最大速度的百分比，参数范围：0 < vel <= 100
 * 		- deviation.coord不为NRC_ACS时，为机器人末端位置点绝对运行速度，单位为 毫米每秒（mm/s），参数范围：vel > 1
 * @param acc 机器人运行加速度，参数范围：0 < vel <= 100
 * 		- deviation.coord为NRC_ACS时，为机器人各关节最大加速度的百分比
 * 		- deviation.coord不为NRC_ACS时，为机器人笛卡尔最大加速度的百分比
 * @param dec 机器人运行减速度，参数范围：0 < vel <= 100
 * 		- deviation.coord为NRC_ACS时，为机器人各关节最大减速度的百分比
 * 		- deviation.coord不为NRC_ACS时，为机器人笛卡尔最大减速度的百分比
 * @param deviation 机器人运动偏移量，详见 NRC_Position
 * @param pl 平滑度，将和后面一条移动指令进行平滑过渡，数值越大，越平滑，轨迹偏差也越大，参数范围：0 <= pl <= 5
 */
int NRC_RunqueueInsertIMOV(int vel, int acc, int dec, const NRC_Position& deviation, int pl=0,int tm = 0);
/**
 * @brief 作业文件插入IMOV指令
 * @pre 调用该函数前，请先调用 NRC_CreateJobfile(std::string jobname) 或 NRC_OpenJobfile(std::string jobname) 创建或打开一个作业文件
* @attention deviation.coord为NRC_ACS时，该指令将使用关节插补方式，deviation.coord为其他值时，使用直线插补方式
 * @param line 将指令插入到第line行，参数范围：0 < line < (NRC_GetJobfileLineSum()+1)
 * @param vel 机器人的运行速度
 * 		- deviation.coord为NRC_ACS时，为机器人最大速度的百分比，参数范围：0 < vel <= 100
 * 		- deviation.coord不为NRC_ACS时，为机器人末端位置点绝对运行速度，单位为 毫米每秒（mm/s），参数范围：vel > 1
 * @param acc 机器人运行加速度，参数范围：0 < vel <= 100
 * 		- deviation.coord为NRC_ACS时，为机器人各关节最大加速度的百分比
 * 		- deviation.coord不为NRC_ACS时，为机器人笛卡尔最大加速度的百分比
 * @param dec 机器人运行减速度，参数范围：0 < vel <= 100
 * 		- deviation.coord为NRC_ACS时，为机器人各关节最大减速度的百分比
 * 		- deviation.coord不为NRC_ACS时，为机器人笛卡尔最大减速度的百分比
 * @param deviation 机器人运动偏移量，详见 NRC_Position
 * @param pl 平滑度，将和后面一条移动指令进行平滑过渡，数值越大，越平滑，轨迹偏差也越大，参数范围：0 <= pl <= 5
 */
int NRC_JobfileInsertIMOV(int line, int vel, int acc, int dec, const NRC_Position& deviation, int pl=0,int tm = 0);

/**
 * @brief 运行队列插入DOUT指令
 * @pre 调用该函数前，请先调用 NRC_CreateNoFlieRunqueue() 创建一个无文件运行队列
 * @param port 要输出的数字输出端口号，参数范围：port > 0
 * @param value 端口输出的状态
 *    -   0  输出低电平
 *    -   1  输出高电平
 */
int NRC_RunqueueInsertDOUT(int port, int value);
/**
 * @brief 作业文件插入DOUT指令
 * @pre 调用该函数前，请先调用 NRC_CreateJobfile(std::string jobname) 或 NRC_OpenJobfile(std::string jobname) 创建或打开一个作业文件
 * @param line 将指令插入到第line行，参数范围：0 < line < (NRC_GetJobfileLineSum()+1)
 * @param port 要输出的数字输出端口号，参数范围：port > 0
 * @param value 端口输出的状态
 *    -   0  输出低电平
 *    -   1  输出高电平
 */
int NRC_JobfileInsertDOUT(int line, int port, int value);

/**
 * @brief 运行队列插入TIMER指令
 * @pre 调用该函数前，请先调用 NRC_CreateNoFlieRunqueue() 创建一个无文件运行队列
 * @param timeSec 要延时的时间，单位为秒，参数范围：timeSec > 0
 */
int NRC_RunqueueInsertTIMER(double timeSec);
/**
 * @brief 作业文件插入TIMER指令
 * @pre 调用该函数前，请先调用 NRC_CreateJobfile(std::string jobname) 或 NRC_OpenJobfile(std::string jobname) 创建或打开一个作业文件
 * @param line 将指令插入到第line行，参数范围：0 < line < (NRC_GetJobfileLineSum()+1)
* @param timeSec 要延时的时间，单位为秒，参数范围：timeSec > 0
 */
int NRC_JobfileInsertTIMER(int line, double timeSec);

/**
 * @brief 运行队列插入WAIT指令
 * @pre 调用该函数前，请先调用 NRC_CreateNoFlieRunqueue() 创建一个无文件运行队列
 * @param port 要检测的数字输入端口号，参数范围：port > 0
 * @param value 要等待的输入状态
 *    -   0  低电平输入状态
 *    -   1  高电平输入状态
 * @param timeoutSec 超时时间，单位为秒，参数范围：timeSec >= 0
 * 		- 如果等待timeoutSec时间仍未满足要求，将不再继续等待，本条指令执行结束
 * 		- 值为0时，将无限时间等待，直到条件成立
 */
int NRC_RunqueueInsertWAIT( int port, int value, double timeoutSec, bool now=false);
/**
 * @brief 作业文件插入WAIT指令
 * @pre 调用该函数前，请先调用 NRC_CreateJobfile(std::string jobname) 或 NRC_OpenJobfile(std::string jobname) 创建或打开一个作业文件
 * @param line 将指令插入到第line行，参数范围：0 < line < (NRC_GetJobfileLineSum()+1)
 * @param port 要检测的数字输入端口号，参数范围：port > 0
 * @param value 要等待的输入状态
 *    -   0  低电平输入状态
 *    -   1  高电平输入状态
 * @param timeoutSec 超时时间，单位为秒，参数范围：timeSec >= 0
 * 		- 如果等待timeoutSec时间仍未满足要求，将不再继续等待，本条指令执行结束
 * 		- 值为0时，将无限时间等待，直到条件成立
 */
int NRC_JobfileInsertWAIT(int line,  int port, int value, double timeoutSec, bool now=false);

/**
 * @brief 运行队列插入UNTIL指令
 * @pre 调用该函数前，请先调用 NRC_CreateNoFlieRunqueue() 创建一个无文件运行队列
 * @param port 要检测的数字输入端口号，参数范围：port > 0
 * @param value 要检测的输入状态
 *    -   0  低电平输入状态
 *    -   1  高电平输入状态
 * @attention 需要和 NRC_RunqueueInsertENDUNTIL() 配合使用
 * @par 示例:
 * @code
 * 		//在UNTIL和ENDUNTIL之间运行时，UNTIL的条件成立，将立刻中断当前运行指令，并跳转到ENDUNTIL执行
 * 		NRC_RunqueueInsertUNTIL(5, 1);
 *			NRC_RunqueueInsertMOVJ(100, pos1, 0);
 *			NRC_RunqueueInsertMOVL(100, pos2, 0);
 *			NRC_RunqueueInsertDOUT(1, 0);
 *			NRC_RunqueueInsertTIMER(0.5);
 *			NRC_RunqueueInsertENDUNTIL();
 * @endcode
 */
int NRC_RunqueueInsertUNTIL( int port, int value);
/**
 * @brief 作业文件插入UNTIL指令
 * @pre 调用该函数前，请先调用 NRC_CreateJobfile(std::string jobname) 或 NRC_OpenJobfile(std::string jobname) 创建或打开一个作业文件
 * @param line 将指令插入到第line行，参数范围：0 < line < (NRC_GetJobfileLineSum()+1)
 * @param port 要检测的数字输入端口号，参数范围：port > 0
 * @param value 要检测的输入状态
 *    -   0  低电平输入状态
 *    -   1  高电平输入状态
 * @attention 需要和 NRC_JobfileInsertENDUNTIL(int line) 配合使用
 * @par 示例:
 * @code
 * 		//在UNTIL和ENDUNTIL之间运行时，UNTIL的条件成立，将立刻中断当前运行指令，并跳转到ENDUNTIL执行
 * 		NRC_JobfileInsertUNTIL(1, 5, 1);
 *			NRC_JobfileInsertMOVJ(2, 100, pos1, 0);
 *			NRC_JobfileInsertMOVL(3, 100, pos2, 0);
 *			NRC_JobfileInsertDOUT(4, 1, 0);
 *			NRC_JobfileInsertTIMER(5, 0.5);
 *			NRC_JobfileInsertENDUNTIL(6);
 * @endcode
 */
int NRC_JobfileInsertUNTIL(int line,  int port, int value);
/**
 * @brief 运行队列插入ENDUNTIL指令
 * @pre 调用该函数前，请先调用 NRC_CreateNoFlieRunqueue() 创建一个无文件运行队列
 * @attention 需要和 NRC_RunqueueInsertUNTIL( int port, int value) 配合使用
 */
int NRC_RunqueueInsertENDUNTIL();
/**
 * @brief 作业文件插入ENDUNTIL指令
 * @pre 调用该函数前，请先调用 NRC_CreateJobfile(std::string jobname) 或 NRC_OpenJobfile(std::string jobname) 创建或打开一个作业文件
 * @param line 将指令插入到第line行，参数范围：0 < line < (NRC_GetJobfileLineSum()+1)
 * @attention 需要和 NRC_JobfileInsertUNTIL(int line,  int port, int value) 配合使用
 */
int NRC_JobfileInsertENDUNTIL(int line);

/**
 * @brief 运行队列插入IF指令
 * @pre 调用该函数前，请先调用 NRC_CreateNoFlieRunqueue() 创建一个无文件运行队列
 * @param port 要检测的数字输入端口号，参数范围：port > 0
 * @param value 要检测的输入状态
 *    -   0  低电平输入状态
 *    -   1  高电平输入状态
 * @attention 需要和 NRC_RunqueueInsertENDIF() 配合使用
 * @par 示例:
 * @code
 * 		//如果IF条件成立，执行IF代码块，否则执行ELSE代码块；如果没有ELSE指令，IF条件不成立，则会跳过IF代码块，直接执行ENDIF指令后面的指令
 * 		NRC_RunqueueInsertIF(5, 1);
 *			NRC_RunqueueInsertMOVJ(100, pos1, 0);
 *			NRC_RunqueueInsertDOUT(1, 0);
 *			NRC_RunqueueInsertELSE();
 *			NRC_RunqueueInsertMOVL(100, pos2, 0);
 *			NRC_RunqueueInsertTIMER(0.5);
 *			NRC_JobfileInsertENDIF();
 * @endcode
 */
int NRC_RunqueueInsertIF( int port, int value);
/**
 * @brief 作业文件插入IF指令
 * @pre 调用该函数前，请先调用 NRC_CreateJobfile(std::string jobname) 或 NRC_OpenJobfile(std::string jobname) 创建或打开一个作业文件
 * @param line 将指令插入到第line行，参数范围：0 < line < (NRC_GetJobfileLineSum()+1)
 * @param port 要检测的数字输入端口号，参数范围：port > 0
 * @param value 要检测的输入状态
 *    -   0  低电平输入状态
 *    -   1  高电平输入状态
 * @attention 需要和 NRC_JobfileInsertENDIF(int line) 配合使用
 * @par 示例:
 * @code
 * 		//如果IF条件成立，执行IF代码块，否则执行ELSE代码块；如果没有ELSE指令，IF条件不成立，则会跳过IF代码块，直接执行ENDIF指令后面的指令
 * 		NRC_JobfileInsertIF(1, 5, 1);
 *			NRC_JobfileInsertMOVJ(2, 100, pos1, 0);
 *			NRC_JobfileInsertDOUT(3, 1, 0);
 *			NRC_JobfileInsertELSE(4);
 *			NRC_JobfileInsertMOVL(5, 100, pos2, 0);
 *			NRC_JobfileInsertTIMER(6, 0.5);
 *			NRC_JobfileInsertENDIF(7);
 * @endcode
 */
int NRC_JobfileInsertIF(int line,  int port, int value);
/**
* @brief 作业文件插入带参数的IF指令
* @pre 调用该函数前，请先调用 NRC_CreateJobfile(std::string jobname) 或 NRC_OpenJobfile(std::string jobname) 创建或打开一个作业文件
* @param line 将指令插入到第line行，参数范围：0 < line < (NRC_GetJobfileLineSum()+1)
* @param varName 要比较的参数，例如 “GI001”
* @param type 比较的方法
* @param value 要比较的大小
* @attention 需要和 NRC_JobfileInsertENDIF(int line) 配合使用
*/
int NRC_JobfileInsertVarIF(int line, std::string varName, NRC_JUDGE type, double value);
/**
 * @brief 作业文件插入WHILE指令
 * @pre 调用该函数前，请先调用 NRC_CreateJobfile(std::string jobname) 或 NRC_OpenJobfile(std::string jobname) 创建或打开一个作业文件
 * @param line 将指令插入到第line行，参数范围：0 < line < (NRC_GetJobfileLineSum()+1)
 * @param port 要检测的数字输入端口号，参数范围：port > 0
 * @param value 要检测的输入状态
 *    -   0  低电平输入状态
 *    -   1  高电平输入状态
 * @attention 需要和 NRC_JobfileInsertENDWHILE(int line) 配合使用
 * @par 示例:
 * @code
 * 		//如果IF条件成立，执行IF代码块，否则执行ELSE代码块；如果没有ELSE指令，IF条件不成立，则会跳过IF代码块，直接执行ENDIF指令后面的指令
 * 		NRC_JobfileInsertIF(1, 5, 1);
 *			NRC_JobfileInsertMOVJ(2, 100, pos1, 0);
 *			NRC_JobfileInsertDOUT(3, 1, 0);
 *			NRC_JobfileInsertELSE(4);
 *			NRC_JobfileInsertMOVL(5, 100, pos2, 0);
 *			NRC_JobfileInsertTIMER(6, 0.5);
 *			NRC_JobfileInsertENDIF(7);
 * @endcode
 */
int NRC_JobfileInsertWHILE(int line,  int port, int value);
/**
* @brief 作业文件插入带参数的WHILE指令
* @pre 调用该函数前，请先调用 NRC_CreateJobfile(std::string jobname) 或 NRC_OpenJobfile(std::string jobname) 创建或打开一个作业文件
* @param line 将指令插入到第line行，参数范围：0 < line < (NRC_GetJobfileLineSum()+1)
* @param varName 要比较的参数，例如 “GI001”
* @param type 比较的方法
* @param value 要比较的大小
* @attention 需要和 NRC_JobfileInsertENDWHILE(int line) 配合使用
*/
int NRC_JobfileInsertVarWHILE(int line, std::string varName, NRC_JUDGE type, double value);
/**
 * @brief 运行队列插入ELSE指令
 * @pre 调用该函数前，请先调用 NRC_CreateNoFlieRunqueue() 创建一个无文件运行队列
 * @attention 需要和 NRC_RunqueueInsertIF( int port, int value) , NRC_RunqueueInsertENDIF() 配合使用
 */
int NRC_RunqueueInsertELSE();
/**
 * @brief 作业文件插入ELSE指令
 * @pre 调用该函数前，请先调用 NRC_CreateJobfile(std::string jobname) 或 NRC_OpenJobfile(std::string jobname) 创建或打开一个作业文件
 * @param line 将指令插入到第line行，参数范围：0 < line < (NRC_GetJobfileLineSum()+1)
 * @attention 需要和 NRC_JobfileInsertIF(int line,  int port, int value), NRC_JobfileInsertENDIF(int line) 配合使用
 */
int NRC_JobfileInsertELSE(int line);
/**
 * @brief 运行队列插入ENDWHILE指令
 * @pre 调用该函数前，请先调用 NRC_CreateNoFlieRunqueue() 创建一个无文件运行队列
 * @attention 需要和 NRC_RunqueueInsertWHILE( int port, int value) 配合使用
 */
int NRC_RunqueueInsertENDWHILE();
/**
 * @brief 作业文件插入ENDWHILE指令
 * @pre 调用该函数前，请先调用 NRC_CreateJobfile(std::string jobname) 或 NRC_OpenJobfile(std::string jobname) 创建或打开一个作业文件
 * @param line 将指令插入到第line行，参数范围：0 < line < (NRC_GetJobfileLineSum()+1)
 * @attention 需要和 NRC_JobfileInsertWHILE(int line,  int port, int value) 配合使用
 */
int NRC_JobfileInsertENDWHILE(int line);
/**
 * @brief 运行队列插入ENDIF指令
 * @pre 调用该函数前，请先调用 NRC_CreateNoFlieRunqueue() 创建一个无文件运行队列
 * @attention 需要和 NRC_RunqueueInsertIF( int port, int value) 配合使用
 */
int NRC_RunqueueInsertENDIF();
/**
 * @brief 作业文件插入ENDIF指令
 * @pre 调用该函数前，请先调用 NRC_CreateJobfile(std::string jobname) 或 NRC_OpenJobfile(std::string jobname) 创建或打开一个作业文件
 * @param line 将指令插入到第line行，参数范围：0 < line < (NRC_GetJobfileLineSum()+1)
 * @attention 需要和 NRC_JobfileInsertIF(int line,  int port, int value) 配合使用
 */
int NRC_JobfileInsertENDIF(int line);
/**
 * @brief 作业文件插入PAUSERUN指令
 * @pre 调用该函数前，请先调用 NRC_CreateJobfile(std::string jobname) 或 NRC_OpenJobfile(std::string jobname) 创建或打开一个作业文件
 * @param line 将指令插入到第line行，参数范围：0 < line < (NRC_GetJobfileLineSum()+1)
 * @attention 需要和 NRC_JobfileInsertIF(int line,  int port, int value) 配合使用
 */
int NRC_JobfileInsertPAUSERUN(int line);
/**
 * @brief 作业文件插入CONTINUERUN指令
 * @pre 调用该函数前，请先调用 NRC_CreateJobfile(std::string jobname) 或 NRC_OpenJobfile(std::string jobname) 创建或打开一个作业文件
 * @param line 将指令插入到第line行，参数范围：0 < line < (NRC_GetJobfileLineSum()+1)
 * @attention 需要和 NRC_JobfileInsertIF(int line,  int port, int value) 配合使用
 */
int NRC_JobfileInsertCONTINUERUN(int line);
/**
 * @brief 作业文件插入STOPRUN指令
 * @pre 调用该函数前，请先调用 NRC_CreateJobfile(std::string jobname) 或 NRC_OpenJobfile(std::string jobname) 创建或打开一个作业文件
 * @param line 将指令插入到第line行，参数范围：0 < line < (NRC_GetJobfileLineSum()+1)
 * @attention 需要和 NRC_JobfileInsertIF(int line,  int port, int value) 配合使用
 */
int NRC_JobfileInsertSTOPRUN(int line);
/**
 * @brief 作业文件插入RESTARTRUN指令
 * @pre 调用该函数前，请先调用 NRC_CreateJobfile(std::string jobname) 或 NRC_OpenJobfile(std::string jobname) 创建或打开一个作业文件
 * @param line 将指令插入到第line行，参数范围：0 < line < (NRC_GetJobfileLineSum()+1)
 * @attention 需要和 NRC_JobfileInsertIF(int line,  int port, int value) 配合使用
 */
int NRC_JobfileInsertRESTARTRUN(int line);
/**
* @brief 作业文件插入CMDNOTE指令
* @pre 调用该函数前，请先调用 NRC_CreateJobfile(std::string jobname) 或 NRC_OpenJobfile(std::string jobname) 创建或打开一个作业文件
* @param line 将指令插入到第line行，参数范围：0 < line < (NRC_GetJobfileLineSum()+1)
* @param note 备注内容
*/
int NRC_JobfileInsertCMDNOTE(int line,  std::string note);
/**
* @brief 作业文件插入PTHREAD_START指令
* @pre 调用该函数前，请先调用 NRC_CreateJobfile(std::string jobname) 或 NRC_OpenJobfile(std::string jobname) 创建或打开一个作业文件
* @param line 将指令插入到第line行，参数范围：0 < line < (NRC_GetJobfileLineSum()+1)
* @param jobName 要开启的局部后台程序名称
*/
int NRC_JobfileInsertPthreadStart(int line,  std::string jobName);
/**
* @brief 作业文件插入PTHREAD_END指令
* @pre 调用该函数前，请先调用 NRC_CreateJobfile(std::string jobname) 或 NRC_OpenJobfile(std::string jobname) 创建或打开一个作业文件
* @param line 将指令插入到第line行，参数范围：0 < line < (NRC_GetJobfileLineSum()+1)
* @param jobName 要结束的局部后台程序名称
*/
int NRC_JobfileInsertPthreadEnd(int line, std::string jobName);
/**
* @brief 作业文件插入SETVAR指令
* @pre 调用该函数前，请先调用 NRC_CreateJobfile(std::string jobname) 或 NRC_OpenJobfile(std::string jobname) 创建或打开一个作业文件
* @param line 将指令插入到第line行，参数范围：0 < line < (NRC_GetJobfileLineSum()+1)
* @param varName 要写入的变量名，如“GI001”，“B099”
* @param varValue 要写入的值
*/
int NRC_JobfileInsertSETVAR(int line, std::string varName, double varValue);
/**
* @brief 作业文件插入OPCmd指令
* @pre 调用该函数前，请先调用 NRC_CreateJobfile(std::string jobname) 或 NRC_OpenJobfile(std::string jobname) 创建或打开一个作业文件
* @param line 将指令插入到第line行，参数范围：0 < line < (NRC_GetJobfileLineSum()+1)
* @param varName 运算参数
* @param type 运算类型
* @param value 运算值
*/
int NRC_JobfileInsertOPCmd(int line, std::string varName, NRC_OPREATION type, double value);
/**
 * @brief 运行队列插入PALON指令
 * @pre 调用该函数前，请先调用 NRC_CreateNoFlieRunqueue() 创建一个无文件运行队列
 * @param id 码垛工艺的工艺号，参数范围：1 <= id <= 9
 * @param type 码垛类型
 *  - 0 码垛
 *  - 1 卸跺
 *  @param var1 存放当前已码工件总数，0表示不存放，1-100表示变量GI001-GI100，参数范围：0 <= var1 <= 100
 *  @param var2 存放当前已码层数，0表示不存放，1-100表示变量GI001-GI100，参数范围：0 <= var1 <= 100
 *  @param var3 存放当前层已码工件数，0表示不存放，1-100表示变量GI001-GI100，参数范围：0 <= var1 <= 100
 *  @attention 需要和 NRC_RunqueueInsertPALOFF(int id, int var) 配合使用
 */
/**
 * @brief 运行队列插入PALON指令
 * @pre 调用该函数前，请先调用 NRC_CreateNoFlieRunqueue() 创建一个无文件运行队列
 * @param id 码垛工艺的工艺号，参数范围：1 <= id <= 9
 * @param type 码垛类型
 *  - 0 码垛
 *  - 1 卸跺
 *  @param var1 存放当前已码工件总数，0表示不存放，1-100表示变量GI001-GI100，参数范围：0 <= var1 <= 100
 *  @param var2 存放当前已码层数，0表示不存放，1-100表示变量GI001-GI100，参数范围：0 <= var1 <= 100
 *  @param var3 存放当前层已码工件数，0表示不存放，1-100表示变量GI001-GI100，参数范围：0 <= var1 <= 100
 *  @attention 需要和 NRC_RunqueueInsertPALOFF(int id, int var) 配合使用
 */
int NRC_RunqueueInsertPALON(int id, int type, int var1=0, int var2=0, int var3=0);
/**
 * @brief 作业文件插入PALON指令
 * @pre 调用该函数前，请先调用 NRC_CreateJobfile(std::string jobname) 或 NRC_OpenJobfile(std::string jobname) 创建或打开一个作业文件
 * @param line 将指令插入到第line行，参数范围：0 < line < (NRC_GetJobfileLineSum()+1)
 * @param id 码垛工艺的工艺号，参数范围：1 <= id <= 9
 * @param type 码垛类型
 *  - 0 码垛
 *  - 1 卸跺
 *  @param var1 存放当前已码工件总数，0表示不存放，1-100表示变量GI001-GI100，参数范围：0 <= var1 <= 100
 *  @param var2 存放当前已码层数，0表示不存放，1-100表示变量GI001-GI100，参数范围：0 <= var2 <= 100
 *  @param var3 存放当前层已码工件数，0表示不存放，1-100表示变量GI001-GI100，参数范围：0 <= var3 <= 100
 * @attention 需要和 NRC_JobfileInsertPALOFF(int line, int id, int var) 配合使用
 */
int NRC_JobfileInsertPALON(int line, int id, int type, int var1=0, int var2=0, int var3=0);
/**
 * @brief 运行队列插入PALOFF指令
 * @pre 调用该函数前，请先调用 NRC_CreateNoFlieRunqueue() 创建一个无文件运行队列
 * @param id 码垛工艺的工艺号，参数范围：1 <= id <= 9
 * @param var 存放码垛是否结束判断，0表示不存放，1-100表示变量GB001-GB100，参数范围：0 <= var <= 100
 * @attention 需要和 NRC_RunqueueInsertPALON(int id, int type, int var1, int var2, int var3) 配合使用
 */
int NRC_RunqueueInsertPALOFF(int id, int var=0);
/**
 * @brief 作业文件插入PALOFF指令
 * @pre 调用该函数前，请先调用 NRC_CreateJobfile(std::string jobname) 或 NRC_OpenJobfile(std::string jobname) 创建或打开一个作业文件
 * @param line 将指令插入到第line行，参数范围：0 < line < (NRC_GetJobfileLineSum()+1)
 * @param id 码垛工艺的工艺号，参数范围：1 <= id <= 9
 * @param var 存放码垛是否结束判断，0表示不存放，1-100表示变量GB001-GB100，参数范围：0 <= var <= 100
 * @attention 需要和 NRC_JobfileInsertPALON(int line, int id, int type, int var1, int var2, int var3) 配合使用
 */
int NRC_JobfileInsertPALOFF(int line, int id, int var=0);
/**
 * @brief 运行队列插入PALGRIPPER指令
 * @pre 调用该函数前，请先调用 NRC_CreateNoFlieRunqueue() 创建一个无文件运行队列
 * @param id 码垛工艺的工艺号，参数范围：1 <= id <= 9
 * @param tool 要更换的抓手编号，参数范围：1 <= id <= 4
 */
int NRC_RunqueueInsertPALGRIPPER(int id, int tool);
/**
 * @brief 作业文件插入PALGRIPPER指令
 * @pre 调用该函数前，请先调用 NRC_CreateJobfile(std::string jobname) 或 NRC_OpenJobfile(std::string jobname) 创建或打开一个作业文件
 * @param line 将指令插入到第line行，参数范围：0 < line < (NRC_GetJobfileLineSum()+1)
 * @param id 码垛工艺的工艺号，参数范围：1 <= id <= 9
 * @param tool 要更换的抓手编号，参数范围：1 <= id <= 4
 */
int NRC_JobfileInsertPALGRIPPER(int line, int id, int tool);
/**
 * @brief 运行队列插入PALCLEAR指令
 * @pre 调用该函数前，请先调用 NRC_CreateNoFlieRunqueue() 创建一个无文件运行队列
 * @param id 码垛工艺的工艺号，参数范围：1 <= id <= 9
 */
int NRC_RunqueueInsertPALCLEAR(int id);
/**
 * @brief 作业文件插入PALCLEAR指令
 * @pre 调用该函数前，请先调用 NRC_CreateJobfile(std::string jobname) 或 NRC_OpenJobfile(std::string jobname) 创建或打开一个作业文件
 * @param line 将指令插入到第line行，参数范围：0 < line < (NRC_GetJobfileLineSum()+1)
 * @param id 码垛工艺的工艺号，参数范围：1 <= id <= 9
 */
int NRC_JobfileInsertPALCLEAR(int line, int id);
/**
 * @brief 运行队列插入PALENTER指令
 * @pre 调用该函数前，请先调用 NRC_CreateNoFlieRunqueue() 创建一个无文件运行队列
 * @param id 码垛工艺的工艺号，参数范围：1 <= id <= 9
 * @param moveType 该条指令所使用的插补方式
 * - 1 关节插补
 * - 2 直线插补
 * - 3 圆弧插补
 * @param vel 机器人的运行速度
 * - 插补方式为关节时  为机器人最大速度的百分比，参数范围：0 < vel <= 100
 * - 插补方式为直线或圆弧时  为机器人末端位置点绝对运行速度，单位为 毫米每秒（mm/s），参数范围：vel > 1
 * @param acc 机器人运行加速度，参数范围：0 < vel <= 100
 * - 插补方式为关节时  为机器人各关节最大加速度的百分比
 * - 插补方式为直线或圆弧时  为机器人笛卡尔最大加速度的百分比
 * @param dec 机器人运行减速度，参数范围：0 < vel <= 100
 * - 插补方式为关节时  为机器人各关节最大减速度的百分比
 * - 插补方式为直线或圆弧时  为机器人笛卡尔最大减速度的百分比
 * @param pl 平滑度，将和后面一条移动指令进行平滑过渡，数值越大，越平滑，轨迹偏差也越大，参数范围：0 <= pl <= 5
 */
int NRC_RunqueueInsertPALENTER(int id, int moveType, int vel, int acc, int dec, int pl);
/**
 * @brief 作业文件插入PALENTER指令
 * @pre 调用该函数前，请先调用 NRC_CreateJobfile(std::string jobname) 或 NRC_OpenJobfile(std::string jobname) 创建或打开一个作业文件
 * @param line 将指令插入到第line行，参数范围：0 < line < (NRC_GetJobfileLineSum()+1)
 * @param id 码垛工艺的工艺号，参数范围：1 <= id <= 9
 * @param moveType 该条指令所使用的插补方式
 * - 1 关节插补
 * - 2 直线插补
 * - 3 圆弧插补
 * @param vel 机器人的运行速度
 * - 插补方式为关节时  为机器人最大速度的百分比，参数范围：0 < vel <= 100
 * - 插补方式为直线或圆弧时  为机器人末端位置点绝对运行速度，单位为 毫米每秒（mm/s），参数范围：vel > 1
 * @param acc 机器人运行加速度，参数范围：0 < vel <= 100
 * - 插补方式为关节时  为机器人各关节最大加速度的百分比
 * - 插补方式为直线或圆弧时  为机器人笛卡尔最大加速度的百分比
 * @param dec 机器人运行减速度，参数范围：0 < vel <= 100
 * - 插补方式为关节时  为机器人各关节最大减速度的百分比
 * - 插补方式为直线或圆弧时  为机器人笛卡尔最大减速度的百分比
 * @param pl 平滑度，将和后面一条移动指令进行平滑过渡，数值越大，越平滑，轨迹偏差也越大，参数范围：0 <= pl <= 5
 */
int NRC_JobfileInsertPALENTER(int line, int id, int moveType, int vel, int acc, int dec, int pl);
/**
 * @brief 运行队列插入PALSHIFT指令
 * @pre 调用该函数前，请先调用 NRC_CreateNoFlieRunqueue() 创建一个无文件运行队列
 * @param id 码垛工艺的工艺号，参数范围：1 <= id <= 9
 * @param moveType 该条指令所使用的插补方式
 * - 1 关节插补
 * - 2 直线插补
 * - 3 圆弧插补
 * @param vel 机器人的运行速度
 * - 插补方式为关节时  为机器人最大速度的百分比，参数范围：0 < vel <= 100
 * - 插补方式为直线或圆弧时  为机器人末端位置点绝对运行速度，单位为 毫米每秒（mm/s），参数范围：vel > 1
 * @param acc 机器人运行加速度，参数范围：0 < vel <= 100
 * - 插补方式为关节时  为机器人各关节最大加速度的百分比
 * - 插补方式为直线或圆弧时  为机器人笛卡尔最大加速度的百分比
 * @param dec 机器人运行减速度，参数范围：0 < vel <= 100
 * - 插补方式为关节时  为机器人各关节最大减速度的百分比
 * - 插补方式为直线或圆弧时  为机器人笛卡尔最大减速度的百分比
 * @param pl 平滑度，将和后面一条移动指令进行平滑过渡，数值越大，越平滑，轨迹偏差也越大，参数范围：0 <= pl <= 5
 */
int NRC_RunqueueInsertPALSHIFT(int id, int moveType, int vel, int acc, int dec, int pl);
/**
 * @brief 作业文件插入PALSHIFT指令
 * @pre 调用该函数前，请先调用 NRC_CreateJobfile(std::string jobname) 或 NRC_OpenJobfile(std::string jobname) 创建或打开一个作业文件
 * @param line 将指令插入到第line行，参数范围：0 < line < (NRC_GetJobfileLineSum()+1)
 * @param id 码垛工艺的工艺号，参数范围：1 <= id <= 9
 * @param moveType 该条指令所使用的插补方式
 * - 1 关节插补
 * - 2 直线插补
 * - 3 圆弧插补
 * @param vel 机器人的运行速度
 * - 插补方式为关节时  为机器人最大速度的百分比，参数范围：0 < vel <= 100
 * - 插补方式为直线或圆弧时  为机器人末端位置点绝对运行速度，单位为 毫米每秒（mm/s），参数范围：vel > 1
 * @param acc 机器人运行加速度，参数范围：0 < vel <= 100
 * - 插补方式为关节时  为机器人各关节最大加速度的百分比
 * - 插补方式为直线或圆弧时  为机器人笛卡尔最大加速度的百分比
 * @param dec 机器人运行减速度，参数范围：0 < vel <= 100
 * - 插补方式为关节时  为机器人各关节最大减速度的百分比
 * - 插补方式为直线或圆弧时  为机器人笛卡尔最大减速度的百分比
 * @param pl 平滑度，将和后面一条移动指令进行平滑过渡，数值越大，越平滑，轨迹偏差也越大，参数范围：0 <= pl <= 5
 */
int NRC_JobfileInsertPALSHIFT(int line, int id, int moveType, int vel, int acc, int dec, int pl);
/**
 * @brief 运行队列插入PALREAL指令
 * @pre 调用该函数前，请先调用 NRC_CreateNoFlieRunqueue() 创建一个无文件运行队列
 * @param id 码垛工艺的工艺号，参数范围：1 <= id <= 9
 * @param moveType 该条指令所使用的插补方式
 * - 1 关节插补
 * - 2 直线插补
 * - 3 圆弧插补
 * @param vel 机器人的运行速度
 * - 插补方式为关节时  为机器人最大速度的百分比，参数范围：0 < vel <= 100
 * - 插补方式为直线或圆弧时  为机器人末端位置点绝对运行速度，单位为 毫米每秒（mm/s），参数范围：vel > 1
 * @param acc 机器人运行加速度，参数范围：0 < vel <= 100
 * - 插补方式为关节时  为机器人各关节最大加速度的百分比
 * - 插补方式为直线或圆弧时  为机器人笛卡尔最大加速度的百分比
 * @param dec 机器人运行减速度，参数范围：0 < vel <= 100
 * - 插补方式为关节时  为机器人各关节最大减速度的百分比
 * - 插补方式为直线或圆弧时  为机器人笛卡尔最大减速度的百分比
 * @param pl 平滑度，将和后面一条移动指令进行平滑过渡，数值越大，越平滑，轨迹偏差也越大，参数范围：0 <= pl <= 5
 */
int NRC_RunqueueInsertPALREAL(int id, int moveType, int vel, int acc, int dec, int pl);
/**
 * @brief 作业文件插入PALREAL指令
 * @pre 调用该函数前，请先调用 NRC_CreateJobfile(std::string jobname) 或 NRC_OpenJobfile(std::string jobname) 创建或打开一个作业文件
 * @param line 将指令插入到第line行，参数范围：0 < line < (NRC_GetJobfileLineSum()+1)
 * @param id 码垛工艺的工艺号，参数范围：1 <= id <= 9
 * @param moveType 该条指令所使用的插补方式
 * - 1 关节插补
 * - 2 直线插补
 * - 3 圆弧插补
 * @param vel 机器人的运行速度
 * - 插补方式为关节时  为机器人最大速度的百分比，参数范围：0 < vel <= 100
 * - 插补方式为直线或圆弧时  为机器人末端位置点绝对运行速度，单位为 毫米每秒（mm/s），参数范围：vel > 1
 * @param acc 机器人运行加速度，参数范围：0 < vel <= 100
 * - 插补方式为关节时  为机器人各关节最大加速度的百分比
 * - 插补方式为直线或圆弧时  为机器人笛卡尔最大加速度的百分比
 * @param dec 机器人运行减速度，参数范围：0 < vel <= 100
 * - 插补方式为关节时  为机器人各关节最大减速度的百分比
 * - 插补方式为直线或圆弧时  为机器人笛卡尔最大减速度的百分比
 * @param pl 平滑度，将和后面一条移动指令进行平滑过渡，数值越大，越平滑，轨迹偏差也越大，参数范围：0 <= pl <= 5
 */
int NRC_JobfileInsertPALREAL(int line, int id, int moveType, int vel, int acc, int dec, int pl);

/**
 * @brief 运行队列插入ARCON指令
 * @pre 调用该函数前，请先调用 NRC_CreateNoFlieRunqueue() 创建一个无文件运行队列
 * @param id 码垛工艺的工艺号，参数范围：1 <= id <= 99
 * @attention 需要和 NRC_RunqueueInsertARCOFF(int id) 配合使用
 */
int NRC_RunqueueInsertARCON(int id);
/**
 * @brief 作业文件插入ARCON指令
 * @pre 调用该函数前，请先调用 NRC_CreateJobfile(std::string jobname) 或 NRC_OpenJobfile(std::string jobname) 创建或打开一个作业文件
 * @param line 将指令插入到第line行，参数范围：0 < line < (NRC_GetJobfileLineSum()+1)
 * @param id 码垛工艺的工艺号，参数范围：1 <= id <= 99
 * @attention 需要和 NRC_JobfileInsertARCOFF(int line, int id) 配合使用
 */
int NRC_JobfileInsertARCON(int line, int id);
/**
 * @brief 运行队列插入ARCOFF指令
 * @pre 调用该函数前，请先调用 NRC_CreateNoFlieRunqueue() 创建一个无文件运行队列
 * @param id 码垛工艺的工艺号，参数范围：1 <= id <= 99
 * @attention 需要和 NRC_RunqueueInsertARCON(int id) 配合使用
 */
int NRC_RunqueueInsertARCOFF(int id);
/**
 * @brief 作业文件插入ARCOFF指令
 * @pre 调用该函数前，请先调用 NRC_CreateJobfile(std::string jobname) 或 NRC_OpenJobfile(std::string jobname) 创建或打开一个作业文件
 * @param line 将指令插入到第line行，参数范围：0 < line < (NRC_GetJobfileLineSum()+1)
 * @param id 码垛工艺的工艺号，参数范围：1 <= id <= 99
 * @attention 需要和 NRC_JobfileInsertARCON(int line, int id) 配合使用
 */
int NRC_JobfileInsertARCOFF(int line, int id);

/**
 * @brief 运行队列插入CustomInstruction指令
 * @pre 调用该函数前，请先调用 NRC_CreateNoFlieRunqueue() 创建一个无文件运行队列
 * @param id 自定义指令的ID
 */
int NRC_RunqueueInsertCustomInstruction(int id);
/**
 * @brief 作业文件插入CustomInstruction指令
 * @pre 调用该函数前，请先调用 NRC_CreateJobfile(std::string jobname) 或 NRC_OpenJobfile(std::string jobname) 创建或打开一个作业文件
 * @param line 将指令插入到第line行，参数范围：0 < line <= (NRC_GetJobfileLineSum()+1)
 * @param id 自定义指令的ID
 */
int NRC_JobfileInsertCustomInstruction(int line, int id);

/**
 * @brief 获取当前运行队列运行的行号
 * @return 返回当前运行队列运行的行号
 */
int NRC_GetRunqueueCurrentRunLine();
/**
 * @brief 获取当前运行作业文件运行的行号
 * @return 返回当前运行作业文件运行的行号
 */
int NRC_GetJobfileCurrentRunLine();

/**
 * @brief 获取当前作业文件要运行的总次数
 * @return 返回当前作业文件要运行的总次数
 */
int NRC_GetCycleIndex();
/**
 * @brief 获取当前作业文件已运行的次数
 * @return 返回当前作业文件已运行的次数
 */
int NRC_GetCycleCount();
/**
 * @brief 获取当前作业文件已运行的时间
 * @return 返回当前作业文件已运行的时间
 */
int NRC_GetCycleTimeSec();
/**
 * @brief 设置当前作业文件要运行的总次数
 * @note 设置当前作业文件要运行的总次数，设置时，同时会把当前已运行次数重置为1
 * @param index 当前作业文件要运行的总次数，设置为0时循环运行，参数范围：index >= 0
 */
int NRC_SetCycleIndex(int index);

/**
 * @brief 设置机器人类型
 * @param type 机器人类型
 * 	- "R_GENERAL_6S" 六轴
 * 	- "R_SCARA" 四轴SCARA
 * 	- "R_FOURAXIS_PALLET" 四轴码垛
 * 	- "R_FOURAXIS" 四轴
 * 	- "R_GENERAL_1S" 一轴
 * 	- "R_GENERAL_5S" 五轴
 * 	- "R_GENERAL_6S_1" 六轴异形一
 * 	- "R_SCARA_TWOAXIS" 两轴SCARA
 * 	- "R_SCARA_THREEAXIS" 三轴SCARA
 * 	- "R_THREE_CARTESIAN_COORDINATE" 三轴直角
 * 	- "R_THREE_CARTESIAN_COORDINATE_1" 三轴异形一
 * 	- "R_GENERAL_7S_RBT" 七轴
 * 	- "R_SCARA_1" 四轴SCARA异形一
 */
int NRC_SetRobotTypeConfig(std::string type);

/**
 * @brief 获取机器人类型
 * @param type 机器人类型
 * 	- "R_GENERAL_6S" 六轴
 * 	- "R_SCARA" 四轴SCARA
 * 	- "R_FOURAXIS_PALLET" 四轴码垛
 * 	- "R_FOURAXIS" 四轴
 * 	- "R_GENERAL_1S" 一轴
 * 	- "R_GENERAL_5S" 五轴
 * 	- "R_GENERAL_6S_1" 六轴异形一
 * 	- "R_SCARA_TWOAXIS" 两轴SCARA
 * 	- "R_SCARA_THREEAXIS" 三轴SCARA
 * 	- "R_THREE_CARTESIAN_COORDINATE" 三轴直角
 * 	- "R_THREE_CARTESIAN_COORDINATE_1" 三轴异形一
 * 	- "R_GENERAL_7S_RBT" 七轴
 * 	- "R_SCARA_1" 四轴SCARA异形一
 */
int NRC_GetRobotTypeConfig(std::string& type);

/**
 *
 * @brief 设置伺服映射关系
 * @param servoMap 伺服映射关系，个数为设置的机器人总轴数，值为每一轴所连接的伺服编号
 * @param syncServoMap 外部轴伺服映射关系，个数为3，值为每一轴所连接的伺服编号,若外部轴不足3个，对应位置值为0
 * @par 说明:
 *   机器人轴与伺服对应关系为：
 *     - 1轴 连接 第2个伺服
 *     - 2轴 连接 第3个伺服
 *     - 3轴 连接 第1个伺服
 *     - 4轴 连接 第4个伺服
 *     - 5轴 连接 第6个伺服
 *     - 6轴 连接 第5个伺服
 *     - 则 servoMap 的值为 { 2, 3, 1, 4, 6, 5 }
 *   外部轴个数与伺服对应关系
 *     - 无外部轴，则 syncServoMap 值为 {0 ,0 ,0}
 *     - 一个外部轴，则 syncServoMap 值为 {7 ,0 ,0}
 *     - 两个外部轴，则 syncServoMap 值为 {7 ,8 ,0}
 * @deprecated 以后替代函数为NRC_SetAllServoMapRelation
 */
int NRC_SetServoMapRelation(std::vector<int> servoMap,std::vector<int> syncServoMap);
/**
 * @brief 设置伺服映射关系
 * @param servoMap 伺服映射关系，个数为设置的机器人总轴数，值为每一轴所连接的伺服编号
 * @param syncGroupSum 外部轴组最大数目，最大为3,最多支持两个双变位机加一个地轨
 * @param syncType,外部轴组类型，0:无，1:单轴变位机，2:双轴变位机，3:地轨
 * @param syncServoMap,外部轴伺服映射关系
 * @par 说明:
 *   机器人轴与伺服对应关系为：
 *     - 1轴 连接 第2个伺服
 *     - 2轴 连接 第3个伺服
 *     - 3轴 连接 第1个伺服
 *     - 4轴 连接 第4个伺服
 *     - 5轴 连接 第6个伺服
 *     - 6轴 连接 第5个伺服
 *     - 则 servoMap 的值为 { 2, 3, 1, 4, 6, 5 }
 *   外部轴个数与伺服对应关系
 *     - 无外部轴，则 syncGroupSum 值为0,
 *     - 一个单轴变位机，则 syncGroupSum 值1,syncType为{1,0,0},syncServoMap为{{7}}
 *     - 两个双轴变位机，一个地轨，则 syncGroupSum 值3,syncType为{2,2,3},syncServoMap为{{7,8},{9,10},{11}}
 */
int NRC_SetAllServoMapRelation(std::vector<int> servoMap,int syncGroupSum, int syncType[], std::vector<std::vector<int>> syncServoMap);
/**
 * @brief 获取连接的伺服类型列表
 * @param nameType 伺服名称类型,0:中文名称,1:英文名称
 * @return 伺服名称列表
 */
std::vector<std::string> NRC_getConnectServoTypeList(int nameType);

/**
 * @brief 设置扩展IO类型
 * @param type 扩展IO类型
 * 	- "custom" 自定义扩展IO
 * 	- "none" 无扩展IO 或 自动识别扩展IO
 * @attention 如果是EtherCat扩展IO,则设置为"none",控制器会自动识别
 * @attention 如果连接了EtherCat扩展IO,设置为"custom"将不会生效
 * @attention 参数设置好后，需重启才能生效
 */
int NRC_SetIOTypeConfig(std::string type);
/**
 * @brief 获取扩展IO类型
 * @param type 返回扩展IO类型
 * 	- "none" 无扩展IO
 * 	- "ethercat" ethercat扩展IO
 * 	- "custom" 自定义扩展IO
 */
int NRC_GetIOTypeConfig(std::string& type);
/**
 * @brief 获取EthercatIO配置
 * @param sum 返回EthercatIO板数目
 * @param typeVec返回EthercatIO类型
 */
int NRC_GetEthercatIOConfig(int& sum, std::vector<std::string>& typeVec);

/**
 * @brief 设置自定义IO dout配置
 * @note 设置自定义IO dout的数目和对应地址，1表示高电平，0表示低电平
 * @param sum 自定义IO dout的数目，参数范围：sum >= 0
 * @param addr 自定义IO dout的对应地址,一个int数值对应1个端口
 */
int NRC_SetCustomIODoutConfig(int sum, int* addr);
/**
 * @brief 设置自定义IO din配置
 * @note 设置自定义IO din的数目和对应地址，1表示高电平，0表示低电平
 * @param sum 自定义IO din的数目，参数范围：sum >= 0
 * @param addr 自定义IO din的对应地址,一个int数值对应1个端口
 * @return
 */
int NRC_SetCustomIODinConfig(int sum, int* addr);

/**
 * @brief 设置内置tcp接口扩展IO检测使能标志
 * @param enable 默认为true,检测扩展IO,设置为false时,将不检测扩展IO
 * @attention 请在调用控制器启动函数 NRC_StartController 前设置使能标志,否则将不生效
 */
void NRC_SetCheckExioEnable(bool enable);

/**
 * @brief 设置机器人DH参数
 * @param config see NRC_RobotDHConfig
 * @attention 请在伺服停止或伺服就绪状态下设置该参数
 */
int NRC_SetRobotDHConfig(NRC_RobotDHConfig config);

/**
 * @brief 获取机器人DH参数
 * @param config see NRC_RobotDHConfig
 */
int NRC_GetRobotDHConfig(NRC_RobotDHConfig& config);

/**
 * @brief 设置机器人关节参数
 * @param axisNum 要设置的轴的序号，参数范围：1 <= axisNum <= 机器人轴总数
 * @param config see NRC_RobotJointConfig
 * @attention 请在伺服停止或伺服就绪状态下设置该参数
 */
int NRC_SetRobotJointConfig(int axisNum, NRC_RobotJointConfig config);

/**
 * @brief 设置机器人笛卡尔参数
 * @param config see NRC_RobotDecareConfig
 * @attention 请在伺服停止或伺服就绪状态下设置该参数
 */
int NRC_SetRobotDecareConfig(NRC_RobotDecareConfig config);

/**
 * @brief 获取机器人笛卡尔参数
 * @param config see NRC_RobotDecareConfig
 */
int NRC_GetRobotDecareConfig(NRC_RobotDecareConfig& config);

/**
 * @brief 点动关节速度设置
 * @param axisNum 要设置的轴的序号，参数范围：1 <= axisNum <= 机器人轴总数
 * @param maxSpeed 点动时，该轴可以达到的最大速度，单位：度/秒
 * @param acc 点动时，该轴的加速度，单位：度/平方秒
 * @attention 请在伺服停止或伺服就绪状态下设置该参数
 */
int NRC_SetJogJointSpeedConfig(int axisNum, double maxSpeed, double acc);
/**
 * @brief 获取点动关节速度
 * @param axisNum 要获取的轴的序号，参数范围：1 <= axisNum <= 机器人轴总数
 * @param maxSpeed 点动时，该轴可以达到的最大速度，单位：度/秒
 * @param acc 点动时，该轴的加速度，单位：度/平方秒
 */
int NRC_GetJogJointSpeedConfig(int axisNum, double& maxSpeed, double& acc);
/**
 * @brief 点动直角速度设置
 * @param maxSpeed 点动时，直角坐标可以达到的最大速度，单位：毫米/秒
 * @param acc 点动时，直角坐标的加速度，单位：毫米/平方秒
 * @attention 请在伺服停止或伺服就绪状态下设置该参数
 */
int NRC_SetJogRectangularSpeedConfig(double maxSpeed, double acc);

/**
 * @brief 获取点动直角速度
 * @param maxSpeed 点动时，直角坐标可以达到的最大速度，单位：毫米/秒
 * @param acc 点动时，直角坐标的加速度，单位：毫米/平方秒
 */
int NRC_GetJogRectangularSpeedConfig(double& maxSpeed, double& acc);
/**
 * @brief 设置点动灵敏度
 * @param sensitivity 该值越小，点动响应越慢，该值越大，点动误差越大，误差较大时，可能引起机器人抖动，单位：度，默认初始值0.001，参数范围：0.0001 <= sensitivity < 1
 * @attention 请在伺服停止或伺服就绪状态下设置该参数
 */
int NRC_SetJogSensitivitySpeedConfig(double sensitivity);

/**
 * @brief 设置机器人插补方式
 * @param method 机器人运动时的插补方式
 * 	- 0 S型插补，机器人加减速较为平滑，但相对于梯形插补加减速较慢，一般大型机器人用该插补方式
 * 	- 1 梯形插补，机器人加减速较为迅速，但容易造成机器人抖动、过载等现象，一般小型机器人用该插补方式
 * @attention 请在伺服停止或伺服就绪状态下设置该参数
 */
int NRC_SetInterpolationMethod(int method);
/**
 * @brief 设置机器人绝对位置分辨率
 * @param resolution 机器人对位置的分辨率，当两个位置之间的差距小于该值时，机器人将认为这两个位置为同一位置，单位：度，参数范围：0.0001 <= resolution <= 0.1
 * @attention 请在伺服停止或伺服就绪状态下设置该参数
 */
int NRC_SetAbsolutePosResolution(double resolution);

/**
 * @brief 设置最大允许动态超差值
 * @param trackingError 最大允许动态超差值，当超差值大于该值时，机器人将停止运行，数组成员个数应不小于机器人的轴数，单位：万分之一度，参数范围：100 <= trackingError <= 5000000
 * @attention 请在伺服停止或伺服就绪状态下设置该参数
 */
int NRC_SetDynamicTrackingErrorMaxAllow(int trackingError[]);
/**
 * @brief 设置最大允许静态超差值
 * @param trackingError 最大允许静态超差值，当超差值大于该值时，机器人将停止运行，数组成员个数应不小于机器人的轴数，单位：万分之一度，参数范围：100 <= trackingError <= 5000000
 * @attention 请在伺服停止或伺服就绪状态下设置该参数
 */
int NRC_SetStaticTrackingErrorMaxAllow(int trackingError[]);

/**
 * @brief 设置机器人范围限制
 * @param range see NRC_RobotRangeLimit
 * @attention 请在伺服停止或伺服就绪状态下设置该参数
 */
int NRC_SetRobotRangeLimit(NRC_RobotRangeLimit range);

/**
 * @brief 获取机器人范围限制
 * @brief 若未限制范围，则enable返回false，范围返回double型数据，若限制范围，则enable返回true，范围返回-9999
 * @param range see NRC_RobotRangeLimit
 */
int NRC_GetRobotRangeLimit(NRC_RobotRangeLimit& range);

/**
 * @brief 设置示教模式最大单步速度
 * @param maxJointSpeed 示教模式下单步运行时最大关节运行速度，单位百分比，参数范围：0 < maxJointSpeed <= 100
 * @param maxDecareSpeed 示教模式下单步运行时最大直线运行速度，单位mm/s，参数范围：2 <= maxJointSpeed <= 9999
 * @attention 请在伺服停止或伺服就绪状态下设置该参数
 */
int NRC_SetTeachMaxStepSpeed(int maxJointSpeed, int maxDecareSpeed);
/**
 * @brief 获取示教模式最大单步速度
 * @param maxJointSpeed 获取到的示教模式下单步运行时最大关节运行速度，单位百分比
 * @param maxDecareSpeed 获取到的示教模式下单步运行时最大直线运行速度，单位mm/s
 */
int NRC_GetTeachMaxStepSpeed(int &maxJointSpeed, int &maxDecareSpeed);

/**
 * @brief 将当前位置设置为零点或清除多圈值
 * @param axisNum 操作的轴的序号，当axisNum为0时，表示全部轴，参数范围：0 <= axisNum <= 机器人轴总数
 * @param mod为设置零点或清除多圈值，0为设置零点，1为清除多圈值
 * @attention 请在伺服停止或伺服就绪状态下设置该参数
 * @attention 执行该函数大约需要两三秒时间
 * @warning 对于大多数类型的伺服，执行该函数时，会使伺服使能上电，请注意安全
 */
int NRC_SetCurrentPosToZeroPos(int axisNum,bool mod);

/**
 * @brief 设置用户坐标参数
 * @note 设置用户坐标系原点相对机器人直角坐标系原点的偏移量，从而确定该用户坐标系
 * @param userNum 要设置的用户坐标系的编号，参数范围：0 < userNum < 10
 * @param deviation 用户坐标系原点相对机器人直角坐标系原点的偏移量
 * 	- deviation.coord 该参数无用
 * 	- deviation.pos[0]-deviation.pos[2] 分别为x,y,z三轴位置的偏移量，单位：毫米
 * 	- deviation.pos[3]-deviation.pos[4] 分别为x,y,z三轴方向的偏移量，单位：弧度
 * @attention 由于实际使用中，很难测量方向的偏移量，所有该函数很少使用，一般使用 NRC_CalibrationUserCoord(int userNum, NRC_Position& origin, NRC_Position& X_Axis, NRC_Position& XOY_Plane) 函数对用户坐标进行标定，自动计算出偏移量
 */
int NRC_SetUserCoordParm(int userNum, NRC_Position& deviation);

/**
 * @brief 获取用户坐标参数
 * @note 获取用户坐标系原点相对机器人直角坐标系原点的偏移量
 * @param userNum 要获取的用户坐标系的编号，参数范围：0 < userNum < 10
 * @param deviation 用户坐标系原点相对机器人直角坐标系原点的偏移量
 * 	- deviation.coord 该参数无用
 * 	- deviation.pos[0]-deviation.pos[2] 分别为x,y,z三轴位置的偏移量，单位：毫米
 * 	- deviation.pos[3]-deviation.pos[4] 分别为x,y,z三轴方向的偏移量，单位：弧度
 */
int NRC_GetUserCoordParm(int userNum,NRC_Position& deviation);

/**
 * @brief 标定用户坐标
 * @note 标定用户坐标系，自动计算用户坐标系原点相对机器人直角坐标系原点的偏移量，从而确定该用户坐标系
 * @param userNum 要标定的用户坐标系的编号，参数范围：0 < userNum < 10
 * @param origin 用户坐标系原点在机器人直角坐标系中的位置
 * @param X_Axis 用户坐标系X轴正方向上任一点在机器人直角坐标系中的位置
 * @param XOY_Plane 用户坐标系XOY平面上任一点在机器人直角坐标系中的位置
 */
int NRC_CalibrationUserCoord(int userNum, NRC_Position& origin, NRC_Position& X_Axis, NRC_Position& XOY_Plane);

/**
 * @brief 切换当前用户坐标
 * @param tagetUser 要切换的目标用户坐标系的编号，参数范围：0 < tagetUser < 10
 */
int NRC_SwitchUserCoord(int tagetUser);
/**
 * @brief 获取当前用户坐标编号
 * @return 当前用户坐标的编号，用户坐标系初始默认值为1
 */
int NRC_GetCurrentUserCoord();

/**
 * @brief 设置工具手参数
 * @note 设置工具手末端位置相对机器人末端位置的偏移量，从而确定该工具坐标系
 * @param toolNum 要设置的工具手的编号，参数范围：1 < toolNum < 10
 * @param deviation 工具手末端位置相对机器人末端位置的偏移量
 * 	- deviation.coord 该参数无用
 * 	- deviation.pos[0]-deviation.pos[2] 分别为x,y,z三轴位置的偏移量，单位：毫米
 * 	- deviation.pos[3]-deviation.pos[4] 分别为x,y,z三轴方向的偏移量，对于四轴SCARA机器人该参数无用，单位：弧度
 * @attention 实际使用中，一般根据工具手的设计尺寸图，直接填入该参数
 */
int NRC_SetToolCoordParm(int toolNum, NRC_Position& deviation);
/**
 * @brief 获取工具手参数
 * @param toolNum 要获取的工具手的编号，参数范围：0 < toolNum < 10
 * @param deviation 要获取到的工具手参数,工具手末端位置相对机器人末端位置的偏移量
 */
int NRC_GetToolCoordParm(int toolNum, NRC_Position& deviation);

/**
 * @brief 标定工具手--7点标定法
 * @note 标定工具手，自动计算工具手末端位置相对机器人末端位置的偏移量，从而确定该工具坐标系
 * @attention 7点标定法仅对六轴串联机器人有效
 * @param toolNum 要设置的工具手的编号，参数范围：0 < toolNum < 10
 * @param pos1 将工具手末端对准一个固定尖端，并保持工具手垂直的一个位置
 * @param pos2 将工具手末端对准一个固定尖端，选取一个位置，不能和pos1，pos3，pos4是同一位置
 * @param pos3 将工具手末端对准一个固定尖端，选取一个位置，不能和pos1，pos2，pos4是同一位置
 * @param pos4 将工具手末端对准一个固定尖端，选取一个位置，不能和pos1，pos2，pos3是同一位置
 * @param pos5 保持工具手垂直的一个位置，可以和pos1点是同一位置
 * @param pos6 相对pos5的X轴正方向上的一个位置
 * @param pos7 相对pos6的Y轴正方向上的一个位置
 * @param calibrationPointNum 6:六点标定,7:七点标定
 */
int NRC_CalibrationToolCoord_7Pos(int toolNum, NRC_Position& pos1, NRC_Position& pos2, NRC_Position& pos3, NRC_Position& pos4, NRC_Position& pos5, NRC_Position& pos6, NRC_Position& pos7, int calibrationPointNum = 7);
/**
 * @brief 切换当前工具手
 * @param tagetUser 要切换的目标工具手的编号，0表示无工具手，参数范围：0 <= tagetTool < 10
 */
int NRC_SwitchToolCoord(int tagetTool);
/**
 * @brief 获取当前工具手编号
 * @return 当前工具手的编号，工具手初始默认值为0，即无工具手
 */
int NRC_GetCurrentToolCoord();

/**
 * @brief 2点标定-设置点数据
 * @param posNum 标定的点的编号，参数范围：1 <= posNum <= 2
 * @param pos 标定的点的位置，需为关节坐标系下的位置
 * @par 示例:
 * @code
 *     NRC_CalibrationToolCoord_2Pos_SetPos(1, pos1);
 *     NRC_CalibrationToolCoord_2Pos_SetPos(2, pos2);
 *     if (NRC_CalibrationToolCoord_2Pos_Cacl() == 0)
 *     {
 *     	//将标定结果写入工具手1
 *     	NRC_CalibrationToolCoord_2Pos_Save(1);
 *     }
 * @endcode
 */
int NRC_CalibrationToolCoord_2Pos_SetPos(int posNum, const NRC_Position& pos);
/**
 * @brief 2点标定-计算标定结果
 * @return 计算标定结果是否成功
 * @retval 0 计算成功
 * @retval -1 计算失败
 */
int NRC_CalibrationToolCoord_2Pos_Cacl();
/**
 * @brief 2点标定-写入标定数据
 * @note 将2点标定的结果写入到指定的工具手中
 * @param tagetTool 要写入的工具手编号，参数范围：1 < tagetTool < 10
 */
int NRC_CalibrationToolCoord_2Pos_Save(int tagetTool);

/**
 * @brief 读取伺服某命令字的值
 * @param axisNum 机器人的轴编号
 * @param index 命令字编码
 * @param subindex 命令字子编码
 * @param value 结果存放入此指针返回
 * @param size 命令字对应的值的字节数
 * @par 示例:
 * @code
 *     unsigned short value = 0;
 *     NRC_ecatGetCommand(1, 0x6041, 0, (unsigned char* )&value, sizeof(value));
 *     printf("value=%d\n", value);
 *
 *     unsigned int value = 0;
 *     NRC_ecatGetCommand(3, 0x202C, 0, (unsigned char* )&value, sizeof(value));
 *     printf("value=%d\n", value);
 * @endcode
 */
int NRC_ecatGetCommand(unsigned int axisNum, unsigned int index, unsigned int subindex, unsigned char* value, unsigned int size);

/**
 * @brief 修改控制器IP
 * @param ip 要修改为的目标IP，要符合IP规则
 */
int NRC_ModifyControllerIP(std::string name,std::string ip,std::string gateway,std::string dns);
/**
 * @brief 恢复出厂设置
 * @attention 恢复出厂设置后，控制器中的各数据将会被清除，请谨慎操作
 * @attention 调用该函数后，控制器随即就会重启
 */
int NRC_RestoreFactorySettings();
/**
 * @brief /重启控制器
 * @attention 调用该函数后，控制器随即就会重启
 */
int NRC_RebootController();

/**
 * @brief 获取电机转速
 * @param vel 电机转速将通过数组返回，数组成员个数应不小于机器人的轴数
 */
int NRC_GetCurrentMotorVel(double vel[]);
/**
 * @brief 获取当前超差值
 * @param trackingError 当前超差值将通过数组返回，数组成员个数应不小于机器人的轴数
 */
int NRC_GetCurrentTrackingError(double trackingError[]);
/**
 * @brief 获取最大超差值
 * @param maxTrackingError 最大超差值将通过数组返回，数组成员个数应不小于机器人的轴数
 */
int NRC_GetMaxTrackingError(double maxTrackingError[]);
/**
 * @brief 获取机器人轴数
 */
int NRC_GetRobotAxisSum();

/**
 * @brief 获取外部轴轴数
 */
int NRC_GetSyncAxisSum();

/**
 * @brief 获取当前时间
 * @return see NRC_TIME
 */
NRC_TIME NRC_GetCurrentTime();

/**
 * @brief 设置使用使用简易码垛还是完整码垛
 * @param id 码垛工艺的工艺号，参数范围：1 <= id <= 9
 * @param type 使用的码垛类型
 * - 0 简易码垛
 * - 0 完整码垛
 */
int NRC_Pallet_SetUsePalletType(int id, int type);
/**
 * @brief 获取使用的是使用简易码垛还是完整码垛
 * @param id 码垛工艺的工艺号，参数范围：1 <= id <= 9
 * @return 使用的码垛类型
 * @retval 0 简易码垛
 * @retval 1 完整码垛
 */
int NRC_Pallet_GetUsePalletType(int id);
/**
 * @brief 设置码垛抓手数据
 * @param id 码垛工艺的工艺号，参数范围：1 <= id <= 9
 * @param gripperSum 可用抓手总数，参数范围：1 <= gripperSum <= 4
 * @param gripper[4] 每个抓手所绑定的工具坐标号，1 <= gripper[i] <= 9
 */
int NRC_Pallet_SetGripperParm(int id, int gripperSum, int gripper[4]);
/**
 * @brief 获取码垛抓手数据
 * @param id 码垛工艺的工艺号，参数范围：1 <= id <= 9
 * @param gripperSum 获取到的可用抓手总数
 * @param gripper[4] 获取到的每个抓手所绑定的工具坐标号
 */
int NRC_Pallet_GetGripperParm(int id, int& gripperSum, int gripper[4]);
/**
 * @brief 设置简易码垛位置数据
 * @param id 码垛工艺的工艺号，参数范围：1 <= id <= 9
 * @param posType 简易码垛的位置类型
 * - 0 起始工件点
 * - 1 列末端
 * - 2 行末端
 * - 3 高末端
 * - 4 起始辅助点
 * - 5 起始入口点
 * @param pos 简易码垛的位置数据，see NRC_Position
 */
int NRC_Pallet_SetSimplePosParm(int id, int posType, NRC_Position pos);
/**
 * @brief 获取简易码垛位置数据
 * @param id 码垛工艺的工艺号，参数范围：1 <= id <= 9
 * @param posType 简易码垛的位置类型
 * - 0 起始工件点
 * - 1 列末端，其托盘X方向(对应用户坐标的X方向)
 * - 2 行末端，其托盘Y方向(对应用户坐标的Y方向)
 * - 3 高末端
 * - 4 起始辅助点
 * - 5 起始入口点
 * @param pos 获取到的简易码垛的位置数据，see NRC_Position
 */
int NRC_Pallet_GetSimplePosParm(int id, int posType, NRC_Position& pos);
/**
 * @brief 设置简易码垛个数数据
 * @param id 码垛工艺的工艺号，参数范围：1 <= id <= 9
 * @param numX 简易码垛在其托盘X方向(对应用户坐标的X方向)上的工件数目，即行数
 * @param numY 简易码垛在其托盘Y方向(对应用户坐标的Y方向)上的工件数目，即列数
 * @param numZ 简易码垛在其托盘Z方向(对应用户坐标的Z方向)上的工件数目，即层数
 */
int NRC_Pallet_SetSimpleNumParm(int id, int numX, int numY, int numZ);
/**
 * @brief 获取简易码垛个数数据
 * @param id 码垛工艺的工艺号，参数范围：1 <= id <= 9
 * @param numX 获取到的简易码垛在其托盘X方向(对应用户坐标的X方向)上的工件数目，即行数
 * @param numY 获取到的简易码垛在其托盘Y方向(对应用户坐标的Y方向)上的工件数目，即列数
 * @param numZ 获取到的简易码垛在其托盘Z方向(对应用户坐标的Z方向)上的工件数目，即层数
 */
int NRC_Pallet_GetSimpleNumParm(int id, int& numX, int& numY, int& numZ);
/**
 * @brief 清除码垛当前状态
 * @param id 码垛工艺的工艺号，参数范围：1 <= id <= 9
 */
int NRC_Pallet_ClearCurrentStatus(int id);
/**
 * @brief 设置码垛已码个数
 * @param id 码垛工艺的工艺号，参数范围：1 <= id <= 9
 * @param layerNum 要修改的已码层数
 * @param layerPalletedWpNum 要修改的层已码工件数
 */
int NRC_Pallet_SetPalletedWpNum(int id, int layerNum, int layerPalletedWpNum);
/**
 * @brief 获取码垛已码个数
 * @param id 码垛工艺的工艺号，参数范围：1 <= id <= 9
 * @param curPalletedWpSum 当前已码工件数
 * @param curLayerNum 当前已码层数
 * @param curLayerPalletedWpNum 当前层的已码工件数
 * @param totalWpNum 垛堆工件总数
 * @param totalLayerNum 垛堆总层数
 * @param curLayerWpSum 当前层的工件总数
 * @attention 对于用作返回值的6个参数，当其值为-1时，表示个数未知
 */
int NRC_Pallet_GetPalletedWpNum(int id,
		int& curPalletedWpSum, int& curLayerNum, int& curLayerPalletedWpNum,
		int& totalWpNum, int& totalLayerNum, int& curLayerWpSum);

/**
 * @brief 设置消息发生时的回调函数
 * @note 当有消息发生时，将会调用此回调函数
 * @param fun 回调函数的函数指针
 */
int NRC_SetMsgHappenCallback(void (*fun)(void));
/**
 * @brief 弹出队列中最早的消息
 * @note 获取到队列中最早的消息，并从队列中移除该消息
 * @return 队列中最早的消息
 */
NRC_Messsage NRC_FirstMesssagePop();
/**
 * @brief 弹出队列中最后的消息
 * @note 获取到队列中最后的消息，并从队列中移除该消息
 * @return 队列中最后的消息
 */
NRC_Messsage NRC_LastMesssagePop();
/**
 * @brief 获取队列中第num个消息
 * @note 获取队列中第num个消息，不会移除该消息
 * @param num 要获取的消息在队列中的编号，最早的消息编号为1，取值范围：0 < num <= NRC_GetMesssageSize()
 * @param msg 获取的消息通过此参数返回
 */
int NRC_GetMesssage(int num, NRC_Messsage& msg);
/**
 * @brief 获取队列中消息总数
 * @return 队列中消息总数
 */
int NRC_GetMesssageSize();
/**
 * @brief 清空消息的队列
 * @note 清空消息的队列
 */
void NRC_ClearMesssage();
/**
 * @brief 清除伺服错误
 * @attention 并不是所有的伺服错误都可以直接清除，有些错误是需要先排除错误情况才能清除
 */
int NRC_ClearServoError();
/**
 * @brief 清除全部错误
 * @note 清空消息的队列，同时清除伺服错误
 * @attention 并不是所有的伺服错误都可以直接清除，有些错误是需要先排除错误情况才能清除
 */
int NRC_ClearAllError();

/**
 * @brief 条件判断类
 * @attention 第一个变量类型不能为常量，即 firstType 不能为 CONST_
 * @par 示例:
 * @code
 * 	//INT变量003小于DOUBLE变量005
 * 	NRC_ConditionJudge(NRC_ConditionJudge::INT_, 3, NRC_ConditionJudge::LESS, NRC_ConditionJudge::DOUBLE_, 5);
 * 	//IO输入端口2等于常量1
 * 	NRC_ConditionJudge(NRC_ConditionJudge::DIN_, 2, NRC_ConditionJudge::EQUAL_TO, NRC_ConditionJudge::CONST_, 1);
 * @endcode
 */
class NRC_ConditionJudge
{
public:
	/**
	 * @brief 变量类型
	 */
	enum VarType
	{
		CONST_,   ///<常量
		BOOL_,   ///<布尔型
		INT_,   ///<整型
		DOUBLE_,   ///<浮点型
		DIN_   ///<IO输入端口
	};
	/**
	 * @brief 判断类型
	 */
    enum LogicType
    {
        EQUAL_TO,   ///<等于
        LESS,           ///<小于
        GREATER,        ///<大于
        LESS_EQUAL,     ///<小于等于
        GREATER_EQUAL,  ///<大于等于
        NOT_EQUAL_TO    ///<不等于
    };
    NRC_ConditionJudge() :
    	firstType(INT_), firstNum(1), judgeType(EQUAL_TO), secondType(CONST_), secondNum(0)
    {
    }
    NRC_ConditionJudge(VarType firstType, int firstNum, LogicType judgeType, VarType secondType, double secondNum) :
    	firstType(firstType), firstNum(firstNum), judgeType(judgeType), secondType(secondType), secondNum(secondNum)
    {
    }
	VarType firstType;
	int firstNum;
	LogicType judgeType;
	VarType secondType;
	double secondNum;
};

class InstrData;
/**
 * @brief 指令数据的基类
 */
class NRC_InstrDataBase
{
public:
   enum Type
   {
		MOVJ = 1,
		MOVL,
		MOVC,
		IMOV,
		MOVJEXT,
		MOVLEXT,
		MOVCEXT,
		DOUT,
		TIMER,
		WAIT,
		ADD,
		UNTIL,
		ENDUNTIL,
		IF,
		ELSEIF,
		ELSE,
		ENDIF,
		WHILE,
		ENDWHILE,
		PALON,
		PALOFF,
		PALGRIPPER,
		PALCLEAR,
		PALENTER,
		PALSHIFT,
		PALREAL,
		ARCON,
		ARCOFF,
		USERDEFINE,
   };
   virtual int NRC_GetInstrFromData(InstrData&) = 0;
   explicit NRC_InstrDataBase(Type t):m_cmdType(t){};
   Type getType(){return m_cmdType;};
   struct NRC_UserParam
   {
      int int_param = 0;
      std::string string_param;
   } userParam;
protected:
	virtual ~NRC_InstrDataBase() {};
	Type m_cmdType;

};
/**
 * @brief 指令MOVJ的数据类
 */
class NRC_InstrDataMOVJ : public NRC_InstrDataBase
{
public:
	NRC_InstrDataMOVJ() : NRC_InstrDataBase(MOVJ),vel(10), acc(10), dec(10), pl(0),aheadTime(0), useType(0) {};
	NRC_InstrDataMOVJ(int vel, int acc, int dec, const NRC_Position& target, int pl, int tm=0, int useType=0) :
		NRC_InstrDataBase(MOVJ),vel(vel), acc(acc), dec(dec), target(target), pl(pl), aheadTime(tm), useType(useType) {};
	virtual int NRC_GetInstrFromData(InstrData&);
	int vel;
	int acc;
	int dec;
	NRC_Position target;
	int pl;
	int aheadTime;
	int useType;
};
/**
 * @brief 指令MOVL的数据类
 */
class NRC_InstrDataMOVL : public NRC_InstrDataBase
{
public:
	NRC_InstrDataMOVL() : NRC_InstrDataBase(MOVL),vel(10), acc(10), dec(10), pl(0), aheadTime(0), useType(0) {};
	NRC_InstrDataMOVL(int vel,  int acc, int dec, const NRC_Position& target, int pl, int tm=0, int useType=0) :
		NRC_InstrDataBase(MOVL),vel(vel), acc(acc), dec(dec), target(target), pl(pl), aheadTime(tm), useType(useType) {};
	virtual int NRC_GetInstrFromData(InstrData&);
	int vel;
	int acc;
	int dec;
	NRC_Position target;
	int pl;
	int aheadTime;
	int useType;
};
/**
 * @brief 指令MOVC的数据类
 */
class NRC_InstrDataMOVC : public NRC_InstrDataBase
{
public:
	NRC_InstrDataMOVC() : NRC_InstrDataBase(MOVC),vel(10), acc(10), dec(10), pl(0),aheadTime(0) {};
	NRC_InstrDataMOVC(int vel,  int acc, int dec, const NRC_Position& target, int pl,int tm = 0) :NRC_InstrDataBase(MOVC), vel(vel), acc(acc), dec(dec), target(target), pl(pl),aheadTime(tm) {};
	virtual int NRC_GetInstrFromData(InstrData&);
	int vel;
	int acc;
	int dec;
	NRC_Position target;
	int pl;
	int aheadTime;
};
/**
 * @brief 指令IMOV的数据类
 */
class NRC_InstrDataIMOV : public NRC_InstrDataBase
{
public:
	NRC_InstrDataIMOV() : NRC_InstrDataBase(IMOV),vel(10), acc(10), dec(10), pl(0),aheadTime(0) {};
	NRC_InstrDataIMOV(int vel,  int acc, int dec, const NRC_Position& deviation, int pl,int tm = 0) : NRC_InstrDataBase(IMOV),vel(vel), acc(acc), dec(dec), deviation(deviation), pl(pl),aheadTime(tm) {};
	virtual int NRC_GetInstrFromData(InstrData&);
	int vel;
	int acc;
	int dec;
	NRC_Position deviation;
	int pl;
	int aheadTime;
};
/**
 * @brief 指令MOVJEXT的数据类
 */
class NRC_InstrDataMOVJEXT : public NRC_InstrDataBase
{
public:
	NRC_InstrDataMOVJEXT() :NRC_InstrDataBase(MOVJEXT), vel(10), acc(10), dec(10), pl(0),aheadTime(0) {};
	NRC_InstrDataMOVJEXT(int vel, int acc, int dec, const NRC_Position& target,const NRC_SyncPosition& targetSync, int pl,int tm = 0) : NRC_InstrDataBase(MOVJEXT),vel(vel), acc(acc), dec(dec), target(target),targetSync(targetSync), pl(pl),aheadTime(tm) {};
	virtual int NRC_GetInstrFromData(InstrData&);
	int vel;
	int acc;
	int dec;
	NRC_Position target;
	NRC_SyncPosition targetSync;
	int pl;
	int aheadTime;
};
/**
 * @brief 指令MOVLEXT的数据类
 */
class NRC_InstrDataMOVLEXT : public NRC_InstrDataBase
{
public:
	NRC_InstrDataMOVLEXT() : NRC_InstrDataBase(MOVLEXT),vel(10), acc(10), dec(10), pl(0), synchronous(false), aheadTime(0) {};
	NRC_InstrDataMOVLEXT(int vel, int acc, int dec, const NRC_Position& target,const NRC_SyncPosition& targetSync, int pl,bool sync,int tm = 0) : NRC_InstrDataBase(MOVLEXT),vel(vel), acc(acc), dec(dec), target(target),targetSync(targetSync), pl(pl),synchronous(sync),aheadTime(tm) {};
	virtual int NRC_GetInstrFromData(InstrData&);
	int vel;
	int acc;
	int dec;
	NRC_Position target;
	NRC_SyncPosition targetSync;
	int pl;
	bool synchronous;
	int aheadTime;
};
/**
 * @brief 指令MOVCEXT的数据类
 */
class NRC_InstrDataMOVCEXT : public NRC_InstrDataBase
{
public:
	NRC_InstrDataMOVCEXT() : NRC_InstrDataBase(MOVCEXT),vel(10), acc(10), dec(10), pl(0), synchronous(false), aheadTime(0) {};
	NRC_InstrDataMOVCEXT(int vel, int acc, int dec, const NRC_Position& target,const NRC_SyncPosition& targetSync, int pl,bool sync,int tm = 0) : NRC_InstrDataBase(MOVCEXT),vel(vel), acc(acc), dec(dec), target(target),targetSync(targetSync), pl(pl),synchronous(sync),aheadTime(tm) {};
	virtual int NRC_GetInstrFromData(InstrData&);
	int vel;
	int acc;
	int dec;
	NRC_Position target;
	NRC_SyncPosition targetSync;
	int pl;
	bool synchronous;
	int aheadTime;
};

/**
 * @brief 指令DOUT的数据类
 */
class NRC_InstrDataDOUT : public NRC_InstrDataBase
{
public:
	NRC_InstrDataDOUT() : NRC_InstrDataBase(DOUT),port(1), value(0) {};
	NRC_InstrDataDOUT(int port, int value) : NRC_InstrDataBase(DOUT),port(port), value(value) {};
	virtual int NRC_GetInstrFromData(InstrData&);
	int port;
	int value;
};
/**
 * @brief 指令TIMER的数据类
 */
class NRC_InstrDataTIMER : public NRC_InstrDataBase
{
public:
	NRC_InstrDataTIMER() : NRC_InstrDataBase(TIMER),timeSec(0) {};
	NRC_InstrDataTIMER(double timeSec) : NRC_InstrDataBase(TIMER),timeSec(timeSec) {};
	virtual int NRC_GetInstrFromData(InstrData&);
	double timeSec;
};
/**
 * @brief 指令WAIT的数据类
 */
class NRC_InstrDataWAIT : public NRC_InstrDataBase
{
public:
	NRC_InstrDataWAIT() : NRC_InstrDataBase(WAIT),timeoutSec(0), now(false) {};
	NRC_InstrDataWAIT(NRC_ConditionJudge* judge, double timeoutSec, bool now=false);
	virtual int NRC_GetInstrFromData(InstrData& instr);
	NRC_ConditionJudge conditionJudge;
	double timeoutSec;
	bool now;
};
/**
 * @brief 指令ADD的数据类
 * @attention 第一个变量的类型不能是常量，即 firstType 不能为 VarType::CONST_
 */
class NRC_InstrDataADD : public NRC_InstrDataBase
{
public:
	/**
	 * @brief 变量类型
	 */
	enum VarType
	{
		CONST_,   ///<常量
		INT_,   ///<整型
		DOUBLE_,   ///<浮点型
	};
	NRC_InstrDataADD() : NRC_InstrDataBase(ADD),
			firstType(INT_), firstNum(1), secondType(CONST_), secondNum(0)
    {
    }
	NRC_InstrDataADD(VarType firstType, int firstNum, VarType secondType, double secondNum) : NRC_InstrDataBase(ADD),
			firstType(firstType), firstNum(firstNum), secondType(secondType), secondNum(secondNum)
    {
    }
	virtual int NRC_GetInstrFromData(InstrData&);
	VarType firstType;
	int firstNum;
	VarType secondType;
	double secondNum;
};

/**
 * @brief 指令UNTIL的数据类
 * @attention 需要和 NRC_InstrDataENDUNTIL 配合使用
 * @see NRC_RunqueueInsertUNTIL( int port, int value)
 */
class NRC_InstrDataUNTIL : public NRC_InstrDataBase
{
public:
	NRC_InstrDataUNTIL() :NRC_InstrDataBase(UNTIL){};
	NRC_InstrDataUNTIL(NRC_ConditionJudge* judge);
	virtual int NRC_GetInstrFromData(InstrData& instr);
	NRC_ConditionJudge conditionJudge;
};
/**
 * @brief 指令ENDUNTIL的数据类
* @attention 需要和 NRC_InstrDataUNTIL 配合使用
 */
class NRC_InstrDataENDUNTIL : public NRC_InstrDataBase
{
public:
	NRC_InstrDataENDUNTIL() : NRC_InstrDataBase(ENDUNTIL){};
	virtual int NRC_GetInstrFromData(InstrData&);
};
/**
 * @brief 指令IF的数据类
 * @attention 需要和 NRC_InstrDataENDIF 配合使用
 * @see NRC_RunqueueInsertIF( int port, int value)
 */
class NRC_InstrDataIF : public NRC_InstrDataBase
{
public:
	NRC_InstrDataIF() : NRC_InstrDataBase(IF){};
	NRC_InstrDataIF(NRC_ConditionJudge* judge);
	virtual int NRC_GetInstrFromData(InstrData& instr);
	NRC_ConditionJudge conditionJudge;
};
/**
 * @brief 指令ELSEIF的数据类
 * @attention 需要和 NRC_InstrDataIF 、NRC_InstrDataENDIF 配合使用
 * @see NRC_InstrDataIF
 */
class NRC_InstrDataELSEIF : public NRC_InstrDataBase
{
public:
	NRC_InstrDataELSEIF() : NRC_InstrDataBase(ELSEIF){};
	NRC_InstrDataELSEIF(NRC_ConditionJudge* judge);
	virtual int NRC_GetInstrFromData(InstrData& instr);
	NRC_ConditionJudge conditionJudge;
};
/**
 * @brief 指令ELSE的数据类
* @attention 需要和 NRC_InstrDataIF , NRC_InstrDataIF 配合使用
 */
class NRC_InstrDataELSE : public NRC_InstrDataBase
{
public:
	NRC_InstrDataELSE(): NRC_InstrDataBase(ELSE) {};
	virtual int NRC_GetInstrFromData(InstrData&);
};
/**
 * @brief 指令ENDIF的数据类
* @attention 需要和 NRC_InstrDataIF 配合使用
 */
class NRC_InstrDataENDIF : public NRC_InstrDataBase
{
public:
	NRC_InstrDataENDIF() : NRC_InstrDataBase(ENDIF) {};
	virtual int NRC_GetInstrFromData(InstrData&);
};
/**
 * @brief 指令WHILE的数据类
 * @attention 需要和 NRC_InstrDataENDWHILE 配合使用
 */
class NRC_InstrDataWHILE : public NRC_InstrDataBase
{
public:
	NRC_InstrDataWHILE() : NRC_InstrDataBase(WHILE){};
	NRC_InstrDataWHILE(NRC_ConditionJudge* judge);
	virtual int NRC_GetInstrFromData(InstrData& instr);
	NRC_ConditionJudge conditionJudge;
};
/**
 * @brief 指令ENDWHILE的数据类
* @attention 需要和 NRC_InstrDataWHILE 配合使用
 */
class NRC_InstrDataENDWHILE : public NRC_InstrDataBase
{
public:
	NRC_InstrDataENDWHILE() : NRC_InstrDataBase(ENDWHILE) {};
	virtual int NRC_GetInstrFromData(InstrData&);
};

/**
 * @brief 指令PALON的数据类
* @attention 需要和 NRC_InstrDataPALOFF 配合使用
 */
class NRC_InstrDataPALON : public NRC_InstrDataBase
{
public:
	NRC_InstrDataPALON() : NRC_InstrDataBase(PALON),id(1), type(0), var1(0), var2(0), var3(0) {};
	NRC_InstrDataPALON(int id, int type, int var1, int var2, int var3) : NRC_InstrDataBase(PALON),id(id), type(type), var1(var1), var2(var2), var3(var3) {};
	virtual int NRC_GetInstrFromData(InstrData&);
	int id;
	int type;
	int var1;
	int var2;
	int var3;
};
/**
 * @brief 指令PALOFF的数据类
* @attention 需要和 NRC_InstrDataPALON 配合使用
 */
class NRC_InstrDataPALOFF : public NRC_InstrDataBase
{
public:
	NRC_InstrDataPALOFF() : NRC_InstrDataBase(PALOFF),id(1), var(0) {};
	NRC_InstrDataPALOFF(int id, int var) : NRC_InstrDataBase(PALOFF),id(id), var(var) {};
	virtual int NRC_GetInstrFromData(InstrData&);
	int id;
	int var;
};
/**
 * @brief 指令PALGRIPPER的数据类
 */
class NRC_InstrDataPALGRIPPER : public NRC_InstrDataBase
{
public:
	NRC_InstrDataPALGRIPPER() : NRC_InstrDataBase(PALGRIPPER),id(1), tool(1){};
	NRC_InstrDataPALGRIPPER(int id, int tool) : NRC_InstrDataBase(PALGRIPPER),id(id), tool(tool) {};
	virtual int NRC_GetInstrFromData(InstrData&);
	int id;
	int tool;
};
/**
 * @brief 指令PALCLEAR的数据类
 */
class NRC_InstrDataPALCLEAR : public NRC_InstrDataBase
{
public:
	NRC_InstrDataPALCLEAR() : NRC_InstrDataBase(PALCLEAR),id(1) {};
	NRC_InstrDataPALCLEAR(int id) : NRC_InstrDataBase(PALCLEAR),id(id) {};
	virtual int NRC_GetInstrFromData(InstrData&);
	int id;
};
/**
 * @brief 指令PALENTER的数据类
 */
class NRC_InstrDataPALENTER : public NRC_InstrDataBase
{
public:
	NRC_InstrDataPALENTER() : NRC_InstrDataBase(PALENTER),id(1), moveType(1), vel(10), acc(10), dec(10), pl(0) {};
	NRC_InstrDataPALENTER(int id, int moveType, int vel, int acc, int dec, int pl) : NRC_InstrDataBase(PALENTER),id(id), moveType(moveType), vel(vel), acc(acc), dec(dec), pl(pl) {};
	virtual int NRC_GetInstrFromData(InstrData&);
	int id;
	int moveType;
	int vel;
	int acc;
	int dec;
	int pl;
};
/**
 * @brief 指令PALSHIFT的数据类
 */
class NRC_InstrDataPALSHIFT : public NRC_InstrDataBase
{
public:
	NRC_InstrDataPALSHIFT() : NRC_InstrDataBase(PALSHIFT),id(1), moveType(1), vel(10), acc(10), dec(10), pl(0) {};
	NRC_InstrDataPALSHIFT(int id, int moveType, int vel, int acc, int dec, int pl) : NRC_InstrDataBase(PALSHIFT),id(id), moveType(moveType), vel(vel), acc(acc), dec(dec), pl(pl) {};
	virtual int NRC_GetInstrFromData(InstrData&);
	int id;
	int moveType;
	int vel;
	int acc;
	int dec;
	int pl;
};
/**
 * @brief 指令PALREAL的数据类
 */
class NRC_InstrDataPALREAL : public NRC_InstrDataBase
{
public:
	NRC_InstrDataPALREAL() : NRC_InstrDataBase(PALREAL),id(1), moveType(1), vel(10), acc(10), dec(10), pl(0) {};
	NRC_InstrDataPALREAL(int id, int moveType, int vel, int acc, int dec, int pl) : NRC_InstrDataBase(PALREAL),id(id), moveType(moveType), vel(vel), acc(acc), dec(dec), pl(pl) {};
	virtual int NRC_GetInstrFromData(InstrData&);
	int id;
	int moveType;
	int vel;
	int acc;
	int dec;
	int pl;
};

/**
 * @brief 指令ARCON的数据类
* @attention 需要和 NRC_InstrDataARCOFF 配合使用
 */
class NRC_InstrDataARCON : public NRC_InstrDataBase
{
public:
	NRC_InstrDataARCON() : NRC_InstrDataBase(ARCON),id(1) {};
	NRC_InstrDataARCON(int id) : NRC_InstrDataBase(ARCON),id(id) {};
	virtual int NRC_GetInstrFromData(InstrData&);
	int id;
};
/**
 * @brief 指令ARCOFF的数据类
* @attention 需要和 NRC_InstrDataARCON 配合使用
 */
class NRC_InstrDataARCOFF : public NRC_InstrDataBase
{
public:
	NRC_InstrDataARCOFF() : NRC_InstrDataBase(ARCOFF),id(1) {};
	NRC_InstrDataARCOFF(int id) : NRC_InstrDataBase(ARCOFF),id(id) {};
	virtual int NRC_GetInstrFromData(InstrData&);
	int id;
};

/**
 * @brief 指令USERDEFINE的数据类
 */
class NRC_InstrDataUserDefine : public NRC_InstrDataBase
{
public:
	NRC_InstrDataUserDefine() : NRC_InstrDataBase(USERDEFINE),id(1) {};
	NRC_InstrDataUserDefine(int id) : NRC_InstrDataBase(USERDEFINE),id(id) {};
	virtual int NRC_GetInstrFromData(InstrData&);
	int id;
};

/**
 * @brief 将一组指令数据插入到运行队列中
 * @param instrVec 要插入的一组指令数据
 * @par 示例:
 * @code
 *			std::vector<NRC_InstrDataBase*> instrVec;
 *			//可以不创建队列，会自动创建
 *			instrVec.push_back(new NRC_InstrDataMOVJ(50, pos1, 5));
 *			instrVec.push_back(new NRC_InstrDataMOVL(30, pos2, 2));
 *			instrVec.push_back(new NRC_InstrDataMOVC(20, pos0, 3));
 *			instrVec.push_back(new NRC_InstrDataMOVC(20, pos1, 3));
 *			NRC_InsertNoFlieRunqueue(instrVec);
 *			//可以分成多组分次插入，后面插入的会接在之前插入的后面
 *			instrVec.clear();
 *			instrVec.push_back(new NRC_InstrDataIMOV(40, dev1, 0));
 *			instrVec.push_back(new NRC_InstrDataDOUT(5, 1));
 *			instrVec.push_back(new NRC_InstrDataTIMER(3.3));
 *			instrVec.push_back(new NRC_InstrDataWAIT(new NRC_ConditionJudge(NRC_ConditionJudge::INT_, 3, NRC_ConditionJudge::LESS, NRC_ConditionJudge::DOUBLE_, 5), 2.2));
 *			instrVec.push_back(new NRC_InstrDataWAIT(new NRC_ConditionJudge(NRC_ConditionJudge::DIN_, 2, NRC_ConditionJudge::EQUAL_TO, NRC_ConditionJudge::CONST_, 1), 0));
 *			instrVec.push_back(new NRC_InstrDataMOVJ(30, pos1, 1));
 *			NRC_InsertNoFlieRunqueue(instrVec);
 *			//开始执行队列
 *			NRC_StartRunNoFlieRunqueue();
 * @endcode
 */
int NRC_InsertNoFlieRunqueue(std::vector<NRC_InstrDataBase*>& instrVec);

/**
 * @brief 开启追加运行模式
 * @note 开启追加运行模式后，添加运行队列即可直接响应运行
 * @warning 成功调用该函数后，机器人自动上使能，请注意安全
 * @attention 只有伺服在就绪状态下才可开启追加运行模式，即 NRC_GetServoStatus() == 1 时
 * @attention 在追加运行模式中，出现伺服报错、运行报错、解析报错，将自动退出追加运行模式，并下使能
 * @attention 在追加运行模式中，切换示教、运行模式，将会自动退出追加运行模式，并下使能
 */
int NRC_OpenInstrAppendRunMode();
/**
 * @brief 关闭追加运行模式
 * @attention 成功调用该函数后，机器人会自动下使能
 * @attention 只有在无运行队列或全部运行队列已运行完毕的情况下才可关闭追加运行模式，即 NRC_GetProgramRunStatus() == 0 时
 */
int NRC_CloseInstrAppendRunMode();
/**
 * @brief 追加运行模式下,添加运行队列
 * @param instrVec 要插入的一组指令数据
 * @warning 添加运行队列后，机器人将会立即执行加入的队列，请注意安全
 * @attention 添加的运行队列只能是机器人移动指令
 * @par 示例:
 * @code
 * 		//开启追加运行模式，机器人自动上使能
 * 		NRC_OpenInstrAppendRunMode();
 *			std::vector<NRC_InstrDataBase*> instrVec;
 *			instrVec.push_back(new NRC_InstrDataMOVJ(50, pos1, 5));
 *			instrVec.push_back(new NRC_InstrDataMOVL(30, pos2, 2));
 *			//添加队列后，机器人直接运行
 *			NRC_AppendRunInstr(instrVec);
 *			......
 *			instrVec.clear();
 *			instrVec.push_back(new NRC_InstrDataMOVC(20, pos0, 3));
 *			instrVec.push_back(new NRC_InstrDataMOVC(20, pos1, 3));
 *			//机器人运行完之前添加的队列后，会接上本次添加的队列
 *			NRC_AppendRunInstr(instrVec);
 *			......
 *			NRC_PauseInstrAppendRun();//暂停运行
 *			......
 *			instrVec.clear();
 *			instrVec.push_back(new NRC_InstrDataMOVJ(50, pos1, 5));
 *			instrVec.push_back(new NRC_InstrDataMOVL(30, pos2, 2));
 *			//暂停时添加的队列，调用再启动运行后，也可正常运行
 *			NRC_AppendRunInstr(instrVec);
 *			......
 *			NRC_RestartInstrAppendRun();//再启动运行
 *			......
 *			//停止运行，机器人停止，并清空全部队列
 *			NRC_StopInstrAppendRun();
 *			//关闭追加运行模式，机器人自动下使能
 *			NRC_CloseInstrAppendRunMode();
 * @endcode
 */
int NRC_AppendRunInstr(std::vector<NRC_InstrDataBase*>& instrVec);
/**
 * @brief 暂停追加运行
 * @note 成功调用该函数后，机器人将暂停运行，该函数会在机器人停止后或调用500毫秒后退出,调用 NRC_RestartInstrAppendRun() 可继续运行
 * @attention 暂停时添加的运行队列，不会立刻运行，而是放入缓存队列中，调用再启动后，才会运行该队列
 */
int NRC_PauseInstrAppendRun();

/**
 * @brief 异步暂停追加运行
 * @note 成功调用该函数后，机器人将暂停运行，该函数会直接退出,调用 NRC_RestartInstrAppendRun() 可继续运行
 * @attention 暂停时添加的运行队列，不会立刻运行，而是放入缓存队列中，调用再启动后，才会运行该队列
 */
int NRC_PauseInstrAppendRunAsynchronous();

/**
 * @brief 再启动追加运行
 * @note 在机器人将暂停时，调用该函数可使机器人继续运行
 */
int NRC_RestartInstrAppendRun();
/**
 * @brief 停止追加运行
 * @note 成功调用该函数后，机器人将停止运行，并清空全部运行队列，退出追加模式
 */
int NRC_StopInstrAppendRun();
/**
 * @brief 获取当前是否是追加运行模式
 * @return 当前是否是追加运行模式
 * @retval  0  当前不是追加运行模式
 * @retval  1  当前处于追加运行模式
 */
int NRC_GetIsInstrAppendRunMode();
/**
 * @brief 获取追加运行当前剩余指令数目
 * @return 当前剩余指令数目
 * @attention 对于MOVC指令，两条为一对，在插入指令时，插入了两条，但在运行时，是记作一条的
 */
int NRC_GetRestAppendInstrNum();
/**
 * @brief 获取当前运行指令剩余点数
 * @return 当前运行指令剩余点数
 * @attention 当该指令未计算计算时，返回为-1
 */
int NRC_GetCurrentInstrRestPosNum();

/**
 * @brief 设置执行完一条指令时的回调函数
 * @note 当执行完一条指令时，将会调用此回调函数
 * @param fun 回调函数的函数指针
 * @attention 该函数与 NRC_SetCompleteOneInstrCallBack(void (*fun)(NRC_InstrDataBase::NRC_UserParam)) ，仅最后一次调用的函数生效
 * @attention 该回调函数不可含有耗时操作，否则将对程序的运行产生严重影响
 */
int NRC_SetCompleteOneInstrCallBack(void (*fun)());
/**
 * @brief 设置执行完一条指令时的回调函数
 * @note 当执行完一条指令时，将会调用此回调函数，该回调函数会将用户参数传入
 * @param fun 回调函数的函数指针
 * @attention 该函数与 NRC_SetCompleteOneInstrCallBack(void (*fun)()) ，仅最后一次调用的函数生效
 * @attention 该回调函数不可含有耗时操作，否则将对程序的运行产生严重影响
 */
int NRC_SetCompleteOneInstrCallBack(void (*fun)(NRC_InstrDataBase::NRC_UserParam));

/**
 * 获取各关节力矩,单位为千分比
 * @param torq以数组的形式返回各关节的力矩值
 */
int NRC_GetTorq(double* torq);

/**
 * 获取各外部轴关节力矩,单位为千分比
 * @param torq以数组的形式返回各外部轴关节的力矩值
 */
int NRC_GetSyncTorq(double* torq);

/**
 * 获取各关节额定力矩
 * @param ratedTorq以数组的形式返回各关节的额定力矩值
 */
int NRC_GetRatedTorque(double* ratedTorq);

/**
 * @brief 设置机器人外部轴数目
 * @param syncGroupNum 要设置的外部轴轴组数，参数范围：0 <= syncGroupNum <= 3
 * @param syncGroupType 要设置的外部轴各轴组类型，1:单轴变位机,2:双轴变位机,3:地轨
 * @attention 请在伺服停止或伺服就绪状态下设置该参数
 * @attention 修改后重启才能生效！！！
 */
int NRC_SetSyncJointNum(int syncGroupNum, std::vector<int> syncGroupType);


/**
 * @brief 设置机器人外部轴参数
 * @param syncGroupNum 要设置的轴组的序号，参数范围：1 <= axisNum <= 3
 * @param syncAxisNum 要设置的某轴组中轴的序号，参数范围：1 <= axisNum <= 2
 * @param config see NRC_RobotJointConfig
 * @attention 请在伺服停止或伺服就绪状态下设置该参数
 */
int NRC_SetSyncJointPara(int syncGroupNum, int syncAxisNum, NRC_RobotJointConfig config);

/**
 * @brief 获取机器人外部轴参数
 * @param syncGroupNum 要设置的轴组的序号，参数范围：1 <= axisNum <= 3
 * @param syncAxisNum 要设置的某轴组中轴的序号，参数范围：1 <= axisNum <= 2
 * @param config see NRC_RobotJointConfig
 */
int NRC_GetSyncJointPara(int syncGroupNum, int syncAxisNum, NRC_RobotJointConfig& config);

/**
 * @brief 设置机器人外部轴点动关节速度
 * @param groupNum 要设置的轴组序号，参数范围：1 <= groupNum <= 外部轴轴组总数
 * @param axisNum 要设置的轴在轴组中的序号，参数范围：1 <= axisNum <= 轴组组总数
 * @param maxSpeed 点动时，该轴可以达到的最大速度，单位：度/秒
 * @param acc 点动时，该轴的加速度，单位：度/平方秒
 * @attention 请在伺服停止或伺服就绪状态下设置该参数
 */
int NRC_SetSyncJogJointSpeedConfig(int groupNum, int axisNum, double maxSpeed, double acc);

/**
 * @brief 获取机器人外部轴点动关节速度
 * @param groupNum 要获取的轴组序号，参数范围：1 <= groupNum <= 外部轴轴组总数
 * @param axisNum 要获取的轴在轴组中的序号，参数范围：1 <= axisNum <= 轴组组总数
 * @param maxSpeed 点动时，该轴可以达到的最大速度，单位：度/秒
 * @param acc 点动时，该轴的加速度，单位：度/平方秒
 */
int NRC_GetSyncJogJointSpeedConfig(int groupNum, int axisNum, double& maxSpeed, double& acc);

/**
 * @brief 将外部轴当前位置设置为零点或清除多圈值
 * @param axisNum 操作的轴的序号，当axisNum为0时，表示全部外部轴，参数范围：0 <= axisNum <= 外部轴轴总数
 * @param mod为设置零点或清除多圈值，0为设置零点，1为清除多圈值
 * @attention 请在伺服停止或伺服就绪状态下设置该参数
 * @attention 执行该函数大约需要两三秒时间
 * @warning 对于大多数类型的伺服，执行该函数时，会使伺服使能上电，请注意安全
 */
int NRC_SetCurrentSyncPosToZeroPos(int axisNum,bool mod);

/**
 * @brief 机器人外部轴点到点运动
 * @note 机器人外部轴以 vel 的速度从当前位置以点到点方式运行到 synctarget 位置
 * @pre 调用该函数前，请将伺服上电使能，可调用 NRC_ServoEnable() 函数将伺服上电
 * @warning 成功调用该函数后，机器人外部轴将开始运动，请注意安全
 * @param vel 机器人外部轴的运行速度，为机器人外部轴最大速度的百分比，参数范围：0 < vel <= 100
 * @param target 机器人本体运动目标位置，详见 NRC_Position
 * @param targetSync 机器人外部轴运动目标位置，详见 NRC_SyncPosition
 * @param acc 机器人外部轴运行加速度，为机器人外部轴各关节最大加速度的百分比，参数范围：0 < vel <= 100
 * @param dec 机器人外部轴运行减速度，为机器人外部轴各关节最大减速度的百分比，参数范围：0 < vel <= 100
 */
int NRC_RobotMoveJointSync(int vel,NRC_Position target, const NRC_SyncPosition& targetSync,  int acc, int dec);

/**
 * @brief 运行队列插入MOVJEXT指令
 * @pre 调用该函数前，请先调用 NRC_CreateNoFlieRunqueue() 创建一个无文件运行队列
 * @param vel 机器人的运行速度，为机器人最大速度的百分比，参数范围：0 < vel <= 100
 * @param acc 机器人运行加速度，为机器人各关节最大加速度的百分比，参数范围：0 < vel <= 100
 * @param dec 机器人运行减速度，为机器人各关节最大减速度的百分比，参数范围：0 < vel <= 100
 * @param target 机器人运动目标位置，详见 NRC_Position
 * @param targetSync 外部轴运动目标位置，详见 NRC_SyncPosition
 * @param pl 平滑度，将和后面一条移动指令进行平滑过渡，数值越大，越平滑，轨迹偏差也越大，参数范围：0 <= pl <= 5
 */
int NRC_RunqueueInsertMOVJEXT(int vel, int acc, int dec, const NRC_Position& target,const NRC_SyncPosition& targetSync, int pl = 0,int tm = 0);

/**
 * @brief 作业文件插入MOVJEXT指令
 * @pre 调用该函数前，请先调用 NRC_CreateJobfile(std::string jobname) 或 NRC_OpenJobfile(std::string jobname) 创建或打开一个作业文件
 * @param line 将指令插入到第line行，参数范围：0 < line <= (NRC_GetJobfileLineSum()+1)
 * @param vel 机器人的运行速度，为机器人最大速度的百分比，参数范围：0 < vel <= 100
 * @param acc 机器人运行加速度，为机器人各关节最大加速度的百分比，参数范围：0 < vel <= 100
 * @param dec 机器人运行减速度，为机器人各关节最大减速度的百分比，参数范围：0 < vel <= 100
 * @param target 机器人运动目标位置，详见 NRC_Position
 * @param targetSync 外部轴运动目标位置，详见 NRC_SyncPosition
 * @param pl 平滑度，将和后面一条移动指令进行平滑过渡，数值越大，越平滑，轨迹偏差也越大，参数范围：0 <= pl <= 5
 */
int NRC_JobfileInsertMOVJEXT(int line, int vel, int acc, int dec, const NRC_Position& target,const NRC_SyncPosition& targetSync, int pl = 0,int tm = 0);

/**
 * @brief 机器人外部轴直线运动
 * @note 机器人本体以 vel 的速度从当前位置以直线方式运行到 target 位置
 * @note 机器人外部轴以 vel 的速度从当前位置以点到点方式运行到 synctarget 位置
 * @pre 调用该函数前，请将伺服上电使能，可调用 NRC_ServoEnable() 函数将伺服上电
 * @warning 成功调用该函数后，机器人外部轴将开始运动，请注意安全
 * @param vel 机器人外部轴的运行速度，为机器人外部轴最大速度的百分比，参数范围：0 < vel <= 100
 * @param target 机器人本体运动目标位置，详见 NRC_Position
 * @param targetSync 机器人外部轴运动目标位置，详见 NRC_SyncPosition
 * @param acc 运行加速度，为机器人和外部轴各关节最大加速度的百分比，参数范围：0 < vel <= 100
 * @param dec 运行减速度，为机器人和外部轴各关节最大减速度的百分比，参数范围：0 < vel <= 100
 */
int NRC_RobotMoveLineSync(int vel,NRC_Position target, const NRC_SyncPosition& targetSync,  int acc, int dec);

/**
 * @brief 运行队列插入MOVLEXT指令
 * @pre 调用该函数前，请先调用 NRC_CreateNoFlieRunqueue() 创建一个无文件运行队列
 * @param vel 机器人的运行速度，为机器人最大速度的百分比，参数范围：0 < vel <= 100
 * @param acc 机器人运行加速度，为机器人各关节最大加速度的百分比，参数范围：0 < vel <= 100
 * @param dec 机器人运行减速度，为机器人各关节最大减速度的百分比，参数范围：0 < vel <= 100
 * @param target 机器人运动目标位置，详见 NRC_Position
 * @param targetSync 外部轴运动目标位置，详见 NRC_SyncPosition
 * @param pl 平滑度，将和后面一条移动指令进行平滑过渡，数值越大，越平滑，轨迹偏差也越大，参数范围：0 <= pl <= 5
 */
int NRC_RunqueueInsertMOVLEXT(int vel, int acc, int dec, const NRC_Position& target,const NRC_SyncPosition& targetSync, int pl = 0,int tm = 0);

/**
 * @brief 作业文件插入MOVLEXT指令
 * @pre 调用该函数前，请先调用 NRC_CreateJobfile(std::string jobname) 或 NRC_OpenJobfile(std::string jobname) 创建或打开一个作业文件
 * @param line 将指令插入到第line行，参数范围：0 < line <= (NRC_GetJobfileLineSum()+1)
 * @param vel 机器人的运行速度，为机器人最大速度的百分比，参数范围：0 < vel <= 100
 * @param acc 机器人运行加速度，为机器人各关节最大加速度的百分比，参数范围：0 < vel <= 100
 * @param dec 机器人运行减速度，为机器人各关节最大减速度的百分比，参数范围：0 < vel <= 100
 * @param target 机器人运动目标位置，详见 NRC_Position
 * @param targetSync 外部轴运动目标位置，详见 NRC_SyncPosition
 * @param pl 平滑度，将和后面一条移动指令进行平滑过渡，数值越大，越平滑，轨迹偏差也越大，参数范围：0 <= pl <= 5
 */
int NRC_JobfileInsertMOVLEXT(int line, int vel, int acc, int dec, const NRC_Position& target,const NRC_SyncPosition& targetSync, int pl = 0,int tm = 0);

/**
 * @brief 运行队列插入MOVCEXT指令
 * @pre 调用该函数前，请先调用 NRC_CreateNoFlieRunqueue() 创建一个无文件运行队列
 * @param vel 机器人的运行速度，为机器人最大速度的百分比，参数范围：0 < vel <= 100
 * @param acc 机器人运行加速度，为机器人各关节最大加速度的百分比，参数范围：0 < vel <= 100
 * @param dec 机器人运行减速度，为机器人各关节最大减速度的百分比，参数范围：0 < vel <= 100
 * @param target 机器人运动目标位置，详见 NRC_Position
 * @param targetSync 外部轴运动目标位置，详见 NRC_SyncPosition
 * @param pl 平滑度，将和后面一条移动指令进行平滑过渡，数值越大，越平滑，轨迹偏差也越大，参数范围：0 <= pl <= 5
 */
int NRC_RunqueueInsertMOVCEXT(int vel, int acc, int dec, const NRC_Position& target,const NRC_SyncPosition& targetSync, int pl = 0,int tm = 0);

/**
 * @brief 作业文件插入MOVCEXT指令
 * @pre 调用该函数前，请先调用 NRC_CreateJobfile(std::string jobname) 或 NRC_OpenJobfile(std::string jobname) 创建或打开一个作业文件
 * @param line 将指令插入到第line行，参数范围：0 < line <= (NRC_GetJobfileLineSum()+1)
 * @param vel 机器人的运行速度，为机器人最大速度的百分比，参数范围：0 < vel <= 100
 * @param acc 机器人运行加速度，为机器人各关节最大加速度的百分比，参数范围：0 < vel <= 100
 * @param dec 机器人运行减速度，为机器人各关节最大减速度的百分比，参数范围：0 < vel <= 100
 * @param target 机器人运动目标位置，详见 NRC_Position
 * @param targetSync 外部轴运动目标位置，详见 NRC_SyncPosition
 * @param pl 平滑度，将和后面一条移动指令进行平滑过渡，数值越大，越平滑，轨迹偏差也越大，参数范围：0 <= pl <= 5
 */
int NRC_JobfileInsertMOVCEXT(int line, int vel, int acc, int dec, const NRC_Position& target,const NRC_SyncPosition& targetSync, int pl = 0,int tm = 0);

/**
 * @brief 获取外部轴当前位置
 * @note 该函数可以获取在 coord 坐标系下外部轴位置，位置数据由参数引用 position 返回
 * @see NRC_COORD
 * @see NRC_SyncPosition
 */
int NRC_GetCurrentSyncPos(NRC_COORD coord, NRC_SyncPosition& position);

/**
 * @brief 判断点位是否可以到达
 * @note 该函数可以判断本体点位target和外部轴点位syncTarget是否超限，结果由result返回，result值为true表示可以到达，值为false表示不可到达
 * @see NRC_Position
 * @see NRC_SyncPosition
 */
int NRC_PosReachable(NRC_Position target,NRC_SyncPosition syncTarget,bool &result);


/**
 * @brief 设置动力学辨识参数
 * @note 该函数用于设置动力学辨识所需的两个参数并返回当前轨迹范围下机器人末端在Z坐标轴上的最大值和最小值:size,控制辨识轨迹的范围;vel,控制辨识轨迹的速度,zMax末端运行到的Z的最大值,zMin末端运行到的Z的最小值
 * @attention 动力学辨识过程中机器人会大幅度运动，因此要确保机器人的运动范围内空旷，无障碍物。执行动力学辨识功能前请认真阅读以下注意事项：
 * 1.目前动力学辨识功能只适用于六轴机器人空载状态下对本体进行辨识。
 * 2.该辨识方法所得动力学参数与手填动力学参数无关。
 * 3.执行辨识程序前确保机器人的运动范围内空旷，无障碍物。
 * 4.辨识轨迹的范围由参数size控制，100时为最大范围；辨识轨迹的速度由参数vel控制，100时为最大速度，此时辨识轨迹运行时间为10秒。
 * 5.辨识轨迹的参数的设置规则：首先设定一个较小的vel值(建议20)，并设置一个较小的size值(建议20)，并执行安全检测程序(NRC_RunSafeCheckProgram)，
 * 在安全的基础上逐步增大size的值，直至达到最大的安全运行范围(此时size值可能未达到100，取决于机器人的运行环境)。
 * 在得到环境所允许的最大size值后，把vel值设置为100，执行辨识程序(NRC_RunIdentifyProgram)。
 * 6.执行辨识时vel值必须是100，而size值没有固定值(理论上size越接近100辨识精度越高)。
 */
int NRC_SetIdentityParam(int size,int vel,double& zMax,double& zMin);

/**
 * @brief 运行范围安全检测程序
 * @note 该函数功能是运行一次动力学辨识的轨迹，以便确认周围环境是否安全，即确保机器人进行辨识时不会碰到周围的人或物
 */
int NRC_RunSafeCheckProgram();

/**
 * @brief 执行动力学辨识程序
 * @note 该函数的功能是进行动力学辨识，沿预定轨迹运行十次，每次运行完成后会对获取到的数据进行计算并返回理论力矩与实际力矩的误差值
 * @param error 返回理论力矩与实际力矩的误差值，数组长度为60，每6个数据为一次运行轨迹所得到的误差值，共有十次轨迹的误差值
 */
int NRC_RunIdentifyProgram();

/**
 * @brief 获取十次辨识力矩误差值
 * @note 该函数的功能是获取十次辨识计算的理论力矩与实际力矩的误差值
 * @param error 返回理论力矩与实际力矩的误差值，数组长度为60，每6个数据为一次运行轨迹所得到的误差值，共有十次轨迹的误差值
 */
int NRC_getIdentifyError(double* error);

/**
 * @brief 停止动力学辨识程序
 * @note 该函数的功能是停止动力学辨识
 */
int NRC_StopIdentityProgram();

/**
 * @brief 设置碰撞检测力矩偏差阈值
 * @note 该函数的功能是设置各关节判定发生碰撞时理论力矩与实际力矩的差值的绝对值，该值越大则判断碰撞发生的灵敏度越低
 * @param param是六位数组，从首元素到尾元素依次表示一到六关节的阈值
 */
int NRC_SetCollisionParam(double* param);

/**
 * @brief 设置碰撞检测功能开关
 * @note 该函数的功能是打开或关闭碰撞检测功能
 * @param param true为打开碰撞检测功能，false为关闭碰撞检测功能
 */
int NRC_SetCollisionSwitch(bool param);

/**
 * @brief 获取碰撞检测功能开关
 * @note 该函数的功能是查看碰撞检测功能是否打开
 * @param param true为碰撞检测功能打开，false为碰撞检测功能关闭
 */
int NRC_GetCollisionSwitch(bool& param);

/**
 * @brief 计算机器人形态
 * @note 该函数的功能是计算机器人各关节在acsPos下的形态,仅对R_GENERAL_6S类型机器人有效,其余机器人类型下conf值为0
 * @param acsPos 六维数组，用于传入机器人各关节位置
 * @param conf 传出机器人形态值的计算结果,0表示机器人类型不是R_GENERAL_6S,1-8对应机器人的8个形态值
 */
int NRC_CalcConfiguration(double* acsPos,int& conf);

/**
 * @brief 自定义socket通讯协议
 * @note 该函数的功能是自定义socket通讯协议
 * @param commandNum 通讯编号,范围 0x9200 - 0x920e
 * @param (*fun)(string) 函数句柄，即commandNum指令要调用的函数
 */
int NRC_SetSocketCustomProtocalCB(int commandNum,void (*fun)(std::string));

/**
 * @brief 发送socket通信
 * @note 该函数的功能是发送socket通信
 * @param commandNum 通讯编号,范围 0x9200 - 0x920e
 * @param str 发送的内容
 */
int NRC_SendSocketCustomProtocal(int commandNum,std::string str);
/**
 * @brief 获取是否连接了示教盒
 */
bool NRC_GetTeachBoxConnectStatus();

/**
 * @brief 作业文件自定义指令
 * @note 该函数的功能是自定义一条指令并插入作业文件中
 * @param (*fun)(int) 函数句柄，即insID指令要调用的函数
 */
int NRC_SetJobFileCustomInstructionCB(void (*fun)(int));

/**
 * @brief 作业文件解析为追加模式指令
 * @note 该函数的功能是把作业文件中的所有指令解析成可以作为追加模式指令的队列
 * @param fileName 要解析的作业文件名
 * @param instrVec 解析完成后得到的追加模式指令队列
 */
int NRC_ParseJobfileToAppendRunInstruction(std::string fileName,std::vector<NRC_InstrDataBase*>& instrVec);

/**
 * @brief 用户主动触发报错
 * @note 该函数的功能是触发报错，效果同伺服报错
 * @param kind <消息级别：0:一般消息，1:警告消息，2:错误消息，3:重要消息
 * @param text 报错内容
 */
int NRC_TriggerErrorReport(int kind,std::string text);

/**
 * @brief 获取当前打开的作业文件的名称
 * @note 该函数的功能是获取当前打开的作业文件的名称
 * @param name 返回当前打开的作业文件的名称
 */
int NRC_GetOpenJobFileName(std::string& name);

/**
 * @brief 向示教器发送光标跳行命令
 * @note 调用该接口,将向示教器发送光标跳行命令,示教器响应后,会将光标跳转到指定作业文件的指定行
 * @param name 返回当前打开的作业文件的名称
 */
int NRC_SendCursorJumpCmdToTeachbox(const std::string& name, int line);

/**
 * @brief 供自定义指令的回调函数调用的单个外部轴恒速运动接口
 * @note 调用该接口,在运行模式下，外部轴syncAxis将会以恒定的vel运动,同时调用多个该函数只有第一个该函数有效
 * @param syncAxis 要运动的外部轴号,从1开始,比如需要外部轴1运动，则syncAxis传入1
 * @param vel 运动的速度，单位度每秒
 */
int NRC_SingleSyncAxisMoveJConstVel_For_CustomInstructionCB(int syncAxis,double vel);

/**
 * @brief 供自定义指令的回调函数调用的停止单个外部轴恒速运动接口
 * @note 调用该接口,将停止外部轴恒速运动,该接口必须在有外部轴恒速运动状态下调用，否则返回-1
 */
int NRC_StopSingleSyncAxisMoveJConstVel_For_CustomInstructionCB();

/**
 * @brief 获取单个外部轴恒速运动标志位接口
 * @param moving true表示NRC_SingleSyncAxisMoveJConstVel_For_CustomInstructionCB正在生效,false表示NRC_SingleSyncAxisMoveJConstVel_For_CustomInstructionCB未生效
 */
int NRC_GetSingleSyncAxisMoveJConstVelMoving(bool& moving);

/**
 * @brief 重置外部轴多圈转动量的接口
 * @note 调用该接口,把外部轴当前位置重置到-360°~360°内,效果同示教器界面中的复位外部轴多圈转动量指令,该接口仅能重置单个外部轴
 * @param syncAxis 要重置的外部轴号,从1开始,比如需要重置外部轴1，则syncAxis传入1
 */
int NRC_ResetSyncAxisMultipleTurns(int syncAxis);

/**
 * @brief 设置清错按键回调函数的接口
 * @note 该函数的功能是设置清错按键回调函数,不影响控制器本身的清错功能
 */
int NRC_SetFaultResetCB(void (*fun)());

/**
 * @brief 设置切到运行模式自动上电
 * @param flag 可选参数值：
 *  -    0  切到运行模式不会自动上电
 *  -    1  切到运行模式自动上电
 */
int NRC_SetRunModeAutoManBegFlag(bool flag);

/**
 * @brief 设置伺服运行模式
 * @param moderValue 伺服运行模式：3:速度模式PV,８:周期位置模式CSP, 9:周期同步速度模式(CSV)
 */
int NRC_SetServoModerOfOperation(unsigned char moderValue);

/**
 * @brief 设置PV模式下运行速度
 * @param axisNum 轴号,1为起始轴数
 * @param vel 设置速度值　单位r/min
 * 仅在PV模式下有用
 */
int NRC_PV_SetTargetVelocity(unsigned int axisNum, double vel);

/**
 * @brief 设置PV模式下运行加速度，减速度
 * @param axisNum 轴号，1为起始轴数
 * @param acc 加速度值　单位r/min
 * @param dec 加速度值　单位r/min
 * 仅在PV模式下有用
 */
int NRC_SetTargetAccAndDec(unsigned int axisNum, double acc, double dec);

/**
 * @brief 查询IO接口数量的接口
 * @note 调用该接口,可以返回特定IO板对应的IO端口数量
 * @param ioNum IO板编号
 * @param ioType IO端口类型 DIN = 0, DOUT = 1, AIN = 2, AOUT = 3
 */
int NRC_GetIOConfig(int ioNum, int ioType);

/**
 * @brief 查询IO板数量的接口
 * @note 调用该接口,可以返回IO板数量
 */
int NRC_GetIOBoardSum();

/**
 * @brief 设置机器人目标位置
 * @param targetPosition 传入各关节的角度位置的数组
 */
int NRC_SetTargetPosition(double* targetPosition);

/**
 * @brief 设置机器人目标力矩
 * @param targetTorq 传入各关节的目标力矩的数组
 */
int NRC_SetTargetTorque(signed short* targetTorq);

/**
 * @brief 设置一个自定义的无参函数，没1ms回调一次
 *   @param void (*fun)() 传入一个函数指针
 */
int NRC_robotRunCycle_Callback(void (*fun)());

/**
 * @brief 获取伺服运行模式
 * @param servoMode 以数组形式返回每个伺服运行模式：
 * 0-模式不变；
*1-规划位置模式（PP）；
*2-速度模式（VL）；
*3-规划速度模式（PV）；
*4-规划转矩模式（PT）；
*5-保留；
*6-寻原点模式（HM）；
*7-插补位置模式（IP），暂不支持；
*8-周期同步位置模式（CSP）；
*9-周期同步速度模式（CSV）；
*10-周期同步转矩模式（CST）。
 */

int  NRC_GetServoMode(int *servoMode);

/**
 * @brief 设置目标速度值
 * @param axisNum 轴号,1为起始轴数
 * @param vel 传入一个double数组设置速度值(注:数组大小需要和当前机器人轴数一致)
 * @如需使用该接口，eni文件必须要配PDO(0x60FF)才可以使用
 */
int NRC_SetTargetVelocity( int *axisVel);

/**
 * @brief 设置点动插补点位个数
 * @param num 点位个数
 */
int NRC_SetJogMoveCalculateNum(int num);
#endif /* API_NRCAPI_H_ */

#ifndef NEXTP_H
#define NEXTP_H

#include <QObject>
#include <QPainter>
#include <QWidget>
#include <QPointer>
#include <QFont>



class Nextp : public QObject
{
    Q_OBJECT
public:
    enum IOTYPE   //IO类型
    {
        NoIO = 0,
        EtherCATIO = 1,//EtherCAT IO
        HUATAIIO = 2             //华太IO
    };

    enum widgetType { UserManagerWind,SettingWind,StateWind,ProjectWind,JobWind,WarnWnd,WaitingWind,AdminloginWind,TechnologyWind,VariableWind,LogWind,PunchWind};

    struct IOCONFIG
    {
        IOTYPE _iotype;     //IO类型
        int _dinPortNum;  //数字输入端口个数
        int _doutPortNum;//数字输出端口个数
        int _ainPortNum;  //模拟输入端口个数
        int _aoutPortNum;//模拟输出端口个数
        IOCONFIG()
        {
            _iotype = NoIO;
            _dinPortNum = 0;
            _doutPortNum = 0;
            _ainPortNum = 0;
            _aoutPortNum = 0;
        }
    };

    //机器人类型
    enum Nextp_RobotType{
        NOTYPE = 0,
        SIX_AXLE_GENERAL     = 1,   //六轴通用机器人
        SIX_AXLE_ONE_GENERAL = 2,   //六S轴机器人
        SIX_AXLE_SPRAY       = 3,   //六轴喷涂机器人
        SIX_AXLE_ABNORMITY   = 4,   //六轴异型一
        FIVE_AXLE_GENERAL    = 5,   //五轴机器人
        FOUR_AXLE_SCARA      = 6,   //四轴SCARA机器人
        FOUR_AXLE_SCARA_ABNORMITY  = 7,   //四轴SCARA异型一机器人
        FOUR_AXLE_STACK      = 8,   //四轴连杆码垛机器人
        FOUR_AXLE_PALLET_1   = 9,   //四轴码垛丝杆机器人
        FOUR_AXLE_GENERAL    = 10,   //四轴机器人
        FOUR_AXLE_ANGLE      = 11,   //四轴直角机器人
        FOUR_AXLE_POLAR_ABNORMITY = 12,   //四轴极坐标异形机器人
        THREE_AXLE_SCARA     = 13,   //三轴SCARA机器人
        THREE_AXLE_ANGLE     = 14,  //三轴直角机器人
        THREE_AXLE_ABNORMITY = 15,  //三轴异形一机器人
        TWO_AXLE_SCARA       = 16,   //二轴SCARA机器人
        SEVEN_AXLE_GENERAL   = 17,  //七轴通用机器人
        ONE_AXLE_GENERAL     = 18,   //一轴机器人
    };

    enum CommandList
    {
        SetFirstUserParaCommand = 0x9200,
        GetFirstUserCommand = 0x9201,
        ReceivedFirstUserCommand = 0x9202,

        SetSecondUserParaCommand = 0x9203,
        GetSecondUserCommand = 0x9204,
        ReceivedSecondUserCommand = 0x9205,

        SetThirdUserParaCommand = 0x9206,
        GetThirdUserCommand = 0x9207,
        ReceivedThirdUserCommand = 0x9208,

        SetFourthUserParaCommand = 0x9209,
        GetFourthUserCommand = 0x920a,
        ReceivedFourthUserCommand = 0x920b,

        SetFifthUserParaCommand = 0x920c,
        GetFifthUserCommand = 0x920d,
        ReceivedFifthUserCommand = 0x920e,
    };

    static QPointer<Nextp> getInstance();
    /*
     *获取机器人类型
     */
    Nextp_RobotType getRobotType();
    /**
     * @brief getUserCoordNum 获取用户坐标号
     * @return 用户坐标号
     */
    int getUserCoordNum();
    /*
     *同步作业文件
     */
    void syncJobFile();
    /*
     * 打开作业文件
     */
    void openJobFile(int robot,QString jobname,int line);

    /*
     * 界面小白条信息弹框
     * message 需要显示的信息
     * duration 信息显示时长 单位 ms
     */
    void showSnackbarMessage(const QString &message, const int &duration);
    /*
     * 系统字体名称
     */
    QString getSystemFont();
    //设置
    void setWidgetParentLocation(QPointer <QWidget> widget);
    //向控制器发送消息
    void sendMessage(const quint16 &command,const QByteArray &data);
    void widgetShowFinish();
    /*
     * 隐藏工艺界面除用户以外的工艺入口
     */
    void hideTechnologyToolbuttons();
    /*
     * 修改用户工艺按钮名称
     *
     * btnName 工艺名称
     */
    void renameUserButtonName(QString btnName);
    /*
     * 注册开始按钮回调函数
     *参数  当前打开的作业文件的名称
     */
    void setHandle(void (*Callback)( QString));
    /*
     * 注册停止按钮回调函数
     * 参数 机器人编号 1-4
     */
    void setStopButtonHandle(void (*Callback)( int));
    /*
     * 注册T30示教器左下角按钮回调函数
     */
    void setReserveButtonHandle(void (*Callback)(void));
    /*
     * 获取操作模式
     * 返回值 0:示教 1:远程 2:运行
     */
    int getOperationMode();
    /*
     * 获取当前机器人程序运行状态
     * 返回值 程序运行状态 0:停止 1：暂停 2:运行
     */
    int  getCurrentRobotProState();
    /*
     * 获取IO板信息
     * IoNum :IO板的数量
     *ioConfig 存储IO板详细参数 ioConfig.size() 与IoNum 相同 ioConfig.at(0):表示IO板1参数信息
     */
    void getIoConfig(int &IoNum,QVector<IOCONFIG> &ioConfig);
    /*
     * 获取Io板数字输入状态
     * 需要自己设置定时器定时查询
     * 查询结果在传递到信号函数 signal_receiveIoDigitDinState
     */
    void getIoDigitDinState();
    /*
     * 获取Io板数字输出状态
     * 需要自己设置定时器定时查询
     * 查询结果在传递到信号函数 signal_receiveIoDigitOutputState
     */
    void getIoDigitOutputState();
    /*
     * 返回值 true 设置成功 false:设置失败
     *设置IO 数字输出端口输出值
     * ionum IO板序号 1-4
     * port IO板端口号
     * value 输出值 0或1
     */
    bool setIoDoutValue(int ionum,int port,int value);

    /**
     * @brief getRobotCoord  获取当前机器人的当前坐标
     * @return 坐标系 0：关节 1：直角  2：工具  3：用户
     */

    int getRobotCoord();

    /*打开或关闭 获取当前坐标系下当前位置
     *open:true 打开 open:false 关闭
     * coord 坐标系 0：关节 1：直角  2：工具  3：用户     -1:表示当前坐标
     */
    void openOrCloseGetCurrentPos(bool open,int coord=-1 );
    /*
     *自动生成文件之前需要调用该函数 清理缓存指令
     */
    void startInsertCommand();
    /*
     * 插入指令
     * 返回值 插入成功或失败
     * errorTxt 插入失败原因
     * cmdtype 指令类型  0：MOVJ 1:MOVL
     * usertype 自定义指令名称
     * 1:取待机点
     * 2:取料中
     * 3:取料点
     * 4:放待机点
     * 5:放料中
     * 6:放料点
     * 7:取料完成点
     * 8:放料完成点
     *pos:当前点位值 7个数值
     * coord 坐标系 0：关节 1：直角  2：工具  3：用户
     * vel 速度 最大速度百分比
     * pl  平滑
     *robot  机器人编号 1-4
     * config 当前机器人姿态
     */
    bool insertCmd(QString &errorTxt,int cmdtype,int usertype,const QVector< double > pos, const int coord, int vel,int pl,const int robot, const int config);
    /*
     * 插入延时指令 TIMER
     * 返回值 插入成功或失败
     * errorTxt 插入失败原因
     * time 延时时长 范围0.01-9999 秒
     */
    bool insertTimerCmd(QString &errorTxt, double time);
    /*
     * 创建作业文件
     * jobname :作业文件名
     * 返回值 ： false: 创建失败   true:创建失败
     * errorTxt：失败原因
     */
    bool creatJobfile(QString jobname,QString & errorTxt);
    /*
     * 开启二次开发界面标志位
     * 开启后，切换模式将不会进行界面跳转，二次开发界面、调用插入指令、开启窗口等接口将会隐藏左侧快捷栏
     */
    void userpageisOpen(bool OK);
    /*
     * 更换账户
     * usertype 操作员 技术员 管理员
     * password 默认为123456
     */
    bool changeAccount(QString usertype,QString password="");
    /*
     * 获取当前账户
     * 返回值 操作员 技术员 管理员
     */
    QString getAccount();
    /*
     * 获取伺服状态
     * 返回值 0：伺服停止 1：伺服就绪 2：伺服停止 3：伺服运行
     */
    int getServoStatus();
    /*
     * 断开与控制器的连接
     */
    void disconnect_robot();
    /*
     * 重新连接控制器
     */
    void connect_robot();
    /*
     * 打开功能窗口
     * widget 功能窗口名
     * x，y 显示窗口的位置（左上角第一个点）
     */
    void open_widget(widgetType widgetType, int x = 0, int y = 0);
    /*
     * 关闭所有功能窗口
     */
    void close_widget();
    /*
     * 插入指令
     * cmd 指令名
     */
    void customCmdInsert(QString cmd);
    /*
     * 修改自定义状态栏
     * name 工艺名
     */
    void changeCustomStateBar(QString name);

//    void customStateBar_clicked();
signals:
    /*
     * 接收机器人运行的作业文件行号
     * robot 机器人
     * jobfile 作业文件名
     * line 行号
     */
    void robot_step_end(int robot,QString jobfile ,int line);
    //文件同步结束
    void signal_finishSyncJobfile();
    //接收控制器消息
    void signal_receiveMessage(const quint16 &command,const QByteArray &data);
    void signal_openWidget();
    void signal_closeWidget();
    /*
     * 接收操作模式信号
     * mode 操作模式 0:示教 1:远程 2:运行
     */
    void signal_robotMode(int mode);
    /*
     * 接收程序运行状态
     * robot 机器人编号 1-4
     * status 程序运行状态  0:停止 1：暂停 2:运
     */
    void  signal_robotProState(int robot ,int status);

    /*
     * 接收当前位置信号
     *pos:当前点位值 7个数值
     * coord 坐标系 0：关节 1：直角  2：工具  3：用户
     *robot  机器人编号 1-4
     * config 当前机器人姿态
     */
    void signal_receiveCurrentPos(const QVector< double > pos, const int coord, const int robot, const int config);
    /*
     * 接收IO板数字输入状态
     *io1dinstate:IO板1数字输入状态
     *io2dinstate:IO板2数字输入状态
     *io3dinstate:IO板3数字输入状态
     *io4dinstate:IO板4数字输入状态
     */
    void signal_receiveIoDigitDinState(const QVector< int > io1dinstate, const QVector< int > io2dinstate, const QVector< int > io3dinstate, const QVector< int > io4dinstate);
    /*
     * 接收IO板数字输出状态
     *io1doutstate:IO板1数字输出状态
     *io2doutstate:IO板2数字输出状态
     *io3doutstate:IO板3数字输出状态
     *io4doutstate:IO板4数字输出状态
     */
    void signal_receiveIoDigitOutputState(const QVector< int > io1doutstate, const QVector< int > io2doutstate, const QVector< int > io3doutstate, const QVector< int > io4doutstate);

    /*
     * 自定义状态栏信号函数
     */
    void signal_customStateBar_clicked();
private:
    explicit Nextp(QObject *parent = 0);
    static QPointer<Nextp> _pInstance;

};

#endif // NEXTP_H

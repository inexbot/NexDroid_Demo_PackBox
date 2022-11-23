#include "settingparawidget.h"
#include "ui_settingparawidget.h"
#include "stdio.h"
#include "widgetmanager.h"
#include <QTime>
#include<QDialog>
#include<QPoint>

QPointer<SettingParaWidget> SettingParaWidget::_pInstance = NULL;
QPointer<SettingParaWidget> SettingParaWidget::getInstance()
{
    if(_pInstance == NULL)
    {
        _pInstance = new SettingParaWidget;
    }
    return _pInstance;
}

SettingParaWidget::SettingParaWidget(QWidget *parent) :
    QStackedWidget(parent),
    ui(new Ui::SettingParaWidget)
{
    ui->setupUi(this);
    this->setCurrentIndex(0);
    this->setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_DeleteOnClose);
    ui->mypassword->setEchoMode(QLineEdit::Password);//密码隐藏

    //*******进入页面初始化
    Nextp::getInstance()->userpageisOpen(1);
    Nextp::getInstance()->sendMessage(Nextp::SetFourthUserParaCommand,QByteArray().append("file"));//
    ui->stackedWidget->setCurrentWidget(ui->mian);
    ui->head_label->setText("主界面");
    ui->test->setText("运行状态");
    ui->shell_adnanced->show();
    ui->reset_wid->hide();
    ui->clear_sum->hide();
    ui->shell_modify->hide();
    ui->btn_advanced->hide();
    ui->shell_returnButton->hide();
    ui->label_password->hide();
    ui->mypassword->hide();
    ui->mian_Run_Mode->setEnabled(true);
    //io
    ui->IO5_PushButton->setCheck(false);
    ui->IO6_PushButton->setCheck(false);
    ui->IO7_PushButton->setCheck(false);
    ui->mian_Run_Mode->setEnabled(true);
    //**********
    _pGetIoInputStatusTimer = new QTimer(this);
    _pGetIoInputStatusTimer->setInterval(400);
    connect(_pGetIoInputStatusTimer, SIGNAL(timeout()), this, SLOT(slot_getIoInputStatus()));
//*********real_time************
    _pPostime = new QTimer(this);
    connect(_pPostime,SIGNAL(timeout()),this, SLOT(slot_getPos()));
    _pPostime->start(400);
    //******real_time  end**
    connect(Nextp::getInstance(),SIGNAL(signal_receiveCurrentPos(const QVector< double > , const int , const int , const int )),
            this,SLOT(slot_receiveCurrentPos(const QVector< double > , const int , const int , const int)));

    connect(Nextp::getInstance(),SIGNAL(signal_receiveIoDigitDinState(const QVector< int > , const QVector< int > , const QVector< int > , const QVector< int > )),
            this,SLOT(slot_receiveIoDigitDinState(const QVector< int > , const QVector< int > , const QVector< int > , const QVector< int >)));

    connect(Nextp::getInstance(),SIGNAL(signal_receiveIoDigitOutputState(const QVector< int > , const QVector< int > , const QVector< int > , const QVector< int > )),
            this,SLOT(slot_receiveIoDigitOutputState(const QVector< int > , const QVector< int > , const QVector< int > , const QVector< int >)));

    connect(WidgetManager::getInstance(),SIGNAL(signal_closeSettingParaWidget()),this,SLOT(slot_closeMyWidget()));

    qDebug()<<"创建 用户自定义页面";
}

SettingParaWidget::~SettingParaWidget()
{
    qDebug()<<"删除 用户自定义页面";
    delete ui;
}


void SettingParaWidget::sendStartData(QString jobname)
{
    Json::Value root;
    Json::FastWriter wt;
    root["start"] ="send start job";
    root["jobname"] =jobname.toStdString();
    Nextp::getInstance()->sendMessage(Nextp::SetFirstUserParaCommand,QByteArray().append(QString::fromStdString(wt.write(root))));

}

void SettingParaWidget::pressReserveButton()
{
    qDebug()<<"按下T30示教器左下角的按钮";
}

void SettingParaWidget::on__pPara1ReturnBtn_clicked()
{
    this->close();
}

void SettingParaWidget::on__pPara1NextPageBtn_clicked()
{
    this->setCurrentIndex(1);
}

void SettingParaWidget::on__pPara2UpPageBtn_clicked()
{
    this->setCurrentIndex(0);
}


void SettingParaWidget::slot_closeMyWidget()
{
    this->close();
}

void SettingParaWidget::slot_receiveIoDigitDinState(const QVector< int > io1dinstatus, const QVector< int > io2dinstatus, const QVector< int > io3dinstatus, const QVector< int >io4dinstatus)
{
    if(io1dinstatus.size()!=0)
    {
        qDebug()<<"IO板1 数字输入状态 :"<<io1dinstatus.size()<<endl;
        for(int i=0;i<io1dinstatus.size();i++)
        {
            qDebug()<<"IO板1 数字输入 port["<<i+1<<"] = "<<io1dinstatus.at(i)<<endl;
        }
    }

    if(io2dinstatus.size()!=0)
    {
        qDebug()<<"IO板2 数字输入状态 :"<<io2dinstatus.size()<<endl;
        for(int i=0;i<io2dinstatus.size();i++)
        {
            qDebug()<<"IO板2 数字输入 port["<<i+1<<"] = "<<io2dinstatus.at(i)<<endl;
        }
    }

    if(io3dinstatus.size()!=0)
    {
        qDebug()<<"IO板3 数字输入状态 :"<<io3dinstatus.size()<<endl;
        for(int i=0;i<io3dinstatus.size();i++)
        {
            qDebug()<<"IO板3 数字输入 port["<<i+1<<"] = "<<io3dinstatus.at(i)<<endl;
        }
    }

    if(io4dinstatus.size()!=0)
    {
        qDebug()<<"IO板4 数字输入状态 :"<<io4dinstatus.size()<<endl;
        for(int i=0;i<io4dinstatus.size();i++)
        {
            qDebug()<<"IO板4 数字输入 port["<<i+1<<"] = "<<io4dinstatus.at(i)<<endl;
        }
    }
}

void SettingParaWidget::slot_receiveIoDigitOutputState(const QVector< int > io1doutstatus, const QVector< int > io2doutstatus, const QVector< int > io3doutstatus, const QVector< int >io4doutstatus)
{
    if(io1doutstatus.size()!=0)
    {
        qDebug()<<"IO板1 数字输出状态 :"<<io1doutstatus.size()<<endl;
        for(int i=0;i<io1doutstatus.size();i++)
        {
            qDebug()<<"IO板1 数字输出 port["<<i+1<<"] = "<<io1doutstatus.at(i)<<endl;
        }
    }

    if(io2doutstatus.size()!=0)
    {
        qDebug()<<"IO板2 数字输出状态 :"<<io2doutstatus.size()<<endl;
        for(int i=0;i<io2doutstatus.size();i++)
        {
            qDebug()<<"IO板2 数字输出 port["<<i+1<<"] = "<<io2doutstatus.at(i)<<endl;
        }
    }

    if(io3doutstatus.size()!=0)
    {
        qDebug()<<"IO板3 数字输出状态 :"<<io3doutstatus.size()<<endl;
        for(int i=0;i<io3doutstatus.size();i++)
        {
            qDebug()<<"IO板3 数字输出 port["<<i+1<<"] = "<<io3doutstatus.at(i)<<endl;
        }
    }

    if(io4doutstatus.size()!=0)
    {
        qDebug()<<"IO板4 数字输出状态 :"<<io4doutstatus.size()<<endl;
        for(int i=0;i<io4doutstatus.size();i++)
        {
            qDebug()<<"IO板4 数字输出 port["<<i+1<<"] = "<<io4doutstatus.at(i)<<endl;
        }
    }
}

void SettingParaWidget::on__pParamodifyBtn_2_clicked()
{
    poslist tmp;
    tmp.pos = _pos;
    tmp.coord = _coord;
    _poslist.append(tmp);
//    Nextp::getInstance()->openOrCloseGetCurrentPos(true);
    Nextp::getInstance()->startInsertCommand();
}

void SettingParaWidget::on__pParamodifyBtn_3_clicked()
{
    QString errorTxt="";
    Nextp::getInstance()->insertCmd(errorTxt,0,1,_pos,_coord,10,20,1,0);
    Nextp::getInstance()->insertTimerCmd(errorTxt,10);
    if(!errorTxt.isEmpty())
    {
        qDebug()<<errorTxt;
    }

    Nextp::getInstance()->insertCmd(errorTxt,1,2,_pos,_coord,10,20,1,0);
    if(!errorTxt.isEmpty())
    {
        qDebug()<<errorTxt;
    }
    Nextp::getInstance()->insertCmd(errorTxt,1,3,_pos,_coord,10,20,1,0);
    if(!errorTxt.isEmpty())
    {
        qDebug()<<errorTxt;
    }
    Nextp::getInstance()->insertCmd(errorTxt,0,4,_pos,_coord,10,20,1,0);
    if(!errorTxt.isEmpty())
    {
        qDebug()<<errorTxt;
    }
    Nextp::getInstance()->insertCmd(errorTxt,1,5,_pos,_coord,10,20,1,0);
    if(!errorTxt.isEmpty())
    {
        qDebug()<<errorTxt;
    }
    Nextp::getInstance()->insertCmd(errorTxt,1,6,_pos,_coord,10,20,1,0);
    if(!errorTxt.isEmpty())
    {
        qDebug()<<errorTxt;
    }
    Nextp::getInstance()->insertCmd(errorTxt,1,7,_pos,_coord,10,20,1,0);
    if(!errorTxt.isEmpty())
    {
        qDebug()<<errorTxt;
    }
    Nextp::getInstance()->insertCmd(errorTxt,1,8,_pos,_coord,10,20,1,0);
}


void SettingParaWidget::on_btn_ioConfig_clicked()
{
    int IoNum = 0;
    Nextp::getInstance()->getIoConfig(IoNum,_ioConfig);
    qDebug()<<"IO板个数="<<_ioConfig.size();
    for(int i=0;i<_ioConfig.size();i++)
    {
            qDebug()<<"第"<<i+1<<"个IO板配置参数:"<<endl;
            if(_ioConfig.at(0)._iotype == Nextp::EtherCATIO)
            {
                qDebug()<<"IO板类型 EtherCATOIO"<<endl;
            }
            else
            {
                qDebug()<<"IO板类型 华太IO"<<endl;
            }
            qDebug()<<"IO板数字输入端口数量 = "<<_ioConfig.at(i)._dinPortNum<<endl;
            qDebug()<<"IO板数字输出端口数量 = "<<_ioConfig.at(i)._doutPortNum<<endl;
            qDebug()<<"IO板模拟输入端口数量 = "<<_ioConfig.at(i)._ainPortNum<<endl;
            qDebug()<<"IO板模拟输出端口数量 = "<<_ioConfig.at(i)._aoutPortNum<<endl;
            qDebug()<<"************************"<<endl;
    }
}

void SettingParaWidget::on_btn_ioInputSxtatus_clicked()
{
    if(_pGetIoInputStatusTimer)
    {
        if(_pGetIoInputStatusTimer->isActive())
        {
            _pGetIoInputStatusTimer->stop();
        }
        else
        {
            _pGetIoInputStatusTimer->start();
        }
    }

}
void SettingParaWidget::slot_getIoInputStatus()
{
    qDebug()<<"查询IO输入端口状态 "<<QTime::currentTime().toString("hh:mm:ss.zzz")<<endl;
    Nextp::getInstance()->getIoDigitDinState();
    Nextp::getInstance()->getIoDigitOutputState();
}
//***接受信息的槽函数 slot_receiveMessage*********
void SettingParaWidget::slot_receiveMessage(const quint16 &command,const QByteArray &data)
{
    Json::Value root;
    Json::Reader reader;
    Json::StyledWriter wt;
    QString jsonData = data.data();
    reader.parse(jsonData.toStdString(), root);
    qDebug()<<"myslot coming"<<endl;
    //参数设定
    if(command == Nextp ::  ReceivedFirstUserCommand)//0x9202
    {
        // qDebug()<<"myslot coming  0x9202"<<endl;
        ui->absorb_Time->setText(QString::number(root["Time"]["absorb_Time"].asDouble(),'f',2));
        ui->lengthways_Time->setText(QString::number(root["Time"]["lengthways_Time"].asDouble(),'f',2));
        ui->across_Time->setText(QString::number(root["Time"]["across_Time"].asDouble(),'f',2));
        ui->pushing_Time->setText(QString::number(root["Time"]["pushing_Time"].asDouble(),'f',2));
    }
    //坐标、io实时更新
    if(command == Nextp ::  ReceivedSecondUserCommand)//0x9205
    {
        // qDebug()<<"myslot coming  0x9205"<<endl;
        ui->pos_1->setText(QString::number(root["pos"]["1"].asDouble(),'f',3));
        ui->pos_2->setText(QString::number(root["pos"]["2"].asDouble(),'f',3));
        ui->pos_3->setText(QString::number(root["pos"]["3"].asDouble(),'f',3));
        ui->pos_4->setText(QString::number(root["pos"]["4"].asDouble(),'f',3));
        ui->pos_5->setText(QString::number(root["pos"]["5"].asDouble(),'f',3));
        ui->pos_6->setText(QString::number(root["pos"]["6"].asDouble(),'f',3));
        //**mian param
        ui->add_sum->setText(QString::number(root["sum"].asInt()));
        ui->mian_run_time->setText(QString::number(root["run_time"].asDouble(),'f',1));
        ui->run_number->setText(QString::number(root["run_number"].asInt()));
        ui->circle_time->setText(QString::number(root["cicle_time"].asDouble(),'f',2));
        //**IO_in param
        ui->in_io_1->setText(QString::number(root["IO1"].asInt()));
        ui->in_io_2->setText(QString::number(root["IO2"].asInt()));
        ui->in_io_3->setText(QString::number(root["IO3"].asInt()));
        ui->in_io_4->setText(QString::number(root["IO4"].asInt()));
        ui->in_io_5->setText(QString::number(root["IO5"].asInt()));
        //**IO_out param
        if(root["IO1_out"].asInt() == 1)
        {
            ui->IO1_PushButton->setCheck(true);
        }
        else if(root["IO1_out"].asInt() == 0)
        {
             ui->IO1_PushButton->setCheck(false);
        }
        if(root["IO2_out"].asInt() == 1)
        {
            ui->IO2_PushButton->setCheck(true);
        }
        else if(root["IO2_out"].asInt() == 0)
        {
             ui->IO2_PushButton->setCheck(false);
        }
        if(root["IO5_out"].asInt() == 1)
        {
            ui->IO5_PushButton->setCheck(true);
        }
        else if(root["IO5_out"].asInt() == 0)
        {
             ui->IO5_PushButton->setCheck(false);
        }
        if(root["IO6_out"].asInt() == 1)
        {
            ui->IO6_PushButton->setCheck(true);
        }
        else if(root["IO6_out"].asInt() == 0)
        {
             ui->IO6_PushButton->setCheck(false);
        }
        if(root["IO7_out"].asInt() == 1)
        {
            ui->IO7_PushButton->setCheck(true);
        }
        else if(root["IO7_out"].asInt() == 0)
        {
             ui->IO7_PushButton->setCheck(false);
        }
        if(root["IO8_out"].asInt() == 1)
        {
            ui->IO8_PushButton->setCheck(true);
        }
        else if(root["IO8_out"].asInt() == 0)
        {
             ui->IO8_PushButton->setCheck(false);
        }
        if(root["IO3_out"].asInt() == 1)
        {
            ui->IO3_PushButton->setCheck(true);
        }
        else if(root["IO3_out"].asInt() == 0)
        {
             ui->IO3_PushButton->setCheck(false);
        }
        //**IO_in param
        if(root["IO1_in"].asInt() == 1)
        {
            ui->IO1_in_PushButton->setCheck(true);
        }
        else if(root["IO1_in"].asInt() == 0)
        {
             ui->IO1_in_PushButton->setCheck(false);
        }
        if(root["IO2_in"].asInt() == 1)
        {
            ui->IO2_in_PushButton->setCheck(true);
        }
        else if(root["IO2_in"].asInt() == 0)
        {
             ui->IO2_in_PushButton->setCheck(false);
        }
        if(root["IO3_in"].asInt() == 1)
        {
            ui->IO3_in_PushButton->setCheck(true);
        }
        else if(root["IO3_in"].asInt() == 0)
        {
             ui->IO3_in_PushButton->setCheck(false);
        }
        if(root["IO4_in"].asInt() == 1)
        {
            ui->IO4_in_PushButton->setCheck(true);
        }
        else if(root["IO4_in"].asInt() == 0)
        {
             ui->IO4_in_PushButton->setCheck(false);
        }
        if(root["IO5_in"].asInt() == 1)
        {
            ui->IO5_in_PushButton->setCheck(true);
        }
        else if(root["IO5_in"].asInt() == 0)
        {
             ui->IO5_in_PushButton->setCheck(false);
        }

    }
    //小白条打印信息
    if(command == Nextp ::  ReceivedThirdUserCommand)//0x9208
    {
        //        qDebug()<<data<<"***************"<<QString(data)<<endl;

        if(QString(data) == "unaffected_pos")//文件初始化
        {
            ui->test->setText("调试状态");
            qDebug()<<"调试状态调试状态调试状态调试状态";
            emit SettingParaWidget::on_test_clicked();
            emit SettingParaWidget::on_sign_ok_clicked();
        }
        if(QString(data) == "no")
        {
            Nextp::getInstance()->showSnackbarMessage("下电状态才可以更新作业文件",2000);
        }
        if(QString(data) == "waitting")
        {
            Nextp::getInstance()->showSnackbarMessage("伺服正在运行，无法修改插入作业文件",2000);
        }
        if(QString(data) == "Out of servo")
        {
            Nextp::getInstance()->showSnackbarMessage("伺服未运行 , 请上电后",2000);
        }
        if(QString(data) == "yes")
        {
            Nextp::getInstance()->showSnackbarMessage("作业文件已更新",2000);
        }
        if(QString(data) == "No running mode")
        {
            Nextp::getInstance()->showSnackbarMessage("非运行模式，不能运行作业文件",2000);
        }
        if(QString(data) == "No at start point")
        {
            Nextp::getInstance()->showSnackbarMessage("不在起点,不能运行作业文件,请复位到起点",2000);
        }
        if(QString(data) == "No stop file")
        {
            Nextp::getInstance()->showSnackbarMessage("非停止状态，启动无效",2000);
        }
        if(QString(data) == "reset_sum")
        {
            Nextp::getInstance()->showSnackbarMessage("非示教模式，不能重置数据",2000);
        }

        if(QString(data) == "pause_file")
        {
            Nextp::getInstance()->showSnackbarMessage("已暂停!  !",2000);
        }
        if(QString(data) == "continue_file")
        {
            Nextp::getInstance()->showSnackbarMessage("已继续!  !",2000);
        }
        if(QString(data) == "stop_file")
        {
            Nextp::getInstance()->showSnackbarMessage("已停止!  !",2000);
        }
        if(QString(data) == "clear_sum")
        {
            Nextp::getInstance()->showSnackbarMessage("已重置累计总产量!  !",2000);
        }
        if(QString(data) == "reset_to_start")
        {
            Nextp::getInstance()->showSnackbarMessage("已复位到起点!  !",2000);
        }
        //上一次未出盒检测
        if(QString(data) == "false_check")
        {
            Nextp::getInstance()->showSnackbarMessage("上一次未出盒!  !",2000);
        }
        //运行模式按钮是否可按
        if(QString(data) == "disable_rnn_mode")
        {
            ui->mian_Stop->setEnabled(true);
            ui->test->setEnabled(false);
            ui->shell_modify->setEnabled(false);
            ui->mian_Run_Mode->setEnabled(false);
            ui->run_select_Pos->setEnabled(false);
            ui->IO1_PushButton->setEnabled(false);
            ui->IO2_PushButton->setEnabled(false);
            ui->IO3_PushButton->setEnabled(false);
            ui->IO4_PushButton->setEnabled(false);
            ui->IO5_PushButton->setEnabled(false);
            ui->IO6_PushButton->setEnabled(false);
            ui->IO7_PushButton->setEnabled(false);
            ui->IO8_PushButton->setEnabled(false);

        }
        if(QString(data) == "enable_rnn_mode")
        {
            ui->mian_Stop->setEnabled(false);
            ui->test->setEnabled(true);
            ui->shell_modify->setEnabled(true);
            ui->mian_Run_Mode->setEnabled(true);
            ui->run_select_Pos->setEnabled(true);
            ui->IO1_PushButton->setEnabled(true);
            ui->IO2_PushButton->setEnabled(true);
            ui->IO3_PushButton->setEnabled(true);
            ui->IO4_PushButton->setEnabled(true);
            ui->IO5_PushButton->setEnabled(true);
            ui->IO6_PushButton->setEnabled(true);
            ui->IO7_PushButton->setEnabled(true);
            ui->IO8_PushButton->setEnabled(true);
        }
        //复位按钮是否可按
        if(QString(data) == "disable_reset")
        {
            ui->main_Reset_2->setEnabled(false);
        }
        if(QString(data) == "enable_reset")
        {
            ui->main_Reset_2->setEnabled(true);
        }

        if(QString(data) == "alarm_light")
        {
            ui->mian_Start->setEnabled(false);
            Nextp::getInstance()->showSnackbarMessage("未正常出盒!  !",2000);
        }
        if(QString(data) == "alarm_down")
        {
            ui->mian_Start->setEnabled(true);
        }
    }
    //选择过渡点保持一致
    if(command == Nextp ::  ReceivedFourthUserCommand)//0x920b
    {
        //judge exc初始化过渡点
        if(root["exc"]["1"].asInt() == 1)
        {
            ui->exc_pos_1->setStyleSheet("QPushButton{background-color: rgb(11, 255, 68); font: 11pt ; border-radius:8px;}");
            judge_exc_1= true;
        }
        else
        {
            ui->exc_pos_1->setStyleSheet("QPushButton{ font: 11pt ;border-radius:8px;background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 rgb(240,240,240),stop:1 rgb(220,220,220));}");
            judge_exc_1= false;
        }

        if(root["exc"]["2"].asInt() == 1)
        {
            ui->exc_pos_2->setStyleSheet("QPushButton{background-color: rgb(11, 255, 68); font: 11pt ; border-radius:8px;}");
            judge_exc_2= true;
        }
        else
        {
            ui->exc_pos_2->setStyleSheet("QPushButton{ font: 11pt ;border-radius:8px;background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 rgb(240,240,240),stop:1 rgb(220,220,220));}");
            judge_exc_2= false;
        }

        if(root["exc"]["3"].asInt() == 1)
        {
            ui->exc_pos_3->setStyleSheet("QPushButton{background-color: rgb(11, 255, 68); font: 11pt ; border-radius:8px;}");
            judge_exc_3= true;
        }
        else
        {
            ui->exc_pos_3->setStyleSheet("QPushButton{ font: 11pt ;border-radius:8px;background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 rgb(240,240,240),stop:1 rgb(220,220,220));}");
            judge_exc_3= false;
        }
        if(root["exc"]["4"].asInt() == 1)
        {
            ui->exc_pos_4->setStyleSheet("QPushButton{background-color: rgb(11, 255, 68); font: 11pt ; border-radius:8px;}");
            judge_exc_4= true;
        }
        else
        {
            ui->exc_pos_4->setStyleSheet("QPushButton{ font: 11pt ;border-radius:8px;background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 rgb(240,240,240),stop:1 rgb(220,220,220));}");
            judge_exc_4= false;
        }
        if(root["exc"]["5"].asInt() == 1)
        {
            ui->exc_pos_5->setStyleSheet("QPushButton{background-color: rgb(11, 255, 68); font: 11pt ; border-radius:8px;}");
            judge_exc_5= true;
        }
        else
        {
            ui->exc_pos_5->setStyleSheet("QPushButton{ font: 11pt ;border-radius:8px;background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 rgb(240,240,240),stop:1 rgb(220,220,220));}");
            judge_exc_5= false;
        }
        if(root["exc"]["6"].asInt() == 1)
        {
            ui->exc_pos_6->setStyleSheet("QPushButton{background-color: rgb(11, 255, 68); font: 11pt ; border-radius:8px;}");
            judge_exc_6= true;
        }
        else
        {
            ui->exc_pos_6->setStyleSheet("QPushButton{ font: 11pt ;border-radius:8px;background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 rgb(240,240,240),stop:1 rgb(220,220,220));}");
            judge_exc_6= false;
        }
        //judge exc初始化过渡点__endl
    }

}
//***不同用户不同权限
void SettingParaWidget::getAccount()
{
    account = Nextp::getInstance()->getAccount();
    if(account == "操作员")
    {
        ui->shell_modify->setEnabled(false);
        ui->shell_adnanced->setEnabled(true);
    }
    if(account == "技术员")
    {
        ui->shell_modify->setEnabled(true);
        ui->shell_adnanced->setEnabled(true);
    }
    if(account == "管理员")
    {
        ui->shell_modify->setEnabled(true);
        ui->shell_adnanced->setEnabled(true);
    }
}
//***判断是否密码正确
void SettingParaWidget::on_passwordButton_clicked()
{
   QString  str = Nextp::getInstance()->getAccount();
    if(ui->account_list->currentText() == "操作员")
    {
        str = "操作员";
    }
    else if(ui->account_list->currentText() == "管理员")
    {
        str = "技术员";
    }
    else if(ui->account_list->currentText() == "高级管理员")
    {
        str = "管理员";
    }
    if(Nextp::getInstance()->changeAccount(str,ui->mypassword->text()))
    {
            qDebug()<<str<<endl;
            Nextp::getInstance()->showSnackbarMessage("切换成功",2000);
            ui->stackedWidget->setCurrentWidget(ui->mian);
            ui->head_label->setText("主界面");
            ui->reset_wid->hide();
            ui->shell_modify->hide();
            ui->shell_returnButton->hide();
            ui->shell_adnanced->show();
            if(Nextp::getInstance()->getAccount() == "管理员")
            {
                ui->btn_advanced->show();
                ui->clear_sum->show();
            }
            else
            {
                ui->btn_advanced->hide();
                ui->clear_sum->hide();
            }
            getAccount();
            ui->mypassword->setText("");//登录后把密码的text清空，防止切换到更高级权限时，还有上次的密码遗留
            _pPostime->start(400);
    }
}
//判断是否密码正确___endl
//***进入点位管理
void SettingParaWidget::on_btn_Poswidget_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->setting_Pos);
    ui->shell_adnanced->hide();
    ui->btn_advanced->hide();
    ui->clear_sum->hide();
    ui->shell_modify->show();
    ui->shell_returnButton->show();
     ui->shell_modify->hide();
     ui->exc_wid->hide();
     ui->sign_wid->hide();
     ui->selected_Pos->setText("起点");
    ui->head_label->setText("点位管理");

    if(Nextp::getInstance()->getAccount() == "技术员" ||Nextp::getInstance()->getAccount() == "管理员")
    {

    }
    else
    {

    }
    Nextp::getInstance()->sendMessage(Nextp::GetFirstUserCommand,QByteArray().append("点位管理"));//messges
}
//进入点位管理___endl
//***进入数据设定
void SettingParaWidget::on_btn_Paramwidget_clicked()
{
    ui->param_wid->hide();
    ui->absorb_Time->setEnabled(false);
    ui->lengthways_Time->setEnabled(false);
    ui->across_Time->setEnabled(false);
    ui->pushing_Time->setEnabled(false);
    ui->stackedWidget->setCurrentWidget(ui->setting_Param);
    ui->shell_adnanced->hide();
    ui->shell_modify->show();
    ui->shell_returnButton->show();
    ui->shell_adnanced->hide();
    ui->clear_sum->hide();
    ui->btn_advanced->hide();
    ui->selected_Pos->setText("kong");
    ui->head_label->setText("参数设定");
    if(Nextp::getInstance()->getAccount() == "技术员" ||Nextp::getInstance()->getAccount() == "管理员")
    {
        ui->shell_modify->setEnabled(true);
    }
    else
    {
        ui->shell_modify->setEnabled(false);
    }

    Json::Value root;
    Json::FastWriter wt;
    Nextp::getInstance()->sendMessage(Nextp::GetFirstUserCommand,QByteArray().append("参数设定"));//messges
}
//进入数据设定__endl
//***进入IO设定
void SettingParaWidget::on_btn_IOwidget_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->setting_IO);
    ui->shell_adnanced->hide();
    ui->clear_sum->hide();
    ui->btn_advanced->hide();
    ui->shell_modify->hide();
    ui->shell_returnButton->show();
    ui->head_label->setText("IO设定");
}
//进入IO设定___endl
//***返回按钮
void SettingParaWidget::on_shell_returnButton_clicked()
{
    if(ui->head_label->text() == tr("点位管理"))
    {
        if(Nextp::getInstance()->getAccount() == "管理员")
        {
            ui->clear_sum->show();
            ui->btn_advanced->show();
        }
        ui->stackedWidget->setCurrentWidget(ui->mian);
        ui->shell_adnanced->show();
        ui->shell_modify->hide();
        ui->shell_returnButton->hide();
        ui->head_label->setText("主界面");
        ui->selected_Pos->setText("请选择点位");
    }
    if(ui->head_label->text() == tr("参数设定"))
    {
        if(ui->shell_modify->text()=="保存")
        {
            ui->param_wid->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);//弹出新窗口之后旧窗口不可点
            ui->param_wid->setWindowModality(Qt::WindowModal);
            ui->param_wid->show();
            ui->param_wid->move(330, 220);

        }
        if(ui->shell_modify->text()=="修改")
        {
            if(Nextp::getInstance()->getAccount() == "管理员")
            {
                ui->clear_sum->show();
                ui->btn_advanced->show();
            }
            ui->stackedWidget->setCurrentWidget(ui->mian);
            ui->shell_adnanced->show();
            ui->shell_modify->hide();
            ui->shell_returnButton->hide();

            Nextp::getInstance()->sendMessage(Nextp::GetFirstUserCommand,QByteArray().append("参数设定"));//messges
            ui->head_label->setText("主界面");
            ui->shell_modify->setText("修改");
        }
    }
    if(ui->head_label->text() == tr("IO设定") || ui->head_label->text() == tr("点位管理"))
    {
        if(Nextp::getInstance()->getAccount() == "管理员")
        {
            ui->clear_sum->show();
            ui->btn_advanced->show();
        }
        ui->stackedWidget->setCurrentWidget(ui->mian);
        ui->shell_adnanced->show();
        ui->shell_modify->hide();
        ui->shell_returnButton->hide();
        ui->head_label->setText("主界面");
    }
}
//返回按钮__endl
//***切换用户
void SettingParaWidget::on_account_list_currentIndexChanged(const QString &arg1)
{
    account =Nextp::getInstance()->getAccount();
    if(account == "操作员")
    {
        if(arg1 == "管理员"||arg1 == "高级管理员")
        {
            ui->label_password->show();
            ui->mypassword->show();
            ui->passwordButton->show();
        }
         if(arg1 == "操作员")
         {
             ui->label_password->hide();
             ui->mypassword->hide();
             ui->passwordButton->show();
         }
        else return;
    }
    if(account == "技术员")
    {
        if(arg1 == "操作员" || arg1 == "管理员")
        {
            ui->label_password->hide();
            ui->mypassword->hide();
            ui->passwordButton->show();
        }
        if(arg1 == "高级管理员")
        {
            ui->label_password->show();
            ui->mypassword->show();
            ui->passwordButton->show();
        }
        else return;
    }
    if(account == "管理员")
    {
        if(arg1 == "操作员")
        {
            ui->label_password->hide();
            ui->mypassword->hide();
            ui->passwordButton->show();
        }
        if(arg1 == "管理员")
        {
            ui->label_password->hide();
            ui->mypassword->hide();
            ui->passwordButton->show();
        }
        else return;
    }
}
//切换用户__endl
void SettingParaWidget::on_shell_adnanced_clicked()
{
    account =Nextp::getInstance()->getAccount();
     if(account == "操作员")
     {
         ui->account_list->setCurrentIndex(0);
     }
     if(account == "技术员")
     {
         ui->account_list->setCurrentIndex(1);
     }
     if(account == "管理员")
     {
         ui->account_list->setCurrentIndex(2);
     }
    emit SettingParaWidget::on_account_list_currentIndexChanged(ui->account_list->currentText());
    ui->stackedWidget->setCurrentWidget(ui->accountpage);
    ui->head_label->setText("用户");
    ui->shell_modify->hide();
    ui->shell_returnButton->hide();
    ui->label_password->hide();
    ui->mypassword->hide();
    ui->shell_adnanced->hide();
    ui->clear_sum->hide();
    ui->btn_advanced->hide();
    _pPostime->stop();
}
//IO1
void SettingParaWidget::on_IO1_PushButton_clicked()
{
    Json::Value root;
    Json::FastWriter wt;
    if(ui->IO1_PushButton->getCheck() == true)
    {
        root["IO1_out"] = 0;
        ui->IO1_PushButton->setCheck(false);
    }
    else if(ui->IO1_PushButton->getCheck() == false)
    {
        root["IO1_out"] = 1;
        ui->IO1_PushButton->setCheck(true);
    }
    root["IO1"] ="IO1";
    Nextp::getInstance()->sendMessage(Nextp::GetSecondUserCommand,QByteArray().append(QString::fromStdString(wt.write(root))));
}
//IO2
void SettingParaWidget::on_IO2_PushButton_clicked()
{
    Json::Value root;
    Json::FastWriter wt;
    if(ui->IO2_PushButton->getCheck() == true)
    {
        root["IO2_out"] = 0;
        ui->IO2_PushButton->setCheck(false);
    }
    else if(ui->IO2_PushButton->getCheck() == false)
    {
        root["IO2_out"] = 1;
        ui->IO2_PushButton->setCheck(true);
    }
    root["IO2"] = "IO2";
    Nextp::getInstance()->sendMessage(Nextp::GetSecondUserCommand,QByteArray().append(QString::fromStdString(wt.write(root))));
}
//IO5
void SettingParaWidget::on_IO5_PushButton_clicked()
{
    Json::Value root;
    Json::FastWriter wt;
    if(ui->IO5_PushButton->getCheck() == true)
    {
        root["IO5_out"] = 0;
        ui->IO5_PushButton->setCheck(false);
    }
    else if(ui->IO5_PushButton->getCheck() == false)
    {
        root["IO5_out"] = 1;
        ui->IO5_PushButton->setCheck(true);
    }
    root["IO5"] = "IO5";
    Nextp::getInstance()->sendMessage(Nextp::GetSecondUserCommand,QByteArray().append(QString::fromStdString(wt.write(root))));
}
//IO6
void SettingParaWidget::on_IO6_PushButton_clicked()
{
    Json::Value root;
    Json::FastWriter wt;
    if(ui->IO6_PushButton->getCheck() == true)
    {
        root["IO6_out"] = 0;
        ui->IO6_PushButton->setCheck(false);
    }
    else if(ui->IO6_PushButton->getCheck() == false)
    {
        root["IO6_out"] = 1;
        ui->IO6_PushButton->setCheck(true);
    }
    root["IO6"] = "IO6";
    Nextp::getInstance()->sendMessage(Nextp::GetSecondUserCommand,QByteArray().append(QString::fromStdString(wt.write(root))));
}
//IO7
void SettingParaWidget::on_IO7_PushButton_clicked()
{
    Json::Value root;
    Json::FastWriter wt;
    if(ui->IO7_PushButton->getCheck() == true)
    {
        root["IO7_out"] = 0;
        ui->IO7_PushButton->setCheck(false);
    }
    else if(ui->IO7_PushButton->getCheck() == false)
    {
        root["IO7_out"] = 1;
        ui->IO7_PushButton->setCheck(true);
    }
    root["IO7"] = "IO7";
    Nextp::getInstance()->sendMessage(Nextp::GetSecondUserCommand,QByteArray().append(QString::fromStdString(wt.write(root))));
}
//IO8
void SettingParaWidget::on_IO8_PushButton_clicked()
{
    Json::Value root;
    Json::FastWriter wt;
    if(ui->IO8_PushButton->getCheck() == true)
    {
        root["IO8_out"] = 0;
        ui->IO8_PushButton->setCheck(false);
    }
    else if(ui->IO8_PushButton->getCheck() == false)
    {
        root["IO8_out"] = 1;
        ui->IO8_PushButton->setCheck(true);
    }
    root["IO8"] = "IO8";
    Nextp::getInstance()->sendMessage(Nextp::GetSecondUserCommand,QByteArray().append(QString::fromStdString(wt.write(root))));
}
//IO3
void SettingParaWidget::on_IO3_PushButton_clicked()
{
    Json::Value root;
    Json::FastWriter wt;
    if(ui->IO3_PushButton->getCheck() == true)
    {
        root["IO3_out"] = 0;
        ui->IO3_PushButton->setCheck(false);
    }
    else if(ui->IO3_PushButton->getCheck() == false)
    {
        root["IO3_out"] = 1;
        ui->IO3_PushButton->setCheck(true);
    }
    root["IO3"] = "IO3";
    Nextp::getInstance()->sendMessage(Nextp::GetSecondUserCommand,QByteArray().append(QString::fromStdString(wt.write(root))));
}

//DIN_IO1
void SettingParaWidget::on_IO1_in_PushButton_clicked()
{
    {
        Json::Value root;
        Json::FastWriter wt;
        if(ui->IO1_in_PushButton->getCheck() == true)
        {
            root["IO1_in_out"] = 0;
            ui->IO1_in_PushButton->setCheck(false);

        }
        else if(ui->IO1_PushButton->getCheck() == false)
        {
            root["IO1_in_out"] = 1;
            ui->IO1_in_PushButton->setCheck(true);

        }
        root["IO1_in"] = "IO1_in";
        Nextp::getInstance()->sendMessage(Nextp::GetSecondUserCommand,QByteArray().append(QString::fromStdString(wt.write(root))));

    }
}
//DIN_IO2
void SettingParaWidget::on_IO2_in_PushButton_clicked()
{
    {
        Json::Value root;
        Json::FastWriter wt;
        if(ui->IO2_in_PushButton->getCheck() == true)
        {
            root["IO2_in_out"] = 0;
            ui->IO2_in_PushButton->setCheck(false);

        }
        else if(ui->IO2_PushButton->getCheck() == false)
        {
            root["IO2_in_out"] = 1;
            ui->IO2_in_PushButton->setCheck(true);

        }
        root["IO2_in"] = "IO2_in";
        Nextp::getInstance()->sendMessage(Nextp::GetSecondUserCommand,QByteArray().append(QString::fromStdString(wt.write(root))));

    }
}
//DIN_IO3
void SettingParaWidget::on_IO3_in_PushButton_clicked()
{
    {
        Json::Value root;
        Json::FastWriter wt;
        if(ui->IO3_in_PushButton->getCheck() == true)
        {
            root["IO3_in_out"] = 0;
            ui->IO3_in_PushButton->setCheck(false);

        }
        else if(ui->IO3_PushButton->getCheck() == false)
        {
            root["IO3_in_out"] = 1;
            ui->IO3_in_PushButton->setCheck(true);

        }
        root["IO3_in"] = "IO3_in";
        Nextp::getInstance()->sendMessage(Nextp::GetSecondUserCommand,QByteArray().append(QString::fromStdString(wt.write(root))));

    }
}
//DIN_IO4
void SettingParaWidget::on_IO4_in_PushButton_clicked()
{
    {
        Json::Value root;
        Json::FastWriter wt;
        if(ui->IO4_in_PushButton->getCheck() == true)
        {
            root["IO4_in_out"] = 0;
            ui->IO4_in_PushButton->setCheck(false);

        }
        else if(ui->IO4_PushButton->getCheck() == false)
        {
            root["IO4_in_out"] = 1;
            ui->IO4_in_PushButton->setCheck(true);

        }
        root["IO4_in"] = "IO4_in";
        Nextp::getInstance()->sendMessage(Nextp::GetSecondUserCommand,QByteArray().append(QString::fromStdString(wt.write(root))));

    }
}
//DIN_IO5
void SettingParaWidget::on_IO5_in_PushButton_clicked()
{
    {
        Json::Value root;
        Json::FastWriter wt;
        if(ui->IO5_in_PushButton->getCheck() == true)
        {
            root["IO5_in_out"] = 0;
            ui->IO5_in_PushButton->setCheck(false);

        }
        else if(ui->IO5_PushButton->getCheck() == false)
        {
            root["IO5_in_out"] = 1;
            ui->IO5_in_PushButton->setCheck(true);

        }
        root["IO5_in"] = "IO5_in";
        Nextp::getInstance()->sendMessage(Nextp::GetSecondUserCommand,QByteArray().append(QString::fromStdString(wt.write(root))));

    }
}

//IO end
//******************modify修改********************
void SettingParaWidget::on_shell_modify_clicked()
{
    //***param
    if(ui->head_label->text() == tr("参数设定"))
    {
        if(ui->shell_modify->text()==tr("修改"))
        {
            ui->absorb_Time->setEnabled(true);
            ui->lengthways_Time->setEnabled(true);
            ui->across_Time->setEnabled(true);
            ui->pushing_Time->setEnabled(true);
//            ui->shell_returnButton->setEnabled(false);
            ui->shell_modify->setText("保存");
        }
        else
        {
            bool ok = true;
            if(ui->absorb_Time->text().toDouble(&ok)<0.01||ui->absorb_Time->text().toDouble(&ok)>5||ok == false)
            {
                Nextp::getInstance()->showSnackbarMessage("吸面纸时间超限（ 0.01 ～ 5.00 ）", 3000);
                return;
            }
            if(ui->lengthways_Time->text().toDouble(&ok)<0.01||ui->lengthways_Time->text().toDouble(&ok)>5||ok == false)
            {
                Nextp::getInstance()->showSnackbarMessage("纵向推气机延时超限（0.01～ 5.00 ）", 3000);
                return;
            }
            if(ui->across_Time->text().toDouble(&ok)<0.01||ui->across_Time->text().toDouble(&ok)>5||ok == false)
            {
                Nextp::getInstance()->showSnackbarMessage("横向推气机延时超限（ 0.01 ～ 5.00 ）", 3000);
                return;
            }
            if(ui->pushing_Time->text().toDouble(&ok) <0.01 ||ui->pushing_Time->text().toDouble(&ok)>10||ok == false)
            {
                Nextp::getInstance()->showSnackbarMessage("下压推气机延时超限（ 0.01 ～ 5.00 ）", 3000);
                return;
            }
            Json::Value root;
            Json::FastWriter wt;
            root["Time"]["absorb_Time"] = ui->absorb_Time->text().toDouble();
            root["Time"]["lengthways_Time"] = ui->lengthways_Time->text().toDouble();
            root["Time"]["across_Time"] = ui->across_Time->text().toDouble();
            root["Time"]["pushing_Time"] = ui->pushing_Time->text().toDouble();
            root["robot"]["coormode"] = ui->comboBox->currentIndex();
            root["robot_Param"] = "robot_Param";
            //            root["robot"]["coormode"] = ui->comboBox->currentText().toDouble();//坐标mode
            Nextp::getInstance()->sendMessage(Nextp::SetFirstUserParaCommand,QByteArray().append(QString::fromStdString(wt.write(root))));
            Nextp::getInstance()->sendMessage(Nextp::GetFirstUserCommand,QByteArray().append("参数设定"));//messges

            emit SettingParaWidget::on_sign_ok_clicked();
            ui->shell_modify->setText("修改");
            //             ui->shell_returnButton->setEnabled(true);
            ui->absorb_Time->setEnabled(false);
            ui->lengthways_Time->setEnabled(false);
            ui->across_Time->setEnabled(false);
            ui->pushing_Time->setEnabled(false);

        }
    }
    //param  end
}
//修改坐标类型名称
void SettingParaWidget::on_comboBox_currentIndexChanged(const QString &arg1)
{
    if(arg1 == "关节")
    {
        ui->X->setText("J1");
        ui->Y->setText("J2");
        ui->Z->setText("J3");
        ui->A->setText("J4");
        ui->B->setText("J5");
        ui->C->setText("J6");
    }
    if(arg1 == "用户"||arg1 == "工具"||arg1 == "直角")
    {
        ui->X->setText("X");
        ui->Y->setText("Y");
        ui->Z->setText("Z");
        ui->A->setText("A");
        ui->B->setText("B");
        ui->C->setText("C");
    }
}
//实时的槽函数
void SettingParaWidget::slot_getPos()
{
    Nextp::getInstance()->sendMessage(Nextp::SetSecondUserParaCommand,QByteArray().append(ui->comboBox->currentText()));
}
//*********real time CoorPos*****End****
//***选择标记点
void SettingParaWidget::on_btn_startPos_clicked()
{
    ui->selected_Pos->setText("起点");
    sign = true;
    if(Nextp::getInstance()->getAccount() == "技术员" ||Nextp::getInstance()->getAccount() == "管理员")
    {
    }
    emit SettingParaWidget::sign_prime_pos();
}
void SettingParaWidget::on_exc_pos_1_clicked()
{
    ui->selected_Pos->setText("过渡点1");
    if(Nextp::getInstance()->getAccount() == "技术员" ||Nextp::getInstance()->getAccount() == "管理员")
    {
        if(judge_exc_1)
        {

        }
        else
        {

        }
    }
    emit SettingParaWidget::sign_minor_pos();
}
void SettingParaWidget::on_exc_pos_2_clicked()
{
    ui->selected_Pos->setText("过渡点2");
    if(Nextp::getInstance()->getAccount() == "技术员" ||Nextp::getInstance()->getAccount() == "管理员")
    {
        if(judge_exc_2)
        {

        }
        else
        {

        }
    }
    emit SettingParaWidget::sign_minor_pos();
}
void SettingParaWidget::on_absorb_paperPos_clicked()
{
     ui->selected_Pos->setText("取料点");
     if(Nextp::getInstance()->getAccount() == "技术员" ||Nextp::getInstance()->getAccount() == "管理员")
     {

     }
     sign = true;
     emit SettingParaWidget::sign_prime_pos();
}
void SettingParaWidget::on_exc_pos_3_clicked()
{
    ui->selected_Pos->setText("过渡点3");
    if(Nextp::getInstance()->getAccount() == "技术员" ||Nextp::getInstance()->getAccount() == "管理员")
    {
        if(judge_exc_3)
        {

        }
        else
        {

        }
    }
    emit SettingParaWidget::sign_minor_pos();
}
void SettingParaWidget::on_exc_pos_4_clicked()
{
    ui->selected_Pos->setText("过渡点4");
    if(Nextp::getInstance()->getAccount() == "技术员" ||Nextp::getInstance()->getAccount() == "管理员")
    {
        if(judge_exc_4)
        {
        }
        else
        {

        }
    }
    emit SettingParaWidget::sign_minor_pos();
}
void SettingParaWidget::on_box_setPos_clicked()
{
     ui->selected_Pos->setText("套盒点");
     if(Nextp::getInstance()->getAccount() == "技术员" ||Nextp::getInstance()->getAccount() == "管理员")
     {

     }
      emit SettingParaWidget::sign_prime_pos();
}
void SettingParaWidget::on_exc_pos_5_clicked()
{
    ui->selected_Pos->setText("过渡点5");
    if(Nextp::getInstance()->getAccount() == "技术员" ||Nextp::getInstance()->getAccount() == "管理员")
    {
        if(judge_exc_5)
        {

        }
        else
        {

        }
    }
    emit SettingParaWidget::sign_minor_pos();
}
void SettingParaWidget::on_exc_pos_6_clicked()
{
    ui->selected_Pos->setText("过渡点6");
    if(Nextp::getInstance()->getAccount() == "技术员" ||Nextp::getInstance()->getAccount() == "管理员")
    {
        if(judge_exc_6)
        {

        }
        else
        {

        }
    }
     emit SettingParaWidget::sign_minor_pos();
}
void SettingParaWidget::on_btn_stopPos_clicked()
{
     ui->selected_Pos->setText("结束点");
     if(Nextp::getInstance()->getAccount() == "技术员" ||Nextp::getInstance()->getAccount() == "管理员")
     {

     }
      emit SettingParaWidget::sign_prime_pos();
}
//选择标记点__endl
//***管理过渡点
//void SettingParaWidget::on_exc_manage_clicked()
//{
//    if(ui->selected_Pos->text() == "过渡点1" || ui->selected_Pos->text() == "过渡点2"||ui->selected_Pos->text() == "过渡点3"||ui->selected_Pos->text() == "过渡点4"||ui->selected_Pos->text() == "过渡点5"||ui->selected_Pos->text() == "过渡点6")
//    {
//        ui->exc_wid->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);//弹出新窗口之后旧窗口不可点
//        ui->exc_wid->setWindowModality(Qt::WindowModal);
//        ui->exc_wid->show();
//        ui->exc_wid->move(330, 220);
//    }
//}
//管理过渡点__endl
//***添加为过渡点弹窗
//cancel pos
void SettingParaWidget::on_exc_cancel_clicked()
{
    if(ui->selected_Pos->text() == "过渡点1")
    {
        ui->exc_pos_1->setStyleSheet("QPushButton{ font: 11pt ;border-radius:8px;background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 rgb(240,240,240),stop:1 rgb(220,220,220));}");
        judge_exc_1 = false;
        emit SettingParaWidget::on_exc_pos_1_clicked();// 更新是否选中为过度点
    }
    if(ui->selected_Pos->text() == "过渡点2")
    {
        ui->exc_pos_2->setStyleSheet("QPushButton{ font: 11pt ;border-radius:8px;background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 rgb(240,240,240),stop:1 rgb(220,220,220));}");
        judge_exc_2 = false;
        emit SettingParaWidget::on_exc_pos_2_clicked();
    }
    if(ui->selected_Pos->text() == "过渡点3")
    {
        ui->exc_pos_3->setStyleSheet("QPushButton{ font: 11pt ;border-radius:8px;background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 rgb(240,240,240),stop:1 rgb(220,220,220));}");
        judge_exc_3 = false;
        emit SettingParaWidget::on_exc_pos_3_clicked();
    }
    if(ui->selected_Pos->text() == "过渡点4")
    {
        ui->exc_pos_4->setStyleSheet("QPushButton{ font: 11pt ;border-radius:8px;background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 rgb(240,240,240),stop:1 rgb(220,220,220));}");
        judge_exc_4 = false;
        emit SettingParaWidget::on_exc_pos_4_clicked();
    }
    if(ui->selected_Pos->text() == "过渡点5")
    {
        ui->exc_pos_5->setStyleSheet("QPushButton{ font: 11pt ;border-radius:8px;background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 rgb(240,240,240),stop:1 rgb(220,220,220));}");
        judge_exc_5 = false;
        emit SettingParaWidget::on_exc_pos_5_clicked();
    }
    if(ui->selected_Pos->text() == "过渡点6")
    {
        ui->exc_pos_6->setStyleSheet("QPushButton{ font: 11pt ;border-radius:8px;background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 rgb(240,240,240),stop:1 rgb(220,220,220));}");
        judge_exc_6 = false;
        emit SettingParaWidget::on_exc_pos_6_clicked();
    }
    ui->exc_wid->hide();

    emit SettingParaWidget::on_sign_ok_clicked();
}
//add pos
void SettingParaWidget::on_exc_ok_clicked()
{
    if(ui->selected_Pos->text() == "过渡点1")
    {
        ui->exc_pos_1->setStyleSheet("QPushButton{background-color: rgb(11, 255, 68); font: 11pt ; border-radius:8px;}");
        judge_exc_1 = true;
        emit SettingParaWidget::on_exc_pos_1_clicked();
    }
    if(ui->selected_Pos->text() == "过渡点2")
    {
         ui->exc_pos_2->setStyleSheet("QPushButton{background-color: rgb(11, 255, 68); font: 11pt ; border-radius:8px;}");
         judge_exc_2 = true;
         emit SettingParaWidget::on_exc_pos_2_clicked();
    }
    if(ui->selected_Pos->text() == "过渡点3")
    {
        ui->exc_pos_3->setStyleSheet("QPushButton{background-color: rgb(11, 255, 68); font: 11pt ; border-radius:8px;}");
        judge_exc_3 = true;
        emit SettingParaWidget::on_exc_pos_3_clicked();
    }
    if(ui->selected_Pos->text() == "过渡点4")
    {
        ui->exc_pos_4->setStyleSheet("QPushButton{background-color: rgb(11, 255, 68); font: 11pt ; border-radius:8px;}");
        judge_exc_4 = true;
        emit SettingParaWidget::on_exc_pos_4_clicked();
    }
    if(ui->selected_Pos->text() == "过渡点5")
    {
        ui->exc_pos_5->setStyleSheet("QPushButton{background-color: rgb(11, 255, 68); font: 11pt ; border-radius:8px;}");
        judge_exc_5 = true;
        emit SettingParaWidget::on_exc_pos_5_clicked();
    }
    if(ui->selected_Pos->text() == "过渡点6")
    {
        ui->exc_pos_6->setStyleSheet("QPushButton{background-color: rgb(11, 255, 68); font: 11pt ; border-radius:8px;}");
        judge_exc_6 = true;
        emit SettingParaWidget::on_exc_pos_6_clicked();
    }

    if( Nextp::getInstance()->getServoStatus() == 0|| Nextp::getInstance()->getServoStatus() == 1)//必须是伺服下电才可以插入作业文件
    {
        ui->exc_wid->hide();
    }
    emit SettingParaWidget::on_sign_ok_clicked();
}
//添加为过渡点弹窗___endl
//选择标记点___end

//seed sign Pos****
//void SettingParaWidget::on_btn_sign_Pos_clicked()
//{
//    ui->sign_wid->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);//弹出新窗口之后旧窗口不可点
//    ui->sign_wid->setWindowModality(Qt::WindowModal);
//    ui->sign_wid->show();
//    ui->sign_wid->move(330, 220);
//}

//槽函数
void SettingParaWidget::sign_prime_pos()
{
    ui->sign_wid->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);//弹出新窗口之后旧窗口不可点
    ui->sign_wid->setWindowModality(Qt::WindowModal);
    ui->sign_wid->show();
    ui->sign_wid->move(330, 180);
}
 void SettingParaWidget::sign_minor_pos()
 {
     if(ui->selected_Pos->text() == "过渡点1" || ui->selected_Pos->text() == "过渡点2"||ui->selected_Pos->text() == "过渡点3"||ui->selected_Pos->text() == "过渡点4"||ui->selected_Pos->text() == "过渡点5"||ui->selected_Pos->text() == "过渡点6")
     {
         ui->exc_wid->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);//弹出新窗口之后旧窗口不可点
         ui->exc_wid->setWindowModality(Qt::WindowModal);
         ui->exc_wid->show();
         ui->exc_wid->move(330, 180);
     }
 }
//槽函数___endl

//seed run pos****
void SettingParaWidget::on_run_select_Pos_clicked()
{
    Nextp::getInstance()->sendMessage(Nextp::GetThirdUserCommand,QByteArray().append( ui->selected_Pos->text()));
}
//end seed sign Pos****

//********运行模式按钮
void SettingParaWidget::on_mian_Run_Mode_clicked()
{
    if(ui->mian_Run_Mode->text() == "单次运行")
    {
        ui->mian_Run_Mode->setText("循环运行");
    }
    else
    {
        ui->mian_Run_Mode->setText("单次运行");
    }
}
//********启动按钮
void SettingParaWidget::on_mian_Start_clicked()
{
//    ui->mian_Stop->setText("暂停");
    ui->main_Reset->setText("停止");
    Nextp::getInstance()->sendMessage(Nextp::GetFourthUserCommand,QByteArray().append(ui->mian_Run_Mode->text()));
}
//***继续/暂停
void SettingParaWidget::on_mian_Stop_clicked()
{
    if(ui->mian_Stop->text() == "暂停")
    {
        Nextp::getInstance()->sendMessage(Nextp::SetFifthUserParaCommand,QByteArray().append(ui->mian_Stop->text()));
        ui->mian_Stop->setText("继续");
    }
    else
    {
        Nextp::getInstance()->sendMessage(Nextp::SetFifthUserParaCommand,QByteArray().append(ui->mian_Stop->text()));
        ui->mian_Stop->setText("暂停");
    }
}
//***停止/复位
void SettingParaWidget::on_main_Reset_clicked()
{
    ui->mian_Stop->setText("暂停");
    if(ui->main_Reset->text() == "停止")
    {
        Nextp::getInstance()->sendMessage(Nextp::SetFifthUserParaCommand,QByteArray().append(ui->main_Reset->text()));
    }
}
//复位
void SettingParaWidget::on_main_Reset_2_clicked()
{
    if(Nextp::getInstance()->getOperationMode() == 2)
    {
        ui->reset_wid->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);//弹出新窗口之后旧窗口不可点
        ui->reset_wid->setWindowModality(Qt::WindowModal);
        ui->reset_wid->show();
        ui->reset_wid->move(150, 220);
    }
    else
    {
        Nextp::getInstance()->showSnackbarMessage("请在运行模式下进行复位",2000);
    }
}
void SettingParaWidget::on_reset_ok_clicked()
{
    Nextp::getInstance()->sendMessage(Nextp::SetFifthUserParaCommand,QByteArray().append(ui->main_Reset_2->text()));
    ui->reset_wid->hide();
}
//复位__endl
//清除总产量
void SettingParaWidget::on_clear_sum_clicked()
{
    Nextp::getInstance()->sendMessage(Nextp::SetFifthUserParaCommand,QByteArray().append(ui->clear_sum->text()));
}

//标记该点的弹窗取消
void SettingParaWidget::on_sign_cancel_clicked()
{
    ui->sign_wid->hide();
}

//标记该点的弹窗确认
void SettingParaWidget::on_sign_ok_clicked()
{
    Json::Value root;
    Json::FastWriter wt;

    root["Point"] = ui->selected_Pos->text().toStdString();
    //过渡点1
    if(judge_exc_1)
    {
          root["judge_exc_1"]  = 1;
    }
    else
    {
         root["judge_exc_1"]  = 0;
    }
    //过渡点2
    if(judge_exc_2)
    {
          root["judge_exc_2"]  = 1;
    }
    else
    {
         root["judge_exc_2"]  = 0;
    }
    //过渡点3
    if(judge_exc_3)
    {
          root["judge_exc_3"]  = 1;
    }
    else
    {
         root["judge_exc_3"]  = 0;
    }
    //过渡点4
    if(judge_exc_4)
    {
          root["judge_exc_4"]  = 1;
    }
    else
    {
         root["judge_exc_4"]  = 0;
    }
    //过渡点5
    if(judge_exc_5)
    {
          root["judge_exc_5"]  = 1;
    }
    else
    {
         root["judge_exc_5"]  = 0;
    }
    //过渡点6
    if(judge_exc_6)
    {
          root["judge_exc_6"]  = 1;
    }
    else
    {
         root["judge_exc_6"]  = 0;
    }
    root["unaffected_pos"]= 1;
    //判断是在那种状态下
    if(ui->test->text() == "调试状态")
    {
        root["check"]=1;
    }
    else if(ui->test->text() == "运行状态")
    {
        root["check"]=0;
    }
    Nextp::getInstance()->sendMessage(Nextp::SetThirdUserParaCommand,QByteArray().append(QString::fromStdString(wt.write(root))));
   if( Nextp::getInstance()->getServoStatus() == 0|| Nextp::getInstance()->getServoStatus() == 1)//必须是伺服下电才可以插入作业文件
   {
       ui->sign_wid->hide();
   }
}
//报警清除
void SettingParaWidget::on_main_Reset_3_clicked()
{
    if(ui->IO3_PushButton->getCheck() == true)
    {
        emit SettingParaWidget::on_IO3_PushButton_clicked();
    }
}
//close exc window
void SettingParaWidget::on_exc_exit_clicked()
{
    ui->exc_wid->hide();
}
//close sign window
void SettingParaWidget::on_sign_exit_clicked()
{
    ui->sign_wid->hide();
}
//close reset window
void SettingParaWidget::on_reset_exit_clicked()
{
    ui->reset_wid->hide();
}
//close reset window
void SettingParaWidget::on_reset_cancel_clicked()
{
     ui->reset_wid->hide();
}

//高级模式
void SettingParaWidget::on_btn_advanced_clicked()
{
    this->close();
     _pPostime->stop();
    Nextp::getInstance()->userpageisOpen(0);
}

//切换状态(运行状态/调试状态)
void SettingParaWidget::on_test_clicked()
{
    Json::Value root;
    Json::FastWriter wt;
    if(ui->test->text() == "运行状态")
    {
        root["check"]=1;
        ui->test->setText("调试状态");
    }
    else
    {
        root["check"]=0;
        ui->test->setText("运行状态");
    }
    root["unaffected_pos"]= 0;
    Nextp::getInstance()->sendMessage(Nextp::SetThirdUserParaCommand,QByteArray().append(QString::fromStdString(wt.write(root))));
}
//参数保存提醒
void SettingParaWidget::on_param_ok_clicked()
{
    emit SettingParaWidget::on_shell_modify_clicked();
    if(Nextp::getInstance()->getAccount() == "管理员")
    {
        ui->clear_sum->show();
        ui->btn_advanced->show();
    }
    ui->stackedWidget->setCurrentWidget(ui->mian);
    ui->shell_adnanced->show();
    ui->shell_modify->hide();
    ui->shell_returnButton->hide();
    ui->param_wid->hide();
    ui->head_label->setText("主界面");
}
void SettingParaWidget::on_param_ok_2_clicked()
{
    ui->param_wid->hide();
    if(Nextp::getInstance()->getAccount() == "管理员")
    {
        ui->clear_sum->show();
        ui->btn_advanced->show();
    }
    ui->stackedWidget->setCurrentWidget(ui->mian);
    ui->shell_adnanced->show();
    ui->shell_modify->hide();
    ui->shell_returnButton->hide();
    Nextp::getInstance()->sendMessage(Nextp::GetFirstUserCommand,QByteArray().append("参数设定"));//messges
    ui->head_label->setText("主界面");
    ui->shell_modify->setText("修改");
}
void SettingParaWidget::on_param_exit_clicked()
{
    ui->param_wid->hide();
    if(Nextp::getInstance()->getAccount() == "管理员")
    {
        ui->clear_sum->show();
        ui->btn_advanced->show();
    }
    ui->stackedWidget->setCurrentWidget(ui->mian);
    ui->shell_adnanced->show();
    ui->shell_modify->hide();
    ui->shell_returnButton->hide();
    Nextp::getInstance()->sendMessage(Nextp::GetFirstUserCommand,QByteArray().append("参数设定"));//messges
    ui->head_label->setText("主界面");
    ui->shell_modify->setText("修改");
}
//参数保存提醒__endl
//试运行
void SettingParaWidget::on_run_allpos_clicked()
{
    Nextp::getInstance()->sendMessage(Nextp::GetFifthUserCommand,QByteArray().append(" "));//messges
}



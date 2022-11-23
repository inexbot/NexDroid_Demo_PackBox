#ifndef SETTINGPARAWIDGET_H
#define SETTINGPARAWIDGET_H

#include <QStackedWidget>
#include "nextp.h"
#include <QPointer>
#include <QDebug>
#include "digitallineedit.h"
#include "lineeditwidget.h"
#include "json/json.h"
#include <QTimer>
#include <QPushButton>
#include"switchbutton.h"
struct poslist
{
    QVector< double > pos;
    int coord;
};

namespace Ui {
class SettingParaWidget;
}

class SettingParaWidget : public QStackedWidget
{
    Q_OBJECT

public:
    static QPointer<SettingParaWidget> getInstance();
    static QPointer<SettingParaWidget> _pInstance;
    ~SettingParaWidget();
    static void sendStartData(QString jobname);
    static void pressReserveButton();
    void slot_receiveMessage(const quint16 &command,const QByteArray &data);


private slots:
    void on__pPara1ReturnBtn_clicked();

    void on__pPara1NextPageBtn_clicked();

    void on__pPara2UpPageBtn_clicked();

//    void on__pParamodifyBtn_clicked();

    void slot_closeMyWidget();

//    void slot_receiveCurrentPos(const QVector< double > pos, const int coord, const int robot, const int config);

    void slot_receiveIoDigitDinState(const QVector< int > io1dinstatus, const QVector< int > io2dinstatus, const QVector< int > io3dinstatus, const QVector< int >io4dinstatus);
    void slot_receiveIoDigitOutputState(const QVector< int > io1doutstatus, const QVector< int > io2doutstatus, const QVector< int > io3doutstatus, const QVector< int >io4doutstatus);

    void on__pParamodifyBtn_2_clicked();

    void on__pParamodifyBtn_3_clicked();

//    void on__pParamodifyBtn_4_clicked();

    void on_btn_ioConfig_clicked();

    void on_btn_ioInputSxtatus_clicked();

    void slot_getIoInputStatus();

   void slot_getPos();//发送实时的坐标系

//    void on_btn_setIoOutput_clicked();

    void on_passwordButton_clicked();

    void getAccount();

    void on_btn_Poswidget_clicked();

    void on_btn_Paramwidget_clicked();

    void on_btn_IOwidget_clicked();

    void on_shell_returnButton_clicked();

    void on_account_list_currentIndexChanged(const QString &arg1);

    void on_shell_adnanced_clicked();





    void on_IO1_PushButton_clicked();

    void on_IO2_PushButton_clicked();

    void on_IO5_PushButton_clicked();

    void on_IO6_PushButton_clicked();

    void on_IO7_PushButton_clicked();

    void on_IO8_PushButton_clicked();



    void on_shell_modify_clicked();


    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_btn_startPos_clicked();

    void on_exc_pos_1_clicked();

    void on_exc_pos_2_clicked();

    void on_absorb_paperPos_clicked();

    void on_exc_pos_3_clicked();

    void on_exc_pos_4_clicked();

    void on_exc_pos_5_clicked();

    void on_exc_pos_6_clicked();

    void on_box_setPos_clicked();

    void on_btn_stopPos_clicked();


//    void on_exc_manage_clicked();

//    void on_btn_sign_Pos_clicked();

    void sign_minor_pos();

    void sign_prime_pos();

    void on_run_select_Pos_clicked();



    void on_mian_Run_Mode_clicked();

    void on_mian_Start_clicked();

    void on_mian_Stop_clicked();

    void on_main_Reset_clicked();






    void on_exc_cancel_clicked();

    void on_exc_ok_clicked();

    void on_main_Reset_2_clicked();



    void on_clear_sum_clicked();

    void on_sign_cancel_clicked();

    void on_sign_ok_clicked();

    void on_main_Reset_3_clicked();

    void on_exc_exit_clicked();

    void on_sign_exit_clicked();

    void on_btn_advanced_clicked();


    void on_IO1_in_PushButton_clicked();

    void on_IO2_in_PushButton_clicked();

    void on_IO3_in_PushButton_clicked();

    void on_IO4_in_PushButton_clicked();

    void on_IO5_in_PushButton_clicked();

    void on_reset_exit_clicked();

    void on_reset_cancel_clicked();

    void on_reset_ok_clicked();


    void on_test_clicked();



    void on_param_ok_clicked();

    void on_param_ok_2_clicked();

    void on_param_exit_clicked();



    void on_IO3_PushButton_clicked();
    

    void on_run_allpos_clicked();



private:
    explicit SettingParaWidget(QWidget *parent = 0);
    Ui::SettingParaWidget *ui;
    QVector< double > _pos;
    int _coord;
    QVector<poslist> _poslist;
    QTimer *_pGetIoInputStatusTimer;
    QTimer *_pPostime;
    QVector<Nextp::IOCONFIG> _ioConfig;
    QString account = "操作员";

    bool sign = false;//点位是否选中

    bool judge_exc_1= false;
    bool judge_exc_2= false;
    bool judge_exc_3= false;
    bool judge_exc_4= false;
    bool judge_exc_5= false;
    bool judge_exc_6= false;
    bool judge_io3 =false;

};

#endif // SETTINGPARAWIDGET_H

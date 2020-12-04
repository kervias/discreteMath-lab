#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logiccal.h"
#include <ctype.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    funcType = 0;
    instruction1 = "输入两个命题变元的真值，求它们的合取、析取、条件和双条件的真值";
    instruction2 = "求任意一个命题公式的真值表，并根据真值表求主范式。\n"
                   "注意：命题变元在a - z中选取，变元个数不要超过20个\n，或运算用|，与运算用&，非运算用!,蕴含运算用>,等价运算用=";
     ui->setupUi(this);


     ui->tBInstruct->setText(instruction1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString  MainWindow::transForm(int i){
    if(i >= 1) return "T";
    if(i == 0) return "F";
    return "WA";
}

int MainWindow::judgeExpression(QString &Qstr){
    if(Qstr.size() == 0) return -1;
    for(int i = 0; i < Qstr.size(); i++){
        if(Qstr[i].isLetter() ){
            Qstr[i] = Qstr[i].toLower();
        }
    }
    return 1;
}

void MainWindow::on_CBfuncType_activated(int index)   //控制当前的功能
{
    funcType = index;
    if(index == 0){
        ui->tBInstruct->setText(instruction1);
        ui->tBResult->setText(" ");
        ui->lineEditP->setEnabled(true);
        ui->lineEditQ->setEnabled(true);
    }
    else{
        ui->tBInstruct->setText(instruction2);
        ui->tBResult->setText(" ");
         ui->lineEditP->setEnabled(false);
         ui->lineEditQ->setEnabled(false);
    }
}

void MainWindow::on_BTCalculate_released()
{
    QString tmp1,tmp2;
    if(funcType == 0)//实现功能一
    {
        tmp1 = ui->lineEditP->text();
        tmp2 = ui->lineEditQ->text();

        //判断P输入的合法性
        if(tmp1 == "F") P = 0;
        else if(tmp1 == "T"){
            P = 1;
        }
        else{
            ui->tBResult->setText("P的输入不合法");
            return;
        }

        //判断Q输入的合法性
        if(tmp2 == "F") Q = 0;
        else if(tmp2 == "T"){
            Q = 1;
        }
        else{
            ui->tBResult->setText("Q的输入不合法");
            return;
        }
        tmp1 = ui->lineEditExpress->text();
        int executeable = judgeExpression(tmp1);
        int a,b,c,d,e;
        LogicCal lc(tmp1,P,Q);
        lc.LogicFunc1(a,b,c,d,e);
        Result = "P析取Q为"+transForm(a)+"\nP合取Q为"+transForm(b)+"\nP条件Q为"+transForm(c)+"\nP双条件Q为"+transForm(d) +"\nP异或Q为"+transForm(e); 
        if(executeable == -1)  //如果表达式输入正确,就将表达式传入计算类，同时传入计算类型，-1为输入为空,0为表达式错误，1为表达式正确
        {
            Result += "\n表达式输入为空";
        }
        else{
            if(executeable == 0) Result += "\n表达式输入不正确";
            else {
                lc.process();
                Result += "\n表达式的结果为"+transForm(lc.CalLstr());
            }

        }
        ui->tBResult->setText(Result);
    }
    else  //实现功能二
    {
        Result = "真值表（用0代替False,1代表True)\n";
        tmp1 = ui->lineEditExpress->text();
        int num = judgeExpression(tmp1);
        if(num == -1){
            ui->tBResult->setText("输入表达式为空");
            return;
        }
        if(num == 0){
            ui->tBResult->setText("输入表达式错误");
            return;
        }
        LogicCal lc(tmp1, 0,0);
        lc.LogicFunc2();
        map<QString,int>::iterator it;
        Result += lc.getDyEle() + "  fc\n";
        for(it = lc.mapReImList.begin(); it != lc.mapReImList.end(); it++){
            cout<<it->first.toStdString()<<"  "<<it->second<<endl;
           Result += it->first + "  "+ QString(QChar(char('0'+it->second)))+"\n";
        }
        Result += "主析取范式:\n" + lc.MXParadigm+"\n";
        Result += "主合取范式:\n" + lc.MHParadigm+"\n";
        ui->tBResult->setText(Result);
    }
}

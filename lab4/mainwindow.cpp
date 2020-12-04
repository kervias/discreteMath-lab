#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qdebug.h>

#include <QIntValidator>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    exeable = 0;
    ui->lEDim->setValidator(new QIntValidator(1,MaxDim,this));  //设置维度输入范围

}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::judgeTF(int tmpdim, QString tmpMat){  //判断输入合法性
    ui->tBCompute->setText("");
    ui->tBEnter->setText("");
    exeable = 0;
    if(tmpdim == 0) {
        QMessageBox::warning(this,"维度","维度不能为空",QMessageBox::Ok);  //维度空警告
        return 0;
    }
    if(tmpMat.isEmpty()) {
        QMessageBox::warning(this,"矩阵","矩阵不能为空",QMessageBox::Ok);  //内容空警告
        return 0;
    }

    QStringList tmpList = tmpMat.split(" ");

    /*
    qDebug()<<"****";
    for(int i = 0; i < tmpList.size(); i++){
        for(int j = 0; j < tmpList.at(i).size(); j++){
            qDebug()<<tmpList.at(i)[j];
        }
        //qDebug()<<endl;
    }
    qDebug()<<"****";
    */

    if(tmpList.size() != tmpdim){
        //qDebug()<<"here1";
        QMessageBox::warning(this,"Warning","矩阵与维度不一致",QMessageBox::Ok);
        return 0;
    }

   for(int i = 0; i < tmpList.size(); i++){
       if(tmpList.at(i).size() != tmpdim){
          // qDebug()<<tmpList.at(i).size();
           //qDebug()<<"here2";
           QMessageBox::warning(this,"Warning","矩阵与维度不一致",QMessageBox::Ok);
           return 0;
       }
       for(int j = 0; j < tmpdim; j++){
            if(tmpList.at(i)[j] != '1' && tmpList.at(i)[j] != '0'){
                //qDebug()<<"here3";
                QMessageBox::warning(this,"Warning","矩阵输入非法字符",QMessageBox::Ok);
                return 0;
            }else{
                IMat[i][j] = int(tmpList.at(i)[j].toLatin1() - '0');
            }
       }
   }

    exeable = 1;
    dim = tmpdim;
    InputMat = tmpMat;
    InitMat = tmpList;

    return 1;
}

void MainWindow::ComputeRMat(){   //计算自反闭包
    if(exeable == 0) return;
    for(int i =0 ; i < dim; i++){
        for(int j = 0; j < dim; j++){
            RMat[i][j] = IMat[i][j];
            if(i == j) RMat[i][j] = 1;
        }
    }
}

void MainWindow::ComputeSMat(){  //计算对称闭包
    if(exeable == 0) return;
    for(int i =0 ; i < dim; i++){
        for(int j = 0; j < dim; j++){
            SMat[i][j] = IMat[i][j] + IMat[j][i];
            //if(SMat[i][j] == 2) SMat[i][j] = 1;
        }
    }
}

void MainWindow::ComputeTMat(){  //计算传递闭包
    if(exeable == 0) return;
    for (int i = 0;i < dim;i++)  {
         for (int j = 0;j < dim;j++)  {
             TMat[i][j] = IMat[i][j];
         }
    }
    for (int i = 0;i < dim;i++)  {
         for (int j = 0;j < dim;j++)  {
             if(TMat[j][i]) {
                 for(int k = 0;k < dim;k++)
                     TMat[j][k] = TMat[j][k] + TMat[i][k];
             }
         }
    }
}

void MainWindow::on_BtEnter_released()
{
    int tmpdim = ui->lEDim->text().toInt();  //获取维度
    QString tmps = ui->tEInput->toPlainText();  //获取矩阵
    QString tmpQst = "";
    if(judgeTF(tmpdim,tmps)){
        tmpQst = "";
        for(int i = 0; i < dim; i++){
           for(int j = 0; j < dim; j++){
               tmpQst += InitMat[i][j] + "   ";
           }
           tmpQst +=  "\n";
        }
        ui->tBEnter->setText(tmpQst);
    }

}

void MainWindow::on_BtCompute_released()
{
    if(exeable == 0){
        QMessageBox::warning(this,"Warning","请确认矩阵",QMessageBox::Ok);
        return;
    }
    ComputeRMat();
    ComputeSMat();
    ComputeTMat();

    QString tmpQst = "自反闭包:\n";
    for(int i = 0; i < dim; i++){
       for(int j = 0; j < dim; j++){
           tmpQst += QString::number(RMat[i][j]) + "   ";
       }
       tmpQst +=  "\n";
    }

    tmpQst += "对称闭包:\n";
    for(int i = 0; i < dim; i++){
       for(int j = 0; j < dim; j++){
           tmpQst += QString::number(SMat[i][j]) + "   ";
       }
       tmpQst +=  "\n";
    }

    tmpQst += "传递闭包:\n";
    for(int i = 0; i < dim; i++){
       for(int j = 0; j < dim; j++){
           tmpQst += QString::number(TMat[i][j]) + "   ";
       }
       tmpQst +=  "\n";
    }
//01001 10000 00001 01001 10010
    ui->tBCompute->setText(tmpQst);
}

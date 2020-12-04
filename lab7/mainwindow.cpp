#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    funcType = None;
    ui->setupUi(this);
    ui->DrawWidget->root = this;
    curMoveVertex = -1;
    ui->curFunc->setEnabled(false);
    ui->curFunc->setText("None");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btAddEdge_clicked()
{
    for(int i = 0; i < ui->DrawWidget->vecVer.size(); i++){
        ui->DrawWidget->vecVer[i]->setStyleSheet("background-color:orange");
    }
    ui->textBrowser->setText("");
    while(!curDelEdge.empty()) curDelEdge.pop();
    funcType = addEdge;
    ui->curFunc->setText("添加边");
}

void MainWindow::on_btAddVertex_clicked()
{
    for(int i = 0; i < ui->DrawWidget->vecVer.size(); i++){
        ui->DrawWidget->vecVer[i]->setStyleSheet("background-color:orange");
    }
    ui->textBrowser->setText("");
    while(!curAddEdge.empty()) curAddEdge.pop();
    while(!curDelEdge.empty()) curDelEdge.pop();

    funcType = addVertex;
    ui->curFunc->setText("添加顶点");
}

void MainWindow::on_btDelVertex_clicked()
{
    for(int i = 0; i < ui->DrawWidget->vecVer.size(); i++){
        ui->DrawWidget->vecVer[i]->setStyleSheet("background-color:orange");
    }
    ui->textBrowser->setText("");
    while(!curAddEdge.empty()) curAddEdge.pop();
    while(!curDelEdge.empty()) curDelEdge.pop();
    funcType = DelVertex;
    ui->curFunc->setText("删除顶点");
}

void MainWindow::on_btMove_clicked()
{
    for(int i = 0; i < ui->DrawWidget->vecVer.size(); i++){
        ui->DrawWidget->vecVer[i]->setStyleSheet("background-color:orange");
    }
    ui->textBrowser->setText("");
    while(!curAddEdge.empty()) curAddEdge.pop();
    while(!curDelEdge.empty()) curDelEdge.pop();
    funcType =Vmove;
    ui->curFunc->setText("移动顶点");
}

void MainWindow::on_btDelEdge_clicked()
{
    for(int i = 0; i < ui->DrawWidget->vecVer.size(); i++){
        ui->DrawWidget->vecVer[i]->setStyleSheet("background-color:orange");
    }
    ui->textBrowser->setText("");
    while(!curAddEdge.empty()) curAddEdge.pop();
    funcType =DelEdge;
    ui->curFunc->setText("删除边");
}

void MainWindow::on_btComp_clicked()
{
    while(!curAddEdge.empty()) curAddEdge.pop();
    while(!curDelEdge.empty()) curDelEdge.pop();
    funcType = Calcu;
    ui->curFunc->setText("计算");
    int b = ui->DrawWidget->DFSWay();
    switch(b){
    case 0:{
         ui->textBrowser->setText("该图无边");
         break;
    }
    case 1:{
        QString s1 = "",s2 = "";
        int m = ui->DrawWidget->staDfs.top();
        while(ui->DrawWidget->staDfs.size() != 1){
            s1 = " -> v" + QString::number(ui->DrawWidget->staDfs.top()) + s1;
            ui->DrawWidget->staDfs.pop();
        }
        int n = ui->DrawWidget->staDfs.top();
        ui->DrawWidget->staDfs.pop();
        ui->DrawWidget->vecVer[m-1]->setStyleSheet("background-color:green");
        ui->DrawWidget->vecVer[n-1]->setStyleSheet("background-color:blue");
        s1 = "v" + QString::number(n) + s1;
        s1 = "DFS欧拉通路求解结果：\n" + s1;

       m = ui->DrawWidget->staFleury.top();
        while(ui->DrawWidget->staFleury.size() != 1){
            s2 = " -> v" + QString::number(ui->DrawWidget->staFleury.top()) + s2;
            ui->DrawWidget->staFleury.pop();
        }
        n = ui->DrawWidget->staFleury.top();
        ui->DrawWidget->staFleury.pop();
        ui->DrawWidget->vecVer[m-1]->setStyleSheet("background-color:red");
        ui->DrawWidget->vecVer[n-1]->setStyleSheet("background-color:gray");
        s2 = "v" + QString::number(n) + s2;
        s2 = "Fleury欧拉通路求解结果：\n" + s2;



        ui->textBrowser->setText(s1+"\n"+s2);
        break;
    }
    case 2:{
        QString s1 = "",s2 = "";
        while(ui->DrawWidget->staDfs.size() != 1){
            s1 = " -> v" + QString::number(ui->DrawWidget->staDfs.top()) + s1;
            ui->DrawWidget->staDfs.pop();
        }
        int n = ui->DrawWidget->staDfs.top();
        ui->DrawWidget->staDfs.pop();
       // ui->DrawWidget->vecVer[m-1]->setStyleSheet("color:green");
        ui->DrawWidget->vecVer[n-1]->setStyleSheet("background-color:blue");
        s1 = "v" + QString::number(n) + s1;
        s1 = "DFS欧拉回路求解结果：\n" + s1;

        qDebug()<<ui->DrawWidget->staFleury.size()<<"***";
        while(ui->DrawWidget->staFleury.size() != 1){
            s2 = " -> v" + QString::number(ui->DrawWidget->staFleury.top()) + s2;
            ui->DrawWidget->staFleury.pop();
        }
        n = ui->DrawWidget->staFleury.top();
        ui->DrawWidget->staFleury.pop();
        //ui->DrawWidget->vecVer[m-1]->setStyleSheet("background-color:red");
        ui->DrawWidget->vecVer[n-1]->setStyleSheet("background-color:gray");
        s2 = "v" + QString::number(n) + s2;
        s2 = "Fleury欧拉回路求解结果：\n" + s2;
        ui->textBrowser->setText(s1 + "\n" + s2);
        break;
    }
    case 3:{
        ui->textBrowser->setText("该图既无欧拉回路也无欧拉通路");
    }
    }

}

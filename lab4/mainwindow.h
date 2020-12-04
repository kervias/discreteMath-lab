#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#define MaxDim 100  //最大维度

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int judgeTF(int tmpdim, QString tmpMat);  //判断输入的正确性
    void ComputeRMat();  //计算自反闭包
    void ComputeSMat();  //计算对称闭包
    void ComputeTMat();  //计算传递闭包


private slots:
    void on_BtEnter_released();

    void on_BtCompute_released();

private:
    Ui::MainWindow *ui;
    int dim;  //矩阵维度,限定最大一百维
    QString InputMat;//矩阵输入
    QStringList InitMat;  //原始矩阵
    bool IMat[MaxDim][MaxDim];
    bool RMat[MaxDim][MaxDim];
    bool SMat[MaxDim][MaxDim];
    bool TMat[MaxDim][MaxDim];
   /* QStringList ReflexMat;  //自反矩阵输出
    QStringList SymMat;  //对称矩阵输出
    QStringList TransMat;  //传递矩阵输出*/
    bool exeable;

};

#endif // MAINWINDOW_H

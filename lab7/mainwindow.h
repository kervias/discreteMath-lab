#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <stack>
using namespace std;

enum CurFuncType{None, addVertex, addEdge, Vmove, DelVertex, DelEdge,Calcu};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    QString s;

    CurFuncType funcType;
    int curMoveVertex;   //若是移动功能激发，记录当前移动顶点编号
    int curDelvert;  //正在删除的结点编号
    stack<int> curAddEdge;
    stack<int> curDelEdge;

private slots:
    void on_btAddEdge_clicked();

    void on_btAddVertex_clicked();

    void on_btDelVertex_clicked();

    void on_btMove_clicked();

    void on_btDelEdge_clicked();

    void on_btComp_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

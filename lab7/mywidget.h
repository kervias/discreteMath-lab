#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <vector>
#include <QStack>
#include <QVector>
#include <QLabel>
#include "mainwindow.h"
#include "vertex.h"
using namespace std;

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = 0);
    MainWindow *root;

    int DFS(int x, int &tmpEdgeNum);  //使用DFSS求欧拉回路
    int DFSWay();
    int isBridge(int curV, int endV, int *p);
    void updateNum();  //更新编号
    void addVert();   //添加顶点
    void delVert(int dvNum);   //删除顶点
    void addEdg(int aEOne, int aETwo);   //添加边
    void delEdge(int dEone, int dEtwo);  //删除边
    void updateEdgeNum();  //更新边的权值
    void DFSFleury(int x, int &tmpEdgeNum, int *p);

    vector< vector<int> > vecGra;   //存储图的关系, 0代表无边，1代表有边
    vector< vector<int> > tmpV;
    vector<Vertex*> vecVer;  //存储顶点
    QVector<QLabel*> vecLabel; //存储边数标签
    QStack<int> staDfs;
    QStack<int> staFleury;
    int EdgeNum;

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *);

signals:

public slots:
};



#endif // MYWIDGET_H

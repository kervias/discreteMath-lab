#ifndef VERTEX_H
#define VERTEX_H
#include <QPushButton>
#include "mainwindow.h"



class Vertex : public QPushButton
{
    Q_OBJECT
public:
    explicit Vertex(QWidget *parent);

    MainWindow *rootM;
    int Number;   //顶点编号
    bool isMove;  //判断当前顶点是否在移动中
protected:
    void mousePressEvent(QMouseEvent *ev);






signals:

public slots:

};

#endif // VERTEX_H

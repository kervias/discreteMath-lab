#include "vertex.h"
#include "mainwindow.h"
#include <QMouseEvent>
#include <QDebug>

Vertex::Vertex(QWidget *parent = 0) : QPushButton(parent)
{
    this->resize(25,25);
    isMove = false;
    this->setStyleSheet("background-color:orange");
}

void Vertex::mousePressEvent(QMouseEvent *ev){

    switch(rootM->funcType){
    case Vmove:
    {
        if(isMove){  //正在移动中
            isMove = false;
            rootM->curMoveVertex = -1;
        }
        else{
            isMove = 1;
            rootM->curMoveVertex = Number;
        }
        break;
    }
    case DelVertex:
    {
        rootM->curDelvert = Number;
        ev->ignore();
        break;
    }

    case addEdge:
    {

        if(!rootM->curAddEdge.empty() && Number ==  rootM->curAddEdge.top()) break;
        rootM->curAddEdge.push(Number);
        ev->ignore();
        break;
    }

    case DelEdge:
    {
        if(!rootM->curDelEdge.empty() && Number ==  rootM->curDelEdge.top()) break;
        rootM->curDelEdge.push(Number);
        ev->ignore();
        break;
    }
    default: break;

  }
}


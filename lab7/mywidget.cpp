#include "mywidget.h"
#include <QMouseEvent>
#include<QDebug>
#include <QPaintEvent>
#include <Qpainter>
#include <QBrush>
#include <cstring>

#include <iostream>
using namespace std;

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{
        this->setMouseTracking(true);
        EdgeNum = 0;
}

void MyWidget::mousePressEvent(QMouseEvent *e){

    if(e->button() == Qt::LeftButton){
        switch (root->funcType) {
        case addVertex:
        {
            qDebug()<<"widget 添加顶点";
            Vertex *ver = new Vertex(this);
            ver->move(e->pos());
            ver->rootM = root;
            ver->show();
            ver->Number = vecVer.size()+1;
            vecVer.push_back(ver);
            addVert();
             break;
        }
        case addEdge:
        {
            qDebug()<<"widget 添加边";
            if(root->curAddEdge.size() == 2){
                int a = root->curAddEdge.top();
                root->curAddEdge.pop();
                int b = root->curAddEdge.top();
                root->curAddEdge.pop();
                if(a > b) addEdg(a,b);
                if(a < b) addEdg(b,a);
                update();
            }
            break;
        }

        case DelVertex:
        {
            qDebug()<<"widget 删除顶点";
           if(root->curDelvert != -1) delVert(root->curDelvert);
            update();
            break;
        }

        case DelEdge:
        {
            qDebug()<<"widget 删除边";
            if(root->curDelEdge.size() == 2){
                int a = root->curDelEdge.top();
                root->curDelEdge.pop();
                int b = root->curDelEdge.top();
                root->curDelEdge.pop();
                if(a > b) delEdge(a,b);
                if(a < b) delEdge(b,a);
                update();
            }
            break;
        }
        default:
            break;
        }
    }
}

void MyWidget::mouseMoveEvent(QMouseEvent *e){

    if(root->funcType == Vmove && root->curMoveVertex != -1){
        vecVer[root->curMoveVertex-1]->move(e->pos());
        vecVer[root->curMoveVertex-1]->show();
        updateEdgeNum();
        update();
    }
}

void MyWidget::updateEdgeNum(){
    QLabel *tmpLa;
    for(int i = 0; i < vecLabel.size(); i++){
        vecLabel[i]->hide();
    }
    vecLabel.clear();
    for(int i = 0; i < int(vecGra.size()); i++){   //画出顶点
        for(int j = 0; j < int(vecGra[i].size()); j++){
                if(vecGra[i][j] > 1){
                    tmpLa = new QLabel(this);
                    tmpLa->resize(15,15);
                    tmpLa->move((vecVer[i]->pos() + vecVer[j]->pos())/2);
                    tmpLa->setText(QString::number(vecGra[i][j]));
                    tmpLa->setStyleSheet("color:red");
                    tmpLa->show();
                    vecLabel.push_back(tmpLa);
                }
        }
}
}

void MyWidget::paintEvent(QPaintEvent *){
    updateNum();  //更新结点编号
   /*for(int i = 0; i < vecGra.size(); i++){
        for(int j = 0; j < vecGra[i].size(); j++)
            cout<<vecGra[i][j];
        cout<<endl;
    }*/

       QPainter p;
       p.begin(this);
       QPen pen;
       pen.setWidth(1);  //设置线宽
       pen.setColor(Qt::green);
    for(int i = 0; i < int(vecGra.size()); i++){   //画出顶点
        for(int j = 0; j < int(vecGra[i].size()); j++){
            if(vecGra[i][j]){
                QPoint p3(12.5,12.5);
                QPoint p1 = vecVer[i]->pos();
                p1=p1 + p3;
                QPoint p2 = vecVer[j]->pos();
                p2=p2+p3;
                p.drawLine(p1,p2);
            }
            if(vecGra[i][j] != vecGra[j][i]) qDebug()<<"出现问题";
        }
    }




}


void MyWidget::updateNum(){
    for(int i = 0; i < int(vecVer.size()); i++){
       vecVer[i]->Number = i + 1;
       vecVer[i]->setText(QString::number(i+1));
    }
}


void MyWidget::addVert(){  //添加顶点
    vector<int> tmpv;
    for(int i =0; i < int(vecGra.size()); i++){
        while(vecGra[i].size() != vecGra.size()+1){
            vecGra[i].push_back(0);
        }
    }
    for(int i = 0; i < int(vecGra.size()+1); i++){
        tmpv.push_back(0);
    }
    vecGra.push_back(tmpv);
}

void MyWidget::delVert(int dvNum){ //删除顶点
     root->curDelvert = -1;
     vecVer[dvNum-1]->hide();
     Vertex *p = vecVer[dvNum-1];
     vecVer.erase(vecVer.begin()+(dvNum-1));
     delete p;
     int sum = 0;
     for(int i = 0; i < int(vecGra.size()); i++){
         sum += vecGra[dvNum-1][i];
     }
     EdgeNum -= sum;

    vecGra.erase(vecGra.begin()+(dvNum-1));
    for(int i = 0; i < int(vecGra.size()+1); i++){
        vecGra[i].erase(vecGra[i].begin() +(dvNum-1));
    }
    updateEdgeNum();
    update();
}

void MyWidget::addEdg(int aEOne, int aETwo){  //添加边
    //if( vecGra[aEOne-1][aETwo-1] == 0 &&  vecGra[aETwo-1][aEOne-1] == 0){
        vecGra[aEOne-1][aETwo-1]++;
        vecGra[aETwo-1][aEOne-1]++;
        EdgeNum++;
       updateEdgeNum();
    //}
}

void MyWidget::delEdge(int dEone, int dEtwo){  //删除边
    if(vecGra[dEone-1][dEtwo-1] > 0&& vecGra[dEtwo-1][dEone-1] > 0){
        vecGra[dEone-1][dEtwo-1]--;
        vecGra[dEtwo-1][dEone-1]--;
         EdgeNum--;
         updateEdgeNum();
    }
}

//tmpV存储图的矩阵
int MyWidget::isBridge(int curV,int endV,int *p){
    if(curV == endV) return 0;
    for(int i = 0; i < int(vecGra.size()); i++){  //遍历所有顶点编号
        if(tmpV[curV][i] && p[i] == 0){  //未被标记，就标记
            //qDebug()<<i+1;
            p[i] = 1;
            if(!isBridge(i,endV,p)) return 0;
        }
    }
    return 1;
}

void MyWidget::DFSFleury(int x,int &tmpEdgeNum,int *p){
    int t = -1;
    for(int i = 0; i < int(vecGra.size()); i++){
        if(tmpV[x][i] > 0){
            //qDebug()<<x+1<<"*"<<i+1<<"*";
            memset(p,0,(4*int(vecGra.size())));//初始化全部为0
            //cout<<endl;
            p[x] = 1;
            //qDebug()<<"*"<<i<<"*";
            tmpV[x][i]--;  //删除边
            tmpV[i][x]--;
            int aa = isBridge(x,i,p);  //x起点，i终点,p标记数组
            tmpV[x][i]++;
            tmpV[i][x]++;   //添加边
            //qDebug()<<"桥"<<aa;
            if(aa) //是桥，如果没有碰到非桥边则等到循环结束处理
            {
                if(t == -1) t = i;
                continue;
            }
            else   //碰到非桥边，就处理
            {
                tmpEdgeNum++;
                staFleury.push(i+1);
                //qDebug()<<i+1<<"*";
                tmpV[x][i]--;
                tmpV[i][x]--;
                DFSFleury(i,tmpEdgeNum,p);
                return;
            }

        }
    }
    if(t != -1){
        staFleury.push(t+1);
        tmpEdgeNum++;
        tmpV[x][t]--;
        tmpV[t][x]--;
        DFSFleury(t,tmpEdgeNum,p);
    }

}

int MyWidget::DFS(int x,int &tmpEdgeNum){
    if(tmpEdgeNum == EdgeNum) return 1;
    for(int i = 0; i < int(vecGra.size()); i++){
        if(tmpV[x][i] > 0 || tmpV[i][x] > 0){
            tmpEdgeNum++;
            staDfs.push(i+1);
            //qDebug()<<i+1<<"*";
            tmpV[x][i]--;
            tmpV[i][x]--;

           int flagA= DFS(i,tmpEdgeNum);
           tmpV[x][i]++;
           tmpV[i][x]++;
           tmpEdgeNum--;
           //qDebug()<< flagA<<"*";
           //if(staDfs.isEmpty()) qDebug()<<"栈为空";
           if(flagA){
               return 1;
           }
           // qDebug()<<"***"<<staDfs.size();
           staDfs.pop();
        }
    }
    return 0;
}

int MyWidget::DFSWay(){
    //复制一个vector
    tmpV.clear();
    vector<int> tmpv;
    for(int i = 0; i < int(vecGra.size()); i++){
        for(int j = 0;  j < int(vecGra.size()); j++){
            tmpv.push_back(vecGra[i][j]);
        }
        tmpV.push_back(tmpv);
        tmpv.clear();
    }

    staDfs.clear();
    staFleury.clear();
    int sum = 0;
    int t = -1;//初始化无边
    int t2 = 0;
    int t2P = -1;
    for(int i = 0; i < int(vecGra.size()); i++){
       sum = 0;
       for(int j = 0; j < int(vecGra[i].size()); j++){
           sum += tmpV[i][j];

           if(sum != 0) t = 1;   //设置有边

       }
        qDebug()<<sum;
       if(sum > 0 && sum%2 == 1){
           if(t2P == -1) t2P = i;
           t2++;
       }
    }
    if(t == -1) return 0;  //无边
    if(t2 == 2){//欧拉通路
        int tmpEdge = 0;
        staDfs.push_back(t2P+1);
        staFleury.push_back(t2P+1);
        //DFS方式
        DFS(t2P,tmpEdge);   //DFS求解
        qDebug()<<"DFS通路计算完成";
        /*for(int i = 0; i < int(vecGra.size()); i++){
            for(int j = 0;  j < int(vecGra.size()); j++){
                cout<<tmpV[i][j];
            }
            cout<<endl;

        }*/
        tmpEdge = 0;   //Fleury求解
        int *p = new int[vecVer.size()];
        DFSFleury(t2P,tmpEdge,p);
        delete []p;

        return 1;

    }
    if(t2 == 0){//欧拉回路
        int tmpEdge = 0;
        staDfs.push_back(1);
        staFleury.push_back(1);
        DFS(0,tmpEdge);
        qDebug()<<"DFS求解完成";   //DFS求解
        /*for(int i = 0; i < int(vecGra.size()); i++){
            for(int j = 0;  j < int(vecGra.size()); j++){
                cout<<tmpV[i][j];
            }
            cout<<endl;

        }*/
        int *p = new int[vecVer.size()];     //Fleury求解
        tmpEdge = 0;
        DFSFleury(0,tmpEdge,p);
        delete []p;
        return 2;
    }
    return 3; //既无欧拉回路也无欧拉通路
}

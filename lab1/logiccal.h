#ifndef LOGICCAL
#define LOGICCAL

#endif // LOGICCAL

#include <iostream>
#include <QString>
#include<QChar>
#include <stack>
#include<map>
#include<ctype.h>
using namespace std;

class LogicCal{
public:
    LogicCal(QString s, int P, int Q);
    void LogicFunc1(int &ra, int &rb, int &rc, int &rd,int &re);
    int CalLstr();   //递归运算
    void process();  //将变元表达式赋值
    void generate(int i);
    int priority(QChar c);  //返回整型值代表优先级程度
    void calOne(stack<int> &s1, QChar c);
    void LogicFunc2();
    QString getDyEle();

//private:
    int LfuncType;  //功能类型
    QString Lstr,initLstr;  //逻辑表达式
    int P;
    int Q;
    int curI;
    //map<QChar,int> mapLetter;  //代表小写字母
    int label[27];
    int label2[27];
    int num; //num代表变元个数
    int tt;
    QString MXParadigm, MHParadigm;
    map<QString, int> mapReImList;
};

#include "logiccal.h"

LogicCal::LogicCal(QString s,int P, int Q){
    this->P = P;
    this->Q = Q;
    initLstr = s;
    initLstr = "(" + initLstr +")";
    int t = 0;
    memset(label,-1,sizeof(label));
    cout<<s.toStdString()<<endl;
    for(int i = 0; i < s.size(); i++){
        if(s[i].isLetter() && label[s[i].toLatin1() - 'a'] == -1){
            label[s[i].toLatin1() - 'a'] = 1;
            label2[t++] = s[i].toLatin1() - 'a';
        }
    }
    this->num = t;
    cout<<"*"<<num<<"*"<<endl;
}

QString LogicCal::getDyEle(){
    QString qs = "";
    for(int i = 0; i < num; i++){
        qs += QString(QChar(char(label2[i]+'a')));
    }
    return qs;
}

void LogicCal::LogicFunc1(int &ra, int &rb, int &rc, int &rd, int &re){  //功能一
    curI = 0;
    if(num > 2){
        label['p' - 'a'] = P;
        label['q' - 'b'] = Q;
    }
    ra = P + Q;  //处理析取
    if(ra == 2) ra = 1;

    rb = P*Q;  //合取

    rc = 1;  //单条件
    if(P == 1 && Q == 0) rc = 0;

    rd = 0;  //双条件
    if(P == Q) rd = 1;

    re = 1 - rd; //异或

}

int LogicCal::priority(QChar c){ //返回优先级程度
    switch(c.toLatin1())
    {
        case '(':return 0;
        case '=':return 1;
        case '>':return 2;
        case '|':return 3;
        case '&':return 4;
        case '!':return 5;
        case '^':return 3;
        default:return -1;
    }
}

void LogicCal::calOne(stack<int> &s1, QChar c){  //c为运算符，是运算符栈顶，一旦发现当前运算符比栈顶运算符低，就进行栈顶元素的计算
    int tmp1,tmp2;
    switch (c.toLatin1()) {
    case '=':{
        tmp1 = s1.top();    s1.pop();
        tmp2 = s1.top();    s1.pop();
        if(tmp1 == tmp2){
            s1.push(1);
        }
        else s1.push(0);
        break;
    }

    case '>':{
        tmp1 = s1.top();    s1.pop();
        tmp2 = s1.top();    s1.pop();
        if(tmp1 == 0 && tmp2 == 1){
            s1.push(0);
        }
        else s1.push(1);
        break;
    }

    case '|':{
        tmp1 = s1.top();    s1.pop();
        tmp2 = s1.top();    s1.pop();
        int tmp = tmp1 + tmp2;
        if(tmp == 2) s1.push(1);
        else s1.push(tmp);
        break;
    }

    case '&':{
        tmp1 = s1.top();    s1.pop();
        tmp2 = s1.top();    s1.pop();
        int tmp = tmp1 * tmp2;
        s1.push(tmp);
        break;
    }

    case '!':{
        tmp1 = s1.top();    s1.pop();
        s1.push(1-tmp1);
        break;
    }

    case '^':{
        tmp1 = s1.top();    s1.pop();
        tmp2 = s1.top();    s1.pop();
        if(tmp1 = tmp2) s1.push(0);
        else s1.push(1);
        break;
    }
    default:
        cout<<c.toLatin1()<<"sdafafef"<<endl;
        break;
    }
}

int LogicCal::CalLstr(){  //递归括号运算
    //cout<<Lstr.toStdString()<<endl;
    stack<QChar> s2;
    stack<int> s1;
    s2.push(Lstr[curI++]);
    while(curI < Lstr.size() && Lstr[curI] != ')'){
        if(Lstr[curI] == '(') s1.push(CalLstr());
        else{
            if(Lstr[curI].isDigit()){  //若是数字就入数字栈
                s1.push(Lstr[curI].toLatin1() - '0');
            }else{//处理运算符
                 QChar cc = s2.top();
                if(priority(Lstr[curI]) > priority(cc)){  //当前优先级大于栈首运算符
                    s2.push(Lstr[curI]);
                }
                else{
                    while(priority(Lstr[curI]) <= priority(cc)){
                        s2.pop();
                        calOne(s1,cc);
                        cc = s2.top();
                    }
                    s2.push(Lstr[curI]);
                }
            }
        }
        curI++;
    }
    //cout<<"***"<<s2.size()<<"  "<<s1.size()<<"***"<<endl;
    QChar cc = s2.top();
    while(s2.size() > 1){
         s2.pop();
         calOne(s1,cc);
         cc = s2.top();
    }
    curI++;
    return s1.top();
}

void LogicCal::process(){//生成只含有0和1和运算符括号的字符串，从而运算
    Lstr = "";
    for(int i = 0; i < initLstr.size(); i++){
        if(initLstr[i].isLetter()){
            if(label[initLstr[i].toLatin1() - 'a'] == 0) Lstr.append('0');
            if(label[initLstr[i].toLatin1() - 'a'] == 1) Lstr.append('1');
        }
        else{
            Lstr.append(initLstr[i]);
        }
    }

}

void LogicCal::generate(int i){  //产生所有的情况
    if(i == num){
         curI = 0;
         process();
        // cout<<Lstr.toStdString()<<endl;
         int t =  CalLstr();
        // cout<<"result  "<<t<<endl;
         QString tmp = "";
         for(int  k = 0; k < 27; k++){
             if(label[k] == 1) tmp += "1";
             if(label[k] == 0) tmp += "0";
         }
         mapReImList[tmp] = t;  //构造真值表映射
         if(t == 1){  //生成主析取范式
            MXParadigm += "(";
             for(int j = 0; j < num; j++){
                 if(label[label2[j]] == 1){
                     MXParadigm += QString(QChar(char(label2[j]+'a'))) +"&";
                 }
                 else{
                     MXParadigm += "!" + QString(QChar(char(label2[j]+'a'))) + "&";
                  }
             }
             MXParadigm.remove(MXParadigm.size()-1,1);
             MXParadigm += ")|";
         }
         else{//生成主合取范式
             MHParadigm += "(";
              for(int j = 0; j < num; j++){
                  if(label[label2[j]] == 0){
                     MHParadigm += QString(QChar(char(label2[j]+'a'))) +"|";
                 }
                 else{
                     MHParadigm += "!"+QString(QChar(char(label2[j]+'a'))) +"|";
                }
              }
              MHParadigm.remove(MHParadigm.size()-1,1);
              MHParadigm += ")&";
         }
         return;
    }
    else{
        label[label2[i]] = 0;
        generate(i+1);
        label[label2[i]] = 1;
        generate(i+1);
    }
}

void LogicCal::LogicFunc2(){  //功能2
    tt = 0;
     MXParadigm = "";
     MHParadigm = "";
     generate(0);
     MHParadigm.remove(MHParadigm.size()-1,1);
     MXParadigm.remove(MXParadigm.size()-1,1);
}

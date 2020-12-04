#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    int funcType;   //项目类型：0为功能1, 1为功能2
    QString instruction1,instruction2;   //说明框的内容
    QString Result,Expression;  //Result为输出结果   Expression为输入的表达式
    int P;
    int Q;

    int judgeExpression(QString &Qstr);
    QString transForm(int i);



private slots:
    void on_CBfuncType_activated(int index);

    void on_BTCalculate_released();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

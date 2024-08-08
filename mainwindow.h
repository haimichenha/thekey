#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "drawPlot.h"
#include <QPainter>
#include <QComboBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QGraphicsView>
#include <QLabel>    //调整标题文字就需要用，下面还要有Label指针
#include <QMainWindow>
#include <QGraphicsScene>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT

// public slots:                     //本体在MainWindow当中，外部访问则设置成公有给drawPlot访问。而作为槽在同一个页面就私有。


signals:
    // void textChanged(const QString &newtext);                         //信号只声明，不实现(不用构造函数)
    void push1cliked(const QString &text);     //按钮的信号需要参数
    void colorChanged(int index1);      //box1 建议参数两两对应，可以不同
                                                                            //参数不同还要记得在信号的地方转换一下，改一下emit，
    void drawChanged(const QString &found, const QString &newfound);       //box2,发现另一个页面需要使用不同的参数，这里就对应另一个页面的参数
    void sizeChanged(int size);      //spin ,尺寸

    void expicture(int newback);           //box3

    void exporting(const QString &over);              //push2
    void functionInputChanged(const QString &functionInput);
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);        //更换背景,外部地址，方便用于别的类。可能需要外部调用就声明为公有
    QLineEdit *getLineEdit()const;              //需要在MainWindow类外读取，graphicsview，lineedit


public slots:

    // void linetextChanged(const QString &newtext);      //文本改变，在函数实现当中发射信号
    void beginDraw();//开始绘画,对应push1,不需要参数

    void comboBox1EditTextChanged(int index1);              //信号和槽，包括另一个界面的参数对应,颜色
    void comboBox2CurrentTextChanged(int index2);   //对应显示drawChanged
    void comboBox3TextChanged(int index3);   //导出的图片背景

    void spinBoxValueChanged(int size);        //修改图像尺寸
    // void handleComboBoxChange(int index);      //处理显示变化

    void pushButton2Clicked();         //导出,不用参数
private:
    Ui::MainWindow *ui;

    QSpinBox *spinBox;
    QSpinBox *spinBox1;
    QSpinBox *spinBox2;
    QSpinBox *spinBoxy1;
    QSpinBox *spinBoxy2;

    QComboBox *comboBox1,*comboBox2,*comboBox3; //定义ui当中的控件指针，方便管理
    QPushButton *pushButton1,*pushButton2;

    QLineEdit *lineEdit;

    drawPlot *drawPlotWindow;        //需要用到的画面对象，函数当中要使用，作为媒介使用scene和view
    QLabel *label1;
    QGraphicsScene *scene;
    QGraphicsView *graphicsview;
    void setConnection();           //用于管理槽和信号
};

#endif // MAINWINDOW_H

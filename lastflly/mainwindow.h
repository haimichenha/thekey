#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>                  //包含自带的窗口
#include <QGraphicsView>                  //包含使用的部件类(pushbutton之类)
#include <QComboBox>
#include <QPushButton>
#include <QSpinBox>
#include <QCheckBox>
#include <QGraphicsScene>              //根据使用的所有部件类型.

QT_BEGIN_NAMESPACE
namespace Ui {                                                               //继承qmain自带窗口,设定父窗口,子部件才能显示在父窗口上(widget)
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow                  //自定义页面继承自带的页面
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);                            //父类指针,
    ~MainWindow();                                                 //清除页面的对象

private slots:
    void exportPlot();                                                     //定义私有槽,响应特定的信号,完成信号和槽的对接实现功能.
    void plotFunction();                            //管理函数图形的绘制(调用所有绘制函数的使用)
    void hidePlot();                                                        //具体响应哪些操作,定义哪些槽,在源文件当中进行相应
                //根据部件
private:                                        //声明指针
    Ui::MainWindow *ui;                              //指针,初始化布局,连接部件.
    QGraphicsView *graphicsView1, *graphicsView2;           //根据ui布局的部件,将对应的对象利用指针指向不同部件
    QComboBox *comboBox1, *comboBox2;
    QPushButton *pushButton;
    QCheckBox *checkBox;
    QSpinBox *spinBox1, *spinBox2, *spinBox3, *spinBox4, *spinBoxF1, *spinBoxF2, *spinBoxF3, *spinBoxF4;
    QGraphicsScene *scene1, *scene2;                    //用于管理两个graphicsView1和2的行为.*     //

    void setupConnection();               //setupconnection用于管理槽和信号的连接
    void drawFunction(QGraphicsScene *scene, int func, QPen pen);  //函数的曲线                 //声明源文件使用的函数
    void drawGrid(QGraphicsScene *scene, double x1, double y1, double x2, double y2);           //用于绘画坐标轴
    void drawAxesAndLabels(QGraphicsScene *scene, double x1, double y1, double x2, double y2);
};
                                            //函数标签
#endif // MAINWINDOW_H

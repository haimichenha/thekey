#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QPoint>
#include <QVector>
#include <QtMath>
#include <QResizeEvent>
#include <QDockWidget>
#include <QStatusBar>
#include <QMessageBox>
#include <QFileDialog>
#include "stucontrol.h"
#include <QDebug>
#include <QScreen>
#include <QApplication>
#include "exportplot.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT         //使用宏，相关槽连接（应该是）

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


protected:   //保护类，子类可以重写这个函数。但是其他的类想修改时，会被保护
    void paintEvent(QPaintEvent* event) override;     //绘画事件
    void resizeEvent(QResizeEvent* event) override;  //窗口调整
    void closeEvent(QCloseEvent* event) override;

private slots:       //mainwindow的槽在自己私有类下，这些函数就是实现具体功能
    // 响应控制面板的signal信号。这些槽函数会在Setupconnections函数当中。然后牵扯控制窗口的signal信号，暂时不介绍
    void Huatutishi(const QString& function); //提示绘制的函数，提示表达式是否错误。
    void Yanse(const QColor& color);             //颜色参数，设置常量保证颜色作为参数不被修改
    void Xianwidth(int width);     //线宽
    void Shixian(bool isTrue);      //实线
    void Wangge(int size);         //网格槽
    // void onCoordinateRangeChanged(double xMin, double xMax, double yMin, double yMax);
    void Exportplot();
    void Clearplot();
    void Wanggeshow(bool visible);

    void Biaoqianshow(bool visible);    // 添加这个,网格标签显示否  // 添加这个,网格标签显示是

    void XMin(double value);    //坐标轴
    void XMax(double value);
    void YMin(double value);
    void YMax(double value);
    void resetHuanyuan();   //还原默认值的按钮

private:              //函数名采用开头大写。变量名采用小写，变量名拼音和单词连接字母大写
    StuControl* kongzhichuang;         //新建控制窗口对象，在stucontrol的cpp文件分配内存则完成创建
    // UI初始化
    void initUI();
    void Setupconnections();            //用来管理实现槽和信号的连接
    void ZhuangtaiBar();    //底部状态提示函数

    void Suofangupdate();      //网格缩放比例

    // 绘图功能
    void Wanggedraw(QPainter& painter);      //绘制网格的函数
    void XYdraw(QPainter& painter);         //X轴和y轴突出绘制

    void Huabi(QPainter& painter);        //真正用来绘制图像的画笔
    void Hanshujisuan();       //用来对基本的数学函数tan等，判断并特殊化处理，以及各函数绘制比例，虚线比例之类的计算，

    // 坐标转换
    QPoint ShijieToPin(double x, double y) const; //把坐标转换,世界坐标到屏幕坐标。世界指的是数学坐标
    QPointF PinToShijie(int x, int y) const;      //把屏幕坐标转化成世界坐标。屏幕指的是像素坐标系统，两者完成特定的数学转换

    // 辅助功能
    void Updatehuanchong();    //更新缓冲
    bool Exportimage(const QString& filePath);
    void Showcuowu(const QString& message);   //提示错误
    void Showxiaoxi(const QString& message);   //提示绘画的函数表达式
    void Labelsdraw(QPainter& painter);          //用于坐标轴的绘画的函数。
    // 控件成员
    // QDockWidget* kongzhiqi;

    // 绘图设置
    bool chonghui;             // 重绘标志
    int xianWidth;              // 线条宽度，w大写
    bool shixian;           // 是否为实线
    int wanggeSize;               // 网格大小
    bool showWangge;              // 是否显示网格
    bool showLabels;            // 是否显示标签

    // 坐标范围
    double xMin;                // X轴最小值
    double xMax;                // X轴最大值
    double yMin;                // Y轴最小值
    double yMax;                // Y轴最大值

    QColor yanse;           // 线条颜色
    // 视图变换参数
    double biliX;              // X轴缩放比例
    double biliY;              // Y轴缩放比例
    double pianyiX;             // X轴偏移
    double pianyiY;             // Y轴偏移

    QStatusBar* xiaoxiBar;     //底部提示消息的那个对象

    // 绘图属性
    QPixmap huanchong;              // 缓冲区

    QString hanshuFunction;     // 当前函数表达式
    QVector<QPointF> points;    // 函数点集
    // 计算相关
    static constexpr double PLOT_PRECISION = 0.1;  // 绘图精度
    static constexpr int AXIS_MARGIN = 30;         // 轴线边距
};

#endif

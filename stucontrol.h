#ifndef STUCONTROL_H
#define STUCONTROL_H

#include <QDialog>
#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QColorDialog>


// 绘图配置结构体
// struct DrawConfig {
//     QString function;      // 函数表达式
//     QColor color;         // 线条颜色
//     int lineWidth;        // 线条宽度
//     bool isSolid;         // 是否为实线
//     int gridSize;         // 网格大小
//     double xMin, xMax;    // X轴范围
//     double ySMin, yMax;    // Y轴范围
// };

class StuControl : public QDialog  //
{
    Q_OBJECT

public:
    explicit StuControl(QWidget *parent = nullptr);
    ~StuControl();

    // 获取当前配置,对于这些函数，注释掉的函数是只用来传递信号，目的是传递数值，但是Setupconnections函数中
    //Setupconnections可以通过直接连接下面的信号函数，获取数值信息。所以单纯发送信号的函数可以注释掉。
    // DrawConfig getCurrentConfig() const;


    // QString hanshuGet() const;  //getCurrentFunction
    // QColor yanseGet () const; //getCurrentColor
    // int xiankuanGet() const; //getCurrentLineWidth
    // // bool shixianIs() const;  //isCurrentLineSolid
    // void FanweiGet(double& xSmin, double& xSmax,
    //                      double& ySmin, double& ySmax) const;  //getCurrentRange
    // int wanggeSize() const;
    // bool wanggeIs() const;
    // bool labelIs() const;

    /*未注释函数是控制函数，调用后直接控制时间的发生，注释报错 */
    void shixianjingyong(bool enabled); //表达式错误则禁用线型切换,
    void resetSHuanyuan(); //重置函数
    void ExportSpanduan(bool enabled);  //错误图像禁止导出


signals:                             //函数名采用开头大写。变量名采用小写，变量名拼音和单词连接字母大写,为了区分，控制窗口部分函数含S，信号带有sig
                 //括号的参数可以按照固定形式，槽连接时可以确定，
                                                //比如按照固定格式写到QDoubleSpinBox:: 冒号会提示选择信号类型，然后确定这里基本参数类型
    void xSmin(double value);
    void xSmax(double value);
    void ySmin(double value);
    void ySmax(double value);            //作为x,y的范围调整的信号

    void wanggeSizeSig(int size);     //变量名称自定义，但是类型对应使用的类型，网格大小用整数，定义为int  //网格尺寸修改
    void drawBiaodashi(const QString& function);   //表达式很多字母，使用常量类型，不让定义的数学函数式子被修改
    void yanseSig(const QColor& color);          //使用qt库默认的颜色变量QColor。

    void xiankuanSig(int width);           //线宽信号
    void shixianSig(bool solid);         //实线虚线切换信号。
    // void coordinateRangeChanged(double xMin, double xMax, double yMin, double yMax);

    void wanggeSig(bool visible);       //变量选择是，或者取反选bool。     //是否显示网格的的复选框信号
    void labelSig(bool visible);     //labelsVisibleChanged        //是否显示标签复选框的信号。

    void exportRequested();           //不需要传递值，不用参数，这些信号不需要数值和或者字符。单单是唤醒功能、
    void clearRequested();
    void resetRequested();

public slots: //实现功能的函数就是槽,stucontrol控制窗口的槽一般转换数值的类型，设置连接条件的连接，还有发射信号，然后mainwindow收到信号
                                                //这样mainwindow就能通过信号，得到需要的数据，进行相应的操作。
    void onHuihua();              //相应函数图像绘制的，即点击绘制按钮，本质是发送信号相应按钮，不需要参数类型
    void onYanse(int index);       //int类型是因为颜色在函数实现的时候，使用了switch语句，选择对应的数字选择颜色
    void onXiankuan(int width);   //线宽改变
    void onShixian();         //虚线实线信号切换
    // void onApplyRangeButtonClicked();
    void onwanggeSize(int size);  //修改函数名onGridSizeChanged     //修改网格尺寸

private:
    // 基本类型
    bool isLine;     //虚线变量

    // 私有方法 ，这些方法用于布局的组合，比如函数输入组合中包含绘制按钮以及表达式输入框QLineEdit
    void initUI();           //在函数中定义程序的布局的函数
    void hanshuzu();  //修改函数名createFunctionGroup      //
    void shixianzu(); //createStyleGroup     //样式设置的组合，颜色、线宽、实现
    void wanggezuobiaoGroup();   //createCoordinateGroup,网格大小，坐标范围组合
    void wanggeLabelGroup();   // 网格标签是否显示的复选框
    void setupConnections();
    /*void XYFanweiGroup();*/          //包含xyfan范围

    // 函数组控件，左边是ui页面设计的控件名称，是固定的，右边是定义对应的指针，即声明其存在
    QGroupBox* hanshuGroup;      //组合
    QLineEdit* hanshuInput;      //输入框
    // QLineEdit* functionEdit;
    QPushButton* drawButton;   //绘制按钮

    // 范围组控件
    QGroupBox* fanweiGroup;    //范围组合
    QDoubleSpinBox* xMinSpin;   //大小范围
    QDoubleSpinBox* xMaxSpin;
    QDoubleSpinBox* yMinSpin;
    QDoubleSpinBox* yMaxSpin;

    // 样式组控件
    QGroupBox* styleGroup;     //样式组合
    // QComboBox* yanseSelect;    //颜色
    // QSpinBox* lineWidthSelect;
    QSpinBox* xiankuanSpin;      //线宽选择spin

    QPushButton* yanseButton;    //颜色选择按钮
    QPushButton* xianStyleButton;

    // 坐标组控件
    QGroupBox* zuobiaoGroup;           //坐标设置组合
    QSpinBox* wanggeSizeSpinBox;       //网格大小控件
    // QSpinBox* gridSizeSelect;

    // 显示组控件
    QGroupBox* xianshiGroup;
    // QCheckBox* showWanggeCheck;          //showGridCheck
    // QCheckBox* showLabelCheck;

    QCheckBox* wanggekejianCheck;       //网格是否显示控件
    QCheckBox* labelKejianCheck;        //标签是否选择的控件

    // 其他按钮
    QPushButton* exportButton;
    QPushButton* clearButton;
    QPushButton* resetButton;
};

#endif

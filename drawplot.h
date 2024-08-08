#ifndef DRAWPLOT_H
#define DRAWPLOT_H

#include "qcombobox.h"
#include "qpushbutton.h"
#include <QWidget>
#include <QPainter>
#include <QComboBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTextEdit>

#include <QString>
#include <QPen>
#include <functional>
#include <QMap>
#include <functional>

QT_BEGIN_NAMESPACE
namespace Ui {
class drawPlot;
}
QT_END_NAMESPACE

class drawPlot : public QWidget
{
    Q_OBJECT

public:         //改为公共
    explicit drawPlot(QSpinBox *spinBox, QSpinBox *spinBox1, QSpinBox *spinBox2, QSpinBox *spinBoxy1, QSpinBox *spinBoxy2,
                      QComboBox *comboBox1, QComboBox *comboBox2, QComboBox *comboBox3,
                      QLineEdit *functionInput,  QGraphicsView *view,
                      QPushButton *pushButton1, QPushButton *pushButton2, QWidget *parent = nullptr);

    ~drawPlot();

    // void updatePlot(double x1, double y1,int function);

public slots:
    void upGraph(const QString &functionInput);     //更新画面     //void LtextChanged(const QString &arg1);
    void colorPlot(int index1);                           //错误，事件归属文本改变在MainWindow当中，不是drawPlot。
    void backdrawPlot(const QString &found, const QString &newfound); //与显示和隐藏关联,          //所以要在drawPlot实现对文本变化的反应，在这边调用MainWindow的公有槽
    void sizePlot(int size);                                    //在drawPlot当中connect使用MainWindow的相关事件。设置可能的槽为公有
    void picturePlot(int newback);
        //     void hidePlot();
        //     void backcolorPlot();
    void exportPlot(const QString &over);
    void plotFunction();               //管理所有用于绘画的函数
    void setFunctionInput(const QString &functionInput);

private slots:

    void onExportPlotClicked();
    void updateFunction(const QString &function);
    void updateSize(int size);
    void updateColor(int index);

private:
    Ui::drawPlot *ui;
    drawPlot *DrawPlot;         //默认
    QTextEdit *textEditFunction;
    QTextEdit *textEditSize;
    QTextEdit *textEditColor;

    QSpinBox *spinBox;
    QSpinBox *spinBox1;
    QSpinBox *spinBox2;
    QSpinBox *spinBoxy1;
    QSpinBox *spinBoxy2;

    QComboBox *comboBox1,*comboBox2,*comboBox3;
    QLineEdit *functionInput;
    QGraphicsScene *scene;                 //管理绘画和控件 的对象
    QGraphicsView *view;                    //管理显示画面 的对象
    double x1, y1, x2, y2;
    QPushButton *pushButton1,*pushButton2;

    // QLineEdit *lineEditFunction,*lineEditColor,LineEditSize;

                        //作为新界面 管理一个窗口，qwidget类,这个窗口包含view和scene,drawPlotWindow是一个实例
    int spinBoxValue;
    void setGraphVisibility(bool visible);

    //构造函数的形式
    /*void drawFunction(QGraphicsScene * scene,int func,QPen pen);*/
    /*void drawGrid(QGraphicsScene *scene,double x,double y); */
    /*void drawAxesAndLables(QGraphicsScene *scene,double x,double y); */      //下面部分参数更完善

    void setConnection();         //管理信号和槽的函数（包含connection式信号槽的对接）

    void setupUI();
    void drawGrid(QGraphicsScene* scene, double x1, double y1, double x2, double y2); //函数曲线
    void drawAxesAndLabels(QGraphicsScene* scene, double x1, double y1, double x2, double y2);  //画横纵轴放（不包括横竖方格）
    void drawFunction(QGraphicsScene *scene, std::function<double(double)> func, QPen pen, double x1, double x2, double y1, double y2);   //画标签和横竖线（方格）
    void initializeFunctionMap();
    void setPlotBounds(double x1, double y1, double x2, double y2);

    std::unordered_map<QString, std::function<double(double)>> functionMap;
    std::function<double(double)> parsedFunction;

    std::function<double(double)> parseFunction(const QString &functionInput);

};
#endif

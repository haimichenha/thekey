#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>
#include <QFileDialog>
#include <QVector>
#include <QGraphicsTextItem>
#include <QPainter>
#include <QGraphicsScene>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)                     // 框架,指定父窗口QMainWindow,父窗口显示,子控件才会存在
{
    ui->setupUi(this);                             //加载用户页面的控件,将部件和页面关联起来,方便
    scene1 = new QGraphicsScene(this);           //this设置父窗口
    scene2 = new QGraphicsScene(this);
    ui->graphicsView1->setScene(scene1);              //在ui当中创建新的场景对象
    ui->graphicsView2->setScene(scene2);


    ui->comboBox1->addItems({"x^2", "ln(x)", "sin(x)", "cos(x)", "sqrt(x)"});              //先在ui设置了comboBox1还有文本,然后,在这里利用additems()函数添加文本
    ui->comboBox2->addItems({"x^2", "ln(x)", "sin(x)", "cos(x)", "sqrt(x)"});             //传入文本


    QList<QSpinBox*> spinBoxes = {ui->spinBox1, ui->spinBox2, ui->spinBox3, ui->spinBox4,
                                   ui->spinBoxF1, ui->spinBoxF2, ui->spinBoxF3, ui->spinBoxF4};


    for (QSpinBox* spinBox : spinBoxes) {        //根据资料,遍历列表,然后设置一个最大最小值
        spinBox->setMinimum(-5000);
        spinBox->setMaximum(5000);
    }


                                                        //后来添加.初始的值(图像小,故设值较大)
    ui->spinBox1->setValue(-1000);
    ui->spinBox2->setValue(1000);                       //一开始图像很小,倒置.115
    ui->spinBox3->setValue(1000);
    ui->spinBox4->setValue(-1000);
    ui->spinBoxF1->setValue(-1000);
    ui->spinBoxF2->setValue(1000);
    ui->spinBoxF3->setValue(1000);
    ui->spinBoxF4->setValue(-1000);

    setupConnection();                           //定义的管理信号和槽的函数(connection)
    plotFunction();
}

MainWindow::~MainWindow() {
    delete ui;
}
                     //初始化部件指针指向对象.//QOverload用于重载标明类型     //发生的事件   //预定义信号      //将时间与槽函数连接
void MainWindow::setupConnection() {
    connect(ui->comboBox1, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::plotFunction);
    connect(ui->comboBox2, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::plotFunction);
    connect(ui->spinBox1, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::plotFunction);
    connect(ui->spinBox2, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::plotFunction);
    connect(ui->spinBox3, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::plotFunction);
    connect(ui->spinBox4, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::plotFunction);
    connect(ui->spinBoxF1, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::plotFunction);
    connect(ui->spinBoxF2, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::plotFunction);
    connect(ui->spinBoxF3, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::plotFunction);
    connect(ui->spinBoxF4, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::plotFunction);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::exportPlot); // 实现了头文件的export槽函数
    connect(ui->checkBox, &QCheckBox::stateChanged, this, &MainWindow::hidePlot);  // 发送勾选信号,调用hidePlot
    }

void MainWindow::plotFunction() {
    scene1->clear();
    scene2->clear();

    double x1 = ui->spinBox1->value();
    double y1Value = ui->spinBox2->value();
    double x2 = ui->spinBox3->value();
    double y2Value = ui->spinBox4->value();

    double x1F = ui->spinBoxF1->value();
    double y1F = ui->spinBoxF2->value();
    double x2F = ui->spinBoxF3->value();
    double y2F = ui->spinBoxF4->value();

    if (x1 == x2) x2 = x1 + 1;
    if (y1Value == y2Value) y2Value = y1Value + 1;
    if (x1F == x2F) x2F = x1F + 1;
    if (y1F == y2F) y2F = y1F + 1;

    scene1->setSceneRect(x1, -y2Value, x2 - x1, y2Value - y1Value);  // Correct scene rect for y-axis
    scene2->setSceneRect(x1F, -y2F, x2F - x1F, y2F - y1F);

    drawGrid(scene1, x1, y1Value, x2, y2Value);
    drawGrid(scene2, x1F, y1F, x2F, y2F);

    drawAxesAndLabels(scene1, x1, y1Value, x2, y2Value);
    drawAxesAndLabels(scene2, x1F, y1F, x2F, y2F);

    int function1 = ui->comboBox1->currentIndex();
    int function2 = ui->comboBox2->currentIndex();

    drawFunction(scene1, function1, QPen(Qt::blue));
    drawFunction(scene1, function2, QPen(Qt::red));

    drawFunction(scene2, function1, QPen(Qt::green));
}

void MainWindow::drawGrid(QGraphicsScene* scene, double x1, double y1, double x2, double y2) {
    QPen gridPen(Qt::gray, 0.5, Qt::DotLine);
    double stepX = (x2 - x1) / 200.0;
    double stepY = (y1 - y2) / 200.0;

    for (double x = x1; x <= x2; x += stepX) {
        scene->addLine(x, -y1, x, -y2, gridPen);
    }
    for (double y = y2; y <= y1; y += stepY) {
        scene->addLine(x1, -y, x2, -y, gridPen);
    }
}

void MainWindow::drawAxesAndLabels(QGraphicsScene* scene, double x1, double y1, double x2, double y2) {
    QPen axisPen(Qt::black);

    // Draw x-axis
    scene->addLine(x1, 0, x2, 0, axisPen);
    // Draw y-axis
    scene->addLine(0, -y1, 0, -y2, axisPen);  // Corrected y-axis line

    QFont font;
    font.setPointSize(8);

    // Draw x-axis grid lines and labels
    double stepX = (x2 - x1) / 10.0;
    for (double x = x1; x <= x2; x += stepX) {
        scene->addLine(x, -5, x, 5, axisPen);
        QGraphicsTextItem* label = scene->addText(QString::number(x));
        label->setPos(x - label->boundingRect().width() / 2, 10);
    }

    // Draw y-axis grid lines and labels
    double stepY = (y1 - y2) / 10.0;
    for (double y = y2; y <= y1; y += stepY) {
        scene->addLine(-5, -y, 5, -y, axisPen);
        QGraphicsTextItem* label = scene->addText(QString::number(y));
        label->setPos(-label->boundingRect().width() - 10, -y - label->boundingRect().height() / 2);
    }
}

void MainWindow::drawFunction(QGraphicsScene *scene, int func, QPen pen) {
    double x1 = ui->spinBox1->value();
    double x2 = ui->spinBox3->value();

    QVector<QPointF> points;
    for (double x = x1; x <= x2; x += (x2 - x1) / 10000.0) {
        double y = 0;
        switch (func) {
        case 0: y = x * x; break;
        case 1: if (x > 0) y = log(x); break;
        case 2: y = 10 * sin(x); break;
        case 3: y = 10 * cos(x); break;
        case 4: if (x >= 0) y = sqrt(x); break;
        }
        points.append(QPointF(x, -y));  // Ensure y is negative
    }

    for (int i = 1; i < points.size(); ++i) {
        scene->addLine(QLineF(points[i - 1], points[i]), pen);
    }
}




void MainWindow::exportPlot() {                                       //导出模块(防)
    QString fileName = QFileDialog::getSaveFileName(this, "Export Plot", "", "PNG Files (*.png);;All Files (*)");
    if (!fileName.isEmpty()) {
        QImage image(scene1->sceneRect().size().toSize(), QImage::Format_ARGB32);        //设置导出图片的大小格式
        QPainter painter(&image);                                                   //QPainter画出图像
        scene1->render(&painter);                                       //rander发送信号,把对象发送出去
        image.save(fileName);
    }
}

void MainWindow::hidePlot() {
    if (ui->checkBox->isChecked()) {
        scene2->clear();                             //清除
    } else {
        plotFunction();                               //取消勾选则显示
    }
}

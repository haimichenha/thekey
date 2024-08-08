#include "mainwindow.h"
#include "drawplot.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPixmap>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    spinBox(new QSpinBox(this)),
    spinBox1(new QSpinBox(this)),
    spinBox2(new QSpinBox(this)),
    spinBoxy1(new QSpinBox(this)),
    spinBoxy2(new QSpinBox(this)),
    comboBox1(new QComboBox(this)),
    comboBox2(new QComboBox(this)),
    comboBox3(new QComboBox(this)),
    pushButton1(new QPushButton(this)),
    pushButton2(new QPushButton(this)),
    lineEdit(new QLineEdit(this)),
    drawPlotWindow(new drawPlot(spinBox, spinBox1, spinBox2, spinBoxy1, spinBoxy2,
                            comboBox1, comboBox2, comboBox3, lineEdit,
                             new QGraphicsView(),
                            pushButton1, pushButton2, nullptr))
{
    ui->setupUi(this);

    ui->setupUi(this);

    drawPlotWindow->setWindowTitle("Control Window");
    drawPlotWindow->setGeometry(100, 100, 600, 400);
    drawPlotWindow->show();

    ui->lineEdit->setPlaceholderText("在此处输入函数");

    ui->label1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->lineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    ui->spinBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    setConnection();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete drawPlotWindow;
}


void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, width(), height(), QPixmap(":/new/prefix1/OIP-C.jpg"));
}

void MainWindow::setConnection()
{
    // connect(spinBox, QOverload<int>::of(&QSpinBox::valueChanged), drawPlotWindow, &drawPlot::plotFunction);
    // connect(spinBox1, QOverload<int>::of(&QSpinBox::valueChanged), drawPlotWindow, &drawPlot::plotFunction);
    // connect(spinBox2, QOverload<int>::of(&QSpinBox::valueChanged), drawPlotWindow, &drawPlot::plotFunction);
    // connect(spinBoxy1, QOverload<int>::of(&QSpinBox::valueChanged), drawPlotWindow, &drawPlot::plotFunction);
    // connect(spinBoxy2, QOverload<int>::of(&QSpinBox::valueChanged), drawPlotWindow, &drawPlot::plotFunction);


    connect(ui->pushButton1, &QPushButton::clicked, this, &MainWindow::beginDraw);
    connect(this, &MainWindow::push1cliked, drawPlotWindow, &drawPlot::plotFunction);
    // connect(ui->pushButton1, &QPushButton::clicked, this, &MainWindow::onCompletedButtonClicked);
    // connect(this, &MainWindow::functionInputChanged, drawPlotWindow, &drawPlot::setFunctionInput);


    // connect(ui->comboBox1, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::comboBox1EditTextChanged);
    // connect(this, &MainWindow::colorChanged, drawPlotWindow, &drawPlot::colorPlot);

    // connect(ui->comboBox2, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::comboBox2CurrentTextChanged);
    // connect(this, &MainWindow::drawChanged, drawPlotWindow, &drawPlot::backdrawPlot);

    connect(ui->comboBox3, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::comboBox3TextChanged);
    connect(this, &MainWindow::exporting, drawPlotWindow, &drawPlot::exportPlot);

    connect(ui->pushButton2, &QPushButton::clicked, this, &MainWindow::pushButton2Clicked);



}

                                                                    //lineedit转到槽获取函数，函数名字可以修改跟头文件里一致
// void MainWindow::linetextChanged(const QString &newtext)       //信号和槽，头文件声明信号signal,还有槽函数，此处声明文本
// {
//     emit textChanged(newtext);
// }


// QLineEdit *MainWindow::getLineEdit()const
// {
//     return lineEdit;
// }

void MainWindow::beginDraw() {
    emit push1cliked("开始");
}

void MainWindow::comboBox1EditTextChanged(int index1) {
    emit colorChanged(index1);
}

void MainWindow::comboBox2CurrentTextChanged(int index2) {
    QString found = ui->comboBox2->itemText(index2);
    QString newfound = found;
    emit drawChanged(found, newfound);
}

void MainWindow::spinBoxValueChanged(int size) {
    emit sizeChanged(size);
}

void MainWindow::comboBox3TextChanged(int index3) {
    QString text = ui->comboBox3->itemText(index3);
    int newback = (text == "White") ? 1 : 0;
    emit expicture(newback);
}

void MainWindow::pushButton2Clicked()
{
    emit exporting("export over");
}

// void MainWindow::onCompletedButtonClicked() {
//     qDebug() << "Completed button clicked";

//     // Retrieve the function input from lineEdit
//     QString functionInput = ui->lineEdit->text();
//     emit functionInputChanged(functionInput); // Emit signal to pass the function input to drawPlot

//     drawPlotWindow->plotFunction(); // Invoke plotFunction to update the plot
// }


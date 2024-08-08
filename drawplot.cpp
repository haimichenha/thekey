#include "drawplot.h"
#include "ui_drawplot.h"
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QFileDialog>
#include <QGraphicsTextItem>
#include <cmath>
#include <QDebug>
#include <QVBoxLayout>
#include <QVector>

drawPlot::drawPlot(QSpinBox *spinBox, QSpinBox *spinBox1, QSpinBox *spinBox2, QSpinBox *spinBoxy1, QSpinBox *spinBoxy2,
                   QComboBox *comboBox1, QComboBox *comboBox2, QComboBox *comboBox3,
                   QLineEdit *functionInput,  QGraphicsView *view,
                   QPushButton *pushButton1, QPushButton *pushButton2, QWidget *parent)
    : QWidget(parent),
    ui(new Ui::drawPlot),
    spinBox(spinBox), spinBox1(spinBox1), spinBox2(spinBox2), spinBoxy1(spinBoxy1), spinBoxy2(spinBoxy2),
    comboBox1(comboBox1), comboBox2(comboBox2), comboBox3(comboBox3),
    functionInput(functionInput),  view(view),
    pushButton1(pushButton1), pushButton2(pushButton2)
{
    ui->setupUi(this);

    // QVBoxLayout *layout = new QVBoxLayout;
    /*this->scene = new QGraphicsScene();*/  // Initialize scene

    // view->setScene(this->scene);

    QVBoxLayout *layout = new QVBoxLayout(this);

    textEditFunction = new QTextEdit(this);
    textEditFunction->setReadOnly(true);
    textEditFunction->setPlaceholderText("Function");

    textEditSize = new QTextEdit(this);
    textEditSize->setReadOnly(true);
    textEditSize->setPlaceholderText("Size");

    textEditColor = new QTextEdit(this);
    textEditColor->setReadOnly(true);
    textEditColor->setPlaceholderText("Color");
    view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // layout->addWidget(view);
    // setLayout(layout);
    // view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QList<QSpinBox*> spinBoxes = {spinBox1, spinBox2, spinBoxy1, spinBoxy2};
    for (QSpinBox* spinBox : spinBoxes) {
        spinBox->setMinimum(-50000);
        spinBox->setMaximum(50000);
    }

    // Set initial values for boundary representation
    // spinBox->setValue(-1000);
    // spinBox1->setValue(-1000);
    // spinBox2->setValue(1000);
    // spinBoxy1->setValue(1000);
    // spinBoxy2->setValue(-1000);

    initializeFunctionMap();
    setConnection();
    plotFunction();
}

drawPlot::~drawPlot()
{
    delete ui;
}

void drawPlot::setConnection()
{
    connect(spinBox1, QOverload<int>::of(&QSpinBox::valueChanged), this, &drawPlot::plotFunction);
    connect(spinBox2, QOverload<int>::of(&QSpinBox::valueChanged), this, &drawPlot::plotFunction);
    connect(spinBoxy1, QOverload<int>::of(&QSpinBox::valueChanged), this, &drawPlot::plotFunction);
    connect(spinBoxy2, QOverload<int>::of(&QSpinBox::valueChanged), this, &drawPlot::plotFunction);

    connect(comboBox1, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &drawPlot::plotFunction);
    connect(comboBox2, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &drawPlot::colorPlot);
    connect(pushButton1, &QPushButton::clicked, this, &drawPlot::onExportPlotClicked);
    connect(pushButton2, &QPushButton::clicked, this, &drawPlot::sizePlot);
}

void drawPlot::initializeFunctionMap() {
    functionMap["x^2"] = [](double x) { return x * x; };
    functionMap["log(x)"] = [](double x) { return x > 0 ? std::log(x) : 0; };
    functionMap["10*sin(x)"] = [](double x) { return 10 * std::sin(x); };
    functionMap["10*cos(x)"] = [](double x) { return 10 * std::cos(x); };
    functionMap["sqrt(x)"] = [](double x) { return x >= 0 ? std::sqrt(x) : 0; };
    functionMap["x"] = [](double x) { return x ; };
    functionMap["sin(x)"] = [](double x) { return 1* std::sin(x); };
    functionMap["cos(x)"] = [](double x) { return 1* std::cos(x); };

}

void drawPlot::setPlotBounds(double x1, double y1, double x2, double y2) {
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
}

void drawPlot::plotFunction()
{
    if (parsedFunction) {
        scene->clear(); // Clear the scene before plotting the new function
        drawFunction(scene, parsedFunction, QPen(Qt::blue), -10, 10, -10, 10);
    }
}

void drawPlot::drawGrid(QGraphicsScene* scene, double x1, double y1, double x2, double y2) {
    QPen gridPen(Qt::gray, 0.5, Qt::DotLine);
    double stepX = (x2 - x1) / 20.0;  // Adjusted step size for better grid spacing
    double stepY = (y1 - y2) / 20.0;  // Adjusted step size for better grid spacing

    // Draw vertical grid lines
    for (double x = x1; x <= x2; x += stepX) {
        scene->addLine(x, y1, x, y2, gridPen);
    }

    // Draw horizontal grid lines
    for (double y = y2; y <= y1; y += stepY) {
        scene->addLine(x1, y, x2, y, gridPen);
    }
}
void drawPlot::drawAxesAndLabels(QGraphicsScene* scene, double x1, double y1, double x2, double y2) {
    QPen axisPen(Qt::black);

    // Draw X axis
    scene->addLine(x1, 0, x2, 0, axisPen);
    // Draw Y axis
    scene->addLine(0, -y1, 0, -y2, axisPen);

    // Draw X axis labels and ticks
    double stepX = (x2 - x1) / 50.0;  // Adjust step size if necessary
    for (double x = x1; x <= x2; x += stepX) {
        scene->addLine(x, -5, x, 5, axisPen);  // Draw tick
        QGraphicsTextItem* label = scene->addText(QString::number(x));  // Add label
        label->setPos(x - label->boundingRect().width() / 2, 5);  // Position label
    }

    // Draw Y axis labels and ticks
    double stepY = (y1 - y2) / 50.0;  // Adjust step size if necessary
    for (double y = y2; y <= y1; y += stepY) {
        scene->addLine(-5, -y, 5, -y, axisPen);  // Draw tick
        QGraphicsTextItem* label = scene->addText(QString::number(y));  // Add label
        label->setPos(-label->boundingRect().width() - 5, -y - label->boundingRect().height() / 2);  // Position label
    }
}


void drawPlot::drawFunction(QGraphicsScene *scene, std::function<double(double)> func, QPen pen, double x1, double x2, double y1, double y2)
{
    QPainterPath path;
    bool isFirstPoint = true;

    for (double x = x1; x <= x2; x += 0.01) {
        double y = func(x);
        // Clip y to fit within y1 and y2 range
        if (y < y2) y = y2;
        if (y > y1) y = y1;

        if (isFirstPoint) {
            path.moveTo(x, -y);  // Use -y to match the coordinate system
            isFirstPoint = false;
        } else {
            path.lineTo(x, -y);  // Use -y to match the coordinate system
        }
    }

    // Create and add path item to scene
    QGraphicsPathItem *pathItem = new QGraphicsPathItem(path);
    pathItem->setPen(pen);
    scene->addItem(pathItem);
}



void drawPlot::colorPlot(int index1) {
    QPen pen;
    if (index1 == 0) {
        pen.setColor(Qt::red);
    } else if (index1 == 1) {
        pen.setColor(Qt::green);
    } else if (index1 == 2) {
        pen.setColor(Qt::blue);
    }
    scene->setForegroundBrush(pen.color());
}

void drawPlot::backdrawPlot(const QString &found, const QString &newfound) {
    if (found == "Hide") {
        this->setVisible(false);
    } else if (found == "Show") {
        this->setVisible(true);        //this：当前的对象

        // 当显示图像时，调用 upGraph 函数
        if (!newfound.isEmpty()) {
            upGraph(newfound);
        }
    }
}

void drawPlot::upGraph(const QString &functionInput) {
    if (parsedFunction) {
        scene->clear(); // Clear the scene before plotting the new function
        drawFunction(scene, parsedFunction, QPen(Qt::blue), -10, 10, -10, 10);
    }
}



void drawPlot::setGraphVisibility(bool visible) {
    this->setVisible(visible);
}

void drawPlot::sizePlot(int size) {
    qDebug() << "Updating plot size to: " << size;

    view->setFixedSize(size, size);
    scene->setSceneRect(0, 0, size, size);

    // 你可以在这里添加额外的逻辑来调整图形的大小
}

void drawPlot::picturePlot(int newback) {
    QString fileName = QFileDialog::getSaveFileName(this, "Export Plot", "", "PNG Files (*.png);;All Files (*)");
    if (!fileName.isEmpty()) {
        QRectF sceneRect = scene->sceneRect();
        QSize imageSize = sceneRect.size().toSize();

        if (imageSize.isEmpty()) {
            qDebug() << "Scene size is empty!";
            return;
        }

        QImage image(imageSize, QImage::Format_ARGB32);
        if (newback == 1) {
            image.fill(Qt::white); // 背景为白色
        } else {
            image.fill(Qt::transparent); // 背景为透明
        }

        QPainter painter(&image);
        if (!painter.isActive()) {
            qDebug() << "Painter is not active!";
            return;
        }

        scene->render(&painter);
        painter.end();

        if (!image.save(fileName)) {
            qDebug() << "Failed to save image!";
        } else {
            qDebug() << "Image saved successfully!";
        }
    } else {
        qDebug() << "Save file dialog was canceled.";
    }
}

void drawPlot::exportPlot(const QString &over) {
    qDebug() << "Received text:" << over;
    QString fileName = QFileDialog::getSaveFileName(this, "Export Plot", "", "PNG Files (*.png);;All Files (*)");
    if (!fileName.isEmpty()) {
        QRectF sceneRect = scene->sceneRect();
        QSize imageSize = sceneRect.size().toSize();

        if (imageSize.isEmpty()) {
            qDebug() << "Scene size is empty!";
            return;
        }

        QImage image(imageSize, QImage::Format_ARGB32);
        image.fill(Qt::transparent);  // 填充为透明色

        QPainter painter(&image);
        if (!painter.isActive()) {
            qDebug() << "Painter is not active!";
            return;
        }

        scene->render(&painter);
        painter.end();  // 结束绘制

        if (!image.save(fileName)) {
            qDebug() << "Failed to save image!";
        } else {
            qDebug() << "Image saved successfully!";
        }
    } else {
        qDebug() << "Save file dialog was canceled.";
    }
}

void drawPlot::onExportPlotClicked() {
    exportPlot("");  // 调用带参数的 exportPlot 函数
}


void drawPlot::updateFunction(const QString &function) {
    textEditFunction->setText(function);
}

void drawPlot::updateSize(int size) {
    textEditSize->setText(QString::number(size));
}

void drawPlot::updateColor(int index) {
    QString colorName;
    switch(index) {
    case 0: colorName = "Red"; break;
    case 1: colorName = "Green"; break;
    case 2: colorName = "Blue"; break;
    default: colorName = "Unknown"; break;
    }
    textEditColor->setText(colorName);
}

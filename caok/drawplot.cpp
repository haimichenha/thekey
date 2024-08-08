#include "drawplot.h"
#include "ui_drawplot.h"
#include <QVBoxLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QGraphicsTextItem>
#include <cmath>
#include <QDebug>
#include <QPen>
#include <QPainterPath>

drawPlot::drawPlot(QSpinBox *spinBox, QSpinBox *spinBox1, QSpinBox *spinBox2, QSpinBox *spinBoxy1, QSpinBox *spinBoxy2,
                   QComboBox *comboBox1, QComboBox *comboBox2, QComboBox *comboBox3,
                   QLineEdit *functionInput, QLineEdit *lineEdit, QGraphicsView *view,
                   QPushButton *pushButton1, QPushButton *pushButton2, QWidget *parent)
    : QWidget(parent),
    ui(new Ui::drawPlot),
    spinBox(spinBox), spinBox1(spinBox1), spinBox2(spinBox2), spinBoxy1(spinBoxy1), spinBoxy2(spinBoxy2),
    comboBox1(comboBox1), comboBox2(comboBox2), comboBox3(comboBox3),
    functionInput(functionInput), lineEdit(lineEdit), scene(nullptr), view(view),
    pushButton1(pushButton1), pushButton2(pushButton2), plotPathItem(nullptr), Colorplot(Qt::black)
{
    ui->setupUi(this);

    this->scene = new QGraphicsScene();  // Initialize scene
    view->setScene(this->scene);

    QVBoxLayout *layout = new QVBoxLayout(this);
    view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addWidget(view);
    setLayout(layout);

    QList<QSpinBox*> spinBoxes = {spinBox1, spinBox2, spinBoxy1, spinBoxy2};
    for (QSpinBox* spinBox : spinBoxes) {
        spinBox->setMinimum(-500);
        spinBox->setMaximum(500);
    }

    initializeFunctionMap();
    setConnection();
    updatePlot(); // Initial plot
}

drawPlot::~drawPlot()
{
    delete ui;
}

void drawPlot::setConnection() {
    connect(spinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, [this]() {
        sizePlot(spinBox->value());
    });

    connect(comboBox1, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this](int index) {
        colorPlot(index);
    });

    connect(spinBox1, QOverload<int>::of(&QSpinBox::valueChanged), this, [this]() {
        updatePlot();
    });

    connect(spinBox2, QOverload<int>::of(&QSpinBox::valueChanged), this, [this]() {
        updatePlot();
    });

    connect(spinBoxy1, QOverload<int>::of(&QSpinBox::valueChanged), this, [this]() {
        updatePlot();
    });

    connect(spinBoxy2, QOverload<int>::of(&QSpinBox::valueChanged), this, [this]() {
        updatePlot();
    });

    connect(functionInput, &QLineEdit::textChanged, this, [this]() {
        updatePlot();
    });

    connect(pushButton1, &QPushButton::clicked, this, [this]() {
        button1Line();
    });
}

void drawPlot::initializeFunctionMap() {
    functionMap["x^2"] = [](double x) { return x * x; };
    functionMap["log(x)"] = [](double x) { return x > 0 ? std::log(x) : 0; };
    functionMap["10*sin(x)"] = [](double x) { return 10 * std::sin(x); };
    functionMap["10*cos(x)"] = [](double x) { return 10 * std::cos(x); };
    functionMap["sqrt(x)"] = [](double x) { return x >= 0 ? std::sqrt(x) : 0; };
    functionMap["x"] = [](double x) { return x; };
    functionMap["sin(x)"] = [](double x) { return std::sin(x); };
    functionMap["cos(x)"] = [](double x) { return std::cos(x); };
    functionMap["2"] = [](double) { return 2.0; };
}

std::function<double(double)> drawPlot::parseFunctionInput(const QString &input) {
    auto it = functionMap.find(input);
    if (it != functionMap.end()) {
        return it.value(); // Use it.value() to get the function associated with the key
    }
    return [](double) -> double { return 0.0; }; // Default to zero if not found
}

void drawPlot::plotFunction(const QString &input) {
    if (!scene) {
        qDebug() << "Scene is not initialized!";
        return;
    }

    auto func = parseFunctionInput(input);
    scene->clear();

    double x1 = spinBox1->value() * 50;
    double x2 = spinBox2->value() * 50;
    double y1 = spinBoxy2->value() * 50;
    double y2 = spinBoxy1->value() * 50;

    if (x1 == 0 && x2 == 0) {
        x1 = -500;
        x2 = 500;
    }
    if (y1 == 0 && y2 == 0) {
        y1 = 500;
        y2 = -500;
    }

    drawGrid(scene, x1, y1, x2, y2);
    drawAxisLabels(scene, x1, y1, x2, y2);

    QPen pen = Colorplot;
    pen.setWidth(spinBox->value()); // Line width from spinBox

    QPainterPath path;
    double step = (x2 - x1) / 1000.0;
    double x = x1;
    double y = func(x) * spinBox->value();
    path.moveTo(x, -y);

    for (x += step; x <= x2; x += step) {
        y = func(x) * spinBox->value();
        path.lineTo(x, -y);
    }

    if (plotPathItem != nullptr) {
        plotPathItem->setPath(path);
        plotPathItem->setPen(pen);
    } else {
        plotPathItem = scene->addPath(path, pen);
    }

    QGraphicsTextItem *label = new QGraphicsTextItem(QString("f(x) = %1").arg(input));
    label->setPos(x2, y2);
    scene->addItem(label);

    qDebug() << "Function plotted successfully";
}

void drawPlot::colorPlot(int colorIndex) {
    QColor color;
    switch (colorIndex) {
    case 0: color = Qt::black; break;
    case 1: color = Qt::yellow; break;
    case 2: color = Qt::blue; break;
    case 3: color = Qt::red; break;
    default: color = Qt::green; break;
    }
    Colorplot.setColor(color);

    // Redraw the plot with the new color
    QString input = functionInput->text();
    plotFunction(input);
}

void drawPlot::sizePlot(int size) {
    qDebug() << "Plot size changed to:" << size;

    // Update pen width
    QPen pen = Colorplot;
    pen.setWidth(size);

    if (plotPathItem != nullptr) {
        plotPathItem->setPen(pen);
        scene->update(); // Optionally, redraw the scene
    }
}

void drawPlot::updatePlot() {
    QString input = functionInput->text();
    plotFunction(input);
}

void drawPlot::button1Line() {
    QString input = functionInput->text();
    plotFunction(input);
}

void drawPlot::drawGrid(QGraphicsScene* scene, double x1, double y1, double x2, double y2) {
    QPen gridPen(Qt::gray, 0.5, Qt::DotLine);
    double stepX = (x2 - x1) / 20.0;
    double stepY = (y1 - y2) / 20.0;

    for (double x = x1; x <= x2; x += stepX) {
        scene->addLine(x, y1, x, y2, gridPen);
    }

    for (double y = y2; y <= y1; y += stepY) {
        scene->addLine(x1, y, x2, y, gridPen);
    }

    scene->addLine(0, y1, 0, y2, QPen(Qt::black, 1.5));
}

void drawPlot::drawAxisLabels(QGraphicsScene* scene, double x1, double y1, double x2, double y2) {
    QFont font;
    font.setPointSize(8);

    double stepX = (x2 - x1) / 10.0;
    for (double x = x1; x <= x2; x += stepX) {
        scene->addLine(x, -5, x, 5, QPen(Qt::black));
        QGraphicsTextItem* label = new QGraphicsTextItem(QString::number(x));
        label->setPos(x, 10);
        label->setFont(font);
        scene->addItem(label);
    }

    double stepY = (y1 - y2) / 10.0;
    for (double y = y2; y <= y1; y += stepY) {
        scene->addLine(-5, y, 5, y, QPen(Qt::black));
        QGraphicsTextItem* label = new QGraphicsTextItem(QString::number(y));
        label->setPos(10, -y);
        label->setFont(font);
        scene->addItem(label);
    }
}

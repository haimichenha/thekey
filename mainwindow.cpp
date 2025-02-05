#include "mainwindow.h"
#include "stucontrol.h"
#include <QCloseEvent>
#include <QPainterPath>

MainWindow::MainWindow(QWidget *parent)        //构造函数，这些
    : QMainWindow(parent)    //构造函数附带的父类窗口，然后自己用来显示的子窗口包括窗口的各个元素才能使用
    , kongzhichuang(nullptr)  // 先初始化为 nullptr
    , chonghui(true)          //这些是对应对象的具体实现，并且传入具体的参数，头文件当中的所有变量都要在这实现才不报错
    , xianWidth(1)
    , biliX(1.0)  //x的比例大小
    , biliY(1.0)     //y的比例大小
    , pianyiX(0.0)     //x的偏移量
    , pianyiY(0.0)    //y的偏移量
    , shixian(true)
    , wanggeSize(1)   //括号当中是默认的数值
    , showLabels(true)
    , xMin(-10.0)
    , xMax(10.0)
    , yMin(-10.0)
    , yMax(10.0)
    , yanse(Qt::black)
{

    // 初始化界面
    initUI();  //构造函数内部调用了页面布局函数，对于控件在窗口当中的显示位置以及属性进行了声明


    // 创建并显示控制面板
    kongzhichuang = new StuControl();            //使用了new进行内存的分配

    kongzhichuang->setWindowTitle("控制面板");  // 设置窗口标题 ->是访问指针成员的操作符，即动态成员使用
    kongzhichuang->show();  // 显示控制面板窗口，此时控制窗口使用show函数（qt默认的显示函数）

    if (QGuiApplication::screens().size() > 0) {          //计算屏幕的信息
        QRect screenGeometry = QGuiApplication::screens().first()->geometry();   //获取尺寸，设置主显示器，geometry()获取显示器的几何信息(位置和大小)
        int x = (screenGeometry.width() - width()) / 2;      //垂直居中和水平居中计算，然后用move进行移动屏幕
        int y = (screenGeometry.height() - height()) / 2;
        move(x, y);
    }

    // // 连接信号和槽，这部分因为有了setupConnections函数，可以不要
    // connect(controlPanel, &StuControl::drawFunction, this, &MainWindow::onDrawFunction);
    // connect(controlPanel, &StuControl::colorChanged, this, &MainWindow::onColorChanged);
    // connect(controlPanel, &StuControl::lineWidthChanged, this, &MainWindow::onLineWidthChanged);
    // connect(controlPanel, &StuControl::lineStyleChanged, this, &MainWindow::onLineStyleChanged);
    // // connect(controlPanel, &StuControl::coordinateRangeChanged, this, &MainWindow::onCoordinateRangeChanged);
    // connect(controlPanel, &StuControl::gridSizeChanged, this, &MainWindow::onGridSizeChanged);
    // connect(controlPanel, &StuControl::gridVisibleChanged, this, &MainWindow::onGridVisibleChanged);
    // connect(controlPanel, &StuControl::labelsVisibleChanged, this, &MainWindow::onLabelsVisibleChanged);


    QRect screenGeometry = QApplication::primaryScreen()->geometry();     //这一段是控制窗口的位置计算，偏右避免重叠
    int x = screenGeometry.width() - kongzhichuang->width() - 20;    //减去当前自身窗口的宽度，计算数值保证不超出屏幕
    int y = (screenGeometry.height() - kongzhichuang->height()) / 2;
    kongzhichuang->move(x, y);

    // 建立连接
    Setupconnections();
    ZhuangtaiBar();

    // 初始化缓冲区
    huanchong = QPixmap(size());
    huanchong.fill(Qt::white);

    // 计算初始比例和偏移
    Suofangupdate();

    // 显示窗口
    kongzhichuang->show();
}

MainWindow::~MainWindow()
{
    delete kongzhichuang;

}

void MainWindow::initUI()
{
    // 创建控制面板
    // controlPanel = new StuControl(this);
    // controlDock = new QDockWidget("控制面板", this);
    // controlDock->setWidget(controlPanel);
    // controlDock->setFeatures(QDockWidget::DockWidgetMovable |
    //                          QDockWidget::DockWidgetFloatable);
    // addDockWidget(Qt::LeftDockWidgetArea, controlDock);

    setWindowTitle("函数图像绘制");
    resize(800, 600);  // 设置合适的初始大小
    // 设置中心窗口的背景
    QPalette pal = palette();
    pal.setColor(QPalette::Window, Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);

    setMouseTracking(true);
}

void MainWindow::ZhuangtaiBar()          //底部消息提示，创建
{
    xiaoxiBar = new QStatusBar(this);
    setStatusBar(xiaoxiBar);         //传入了我们的指针对象xiaoxiBar
    xiaoxiBar->showMessage("就绪");
}

void MainWindow::Setupconnections()
{
    // 连接控制面板的信号到主窗口的信号,stu的信号可以直接用来mainwindow连接，后面一个是mainwindow的槽。连接发生信号的函数的话，比如wanggeIs就没反应。
    connect(kongzhichuang, &StuControl::drawBiaodashi,  // 函数绘制信号      drawBiaodashi用来代表存放数学表达式的对象，这么一个信号
            this, &MainWindow::Huatutishi);           //当然drawBiaodashi是一个信号，不是一个函数。后面这个&取mainwindow的地址
    connect(kongzhichuang, &StuControl::yanseSig,       // 颜色改变信号
            this, &MainWindow::Yanse);                  //往下找Yanse这个函数，函数的内容即实现颜色切换的逻辑和代码，其他函数同理
    connect(kongzhichuang, &StuControl::xiankuanSig,    // 线宽改变信号
            this, &MainWindow::Xianwidth);
    connect(kongzhichuang, &StuControl::shixianSig,     // 实线/虚线信号
            this, &MainWindow::Shixian);
    connect(kongzhichuang, &StuControl::wanggeSizeSig,     // 网格大小信号
            this, &MainWindow::Wangge);
    connect(kongzhichuang, &StuControl::wanggeSig,      // 网格显示信号
            this, &MainWindow::Wanggeshow);
    connect(kongzhichuang, &StuControl::labelSig,       // 标签显示信号
            this, &MainWindow::Biaoqianshow);
    connect(kongzhichuang, &StuControl::exportRequested, // 导出信号
            this, &MainWindow::Exportplot);
    connect(kongzhichuang, &StuControl::clearRequested,  // 清除信号
            this, &MainWindow::Clearplot);

    connect(kongzhichuang, &StuControl::resetRequested,  //重置
            this, &MainWindow::resetHuanyuan);

    // 坐标轴范围信号
    connect(kongzhichuang, &StuControl::xSmin, this, &MainWindow::XMin);   //Stucontrol的信号用添加S和sig与mainwindow变量稍微进行区分
    connect(kongzhichuang, &StuControl::xSmax, this, &MainWindow::XMax); //前面还是信号。后面还是槽函数（实现功能的函数）,有细微的区分
    connect(kongzhichuang, &StuControl::ySmin, this, &MainWindow::YMin);
    connect(kongzhichuang, &StuControl::ySmax, this, &MainWindow::YMax);
}

// 坐标转换函数
QPoint MainWindow::ShijieToPin(double x, double y) const          //把世界坐标转化成为屏幕坐标的函数
{                                                                 //世界坐标就是数学当中的坐标系，屏幕坐标是以像素为单位，原点在左上角
    int screenX = static_cast<int>((x - xMin) * biliX + AXIS_MARGIN);
    int screenY = height() - AXIS_MARGIN - static_cast<int>((y - yMin) * biliY);
    return QPoint(screenX, screenY);
}


QPointF MainWindow::PinToShijie(int x, int y) const            //屏幕坐标转化成为世界坐标，世界坐标原点在中心，适用数学计算
{
    double worldX = (x - AXIS_MARGIN) / biliX + xMin;
    double worldY = ((height() - AXIS_MARGIN - y) / biliY) + yMin;  //AXIS_MARGIN在头文件当中定义用于记录轴线边距
    return QPointF(worldX, worldY);
}

void MainWindow::resizeEvent(QResizeEvent* event)        // 绘图尺寸调整，即mainwindow的保护成员之一
{
    QMainWindow::resizeEvent(event);          //冒号表示调用resizeEvent函数，调用对象

    // 调整缓冲区大小                   //缓冲区就是中间过渡的对象，在同等尺寸的缓冲区进行绘制，并把内容一次性传递给新窗口，下面那个函数调整窗口大小
    huanchong = QPixmap(size());               //缓冲的目的是让图像连贯，不出现闪烁
    Suofangupdate();
}

void MainWindow::paintEvent(QPaintEvent*)
{
    if (chonghui) {
        huanchong.fill(Qt::white);         //huanchong（缓冲函数）.fill（自带的填充函数ctrl加鼠标跳转）
        QPainter bufferPainter(&huanchong);    //类名  成员名，然后用&符号取huanchong的地址，用来告知地址
        bufferPainter.setRenderHint(QPainter::Antialiasing);

        // 绘制各个元素
        if (showWangge) {    //showWangge是网格复选框是显示的状态，然后就调用Wanggedrawg函数，并且把对应的bufferPainter变量传入进行处理
            Wanggedraw(bufferPainter);
        }
        XYdraw(bufferPainter);//
        if (showLabels) {
            Labelsdraw(bufferPainter);
        }
        if (!hanshuFunction.isEmpty()) {
            Huabi(bufferPainter);
        }

        chonghui = false;                //三种if之外的情况就变成false
    }

    // 将缓冲区内容绘制到窗口
    QPainter painter(this);
    painter.drawPixmap(0, 0, huanchong);               //前面两个是原点坐标
}

void MainWindow::Wanggedraw(QPainter& painter)
{
    QPen gridPen(QColor(200, 200, 200));           // 创建了QPen类的gridPen名称的对象，颜色的三个数字代表的是颜色分量红绿蓝
    gridPen.setWidth(1);
    gridPen.setStyle(Qt::DotLine);
    painter.setPen(gridPen);

    // 计算网格步长
    double step = wanggeSize;

    // 计算合适的网格线位置
    double startX = ceil(xMin / step) * step;       // 使用ceil函数确保起始位置是步长的整数倍
    double startY = ceil(yMin / step) * step;

    // 垂直网格线
    for (double x = startX; x <= xMax; x += step) {
        QPoint start = ShijieToPin(x, yMin);
        QPoint end = ShijieToPin(x, yMax);
        painter.drawLine(start, end);              // 画线传入开始和结束位置
    }

    // 水平网格线
    for (double y = startY; y <= yMax; y += step) {
        QPoint start = ShijieToPin(xMin, y);
        QPoint end = ShijieToPin(xMax, y);
        painter.drawLine(start, end);              // 画线传入开始和结束位置
    }
}

void MainWindow::XYdraw(QPainter& painter)
{
    // 设置坐标轴的画笔
    QPen axisPen(Qt::black);
    axisPen.setWidth(2);
    axisPen.setStyle(Qt::SolidLine);  // 坐标轴始终使用实线
    painter.setPen(axisPen);
    painter.setBrush(Qt::black);      // 箭头填充颜色

    // 调试输出
    qDebug() << "绘制坐标轴 - "
             << "X范围:" << xMin << "到" << xMax
             << "Y范围:" << yMin << "到" << yMax;

    // 绘制X轴
    QPoint xStart = ShijieToPin(xMin, 0);           // 转换为屏幕坐标系
    QPoint xEnd = ShijieToPin(xMax, 0);             // 转换为屏幕坐标系
    painter.drawLine(xStart, xEnd);

    // 绘制Y轴
    QPoint yStart = ShijieToPin(0, yMin);
    QPoint yEnd = ShijieToPin(0, yMax);
    painter.drawLine(yStart, yEnd);

    // 箭头大小和角度设置
    const int arrowSize = 10;                       // 箭头大小
    const double arrowAngle = 25;                   // 箭头角度（度）
    const double toRad = M_PI / 180.0;              // 角度转弧度

    // 绘制X轴箭头
    {
        QPolygon arrow;
        QPoint tip = xEnd;                         // 箭头尖端，位于X轴的终点

        // 计算箭头两侧的点
        QPoint p1(
            tip.x() - arrowSize * cos(toRad * arrowAngle), // x坐标：从尖端向左移动
            tip.y() - arrowSize * sin(toRad * arrowAngle)  // y坐标：向上移动
            );
        QPoint p2(
            tip.x() - arrowSize * cos(toRad * arrowAngle), // x坐标：同上
            tip.y() + arrowSize * sin(toRad * arrowAngle)  // y坐标：向下移动
            );

        arrow << tip << p1 << p2;
        painter.drawPolygon(arrow);                 // 绘制由三个点组成的三角形箭头
    }

    // 绘制Y轴箭头
    {
        QPolygon arrow;
        QPoint tip = yEnd;                          // 箭头尖端，位于Y轴的终点

        // 计算箭头两侧的点
        QPoint p1(
            tip.x() - arrowSize * sin(toRad * arrowAngle), // x坐标：向左移动
            tip.y() - arrowSize * cos(toRad * arrowAngle)  // y坐标：从尖端向上移动
            );
        QPoint p2(
            tip.x() + arrowSize * sin(toRad * arrowAngle), // x坐标：向右移动
            tip.y() - arrowSize * cos(toRad * arrowAngle)  // y坐标：同上
            );

        arrow << tip << p1 << p2;
        painter.drawPolygon(arrow);                 // 绘制Y轴的箭头三角形，即坐标轴最末段的箭头标记的绘制
    }

    // 在坐标轴上添加刻度
    if (showLabels) {
        const int tickLength = 5;                   // 刻度线长度
        QPen tickPen = axisPen;
        tickPen.setWidth(1);
        painter.setPen(tickPen);

        // X轴刻度
        for (int x = ceil(xMin); x <= floor(xMax); x += wanggeSize) {
            if (x == 0) continue;                   // 跳过原点
            QPoint tickStart = ShijieToPin(x, 0);
            painter.drawLine(tickStart,
                             QPoint(tickStart.x(), tickStart.y() + tickLength)); // 绘制垂直刻度线
        }

        // Y轴刻度
        for (int y = ceil(yMin); y <= floor(yMax); y += wanggeSize) {
            if (y == 0) continue;                   // 跳过原点
            QPoint tickStart = ShijieToPin(0, y);
            painter.drawLine(tickStart,
                             QPoint(tickStart.x() - tickLength, tickStart.y())); // 绘制水平刻度线
        }
    }
}


void MainWindow::Labelsdraw(QPainter& painter)
{
    painter.setPen(Qt::black);
    QFont font = painter.font();
    font.setPointSize(8);
    painter.setFont(font);             //前面这一段是设置基本的绘画属性

    // 绘制X轴刻度和标签
    for (double x = ceil(xMin); x <= floor(xMax); x += wanggeSize) {
        if (qFuzzyIsNull(x)) continue; // 跳过原点
        QPoint pos = ShijieToPin(x, 0);
        painter.drawLine(pos.x(), pos.y() - 4, pos.x(), pos.y() + 4);
        painter.drawText(QRect(pos.x() - 20, pos.y() + 5, 40, 20),
                         Qt::AlignHCenter, QString::number(x));
    }

    // 绘制Y轴刻度和标签
    for (double y = ceil(yMin); y <= floor(yMax); y += wanggeSize) {
        if (qFuzzyIsNull(y)) continue; // 跳过原点
        QPoint pos = ShijieToPin(0, y);
        painter.drawLine(pos.x() - 4, pos.y(), pos.x() + 4, pos.y());
        painter.drawText(QRect(pos.x() - 30, pos.y() - 10, 25, 20),
                         Qt::AlignRight | Qt::AlignVCenter, QString::number(y));
    }

    // 绘制原点标签
    QPoint origin = ShijieToPin(0, 0);
    painter.drawText(QRect(origin.x() + 5, origin.y() + 5, 20, 20),
                     Qt::AlignLeft | Qt::AlignTop, "O");
}

void MainWindow::Hanshujisuan()
{
    points.clear(); // 清空当前的点集
    QVector<QPointF> tempPoints; // 用于存储计算出的点的临时容器

    // 检查是否正在显示错误标记（当用户输入非法函数时，yanse会被设置为红色）
    if (yanse == Qt::red && points.size() == 5) {
        return; // 如果是错误标记，直接返回，避免重复计算
    }

    // 处理常函数(y=c)的特殊情况，例如"y=5"
    if (hanshuFunction.startsWith("y=")) {
        bool ok;
        double value = hanshuFunction.mid(2).toDouble(&ok); // 提取y=c中的常数值
        if (ok && value >= yMin && value <= yMax) {
            // 如果值在y轴范围内，直接绘制水平线，连接左右边界
            tempPoints.append(QPointF(xMin, value)); // 左端点：x轴最小值，y=常数值
            tempPoints.append(QPointF(xMax, value)); // 右端点：x轴最大值，y=常数值
            points = tempPoints; // 更新点集
            return; // 常函数处理完毕，直接返回
        }
    }

    // 根据函数类型动态调整x轴的步长（step），影响采样密度
    double step;
    if (hanshuFunction == "log(x)" || hanshuFunction.contains("ln(x)")) {
        step = (xMax - xMin) / (width() * 40); // 对数函数变化剧烈，增加采样密度（更小的步长）
    } else {
        step = (xMax - xMin) / (width() * 20); // 其他函数使用默认采样率
    }

    // 遍历x轴范围内的每个点，计算对应的y值
    for (double x = xMin; x <= xMax; x += step) {
        double y = 0;
        bool validPoint = true; // 标记当前点是否在定义域和值域内

        // 根据函数表达式选择计算逻辑
        if (hanshuFunction == "sin(x)") {
            y = 10 * qSin(x); // 计算放大10倍的sin值，使波形更明显
        }
        else if (hanshuFunction == "cos(x)") {
            y = 10 * qCos(x); // 同上，处理cos函数
        }
        else if (hanshuFunction == "tan(x)") {
            // tan(x)在cos(x)=0处（如π/2, 3π/2）无定义，需要排除这些点
            if (fabs(qCos(x)) < 0.01) { // 近似判断cos(x)是否接近0
                tempPoints.append(QPointF(x, qQNaN())); // 添加无效点（NaN）作为断点
                continue; // 跳过当前x值
            }
            y = 5 * qTan(x); // 计算并缩小tan值，避免过大
            if (fabs(y) > 25) { // 限制y值范围，防止绘图溢出
                y = (y > 0) ? 25 : -25; // 截断到±25
            }
        }
        else if (hanshuFunction == "log(x)" || hanshuFunction.contains("ln(x)")) {
            if (x <= 0) { // 对数函数定义域为x>0
                tempPoints.append(QPointF(x, qQNaN())); // 非定义域点标记为NaN
                continue;
            }
            y = 0.5 * qLn(x); // 计算自然对数并缩小0.5倍，调整显示比例
        }
        else if (hanshuFunction == "x^2") {
            y = x * x; // 平方函数
        }
        else if (hanshuFunction == "x^3") {
            y = x * x * x; // 立方函数
        }
        else if (hanshuFunction.startsWith("x=")) {  // 处理垂直直线（如"x=3"）
            bool ok;
            double value = hanshuFunction.mid(2).toDouble(&ok); // 提取x的常数值
            if (!ok) continue; // 转换失败则跳过
            if (x == value) y = x; // 仅在x等于常数值时有效（实际会被后续范围检查过滤）
            else validPoint = false; // 其他x值无效
        }
        else if (hanshuFunction.startsWith("arccos")) {
            // 反余弦函数定义域为[-1, 1]
            if (x < -1 || x > 1) {
                tempPoints.append(QPointF(x, qQNaN())); // 非定义域点标记为NaN
                continue;
            }
            y = 2.0 * qAcos(x); // 计算结果放大2倍，便于可视化
        } else if (hanshuFunction.startsWith("y=")) {
            // 再次处理常函数，确保覆盖可能的遗漏情况
            bool ok;
            double value = hanshuFunction.mid(2).toDouble(&ok);
            if (ok) {
                y = value;
            } else {
                validPoint = false; // 转换失败则标记为无效
            }
        } else {
            tempPoints.append(QPointF(x, qQNaN())); // 未知函数类型，跳过
            continue;
        }

        // 检查y值是否在允许的范围内，并存储有效点
        if (!qIsNaN(y) && y >= yMin && y <= yMax) {
            tempPoints.append(QPointF(x, y));
        }
    }

    // 处理虚线显示逻辑（shixian为false时启用虚线）
    if (!shixian) {
        QVector<QPointF> dashPoints; // 存储虚线点集

        // 特殊处理arccos函数的虚线（较短线段和间隙）
        if (hanshuFunction == "arccos(x)") {
            const double segmentLength = 0.2;  // 实线段长度（x轴方向）
            const double gapLength = 0.2;      // 间隙长度
            double currentX = -1.0;  // arccos定义域起点
            bool isDrawing = true;    // 当前是否绘制实线段

            while (currentX <= 1.0) { // 遍历定义域[-1, 1]
                if (isDrawing) {
                    // 计算当前线段结束位置，防止超出定义域
                    double endX = qMin(currentX + segmentLength, 1.0);
                    // 在实线段内按步长计算点
                    for (double x = currentX; x <= endX; x += step) {
                        double y = 2.0 * qAcos(x);
                        if (y >= yMin && y <= yMax) {
                            dashPoints.append(QPointF(x, y)); // 添加有效点
                        }
                    }
                    // 线段结束添加NaN断点，实现虚线效果
                    if (!dashPoints.isEmpty()) {
                        dashPoints.append(QPointF(qQNaN(), qQNaN()));
                    }
                }
                // 更新currentX：绘制时前进segmentLength，否则前进gapLength
                currentX += isDrawing ? segmentLength : gapLength;
                isDrawing = !isDrawing; // 切换绘制状态
            }
            points = dashPoints; // 最终点集赋值
        }
        // 处理对数函数的虚线
        else if (hanshuFunction == "log(x)" || hanshuFunction.contains("ln(x)")) {
            const double segmentLength = 0.5; // 实线段长度（x轴）
            const double gapLength = 0.5;     // 间隙长度
            double currentX = xMin;           // 起始x值
            bool isDrawing = true;            // 当前绘制状态

            while (currentX <= xMax) {
                if (isDrawing) {
                    double endX = qMin(currentX + segmentLength, xMax);
                    // 在实线段内生成点
                    for (double x = currentX; x <= endX; x += step) {
                        if (x > 0) { // 确保对数定义域
                            double y = 0.5 * qLn(x);
                            if (y >= yMin && y <= yMax) {
                                dashPoints.append(QPointF(x, y));
                            }
                        }
                    }
                    // 添加断点分隔线段
                    if (!dashPoints.isEmpty()) {
                        dashPoints.append(QPointF(qQNaN(), qQNaN()));
                    }
                }
                currentX += isDrawing ? segmentLength : gapLength;
                isDrawing = !isDrawing; // 切换状态
            }
            points = dashPoints;
        } else {
            // 通用虚线处理：交替生成实线段和间隙
            int dashLength = 25; // 实线段点数
            int gapLength = 20;  // 间隙点数
            bool isDrawing = true;
            int count = 0; // 当前段内点数计数

            for (const auto& point : tempPoints) {
                // 遇到NaN表示函数断点（如tan的无穷大）
                if (qIsNaN(point.y())) {
                    points.append(point); // 直接保留断点
                    isDrawing = true;     // 新段开始，重置状态
                    count = 0;
                    continue;
                }

                // 达到当前段长度限制时切换状态
                if (count >= (isDrawing ? dashLength : gapLength)) {
                    isDrawing = !isDrawing;
                    count = 0;
                }

                // 根据状态添加点或断点
                points.append(isDrawing ? point : QPointF(point.x(), qQNaN()));
                count++;
            }
        }
    } else {
        points = tempPoints; // 实线模式直接使用所有点
    }
}




void MainWindow::Huabi(QPainter& painter)
{
    if (points.isEmpty()) return; // 如果点集为空，直接返回

    QPen pen(yanse); // 设置画笔颜色
    pen.setWidth(xianWidth); // 设置画笔宽度
    pen.setStyle(Qt::SolidLine); // 设置画笔样式为实线
    painter.setPen(pen); // 将画笔设置到QPainter
    painter.setRenderHint(QPainter::Antialiasing); // 启用抗锯齿

    QPoint prevPoint; // 上一个点
    bool first = true; // 标记是否是第一个点

    // 遍历点集
    for (const QPointF& point : points) {
        if (qIsNaN(point.y())) { // 如果y值是NaN，跳过该点
            first = true; // 标记下一个点为第一个点
            continue;
        }

        QPoint screenPoint = ShijieToPin(point.x(), point.y()); // 将世界坐标转换为屏幕坐标
        if (!first) {
            painter.drawLine(prevPoint, screenPoint); // 画线连接上一个点和当前点
        }
        prevPoint = screenPoint; // 更新上一个点
        first = false; // 更新第一个点标记
    }
}

void MainWindow::Updatehuanchong()
{
    huanchong.fill(Qt::white); // 用白色填充缓冲区
    chonghui = true; // 设置重绘标志
    update(); // 请求更新窗口
}

bool MainWindow::Exportimage(const QString& filePath)
{
    return huanchong.save(filePath); // 保存缓冲区内容到文件
}



// 槽函数实现
// 槽函数实现
void MainWindow::Huatutishi(const QString& function)
{
    hanshuFunction = function.toLower().trimmed();

    // 更严格的函数表达式检查
    bool isValidFunction = false;

    // 基本函数检查
    if (hanshuFunction == "sin(x)" ||
        hanshuFunction == "cos(x)" ||
        hanshuFunction == "tan(x)" ||
        hanshuFunction == "log(x)" ||
        hanshuFunction == "ln(x)" ||
        hanshuFunction == "x^2" ||
        hanshuFunction == "x^3" ||
        hanshuFunction == "arccos(x)") {
        isValidFunction = true;
    }

    // 垂直线检查 (x=n)
    else if (hanshuFunction.startsWith("x=")) {
        bool ok;
        hanshuFunction.mid(2).toDouble(&ok);
        isValidFunction = ok;
    }

    // 水平线检查 (y=n)
    else if (hanshuFunction.startsWith("y=")) {
        bool ok;
        hanshuFunction.mid(2).toDouble(&ok);
        isValidFunction = ok;
    }

    if (!isValidFunction) {
        // 保存原始颜色和线型
        QColor originalColor = yanse;
        bool originalLine = shixian;

        yanse = Qt::red;
        shixian = true;  // 错误标记始终使用实线

        // 清除现有点集
        points.clear();
        QVector<QPointF> errorPoints;

        // 添加叉号的点
        errorPoints.append(QPointF(xMin, yMin));
        errorPoints.append(QPointF(xMax, yMax));
        errorPoints.append(QPointF(qQNaN(), qQNaN())); // 断开线段
        errorPoints.append(QPointF(xMin, yMax));
        errorPoints.append(QPointF(xMax, yMin));

        points = errorPoints;
        xiaoxiBar->showMessage("无效的函数表达式: " + function, 3000);

        // 更新显示
        Updatehuanchong();

        // 恢复原始颜色和线型
        yanse = originalColor;
        shixian = originalLine;

        // 禁用控制面板的线型切换按钮和导出按钮
        if (kongzhichuang) {
            kongzhichuang->shixianjingyong(false);
            kongzhichuang->ExportSpanduan(false);
        }
    } else {
        xiaoxiBar->showMessage("正在绘制函数: " + function);
        // 启用控制面板的线型切换按钮和导出按钮
        if (kongzhichuang) {
            kongzhichuang->shixianjingyong(true);
            kongzhichuang->ExportSpanduan(true);
        }
        Hanshujisuan();
        Updatehuanchong();
    }
}

void MainWindow::Yanse(const QColor& color)
{
    yanse = color;
    Updatehuanchong();
}

void MainWindow::Xianwidth(int width)
{
    xianWidth = width;
    Updatehuanchong();
}

void MainWindow::Shixian(bool isTrue)
{
    // 如果当前是错误标记状态，不处理线型切换
    if (yanse == Qt::red) {
        return;
    }

    qDebug() << "切换线型:" << (isTrue ? "实线" : "虚线");
    shixian = isTrue;

    // 重新计算并绘制整个函数
    if (!hanshuFunction.isEmpty()) {
        // 清空并重新计算点
        points.clear();
        Hanshujisuan();

        // 完全重绘
        huanchong.fill(Qt::white);
        chonghui = true;
        update();
    }
}


void MainWindow::Wangge(int size)
{
    qDebug() << "接收到网格大小改变:" << size;
    wanggeSize = size;
    chonghui = true;
    update();
}
// void MainWindow::onCoordinateRangeChanged(double newXMin, double newXMax,
//                                           double newYMin, double newYMax)
// {
//     // 验证输入值的有效性
//     if (newXMin >= newXMax || newYMin >= newYMax) {
//         showError("坐标范围设置无效！");
//         return;
//     }

//     xMin = newXMin;
//     xMax = newXMax;
//     yMin = newYMin;
//     yMax = newYMax;

//     updateScaleAndOffset();
//     calculateFunctionPoints();
//     updateBuffer();
// }

void MainWindow::Wanggeshow(bool visible)
{
    showWangge = visible;
    chonghui = true;    // 添加重绘标记
    Updatehuanchong();       // 更新缓冲
    update();            // 触发重绘
}
void MainWindow::Biaoqianshow(bool visible)
{
    showLabels = visible;
    chonghui = true;    // 添加重绘标记
    Updatehuanchong();       // 更新缓冲
    update();            // 触发重绘
}

void MainWindow::Exportplot()
{
    // 首先选择背景颜色
    QColor backgroundColor = QColorDialog::getColor(Qt::white, this, "选择导出图像的背景颜色");
    if (!backgroundColor.isValid()) {
        return;  // 如果用户取消颜色选择则退出
    }

    // 然后选择保存路径
    QString filePath = QFileDialog::getSaveFileName(
        this,
        "选择保存位置",
        QDir::homePath() + "/未命名.png",
        "PNG 图像 (*.png);;JPEG 图像 (*.jpg *.jpeg);;所有文件 (*.*)"
        );

    if (!filePath.isEmpty()) {
        // 创建临时pixmap用于导出
        QPixmap exportPixmap = huanchong;
        QPainter painter(&exportPixmap);

        // 使用选择的背景颜色
        painter.fillRect(exportPixmap.rect(), backgroundColor);

        // 重新绘制所有内容
        if (showWangge) {
            Wanggedraw(painter);
        }
        XYdraw(painter);
        if (showLabels) {
            Labelsdraw(painter);
        }
        if (!hanshuFunction.isEmpty()) {
            Huabi(painter);
        }

        // 保存图像
        if (exportPixmap.save(filePath)) {
            Showxiaoxi(QString("图像已成功导出到: %1\n背景颜色: #%2")
                           .arg(filePath)
                           .arg(backgroundColor.name()));
        } else {
            Showcuowu("导出失败！");
        }
    }
}

void MainWindow::Clearplot()
{
    hanshuFunction.clear();
    points.clear();
    Updatehuanchong();
    Showxiaoxi("图像已清除");
}

void MainWindow::Showcuowu(const QString& message)
{
    QMessageBox::warning(this, "错误", message);
    xiaoxiBar->showMessage("错误: " + message, 3000);
}

void MainWindow::Showxiaoxi(const QString& message)
{
    xiaoxiBar->showMessage(message, 3000);
}

// 窗口关闭事件
void MainWindow::closeEvent(QCloseEvent* event)
{
    if (kongzhichuang) {
        kongzhichuang->close();
        delete kongzhichuang;
        kongzhichuang = nullptr;
    }
    event->accept();
}

void MainWindow::Suofangupdate()
{
    // 计算缩放比例和偏移量
    biliX = width() / (xMax - xMin);
    biliY = height() / (yMax - yMin);

    pianyiX = -xMin * biliX;
    pianyiY = yMax * biliY;

    // 更新缓冲区大小
    if (size() != huanchong.size()) {
        huanchong = QPixmap(size());
    }

    // 触发重绘
    chonghui = true;
    update();
}

void MainWindow::XMin(double value)
{
    // 如果输入值小于x的最大值，更新x的最小值并进行缩放和重绘
    if (value < xMax) {
        xMin = value;
        Suofangupdate();   // 更新缩放比例和偏移量
        Hanshujisuan();    // 重新计算函数点
        Updatehuanchong(); // 更新缓冲区并重绘
    }
}

void MainWindow::XMax(double value)
{
    // 如果输入值大于x的最小值，更新x的最大值并进行缩放和重绘
    if (value > xMin) {
        xMax = value;
        Suofangupdate();   // 更新缩放比例和偏移量
        Hanshujisuan();    // 重新计算函数点
        Updatehuanchong(); // 更新缓冲区并重绘
    }
}

void MainWindow::YMin(double value)
{
    // 如果输入值小于y的最大值，更新y的最小值并进行缩放和重绘
    if (value < yMax) {
        yMin = value;
        Suofangupdate();   // 更新缩放比例和偏移量
        Hanshujisuan();    // 重新计算函数点
        Updatehuanchong(); // 更新缓冲区并重绘
    }
}

void MainWindow::YMax(double value)
{
    // 如果输入值大于y的最小值，更新y的最大值并进行缩放和重绘
    if (value > yMin) {
        yMax = value;
        Suofangupdate();   // 更新缩放比例和偏移量
        Hanshujisuan();    // 重新计算函数点
        Updatehuanchong(); // 更新缓冲区并重绘
    }
}

void MainWindow::resetHuanyuan()
{
    // 重置所有值到默认状态
    wanggeSize = 1;
    xianWidth = 2;
    xMin = -10.0;
    xMax = 10.0;
    yMin = -10.0;
    yMax = 10.0;

    // 更新显示
    Suofangupdate();
    Hanshujisuan();
    Updatehuanchong();

    // 显示提示信息
    Showxiaoxi("已重置为默认值");
}

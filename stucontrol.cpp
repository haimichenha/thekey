#include "stucontrol.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QGroupBox>
#include <QMessageBox>
#include <QColor>
#include <QCheckBox>

StuControl::StuControl(QWidget *parent)
    : QDialog(parent)                  // 调用父类QDialog的构造函数，并传入父窗口参数
    , isLine(true)                     // 初始化标记为实线
    // 函数组，初始化各个指针为空
    , hanshuGroup(nullptr)
    , hanshuInput(nullptr)
    , drawButton(nullptr)
    // 范围和坐标组，初始化各个指针为空
    , zuobiaoGroup(nullptr)
    , xMinSpin(nullptr)
    , xMaxSpin(nullptr)
    , yMinSpin(nullptr)
    , yMaxSpin(nullptr)
    , wanggeSizeSpinBox(nullptr)
    // 样式组，初始化各个指针为空
    , styleGroup(nullptr)
    , yanseButton(nullptr)
    , xianStyleButton(nullptr)
    , xiankuanSpin(nullptr)
    // 显示组，初始化各个指针为空
    , xianshiGroup(nullptr)
    , wanggekejianCheck(nullptr)
    , labelKejianCheck(nullptr)
    // 其他按钮，初始化各个指针为空
    , exportButton(nullptr)
    , clearButton(nullptr)
    , resetButton(nullptr)
{
    // 设置窗口标志，使窗口始终位于顶部
    setWindowFlags(Qt::Window | Qt::WindowStaysOnTopHint);
    // 设置窗口为非模态
    setModal(false);
    // 设置窗口标题为"控制面板"
    setWindowTitle("控制面板");
    // 设置窗口的最小尺寸
    setMinimumSize(300, 400);

    // 初始化用户界面
    initUI();
    // 设置信号和槽的连接
    setupConnections();
}


StuControl::~StuControl()
{
    // 析构函数
}

void StuControl::initUI()
{
    // 创建主布局
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(10); // 设置主布局的间距为10

    // 创建各个功能组
    hanshuzu();                 // 调用函数创建函数输入组
    shixianzu();                // 调用函数创建样式设置组
    wanggezuobiaoGroup();       // 调用函数创建网格坐标组
    wanggeLabelGroup();         // 调用函数创建网格标签组

    // 添加功能组到主布局
    mainLayout->addWidget(hanshuGroup); // 添加函数输入组到主布局
    mainLayout->addWidget(styleGroup);  // 添加样式设置组到主布局
    mainLayout->addWidget(zuobiaoGroup); // 添加网格坐标组到主布局
    mainLayout->addWidget(xianshiGroup); // 添加网格标签组到主布局

    // 创建操作按钮
    exportButton = new QPushButton("导出图像", this); // 创建导出图像按钮
    clearButton = new QPushButton("清除图像", this);  // 创建清除图像按钮

    // 添加按钮到主布局
    QHBoxLayout* buttonLayout = new QHBoxLayout; // 创建水平布局用于放置按钮
    buttonLayout->addWidget(exportButton);       // 将导出图像按钮添加到水平布局
    buttonLayout->addWidget(clearButton);        // 将清除图像按钮添加到水平布局
    mainLayout->addLayout(buttonLayout);         // 将水平布局添加到主布局

    // 添加弹簧
    mainLayout->addStretch(); // 添加弹簧，将按钮布局推到顶端

    setLayout(mainLayout);    // 设置主布局为窗口的布局
}

void StuControl::hanshuzu()
{
    hanshuGroup = new QGroupBox("函数输入", this); // 创建函数输入组框
    QVBoxLayout* layout = new QVBoxLayout;         // 创建垂直布局用于放置控件

    // 创建函数输入框
    hanshuInput = new QLineEdit(this); // 创建行编辑用于输入函数表达式
    hanshuInput->setPlaceholderText("请输入函数表达式"); // 设置占位符文本

    // 创建绘制按钮
    drawButton = new QPushButton("绘制", this); // 创建绘制按钮

    // 添加到布局
    layout->addWidget(hanshuInput); // 将函数输入框添加到垂直布局
    layout->addWidget(drawButton);  // 将绘制按钮添加到垂直布局

    hanshuGroup->setLayout(layout); // 设置垂直布局为函数输入组框的布局
}

void StuControl::shixianzu()
{
    styleGroup = new QGroupBox("样式设置", this); // 创建样式设置组框
    QGridLayout* layout = new QGridLayout(styleGroup); // 创建网格布局用于放置控件

    // 线宽设置
    layout->addWidget(new QLabel("线宽:", this), 0, 0); // 在网格布局的第0行第0列添加标签
    xiankuanSpin = new QSpinBox(this); // 创建旋转框用于设置线宽
    xiankuanSpin->setRange(1, 10); // 设置线宽旋转框的范围
    xiankuanSpin->setValue(2); // 设置线宽旋转框的初始值
    layout->addWidget(xiankuanSpin, 0, 1); // 在网格布局的第0行第1列添加线宽旋转框

    // 颜色设置
    yanseButton = new QPushButton("颜色", this); // 创建颜色按钮
    layout->addWidget(yanseButton, 1, 0); // 在网格布局的第1行第0列添加颜色按钮

    // 线型设置
    xianStyleButton = new QPushButton("实线", this); // 创建线型按钮
    layout->addWidget(xianStyleButton, 1, 1); // 在网格布局的第1行第1列添加线型按钮

    styleGroup->setLayout(layout); // 设置网格布局为样式设置组框的布局
}


void StuControl::wanggezuobiaoGroup()
{
    zuobiaoGroup = new QGroupBox("坐标设置", this); // 创建坐标设置组框
    QVBoxLayout* coordLayout = new QVBoxLayout(zuobiaoGroup); // 创建垂直布局用于放置控件，并将其设置为组框的布局

    // 网格设置
    QHBoxLayout* gridLayout = new QHBoxLayout; // 创建水平布局用于放置网格大小控件
    wanggeSizeSpinBox = new QSpinBox(this); // 创建旋转框用于设置网格大小
    wanggeSizeSpinBox->setRange(1, 10); // 设置网格大小旋转框的范围
    wanggeSizeSpinBox->setValue(1); // 设置网格大小旋转框的初始值
    gridLayout->addWidget(new QLabel("网格大小:", this)); // 在水平布局中添加标签
    gridLayout->addWidget(wanggeSizeSpinBox); // 在水平布局中添加网格大小旋转框
    coordLayout->addLayout(gridLayout); // 将网格大小设置布局添加到垂直布局中

    // 坐标范围设置
    QGridLayout* rangeLayout = new QGridLayout; // 创建网格布局用于放置坐标范围控件

    xMinSpin = new QDoubleSpinBox(this); // 创建双精度旋转框用于设置x最小值
    xMaxSpin = new QDoubleSpinBox(this); // 创建双精度旋转框用于设置x最大值
    yMinSpin = new QDoubleSpinBox(this); // 创建双精度旋转框用于设置y最小值
    yMaxSpin = new QDoubleSpinBox(this); // 创建双精度旋转框用于设置y最大值

    // 将所有旋转框添加到列表中，方便统一设置
    const QList<QDoubleSpinBox*> spinBoxes = {xMinSpin, xMaxSpin, yMinSpin, yMaxSpin};
    for (auto spinBox : spinBoxes) {
        spinBox->setRange(-1000, 1000); // 设置旋转框的范围
        spinBox->setSingleStep(1); // 设置旋转框的步长
        spinBox->setDecimals(2); // 设置旋转框的小数位数
    }

    // 设置默认值
    xMinSpin->setValue(-10); // 设置x最小值的默认值
    xMaxSpin->setValue(10); // 设置x最大值的默认值
    yMinSpin->setValue(-10); // 设置y最小值的默认值
    yMaxSpin->setValue(10); // 设置y最大值的默认值

    // 将标签和旋转框添加到网格布局中
    rangeLayout->addWidget(new QLabel("X最小值:"), 0, 0); // 添加X最小值标签到网格布局的第0行第0列
    rangeLayout->addWidget(xMinSpin, 0, 1); // 添加X最小值旋转框到网格布局的第0行第1列
    rangeLayout->addWidget(new QLabel("X最大值:"), 0, 2); // 添加X最大值标签到网格布局的第0行第2列
    rangeLayout->addWidget(xMaxSpin, 0, 3); // 添加X最大值旋转框到网格布局的第0行第3列
    rangeLayout->addWidget(new QLabel("Y最小值:"), 1, 0); // 添加Y最小值标签到网格布局的第1行第0列
    rangeLayout->addWidget(yMinSpin, 1, 1); // 添加Y最小值旋转框到网格布局的第1行第1列
    rangeLayout->addWidget(new QLabel("Y最大值:"), 1, 2); // 添加Y最大值标签到网格布局的第1行第2列
    rangeLayout->addWidget(yMaxSpin, 1, 3); // 添加Y最大值旋转框到网格布局的第1行第3列

    coordLayout->addLayout(rangeLayout); // 将坐标范围设置布局添加到垂直布局中
}

void StuControl::wanggeLabelGroup()
{
    xianshiGroup = new QGroupBox("显示选项", this); // 创建显示选项组框
    QVBoxLayout* mainLayout = new QVBoxLayout; // 创建垂直布局用于放置控件

    // 创建一个水平布局用于放置两个复选框
    QHBoxLayout* checkboxLayout = new QHBoxLayout; // 创建水平布局用于放置复选框

    // 创建复选框
    wanggekejianCheck = new QCheckBox("显示网格", this); // 创建复选框用于控制网格显示
    labelKejianCheck = new QCheckBox("显示标签", this); // 创建复选框用于控制标签显示
    wanggekejianCheck->setChecked(true); // 设置网格显示复选框为选中状态
    labelKejianCheck->setChecked(true); // 设置标签显示复选框为选中状态

    // 将两个复选框添加到水平布局中
    checkboxLayout->addWidget(wanggekejianCheck); // 将网格显示复选框添加到水平布局中
    checkboxLayout->addWidget(labelKejianCheck); // 将标签显示复选框添加到水平布局中

    // 创建重置按钮
    resetButton = new QPushButton("重置默认值", this); // 创建重置按钮
    resetButton->setFixedHeight(30); // 设置重置按钮的固定高度为30像素

    // 将水平布局（包含复选框）添加到主布局
    mainLayout->addLayout(checkboxLayout); // 将复选框水平布局添加到垂直主布局中

    // 添加一些间距
    mainLayout->addSpacing(5); // 在主布局中添加5像素的间距

    // 添加重置按钮
    mainLayout->addWidget(resetButton); // 将重置按钮添加到主布局中

    xianshiGroup->setLayout(mainLayout); // 设置垂直主布局为显示选项组框的布局
}



void StuControl::setupConnections()
{
    // 函数绘制相关
    if (drawButton && hanshuInput) {
        connect(drawButton, &QPushButton::clicked,
                this, &StuControl::onHuihua); // 连接绘制按钮的点击信号到绘制函数槽
        connect(hanshuInput, &QLineEdit::returnPressed,
                this, &StuControl::onHuihua); // 连接函数输入框的回车信号到绘制函数槽
    }

    // 样式设置相关
    if (yanseButton) {
        connect(yanseButton, &QPushButton::clicked, this, [this]() {
            QColor color = QColorDialog::getColor(Qt::black, this); // 弹出颜色选择对话框，默认颜色为黑色
            if (color.isValid()) {
                emit yanseSig(color); // 如果选择了有效颜色，发送颜色信号
            }
        });
    }

    if (xiankuanSpin) {
        connect(xiankuanSpin, QOverload<int>::of(&QSpinBox::valueChanged),
                this, &StuControl::xiankuanSig); // 连接线宽旋转框的值变化信号到线宽信号槽
    }

    if (xianStyleButton) {
        connect(xianStyleButton, &QPushButton::clicked,
                this, &StuControl::onShixian); // 连接线型按钮的点击信号到线型槽函数
    }

    // 坐标范围设置相关
    if (xMinSpin && xMaxSpin && yMinSpin && yMaxSpin) {
        connect(xMinSpin, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
                this, &StuControl::xSmin); // 连接x最小值旋转框的值变化信号到x最小值槽函数
        connect(xMaxSpin, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
                this, &StuControl::xSmax); // 连接x最大值旋转框的值变化信号到x最大值槽函数
        connect(yMinSpin, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
                this, &StuControl::ySmin); // 连接y最小值旋转框的值变化信号到y最小值槽函数
        connect(yMaxSpin, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
                this, &StuControl::ySmax); // 连接y最大值旋转框的值变化信号到y最大值槽函数
    }

    // 网格设置相关
    if (wanggeSizeSpinBox) {
        connect(wanggeSizeSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
                this, &StuControl::onwanggeSize); // 连接网格大小旋转框的值变化信号到网格大小槽函数
    }

    // 显示选项相关
    if (wanggekejianCheck) {
        connect(wanggekejianCheck, &QCheckBox::toggled,
                this, &StuControl::wanggeSig); // 连接网格显示复选框的切换信号到网格信号槽
    }

    if (labelKejianCheck) {
        connect(labelKejianCheck, &QCheckBox::toggled,
                this, &StuControl::labelSig); // 连接标签显示复选框的切换信号到标签信号槽
    }

    if (resetButton) {
        connect(resetButton, &QPushButton::clicked,
                this, [this]() {
                    emit resetRequested();  // 发送重置信号
                });
    }

    // 操作按钮相关
    if (exportButton) {
        connect(exportButton, &QPushButton::clicked,
                this, &StuControl::exportRequested); // 连接导出按钮的点击信号到导出请求槽
    }

    if (clearButton) {
        connect(clearButton, &QPushButton::clicked,
                this, &StuControl::clearRequested); // 连接清除按钮的点击信号到清除请求槽
    }
}

void StuControl::onHuihua()
{
    QString biaodashi = hanshuInput->text().trimmed(); // 获取并修剪函数输入框中的文本
    if (!biaodashi.isEmpty()) {
        emit drawBiaodashi(biaodashi); // 如果表达式不为空，发送绘制表达式信号
    }
}

void StuControl::onYanse(int index)
{
    QColor color;
    switch (index) {
    case 0: // 黑色
        color = Qt::black; // 设置颜色为黑色
        break;
    case 1: // 红色
        color = Qt::red; // 设置颜色为红色
        break;
    case 2: // 蓝色
        color = Qt::blue; // 设置颜色为蓝色
        break;
    case 3: // 绿色
        color = Qt::green; // 设置颜色为绿色
        break;
    default:
        color = Qt::black; // 默认设置颜色为黑色
    }
    emit yanseSig(color); // 发送颜色信号
}

void StuControl::onXiankuan(int width)
{
    emit xiankuanSig(width); // 发送线宽信号，传递新的线宽值
}

void StuControl::onShixian()
{
    isLine = !isLine; // 切换线型状态
    xianStyleButton->setText(isLine ? "实线" : "虚线"); // 更新按钮文本，根据当前线型状态设置为"实线"或"虚线"
    qDebug() << "切换线型状态:" << isLine; // 输出调试信息，显示当前线型状态
    emit shixianSig(isLine); // 发送线型信号，传递当前线型状态
    update(); // 请求更新窗口，触发重绘事件
}

void StuControl::onwanggeSize(int size)
{
    emit wanggeSizeSig(size); // 发送网格大小信号，传递新的网格大小值
}


// 获取当前设置值的函数，这部分是原本发射信号的函数容器，但是可以直接信号连接槽，即使是两个不同的窗口
// QString StuControl::hanshuGet() const         //也能通过这样信号连接槽来实现连接，那么发射信号的容器就没有必要用，注释掉
// {
//     return hanshuInput->text();
// }

// QColor StuControl::yanseGet() const
// {
//     switch (yanseSelect->currentIndex()) {
//     case 0: return Qt::black;
//     case 1: return Qt::red;
//     case 2: return Qt::blue;
//     case 3: return Qt::green;
//     default: return Qt::black;
//     }
// }

// int StuControl::xiankuanGet() const
// {
//     return xiankuanSpin ? xiankuanSpin->value() : 2;
// }

// bool StuControl::shixianIs() const
// {
//     return isLine;
// }

// void StuControl::FanweiGet(double& xSmin, double& xSmax,
//                            double& ySmin, double& ySmax) const
// {
//     xSmin = xMinSpin->value();
//     xSmax = xMaxSpin->value();
//     ySmin = yMinSpin->value();
//     ySmax = yMaxSpin->value();
// }

// int StuControl::wanggeSize() const
// {
//     return wanggeSizeSpinBox ? wanggeSizeSpinBox->value() : 1;
// }

/*bool StuControl::wanggeIs() const
{
    return wanggekejianCheck->isChecked();
}

bool StuControl::labelIs() const
{
    return labelKejianCheck->isChecked();
}*/

void StuControl::resetSHuanyuan()
{
    // 重置函数输入
    if (hanshuInput) {
        hanshuInput->clear(); // 清空函数输入框
    }

    // 重置坐标范围
    if (xMinSpin) {
        xMinSpin->setValue(-10.0); // 重置x最小值为-10.0
    }
    if (xMaxSpin) {
        xMaxSpin->setValue(10.0); // 重置x最大值为10.0
    }
    if (yMinSpin) {
        yMinSpin->setValue(-10.0); // 重置y最小值为-10.0
    }
    if (yMaxSpin) {
        yMaxSpin->setValue(10.0); // 重置y最大值为10.0
    }

    // 重置样式设置
    isLine = true; // 重置线型为实线
    if (xianStyleButton) {
        xianStyleButton->setText("实线"); // 更新线型按钮文本为“实线”
    }
    if (xiankuanSpin) {
        xiankuanSpin->setValue(2); // 重置线宽为2
    }

    // 重置网格大小
    if (wanggeSizeSpinBox) {
        wanggeSizeSpinBox->setValue(1); // 重置网格大小为1
    }

    // 重置显示选项
    if (wanggekejianCheck) {
        wanggekejianCheck->setChecked(true); // 重置网格显示为选中状态
    }
    if (labelKejianCheck) {
        labelKejianCheck->setChecked(true); // 重置标签显示为选中状态
    }
}

void StuControl::shixianjingyong(bool enabled)
{
    if (xianStyleButton) {
        xianStyleButton->setEnabled(enabled); // 启用或禁用线型按钮
    }
}

void StuControl::ExportSpanduan(bool enabled)
{
    if (exportButton) {
        exportButton->setEnabled(enabled); // 启用或禁用导出按钮
    }
}

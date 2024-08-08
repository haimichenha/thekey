/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label_49;
    QLabel *label_48;
    QGraphicsView *graphicsView1;
    QWidget *widget;
    QFrame *linefen1;
    QFrame *linefen3;
    QLabel *label_7;
    QComboBox *comboBox1;
    QLabel *label_8;
    QPushButton *pushButton;
    QComboBox *comboBox2;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QSpinBox *spinBox1;
    QLabel *label_3;
    QSpinBox *spinBox2;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_6;
    QLabel *label_4;
    QSpinBox *spinBox3;
    QLabel *label_5;
    QSpinBox *spinBox4;
    QFrame *linefen2_5;
    QLabel *label_9;
    QLabel *label_10;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_41;
    QLabel *label_42;
    QSpinBox *spinBoxF1;
    QLabel *label_43;
    QSpinBox *spinBoxF2;
    QWidget *layoutWidget21;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_44;
    QLabel *label_45;
    QSpinBox *spinBoxF3;
    QLabel *label_46;
    QSpinBox *spinBoxF4;
    QCheckBox *checkBox;
    QGraphicsView *graphicsView2;
    QWidget *widget2;
    QDialogButtonBox *buttonBox;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(827, 644);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label_49 = new QLabel(centralwidget);
        label_49->setObjectName("label_49");
        label_49->setGeometry(QRect(240, 290, 241, 21));
        label_48 = new QLabel(centralwidget);
        label_48->setObjectName("label_48");
        label_48->setGeometry(QRect(540, 290, 141, 21));
        graphicsView1 = new QGraphicsView(centralwidget);
        graphicsView1->setObjectName("graphicsView1");
        graphicsView1->setGeometry(QRect(240, 310, 301, 261));
        graphicsView1->setStyleSheet(QString::fromUtf8("ont: 14pt \"MV Boli\";\n"
"background-color: rgb(255, 250, 244);"));
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(240, 170, 471, 121));
        linefen1 = new QFrame(widget);
        linefen1->setObjectName("linefen1");
        linefen1->setGeometry(QRect(140, 0, 16, 121));
        linefen1->setFrameShape(QFrame::VLine);
        linefen1->setFrameShadow(QFrame::Sunken);
        linefen3 = new QFrame(widget);
        linefen3->setObjectName("linefen3");
        linefen3->setGeometry(QRect(400, 0, 20, 121));
        linefen3->setFrameShape(QFrame::VLine);
        linefen3->setFrameShadow(QFrame::Sunken);
        label_7 = new QLabel(widget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(300, 0, 59, 20));
        comboBox1 = new QComboBox(widget);
        comboBox1->addItem(QString());
        comboBox1->addItem(QString());
        comboBox1->addItem(QString());
        comboBox1->addItem(QString());
        comboBox1->addItem(QString());
        comboBox1->setObjectName("comboBox1");
        comboBox1->setGeometry(QRect(290, 40, 91, 31));
        label_8 = new QLabel(widget);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(410, 50, 59, 20));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(410, 70, 51, 31));
        comboBox2 = new QComboBox(widget);
        comboBox2->addItem(QString());
        comboBox2->addItem(QString());
        comboBox2->addItem(QString());
        comboBox2->addItem(QString());
        comboBox2->addItem(QString());
        comboBox2->setObjectName("comboBox2");
        comboBox2->setGeometry(QRect(290, 90, 91, 31));
        layoutWidget1 = new QWidget(widget);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(0, 0, 61, 121));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget1);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        spinBox1 = new QSpinBox(layoutWidget1);
        spinBox1->setObjectName("spinBox1");

        verticalLayout->addWidget(spinBox1);

        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName("label_3");

        verticalLayout->addWidget(label_3);

        spinBox2 = new QSpinBox(layoutWidget1);
        spinBox2->setObjectName("spinBox2");
        spinBox2->setStyleSheet(QString::fromUtf8("font: 12pt \"Microsoft YaHei UI\";"));

        verticalLayout->addWidget(spinBox2);

        layoutWidget = new QWidget(widget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(70, 0, 64, 121));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName("label_6");

        verticalLayout_2->addWidget(label_6);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName("label_4");

        verticalLayout_2->addWidget(label_4);

        spinBox3 = new QSpinBox(layoutWidget);
        spinBox3->setObjectName("spinBox3");
        spinBox3->setStyleSheet(QString::fromUtf8("font: 9pt \"\346\245\267\344\275\223\";"));

        verticalLayout_2->addWidget(spinBox3);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName("label_5");

        verticalLayout_2->addWidget(label_5);

        spinBox4 = new QSpinBox(layoutWidget);
        spinBox4->setObjectName("spinBox4");
        spinBox4->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";\n"
"font: 12pt \"Microsoft YaHei UI\";"));

        verticalLayout_2->addWidget(spinBox4);

        linefen2_5 = new QFrame(widget);
        linefen2_5->setObjectName("linefen2_5");
        linefen2_5->setGeometry(QRect(280, 0, 21, 121));
        linefen2_5->setFrameShape(QFrame::VLine);
        linefen2_5->setFrameShadow(QFrame::Sunken);
        label_9 = new QLabel(widget);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(290, 20, 31, 16));
        label_10 = new QLabel(widget);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(290, 70, 31, 16));
        layoutWidget2 = new QWidget(widget);
        layoutWidget2->setObjectName("layoutWidget2");
        layoutWidget2->setGeometry(QRect(161, 0, 51, 121));
        verticalLayout_4 = new QVBoxLayout(layoutWidget2);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_41 = new QLabel(layoutWidget2);
        label_41->setObjectName("label_41");

        verticalLayout_4->addWidget(label_41);

        label_42 = new QLabel(layoutWidget2);
        label_42->setObjectName("label_42");

        verticalLayout_4->addWidget(label_42);

        spinBoxF1 = new QSpinBox(layoutWidget2);
        spinBoxF1->setObjectName("spinBoxF1");

        verticalLayout_4->addWidget(spinBoxF1);

        label_43 = new QLabel(layoutWidget2);
        label_43->setObjectName("label_43");

        verticalLayout_4->addWidget(label_43);

        spinBoxF2 = new QSpinBox(layoutWidget2);
        spinBoxF2->setObjectName("spinBoxF2");
        spinBoxF2->setStyleSheet(QString::fromUtf8("font: 12pt \"Microsoft YaHei UI\";"));

        verticalLayout_4->addWidget(spinBoxF2);

        layoutWidget21 = new QWidget(widget);
        layoutWidget21->setObjectName("layoutWidget21");
        layoutWidget21->setGeometry(QRect(230, 0, 51, 121));
        verticalLayout_5 = new QVBoxLayout(layoutWidget21);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_44 = new QLabel(layoutWidget21);
        label_44->setObjectName("label_44");

        verticalLayout_5->addWidget(label_44);

        label_45 = new QLabel(layoutWidget21);
        label_45->setObjectName("label_45");

        verticalLayout_5->addWidget(label_45);

        spinBoxF3 = new QSpinBox(layoutWidget21);
        spinBoxF3->setObjectName("spinBoxF3");

        verticalLayout_5->addWidget(spinBoxF3);

        label_46 = new QLabel(layoutWidget21);
        label_46->setObjectName("label_46");

        verticalLayout_5->addWidget(label_46);

        spinBoxF4 = new QSpinBox(layoutWidget21);
        spinBoxF4->setObjectName("spinBoxF4");
        spinBoxF4->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";"));

        verticalLayout_5->addWidget(spinBoxF4);

        checkBox = new QCheckBox(widget);
        checkBox->setObjectName("checkBox");
        checkBox->setGeometry(QRect(410, 30, 71, 21));
        graphicsView2 = new QGraphicsView(centralwidget);
        graphicsView2->setObjectName("graphicsView2");
        graphicsView2->setGeometry(QRect(540, 310, 171, 261));
        graphicsView2->setStyleSheet(QString::fromUtf8("ont: 14pt \"MV Boli\";\n"
"background-color: rgb(255, 250, 244);"));
        widget2 = new QWidget(centralwidget);
        widget2->setObjectName("widget2");
        widget2->setGeometry(QRect(220, 140, 551, 471));
        buttonBox = new QDialogButtonBox(widget2);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(350, 0, 164, 18));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 827, 17));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        dockWidget = new QDockWidget(MainWindow);
        dockWidget->setObjectName("dockWidget");
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName("dockWidgetContents");
        dockWidget->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(Qt::LeftDockWidgetArea, dockWidget);
        QWidget::setTabOrder(graphicsView1, comboBox1);
        QWidget::setTabOrder(comboBox1, pushButton);
        QWidget::setTabOrder(pushButton, comboBox2);
        QWidget::setTabOrder(comboBox2, spinBox1);
        QWidget::setTabOrder(spinBox1, spinBox2);
        QWidget::setTabOrder(spinBox2, spinBox3);
        QWidget::setTabOrder(spinBox3, spinBox4);
        QWidget::setTabOrder(spinBox4, spinBoxF1);
        QWidget::setTabOrder(spinBoxF1, spinBoxF2);
        QWidget::setTabOrder(spinBoxF2, spinBoxF3);
        QWidget::setTabOrder(spinBoxF3, spinBoxF4);
        QWidget::setTabOrder(spinBoxF4, checkBox);
        QWidget::setTabOrder(checkBox, graphicsView2);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_49->setText(QCoreApplication::translate("MainWindow", "\347\273\230\345\210\266\345\233\276\345\203\217\345\214\205\345\220\253\345\207\275\346\225\260\344\270\200(\350\223\235)\345\207\275\346\225\260\344\272\214(\347\272\242):", nullptr));
        label_48->setText(QCoreApplication::translate("MainWindow", "\345\233\272\345\256\232\345\233\276\345\203\217(\351\232\220\350\227\217/\346\230\276\347\244\272):", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\345\207\275\346\225\260\345\274\217\345\255\220:", nullptr));
        comboBox1->setItemText(0, QCoreApplication::translate("MainWindow", "y=x^2", nullptr));
        comboBox1->setItemText(1, QCoreApplication::translate("MainWindow", "y=ln(x)", nullptr));
        comboBox1->setItemText(2, QCoreApplication::translate("MainWindow", "y=sin(x)", nullptr));
        comboBox1->setItemText(3, QCoreApplication::translate("MainWindow", "y=cos(x)", nullptr));
        comboBox1->setItemText(4, QCoreApplication::translate("MainWindow", "y=sqrt(x)", nullptr));

#if QT_CONFIG(tooltip)
        comboBox1->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>\347\272\277<span style=\" vertical-align:sub;\">1</span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_8->setText(QCoreApplication::translate("MainWindow", "\345\233\276\345\203\217\346\215\225\346\215\211:", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\207\272", nullptr));
        comboBox2->setItemText(0, QCoreApplication::translate("MainWindow", "y=x^2", nullptr));
        comboBox2->setItemText(1, QCoreApplication::translate("MainWindow", "y=ln(x)", nullptr));
        comboBox2->setItemText(2, QCoreApplication::translate("MainWindow", "y=sin(x)", nullptr));
        comboBox2->setItemText(3, QCoreApplication::translate("MainWindow", "y=cos(x)", nullptr));
        comboBox2->setItemText(4, QCoreApplication::translate("MainWindow", "y=sqrt(x)", nullptr));

#if QT_CONFIG(tooltip)
        comboBox2->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>\347\272\277<span style=\" vertical-align:sub;\">2</span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label->setText(QCoreApplication::translate("MainWindow", "\345\220\221\344\270\212\345\267\246\347\247\273:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\345\207\217:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\345\220\221\344\270\212\345\212\240:", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\345\220\221\344\270\213\345\217\263\347\247\273", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\345\212\240:", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\345\220\221\344\270\213\345\207\217:", nullptr));
#if QT_CONFIG(tooltip)
        spinBox4->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_9->setText(QCoreApplication::translate("MainWindow", "\345\207\275\346\225\260\344\270\200", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "\345\207\275\346\225\260\344\272\214", nullptr));
        label_41->setText(QCoreApplication::translate("MainWindow", "\345\220\221\344\270\212\345\267\246\347\247\273", nullptr));
        label_42->setText(QCoreApplication::translate("MainWindow", "\345\207\217:", nullptr));
        label_43->setText(QCoreApplication::translate("MainWindow", "\345\220\221\344\270\212\345\212\240:", nullptr));
        label_44->setText(QCoreApplication::translate("MainWindow", "\345\220\221\344\270\213\345\217\263\347\247\273", nullptr));
        label_45->setText(QCoreApplication::translate("MainWindow", "\345\212\240:", nullptr));
        label_46->setText(QCoreApplication::translate("MainWindow", "\345\220\221\344\270\213\345\207\217:", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "\351\232\220\350\227\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

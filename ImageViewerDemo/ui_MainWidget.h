/********************************************************************************
** Form generated from reading UI file 'MainWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWIDGET_H
#define UI_MAINWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWidget
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *imageViewHost;

    void setupUi(QWidget *MainWidget)
    {
        if (MainWidget->objectName().isEmpty())
            MainWidget->setObjectName("MainWidget");
        MainWidget->resize(800, 600);
        gridLayout = new QGridLayout(MainWidget);
        gridLayout->setObjectName("gridLayout");
        imageViewHost = new QVBoxLayout();
        imageViewHost->setObjectName("imageViewHost");

        gridLayout->addLayout(imageViewHost, 0, 0, 1, 1);


        retranslateUi(MainWidget);

        QMetaObject::connectSlotsByName(MainWidget);
    } // setupUi

    void retranslateUi(QWidget *MainWidget)
    {
        MainWidget->setWindowTitle(QCoreApplication::translate("MainWidget", "MainWidget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWidget: public Ui_MainWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIDGET_H

/********************************************************************************
** Form generated from reading UI file 'ImageViewWidget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEVIEWWIDGET_H
#define UI_IMAGEVIEWWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageViewWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QToolButton *tbtn_selectImageFIle;
    QToolButton *tbtn_select;
    QToolButton *tbtn_zoom;
    QToolButton *tbtn_drawLine;
    QToolButton *tbtn_drawRectangle;
    QToolButton *tbtn_drawPolygon;
    QToolButton *tbtn_freeDraw;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QGridLayout *gridLayout;
    QVBoxLayout *lay_viewHost;
    QLabel *lab_info;

    void setupUi(QWidget *ImageViewWidget)
    {
        if (ImageViewWidget->objectName().isEmpty())
            ImageViewWidget->setObjectName("ImageViewWidget");
        ImageViewWidget->resize(400, 317);
        horizontalLayout = new QHBoxLayout(ImageViewWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        tbtn_selectImageFIle = new QToolButton(ImageViewWidget);
        tbtn_selectImageFIle->setObjectName("tbtn_selectImageFIle");
        tbtn_selectImageFIle->setMinimumSize(QSize(34, 34));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/tools/images/image.svg"), QSize(), QIcon::Normal, QIcon::Off);
        tbtn_selectImageFIle->setIcon(icon);
        tbtn_selectImageFIle->setIconSize(QSize(24, 24));

        verticalLayout->addWidget(tbtn_selectImageFIle);

        tbtn_select = new QToolButton(ImageViewWidget);
        tbtn_select->setObjectName("tbtn_select");
        tbtn_select->setMinimumSize(QSize(34, 34));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/tools/images/Selection.svg"), QSize(), QIcon::Normal, QIcon::Off);
        tbtn_select->setIcon(icon1);
        tbtn_select->setIconSize(QSize(24, 24));

        verticalLayout->addWidget(tbtn_select);

        tbtn_zoom = new QToolButton(ImageViewWidget);
        tbtn_zoom->setObjectName("tbtn_zoom");
        tbtn_zoom->setMinimumSize(QSize(34, 34));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/tools/images/zoom-select.svg"), QSize(), QIcon::Normal, QIcon::Off);
        tbtn_zoom->setIcon(icon2);
        tbtn_zoom->setIconSize(QSize(24, 24));

        verticalLayout->addWidget(tbtn_zoom);

        tbtn_drawLine = new QToolButton(ImageViewWidget);
        tbtn_drawLine->setObjectName("tbtn_drawLine");
        tbtn_drawLine->setMinimumSize(QSize(34, 34));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/tools/images/line.svg"), QSize(), QIcon::Normal, QIcon::Off);
        tbtn_drawLine->setIcon(icon3);
        tbtn_drawLine->setIconSize(QSize(24, 24));

        verticalLayout->addWidget(tbtn_drawLine);

        tbtn_drawRectangle = new QToolButton(ImageViewWidget);
        tbtn_drawRectangle->setObjectName("tbtn_drawRectangle");
        tbtn_drawRectangle->setMinimumSize(QSize(34, 34));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/tools/images/rectangle.svg"), QSize(), QIcon::Normal, QIcon::Off);
        tbtn_drawRectangle->setIcon(icon4);
        tbtn_drawRectangle->setIconSize(QSize(24, 24));

        verticalLayout->addWidget(tbtn_drawRectangle);

        tbtn_drawPolygon = new QToolButton(ImageViewWidget);
        tbtn_drawPolygon->setObjectName("tbtn_drawPolygon");
        tbtn_drawPolygon->setMinimumSize(QSize(34, 34));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/tools/images/polygon.svg"), QSize(), QIcon::Normal, QIcon::Off);
        tbtn_drawPolygon->setIcon(icon5);
        tbtn_drawPolygon->setIconSize(QSize(24, 24));

        verticalLayout->addWidget(tbtn_drawPolygon);

        tbtn_freeDraw = new QToolButton(ImageViewWidget);
        tbtn_freeDraw->setObjectName("tbtn_freeDraw");
        tbtn_freeDraw->setMinimumSize(QSize(34, 34));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/tools/images/brush.svg"), QSize(), QIcon::Normal, QIcon::Off);
        tbtn_freeDraw->setIcon(icon6);
        tbtn_freeDraw->setIconSize(QSize(24, 24));

        verticalLayout->addWidget(tbtn_freeDraw);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        widget = new QWidget(ImageViewWidget);
        widget->setObjectName("widget");
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName("gridLayout");
        lay_viewHost = new QVBoxLayout();
        lay_viewHost->setObjectName("lay_viewHost");

        gridLayout->addLayout(lay_viewHost, 0, 0, 1, 1);


        verticalLayout_2->addWidget(widget);

        lab_info = new QLabel(ImageViewWidget);
        lab_info->setObjectName("lab_info");
        lab_info->setMaximumSize(QSize(16777215, 25));
        lab_info->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(lab_info);


        horizontalLayout->addLayout(verticalLayout_2);


        retranslateUi(ImageViewWidget);

        QMetaObject::connectSlotsByName(ImageViewWidget);
    } // setupUi

    void retranslateUi(QWidget *ImageViewWidget)
    {
        ImageViewWidget->setWindowTitle(QCoreApplication::translate("ImageViewWidget", "Form", nullptr));
        tbtn_selectImageFIle->setText(QString());
        tbtn_select->setText(QString());
        tbtn_zoom->setText(QString());
        tbtn_drawLine->setText(QString());
        tbtn_drawRectangle->setText(QString());
        tbtn_drawPolygon->setText(QString());
        tbtn_freeDraw->setText(QString());
        lab_info->setText(QCoreApplication::translate("ImageViewWidget", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ImageViewWidget: public Ui_ImageViewWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEVIEWWIDGET_H

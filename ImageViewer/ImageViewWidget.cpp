#include "ImageViewWidget.h"
#include "ui_ImageViewWidget.h"
#include <qmessagebox.h>
#include <QFileDialog>
#include <qimagereader.h>
#include <nmmintrin.h>//sse4.2
#include <qthread.h>
#include <qfuture.h>
#include <qfuturewatcher.h>
#include <QtConcurrent/QtConcurrent>

ImageViewWidget::ImageViewWidget(QWidget* parent) :
	QWidget(parent),
	ui(new Ui::ImageViewWidget),
	m_image_view(new ImageViewer())
{
	ui->setupUi(this);
	ui->lay_viewHost->addWidget(m_image_view);
	this->setMouseTracking(true);
	QImageReader::setAllocationLimit(0);
}

ImageViewWidget::~ImageViewWidget()
{
	delete ui;
}

QWidget* ImageViewWidget::getWidget(int index)
{
	switch (index)
	{
	case 0:
		return this;
		break;
	default:
		break;
	}

	return nullptr;
}

void ImageViewWidget::showImage(const QImage& image)
{
	m_image_view->setPixmap(QPixmap::fromImage(image));
}

void ImageViewWidget::showImage(const QPixmap& pixmap)
{
	m_image_view->setPixmap(pixmap);
}

void ImageViewWidget::on_showImage(const QPixmap& pixmap)
{
	m_image_view->setPixmap(pixmap);
}

void ImageViewWidget::on_tbtn_select_clicked()
{
	qDebug() << "select clicked : ";
}


void ImageViewWidget::on_tbtn_zoom_clicked()
{
	//qDebug() << "zoom clicked : ";
	m_image_view->fitShow();
}


void ImageViewWidget::on_tbtn_drawLine_clicked()
{
	qDebug() << "draw line clicked : ";
}


void ImageViewWidget::on_tbtn_drawRectangle_clicked()
{
	qDebug() << "draw rectangle clicked : ";
}


void ImageViewWidget::on_tbtn_drawPolygon_clicked()
{
	qDebug() << "draw polygon clicked : ";

}


void ImageViewWidget::on_tbtn_freeDraw_clicked()
{
	qDebug() << "free draw clicked : ";

}


void ImageViewWidget::on_tbtn_selectImageFIle_clicked()
{
	//open a image file
	QString file_name = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files(*.jpg *.png *.bmp)"));
	if (file_name.isEmpty())
	{
		return;
	}
	else
	{
		if (!(m_image.load(file_name)))
		{
			QMessageBox::information(this, tr("Error"), tr("Open Image Failed!"));
			return;
		}
		else
		{
			showImage(m_image);
		}
	}
}


#ifndef IMAGEVIEWWIDGET_H
#define IMAGEVIEWWIDGET_H

#include <QWidget>
#include <qmutex.h>
#include "ImageViewer_global.h"
#include "ImageViewer.h"

namespace Ui {
	class ImageViewWidget;
}

class ImageViewWidget :
	public QWidget
	, public ImageViewerInterface
{
	Q_OBJECT
		Q_PLUGIN_METADATA(IID ImageViewerInterface_IID)
		Q_INTERFACES(ImageViewerInterface)
public:
	explicit ImageViewWidget(QWidget* parent = nullptr);
	~ImageViewWidget();
	struct Bayer2BGR888ThreadData
	{
		uchar* src_data;
		uchar* dst_data;
		int width;
		int height;
		int type;
	};
public:
	virtual QWidget* getWidget(int index = 0) override;
	virtual void showImage(const QImage& image) override;
	virtual void showImage(const QPixmap& pixmap) override;
private:

signals:
	void sign_showImage(const QPixmap& pixmap);
private slots:
	void on_showImage(const QPixmap& pixmap);

	void on_tbtn_select_clicked();

	void on_tbtn_zoom_clicked();

	void on_tbtn_drawLine_clicked();

	void on_tbtn_drawRectangle_clicked();

	void on_tbtn_drawPolygon_clicked();

	void on_tbtn_freeDraw_clicked();

	void on_tbtn_selectImageFIle_clicked();

private:
	Ui::ImageViewWidget* ui;
	QPixmap m_pixmap;
	QImage m_image;
	QImage m_rgb_image;
	QBitmap m_marsk_bitmap;
	ImageViewer* m_image_view;
	QMutex m_mutex;
};

#endif // IMAGEVIEWWIDGET_H

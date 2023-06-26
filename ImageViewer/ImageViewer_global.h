#ifndef IMAGEVIEWER_GLOBAL_H
#define IMAGEVIEWER_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QObject>
#if defined(IMAGEVIEWER_LIBRARY)
#  define IMAGEVIEWER_EXPORT Q_DECL_EXPORT
#else
#  define IMAGEVIEWER_EXPORT Q_DECL_IMPORT
#endif

class ImageViewerInterface
{

public:
	~ImageViewerInterface() = default;

	virtual QWidget* getWidget(int index = 0) = 0;
	virtual void showImage(const QImage& _image) = 0;
	virtual void showImage(const QPixmap& _pixmap) = 0;
signals:
	void imageDispFinish(double _refresh_time);
};

QT_BEGIN_NAMESPACE
#define ImageViewerInterface_IID "org.qter.Modules.ImageViewerInterface"
Q_DECLARE_INTERFACE(ImageViewerInterface, ImageViewerInterface_IID)
QT_END_NAMESPACE


#endif // IMAGEVIEWER_GLOBAL_H

#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QWheelEvent>
#include <QMouseEvent>
#include "ImageViewerStyle.h"
#include "ShapeRectangle.h"

//a graphicsview class that can move and zoom
class ImageViewer
	:public QGraphicsView
{
	Q_OBJECT
public:
	ImageViewer(QWidget* parent = nullptr);
	~ImageViewer();
	enum ViewMode {
		FreeMode,
		TransMode,
		ZoomMode,
		DrawShape,
		FreeDraw,
		SelectShape
	};
	void setPixmap(const QPixmap& _pixmap);
	void fitShow();
protected:
	void resizeEvent(QResizeEvent* event);
	void wheelEvent(QWheelEvent* event);
	void drawBackground(QPainter* painter, const QRectF& r);
	void drawGrid(QPainter* painter, double gridStep);

	void mousePressEvent(QMouseEvent* e);
	void mouseMoveEvent(QMouseEvent* e);
	void mouseReleaseEvent(QMouseEvent* e);
private:
	QGraphicsScene* m_scene;
	QGraphicsPixmapItem* pixmapItem;
	QPixmap m_pixmap;

	qreal max_factor = 200;
	QPointF m_scenePos;
	QPointF m_pressPos;
	bool m_moveScene;
	qreal m_currentScale;

	ImageViewerStyleManager m_style_manager;
};

#endif // IMAGEVIEWER_H

#include "ImageViewer.h"
#include <qpalette.h>
#include <qcoreapplication.h>
#include "ShapeHandle.h"

ImageViewer::ImageViewer(QWidget* parent) :
	QGraphicsView(parent),
	m_scenePos(QPoint()),
	m_pressPos(QPoint()),
	m_moveScene(false),
	m_scene(new QGraphicsScene(this)),
	m_currentScale(1.0)
{
	setRenderHint(QPainter::Antialiasing);
	setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
	setBackgroundBrush(QBrush(QColor::fromRgb(80, 80, 80)));

	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	setCacheMode(QGraphicsView::CacheBackground);

	this->setScene(m_scene);

	m_style_manager.setConfigDir(QCoreApplication::applicationDirPath() + "/../Config");

	//add a shapehandle to test
	ShapeRectangle* rect = new ShapeRectangle();
	//rect->setRect(QRectF(0, 0, 100, 100));
	rect->setPos(QPointF(100, 100));
	m_scene->addItem(rect);

	pixmapItem = new QGraphicsPixmapItem();
	pixmapItem->setFlag(QGraphicsItem::ItemIsMovable, false);
	m_scene->addItem(pixmapItem);
	m_scene->setSceneRect(-50000, -50000, 100000, 100000);
}

ImageViewer::~ImageViewer()
{
}

void ImageViewer::setPixmap(const QPixmap& _pixmap)
{
	m_pixmap = _pixmap;
	pixmapItem->setPixmap(m_pixmap);
	QRect tmp_rect = m_pixmap.rect();
	//zoom the scene to fit show the image
	fitInView(pixmapItem, Qt::KeepAspectRatio);
	this->centerOn(tmp_rect.center());
	m_currentScale = 1.0;
}

void ImageViewer::fitShow()
{
	setPixmap(m_pixmap);
}

void ImageViewer::resizeEvent(QResizeEvent* event)
{
	QGraphicsView::resizeEvent(event);
	this->update();
}

void ImageViewer::wheelEvent(QWheelEvent* e)
{
	qreal scaleFactor = 1.15;
	//check qt version if qt versin greater than 6.0
#if (QT_VERSION <= QT_VERSION_CHECK(6,0,0))
	if (e->delta() > 0)
#else
	if (e->angleDelta().y() > 0)
#endif
	{
		if (m_currentScale < max_factor)
		{
			scale(scaleFactor, scaleFactor);
			m_currentScale *= scaleFactor;
		}
	}
	else if (m_currentScale > 0.1)
	{
		scale(1 / scaleFactor, 1 / scaleFactor);
		m_currentScale /= scaleFactor;
	}

	update();
}

void ImageViewer::mousePressEvent(QMouseEvent* e)
{
	QMouseEvent fake(e->type(), e->pos(), Qt::LeftButton, Qt::LeftButton, e->modifiers());

	m_scenePos = mapToScene(e->pos());
	m_pressPos = m_scenePos;

	if (e->button() == Qt::MiddleButton)
	{
		setDragMode(QGraphicsView::ScrollHandDrag);
		setInteractive(false);

		e = &fake;

		m_moveScene = true;
	}
	else if (e->button() == Qt::LeftButton)
	{
		setDragMode(QGraphicsView::RubberBandDrag);
	}
	else if (e->button() == Qt::RightButton)
	{

	}

	update();
	QGraphicsView::mousePressEvent(e);
}

void ImageViewer::mouseMoveEvent(QMouseEvent* e)
{
	m_scenePos = mapToScene(e->pos());

	if (m_moveScene)
	{
		QPointF difference = m_pressPos - m_scenePos;
		setSceneRect(sceneRect().translated(difference.x(), difference.y()));
	}

	update();
	QGraphicsView::mouseMoveEvent(e);
}

void ImageViewer::mouseReleaseEvent(QMouseEvent* e)
{
	QMouseEvent fake(e->type(), e->pos(), Qt::LeftButton, Qt::LeftButton, e->modifiers());

	if (e->button() == Qt::MiddleButton)
	{
		setDragMode(QGraphicsView::NoDrag);
		setInteractive(true);

		e = &fake;
	}

	m_moveScene = false;
	update();
	QGraphicsView::mouseReleaseEvent(e);
}

void ImageViewer::drawBackground(QPainter* painter, const QRectF& rect)
{
	QGraphicsView::drawBackground(painter, rect);
	static ImageViewerStyle style = m_style_manager.getImageViewerStyle("");
	static QBrush brush = QBrush(style.backgroundColor);
	static QPixmap bgImage(style.chess_width * 2, style.chess_width * 2);
#define DRAW_CHESS
#ifdef DRAW_CHESS
	bgImage.fill(style.backgroundColor);
	QPainter painter1(&bgImage);
	painter1.fillRect(0, 0, style.chess_width,
		style.chess_width,
		style.foregroundColor);
	painter1.fillRect(
		style.chess_width,
		style.chess_width,
		style.chess_width,
		style.chess_width,
		style.foregroundColor);
	painter1.end();
#if (QT_VERSION <= QT_VERSION_CHECK(6,0,0))
	painter->resetMatrix();
#else
	painter->resetTransform();
#endif
	painter->drawTiledPixmap(this->rect(), bgImage);
#else

	QPen pfine(QColor::fromRgb(50, 50, 50), 0.6);

	painter->setPen(pfine);
	drawGrid(painter, 15);

	QPen p(QColor::fromRgb(50, 50, 50), 2.0);

	painter->setPen(p);
	drawGrid(painter, 150);
#endif // DRAW_CHESS

}

void ImageViewer::drawGrid(QPainter* painter, double gridStep)
{
	QRect   windowRect = rect();
	QPointF tl = mapToScene(windowRect.topLeft());
	QPointF br = mapToScene(windowRect.bottomRight());

	double left = qFloor(tl.x() / gridStep - 0.5);
	double right = qFloor(br.x() / gridStep + 1.0);
	double bottom = qFloor(tl.y() / gridStep - 0.5);
	double top = qFloor(br.y() / gridStep + 1.0);

	for (int xi = int(left); xi <= int(right); ++xi)
	{
		QLineF line(xi * gridStep, bottom * gridStep,
			xi * gridStep, top * gridStep);

		painter->drawLine(line);
	}

	for (int yi = int(bottom); yi <= int(top); ++yi)
	{
		QLineF line(left * gridStep, yi * gridStep,
			right * gridStep, yi * gridStep);
		painter->drawLine(line);
	}

}


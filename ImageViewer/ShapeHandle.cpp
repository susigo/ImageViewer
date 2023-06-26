#include "ShapeHandle.h"
#include <qgraphicsscene.h>
#include <qgraphicsview.h>

int ShapeHandle::m_size = 10;
int ShapeHandle::m_hover_size = 15;
QColor ShapeHandle::m_default_color = QColor("#eb5424");
QColor ShapeHandle::m_hover_color = QColor("#ffdd00");
QPen ShapeHandle::m_pen = QPen(QBrush(m_default_color), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
QBrush ShapeHandle::m_brush = QBrush(m_default_color);

ShapeHandle::ShapeHandle(QGraphicsItem* parent)
	:QGraphicsItem(parent)
{
	setFlag(QGraphicsItem::ItemIsSelectable, true);
	setFlag(QGraphicsItem::ItemIsMovable, true);
	setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
	setAcceptHoverEvents(true);

	setZValue(1000);
	m_boundingRect = QRectF(-m_size / 2, -m_size / 2, m_size, m_size);
}

void ShapeHandle::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
	m_is_hovered = true;
	this->update();
}

void ShapeHandle::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
	m_is_hovered = false;
	this->update();
}

QRectF ShapeHandle::boundingRect() const
{
	return m_boundingRect;
}

void ShapeHandle::paint(QPainter* painter,
	const QStyleOptionGraphicsItem* option,
	QWidget* widget)
{
	double ratio = getSceneScalRatio();
	if (m_is_hovered)
	{
		int real_size = m_hover_size / ratio;
		m_boundingRect = QRectF(
			-real_size / 2,
			-real_size / 2,
			real_size,
			real_size);
		m_pen.setColor(m_hover_color);
		m_brush.setColor(m_hover_color);
	}
	else
	{
		int real_size = m_size / ratio;
		m_boundingRect = QRectF(
			-real_size / 2,
			-real_size / 2,
			real_size,
			real_size);
		m_pen.setColor(m_default_color);
		m_brush.setColor(m_default_color);
	}
	m_brush.setStyle(Qt::SolidPattern);
	painter->setBrush(m_brush);
	painter->setPen(Qt::NoPen);
	painter->setRenderHint(QPainter::Antialiasing, false);
	painter->drawRect(m_boundingRect);
	//qDebug() << "scene ratio : " << getSceneScalRatio();
}

//get the ratio of the scene to the screen
double ShapeHandle::getSceneScalRatio()
{
	auto a = this->scene()->views().at(0)->transform();
	return a.m11();
}

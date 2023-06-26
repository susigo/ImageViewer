#include "ShapeBase.h"
#include <qgraphicsscene.h>
#include <qgraphicsview.h>

QColor ShapeBase::m_default_color = QColor("#00a4e4");
QColor ShapeBase::m_hover_color = QColor("#aa7ac143");
QPen ShapeBase::m_pen = QPen(m_default_color, 1);
QBrush ShapeBase::m_brush = QBrush(m_hover_color);

ShapeBase::ShapeBase(QGraphicsItem* parent)
	:QGraphicsItem(parent)
{
	setFlag(QGraphicsItem::ItemIsSelectable, true);
	setFlag(QGraphicsItem::ItemIsMovable, true);
	setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
	setAcceptHoverEvents(true);
	setZValue(1000);
}

void ShapeBase::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
	m_is_hovered = true;
	this->update();
}

void ShapeBase::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
	m_is_hovered = false;
	this->update();
}

void ShapeBase::focusInEvent(QFocusEvent* event)
{
	m_is_selected = true;
	for (auto& elem : m_handles)
		elem->setVisible(true);
	this->update();
}

void ShapeBase::focusOutEvent(QFocusEvent* event)
{
	m_is_selected = false;
	for (auto& elem : m_handles)
		elem->setVisible(false);
	this->update();
}

QRectF ShapeBase::boundingRect() const
{
	return m_boundingRect;
}

QPainterPath ShapeBase::shape() const
{
	QPainterPath path;
	path.addPath(m_shape_path);
	return path;
}

void ShapeBase::paint(QPainter* painter,
	const QStyleOptionGraphicsItem* option,
	QWidget* widget)
{
	double ratio = getSceneScalRatio();
	double pen_width = m_line_width / ratio;
	m_pen.setWidth(pen_width);
	if (m_is_hovered)
	{
		m_pen.setColor(m_hover_color);
	}
	else
	{
		m_pen.setColor(m_default_color);
	}
	painter->setPen(m_pen);
	if (m_is_selected)
	{
		m_brush.setStyle(Qt::SolidPattern);
		m_brush.setColor(m_hover_color);
		painter->setBrush(m_brush);
	}
	else
	{
		m_brush.setColor(Qt::NoBrush);
		painter->setBrush(Qt::NoBrush);
	}
	//draw shape
	painter->drawPath(m_shape_path);
}
double ShapeBase::getSceneScalRatio()
{
	auto a = this->scene()->views().at(0)->transform();
	return a.m11();
}
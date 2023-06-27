#include "ShapeHandle.h"
#include <qgraphicsscene.h>
#include <qgraphicsview.h>

int ShapeHandle::m_size = 10;
int ShapeHandle::m_hover_size = 15;
QColor ShapeHandle::m_default_color = QColor("#eb5424");
QColor ShapeHandle::m_hover_color = QColor("#ffdd00");
QPen ShapeHandle::m_pen = QPen(QBrush(m_default_color), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
QBrush ShapeHandle::m_brush = QBrush(m_default_color);

ShapeHandle::ShapeHandle(HandleTypeEnum _handle_type, QGraphicsItem* parent)
	:QGraphicsItem(parent)
{
	setFlag(QGraphicsItem::ItemIsSelectable, true);
	if (_handle_type == HANDLE_MOVE)
	{
		setFlag(QGraphicsItem::ItemIsMovable, true);
	}
	setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
	setAcceptHoverEvents(true);
	//this->setVisible(false);
	setZValue(1000);
	m_boundingRect = QRectF(-m_size / 2, -m_size / 2, m_size, m_size);
	m_handle_type = _handle_type;
}

ShapeHandle::HandleTypeEnum ShapeHandle::getHandleType()
{
	return m_handle_type;
}

void ShapeHandle::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
	Q_UNUSED(event);
	m_is_hovered = true;
	this->update();
}

void ShapeHandle::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
	Q_UNUSED(event);
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
	Q_UNUSED(option);
	Q_UNUSED(widget);

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
	switch (m_handle_type)
	{
	case HANDLE_SIZE:
	case HANDLE_MOVE:
		//painter->drawEllipse(m_boundingRect);
		painter->drawRect(m_boundingRect);
		break;
	case HANDLE_ROTATE:
		painter->drawEllipse(m_boundingRect);
		break;
	default:
		break;
	}
	//qDebug() << "scene ratio : " << getSceneScalRatio();
}

//get the ratio of the scene to the screen
double ShapeHandle::getSceneScalRatio()
{
	auto a = this->scene()->views().at(0)->transform();
	return a.m11();
}

void ShapeHandle::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsItem::mouseMoveEvent(event);
	QPointF scene_pos = mapToScene(event->pos());
	sign_handleMouseMove(scene_pos);
	//qDebug() << "handle mouse move" << scene_pos;
}

void ShapeHandle::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsItem::mouseReleaseEvent(event);
	QPointF scene_pos = mapToScene(event->pos());
	sign_handleMouseRelease(scene_pos);
	//qDebug() << "handle mouse release" << scene_pos;
}

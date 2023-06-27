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
	setFlag(QGraphicsItem::ItemIsFocusable);
	setAcceptHoverEvents(true);
	setZValue(1000);
	m_is_selected = false;
	m_is_hovered = false;
	m_handles.clear();

	ShapeHandle* _handle = new ShapeHandle(ShapeHandle::HANDLE_SIZE, this);
	addHandle(_handle);
	_handle = new ShapeHandle(ShapeHandle::HANDLE_ROTATE, this);
	addHandle(_handle);
}

void ShapeBase::setSizeHandlePos(QPointF _scene_pos, bool _is_final)
{
	switch (m_resize_policy)
	{
	case ShapeBase::RESIZE_Center:
	{
		//update the bounding rect
		QPointF p1 = this->pos();
		QPointF p2 = _scene_pos;
		double dist = sqrt(pow(p2.x() - p1.x(), 2) + pow(p2.y() - p1.y(), 2));

		double shape_angle = this->rotation() * 3.1415926 / 180;
		double angle = shape_angle - atan2(p2.y() - p1.y(), p2.x() - p1.x());

		double half_width = fabs(dist * cos(angle));
		double half_height = fabs(dist * sin(angle));
		m_boundingRect = QRectF(-half_width, -half_height, 2 * half_width, 2 * half_height);
	}
	//中心不变
	break;
	case ShapeBase::RESIZE_LeftTop:
	{
		QPointF p1 = mapToScene(m_boundingRect.topLeft());
		QPointF p2 = _scene_pos;
		double dist = sqrt(pow(p2.x() - p1.x(), 2) + pow(p2.y() - p1.y(), 2));

		double shape_angle = this->rotation() * 3.1415926 / 180;
		double angle = shape_angle - atan2(p2.y() - p1.y(), p2.x() - p1.x());

		double width = fabs(dist * cos(angle));
		double height = fabs(dist * sin(angle));

		//qDebug() << "dist : " << p2.x() - p1.x() << " ; width : " << width;
		if (_is_final)
		{
			QPointF center = mapToScene(m_boundingRect.center());
			this->setPos(center);
			m_boundingRect = QRectF(-0.5 * width, -0.5 * height, width, height);
		}
		else
		{
			QPointF topleft = m_boundingRect.topLeft();
			m_boundingRect = QRectF(topleft.x(), topleft.y(), width, height);

		}
	}
	break;
	default:
		break;
	}
	//m_shape_path = QPainterPath();
	//m_shape_path.addRect(m_boundingRect);
	updateHandlePos();
	updateShapePath();
	this->update();
}

void ShapeBase::setRotateHandlePos(QPointF _scene_pos, bool _is_final)
{
	QPointF p1 = this->pos();
	QPointF p2 = _scene_pos;

	double angle = 90 + atan2(p2.y() - p1.y(), p2.x() - p1.x()) * 180 / 3.1415926;
	this->setRotation(angle);
}

void ShapeBase::setMoveHandlePos(ShapeHandle* _handle, QPointF _scene_pos, bool _is_final)
{

}

void ShapeBase::addHandle(ShapeHandle* _handle)
{
	if (_handle == nullptr)
	{
		return;
	}
	if (_handle->getHandleType() == ShapeHandle::HANDLE_MOVE)
	{
		m_move_handles.append(_handle);
		updateMoveHandlePos();
	}
	else
	{
		m_handles[_handle->getHandleType()] = _handle;
	}
	connect(_handle, &ShapeHandle::sign_handleMouseMove,
		this, &ShapeBase::onMoveHandlePosChanged);
	connect(_handle, &ShapeHandle::sign_handleMouseRelease,
		this, &ShapeBase::onMoveHandlePosFinal);
}

void ShapeBase::onMoveHandlePosChanged(QPointF _scene_pos)
{
	ShapeHandle* _han = qobject_cast<ShapeHandle*>(sender());
	if (_han == nullptr)
	{
		return;
	}

	switch (_han->getHandleType())
	{
	case ShapeHandle::HANDLE_SIZE:
		setSizeHandlePos(_scene_pos);
		break;
	case ShapeHandle::HANDLE_ROTATE:
		setRotateHandlePos(_scene_pos);
		break;
	case ShapeHandle::HANDLE_MOVE:
		setMoveHandlePos(_han, _scene_pos);
		break;
	}
}

void ShapeBase::onMoveHandlePosFinal(QPointF _scene_pos)
{
	ShapeHandle* _han = qobject_cast<ShapeHandle*>(sender());
	if (_han == nullptr)
	{
		return;
	}
	switch (_han->getHandleType())
	{
	case ShapeHandle::HANDLE_SIZE:
		setSizeHandlePos(_scene_pos, true);
		break;
	case ShapeHandle::HANDLE_ROTATE:
		setRotateHandlePos(_scene_pos);
		break;
	case ShapeHandle::HANDLE_MOVE:
		setMoveHandlePos(_han, _scene_pos, true);
		break;
	}
}

void ShapeBase::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
	QGraphicsItem::hoverEnterEvent(event);
	m_is_hovered = true;
	this->update();
}

void ShapeBase::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
	QGraphicsItem::hoverLeaveEvent(event);
	m_is_hovered = false;
	this->update();
}

void ShapeBase::focusInEvent(QFocusEvent* event)
{
	QGraphicsItem::focusInEvent(event);
	m_is_selected = true;
	this->update();
}

void ShapeBase::focusOutEvent(QFocusEvent* event)
{
	QGraphicsItem::focusOutEvent(event);
	m_is_selected = false;
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
	Q_UNUSED(option);
	Q_UNUSED(widget);

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

	if (m_show_center_cross)
	{
		drawCenterCross(painter);
	}

	if (m_show_rotate_hint)
	{
		drawRotateHintLine(painter);
	}
}
double ShapeBase::getSceneScalRatio()
{
	auto a = this->scene()->views().at(0)->transform();
	return a.m11();
}

void ShapeBase::updateMoveHandlePos()
{
}

void ShapeBase::updateHandlePos()
{
	//m_handles[ShapeHandle::HANDLE_ROTATE]->setPos(
	//	m_boundingRect.topRight() + QPoint(0.1 * m_boundingRect.width(), 0.5 * m_boundingRect.height()));

	m_handles[ShapeHandle::HANDLE_ROTATE]->setPos(
		m_boundingRect.center() - QPoint(0, 0.6 * m_boundingRect.height()));


	m_handles[ShapeHandle::HANDLE_SIZE]->setPos(
		m_boundingRect.bottomRight());
}

void ShapeBase::drawCenterCross(QPainter* painter)
{
	//draw center cross
	double ratio = getSceneScalRatio();
	int cross_len = 5 / ratio;
	double pen_width = 2 / ratio;
	painter->setPen(QPen(Qt::red, pen_width));
	QPoint center = m_boundingRect.center().toPoint();
	QPoint p1 = center + QPoint(-cross_len, 0);
	QPoint p2 = center + QPoint(cross_len, 0);
	painter->drawLine(p1, p2);
	p1 = center + QPoint(0, -cross_len);
	p2 = center + QPoint(0, cross_len);
	painter->drawLine(p1, p2);
}

void ShapeBase::drawRotateHintLine(QPainter* painter)
{
	double ratio = getSceneScalRatio();
	double pen_width = 2 / ratio;
	QPoint center = m_boundingRect.center().toPoint();
	//draw line from m_boundRect.center() to rotate handle
	painter->setPen(QPen(Qt::blue, pen_width));
	QPoint p2 = m_handles[ShapeHandle::HANDLE_ROTATE]->pos().toPoint();
	painter->drawLine(center, p2);
}

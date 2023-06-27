#pragma once
#include "ShapeBase.h"

class ShapeLine : public ShapeBase
{
public:
	ShapeLine(QGraphicsItem* parent = nullptr) :
		ShapeBase(parent)
	{
		m_shape_type = ShapeTypeEnum::SHAPE_LINE;
		m_boundingRect = QRectF(-100, -30, 200, 60);
		m_shape_path.addRect(m_boundingRect);
		m_show_rotate_hint = false;
		//m_show_center_cross = false;
		m_handles[ShapeHandle::HANDLE_SIZE]->setVisible(false);
		m_handles[ShapeHandle::HANDLE_ROTATE]->setVisible(false);

		p1 = new ShapeHandle(ShapeHandle::HANDLE_MOVE, this);
		addHandle(p1);
		p2 = new ShapeHandle(ShapeHandle::HANDLE_MOVE, this);
		addHandle(p2);

		p1->setPos(QPointF(-100, 0));
		p2->setPos(QPointF(100, 0));

		updateHandlePos();
		updateShapePath();
	}
	~ShapeLine() = default;

	virtual void setMoveHandlePos(ShapeHandle* _handle, QPointF _scene_pos, bool _is_final = false) override
	{
		QPointF pos1;
		QPointF pos2;
		QPointF ori_p1;
		QPointF ori_p2;
		if (_handle == p1)
		{
			//pos1 = mapToScene(_handle->pos());
			//pos2 = mapToScene(p2->pos());
			pos1 = _handle->pos();
			pos2 = p2->pos();
		}
		else
		{
			//pos1 = mapToScene(p1->pos());
			//pos2 = mapToScene(_handle->pos());
			pos1 = p1->pos();
			pos2 = _handle->pos();
		}

		QPointF final_center = 0.5 * (pos1 + pos2);
		if (_is_final)
		{
			double dist = sqrt(pow(pos2.x() - pos1.x(), 2) + pow(pos2.y() - pos1.y(), 2));
			m_boundingRect = QRectF(-0.5 * dist, -0.5 * 30, dist, 30);
			final_center = mapToScene(final_center);
			this->setPos(final_center);
			p1->setPos(-0.5 * dist, 0);
			p2->setPos(0.5 * dist, 0);
			pos2 = mapToScene(pos2);
			pos1 = mapToScene(pos1);
			double angle = atan2(pos2.y() - pos1.y(), pos2.x() - pos1.x()) * 180 / 3.1415926;
			//qDebug() << (unsigned int)_handle << "angle: " << angle;
			this->setRotation(angle);
		}
		else
		{
			QPointF tmp_diff = pos2 - pos1;
			tmp_diff.setX(fabs(tmp_diff.x()));
			tmp_diff.setY(fabs(tmp_diff.y()));
			m_boundingRect = QRectF(
				final_center.x() - tmp_diff.x() * 0.5,
				final_center.y() - tmp_diff.y() * 0.5,
				tmp_diff.x(),
				tmp_diff.y());
		}
		updateShapePath();
		this->update();
	}

	virtual void updateShapePath() override
	{
		m_shape_path = QPainterPath();
		QLineF line(p1->pos(), p2->pos());
		m_shape_path.moveTo(line.p1());
		m_shape_path.lineTo(line.p2());
		//m_shape_path.addRect(m_boundingRect);
	}

	virtual void setPoints(QPolygonF _points) override
	{
		if (_points.count() < getDrawPointsCount())
		{
			return;
		}
		emit sign_shapeComplete(this);
		QPointF pos1 = _points.at(0);
		QPointF pos2 = _points.at(1);
		QPointF final_center = 0.5 * (pos1 + pos2);
		double dist = sqrt(pow(pos2.x() - pos1.x(), 2) + pow(pos2.y() - pos1.y(), 2));
		m_boundingRect = QRectF(-0.5 * dist, -0.5 * 30, dist, 30);
		final_center = mapToScene(final_center);
		this->setPos(final_center);
		p1->setPos(-0.5 * dist, 0);
		p2->setPos(0.5 * dist, 0);
		pos2 = mapToScene(pos2);
		pos1 = mapToScene(pos1);
		double angle = atan2(pos2.y() - pos1.y(), pos2.x() - pos1.x()) * 180 / 3.1415926;
		this->setRotation(angle);
		updateShapePath();
		this->update();

	}
private:
	ShapeHandle* p1;
	ShapeHandle* p2;
};
#pragma once
#include "ShapeBase.h"

class ShapeRectangle : public ShapeBase
{
public:
	ShapeRectangle(QGraphicsItem* parent = nullptr) :
		ShapeBase(parent)
	{
		m_shape_type = ShapeTypeEnum::SHAPE_RECTANGLE;
		m_boundingRect = QRectF(-100, -100, 200, 200);
		m_shape_path.addRect(m_boundingRect);
		updateHandlePos();
	}
	~ShapeRectangle() = default;
	virtual void updateShapePath() override
	{
		m_shape_path = QPainterPath();
		m_shape_path.addRect(m_boundingRect);
	}
	virtual void setPoints(QPolygonF _points) override
	{
		if (_points.count() < getDrawPointsCount())
		{
			return;
		}
		QPointF pos1 = _points.at(0);
		QPointF pos2 = _points.at(1);
		QPointF center = 0.5 * (pos1 + pos2);
		double width = abs(pos2.x() - pos1.x());
		double height = abs(pos2.y() - pos1.y());
		m_boundingRect = QRectF(-0.5 * width, -0.5 * height, width, height);
		this->setPos(center);
		updateHandlePos();
		this->update();
		emit sign_shapeComplete(this);

	}
protected:
	QMap<int, QPointF> m_points;

};

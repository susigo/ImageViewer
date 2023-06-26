#pragma once
#include "ShapeBase.h"

class ShapeRectangle : public ShapeBase
{
public:
	ShapeRectangle(QGraphicsItem* parent = nullptr) :
		ShapeBase(parent)
	{
		m_shape_type = ShapeTypeEnum::SHAPE_RECTANGLE;
		m_boundingRect = QRectF(0, 0, 200, 200);
		m_shape_path.addRect(m_boundingRect);

		for (int i = 0; i < 4; i++)
		{
			ShapeHandle* tmp_handle = new ShapeHandle(this);
			m_handles.insert(i, tmp_handle);
		}
	}
	~ShapeRectangle() = default;
protected:

};

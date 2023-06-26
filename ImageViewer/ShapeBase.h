#ifndef SHAPEBASE_H
#define SHAPEBASE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include "ShapeHandle.h"

class ShapeBase : public QGraphicsItem
{
public:
	enum ShapeTypeEnum
	{
		SHAPE_TEST,
		SHAPE_RECTANGLE,
		SHAPE_ELLIPSE,
		SHAPE_POLYGON,
		SHAPE_FREEDRAW
	};
	ShapeBase(QGraphicsItem* parent = nullptr);
	~ShapeBase() = default;
protected:
	void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
	void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
	void focusInEvent(QFocusEvent* event) override;
	void focusOutEvent(QFocusEvent* event) override;
	QPainterPath shape() const override;

	QRectF boundingRect() const override;

	void paint(QPainter* painter,
		const QStyleOptionGraphicsItem* option,
		QWidget* widget) override;

	double getSceneScalRatio();
protected:
	ShapeTypeEnum m_shape_type = SHAPE_TEST;
	QMap<int, ShapeHandle* > m_handles;
	QRectF m_boundingRect;
	QPainterPath m_shape_path;
	static QColor m_default_color;
	static QColor m_hover_color;
	static QPen m_pen;
	static QBrush m_brush;
	double m_active_ratio = 1.1;//激活时的放大倍数
	bool m_is_hovered = false;
	bool m_is_selected = false;
	int m_line_width = 2;
};



#endif // SHAPEBASE_H

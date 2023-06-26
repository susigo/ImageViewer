#ifndef SHAPEHANDLE_H
#define SHAPEHANDLE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

class ShapeHandle : public QGraphicsItem
{
public:
	ShapeHandle(QGraphicsItem* parent = nullptr);
	~ShapeHandle() = default;
protected:
	void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
	void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

	QRectF boundingRect() const override;
	void paint(QPainter* painter,
		const QStyleOptionGraphicsItem* option,
		QWidget* widget) override;
	double getSceneScalRatio();
private:
	QRectF m_boundingRect;
	static int m_size;//在屏幕空间的大小，单位为像素
	static int m_hover_size;//鼠标悬停时的大小
	static QColor m_default_color;
	static QColor m_hover_color;
	static QPen m_pen;
	static QBrush m_brush;
	double m_active_ratio = 1.1;//激活时的放大倍数
	bool m_is_hovered = false;
};


#endif // SHAPEHANDLE_H

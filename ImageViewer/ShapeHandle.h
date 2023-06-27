#ifndef SHAPEHANDLE_H
#define SHAPEHANDLE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QFocusEvent>
class ShapeHandle : public QObject, public QGraphicsItem
{
	Q_OBJECT
		Q_INTERFACES(QGraphicsItem)
public:
	enum HandleTypeEnum
	{
		HANDLE_SIZE,
		HANDLE_ROTATE,
		HANDLE_MOVE
	};
	ShapeHandle(HandleTypeEnum _handle_type, QGraphicsItem* parent = nullptr);
	~ShapeHandle() = default;
	HandleTypeEnum getHandleType();
signals:
	void sign_handleMouseMove(QPointF _scene_pos);
	void sign_handleMouseRelease(QPointF _scene_pos);
protected:
	void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
	void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
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
	HandleTypeEnum m_handle_type = HANDLE_SIZE;
};


#endif // SHAPEHANDLE_H

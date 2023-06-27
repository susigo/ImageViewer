#ifndef SHAPEBASE_H
#define SHAPEBASE_H

#include <QGraphicsItem>
#include <QGraphicsItemGroup>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QFocusEvent>
#include "ShapeHandle.h"

class ShapeBase : public QObject, public QGraphicsItem
{
	Q_OBJECT
		Q_INTERFACES(QGraphicsItem)
public:
	enum ShapeTypeEnum
	{
		SHAPE_NONE,
		SHAPE_LINE,
		SHAPE_RECTANGLE,
		SHAPE_ELLIPSE,
		SHAPE_POLYGON,
		SHAPE_FREEDRAW
	};
	//设置尺寸handle的响应方式
	enum ResizePolicyEnum
	{
		RESIZE_Center,
		RESIZE_LeftTop,
	};

	ShapeBase(QGraphicsItem* parent = nullptr);
	~ShapeBase() = default;
	//设置尺寸handle的位置
	virtual void setSizeHandlePos(QPointF _scene_pos, bool _is_final = false);
	//设置旋转handle的位置
	virtual void setRotateHandlePos(QPointF _scene_pos, bool _is_final = false);
	//设置移动handle的位置,各个子类的实现不同
	virtual void setMoveHandlePos(ShapeHandle* _handle, QPointF _scene_pos, bool _is_final = false);
	//各个子类需要实现的更新形状的函数
	virtual void updateShapePath() = 0;
	//在绘制过程中更新形状的函数，每个子类的实现不同
	virtual void setPoints(QPolygonF _points) = 0;
	virtual int getDrawPointsCount() { return 2; }
	void addHandle(ShapeHandle* _handle);
signals:
	void sign_shapeComplete(ShapeBase* _shape);
private slots:
	//尺寸handle的鼠标移动响应
	void onMoveHandlePosChanged(QPointF _scene_pos);
	//尺寸handle的鼠标释放响应,决定物体的最终形态与位置
	void onMoveHandlePosFinal(QPointF _scene_pos);
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

	void updateMoveHandlePos();

	void updateHandlePos();

	void drawCenterCross(QPainter* painter);

	void drawRotateHintLine(QPainter* painter);

protected:
	ShapeTypeEnum m_shape_type = SHAPE_NONE;
	ResizePolicyEnum m_resize_policy = RESIZE_LeftTop;
	QMap<int, ShapeHandle* > m_handles;
	QList<ShapeHandle* > m_move_handles;
	QRectF m_boundingRect;
	QPainterPath m_shape_path;
	static QColor m_default_color;
	static QColor m_hover_color;
	static QPen m_pen;
	static QBrush m_brush;
	double m_active_ratio = 1.1;//激活时的放大倍数
	int m_line_width = 2;
	bool m_is_hovered = false;
	bool m_is_selected = false;
	bool m_show_rotate_hint = true;
	bool m_show_center_cross = true;
};



#endif // SHAPEBASE_H

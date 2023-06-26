#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "../ImageViewer/ImageViewer_global.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget
{
	Q_OBJECT

public:
	MainWidget(QWidget* parent = nullptr);
	~MainWidget();
	void loadModules();
private:
	Ui::MainWidget* ui;
	ImageViewerInterface* m_imageviewer = nullptr;
	QWidget* m_imageviewerWidget = nullptr;
};
#endif // MAINWIDGET_H

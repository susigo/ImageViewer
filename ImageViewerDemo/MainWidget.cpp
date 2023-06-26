#include "MainWidget.h"
#include "ui_MainWidget.h"
#include <QPluginLoader>
#include <QDebug>
MainWidget::MainWidget(QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::MainWidget)
{
	ui->setupUi(this);
	loadModules();
}

MainWidget::~MainWidget()
{
	delete ui;
}

void MainWidget::loadModules()
{
	QObject* tmp_obj_ptr = nullptr;
	QPluginLoader loader(QCoreApplication::applicationDirPath() + "/ImageViewer.dll");

	tmp_obj_ptr = loader.instance();
	if (tmp_obj_ptr)
	{
		m_imageviewer = qobject_cast<ImageViewerInterface*>(tmp_obj_ptr);

		m_imageviewerWidget = m_imageviewer->getWidget();
		ui->imageViewHost->addWidget(m_imageviewerWidget);
		//m_imageviewerWidget->show();
	}
	else
	{
		qDebug() << loader.errorString();
	}
}


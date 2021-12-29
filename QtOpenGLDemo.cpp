#include "QtOpenGLDemo.h"

QtOpenGLDemo::QtOpenGLDemo(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
	core_widget = new CoreFunctionWidget(this);
	core_widget->setObjectName(QStringLiteral("openGLWidget"));
	core_widget->setGeometry(QRect(0, 0, 300, 300));

	connect(this->core_widget, SIGNAL(projection_change(QString)), this, SLOT(set_projection_button(QString)));
}
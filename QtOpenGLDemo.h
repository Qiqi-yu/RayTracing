#pragma once

#include <QtWidgets/QWidget>
#include "ui_QtOpenGLDemo.h"
#include "OpenGLWidget.h"

class QtOpenGLDemo : public QWidget
{
    Q_OBJECT

public:
    QtOpenGLDemo(QWidget *parent = Q_NULLPTR);

public slots: 
private:
    Ui::QtOpenGLDemoClass ui;
	CoreFunctionWidget * core_widget;
};

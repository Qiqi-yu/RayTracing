#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include<QOpenGLFramebufferObject>
#include <QKeyEvent> 
#include <QTimer> 
#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Ray.h"
#include "Scene.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texture;
};

class CoreFunctionWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
	Q_OBJECT
public:
	explicit CoreFunctionWidget(QWidget *parent = nullptr);
	~CoreFunctionWidget();

signals:
	void projection_change(QString);

protected:
	virtual void initializeGL();
	virtual void resizeGL(int w, int h);
	virtual void paintGL();
	void initRayTracing();


	void keyPressEvent(QKeyEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	int mouse_x, mouse_y;
	float v = 0.1f;
public:
	QString version;

private:
	// ply Ä£ÐÍshader
	QOpenGLShaderProgram shaderProgram;
	GLuint VBO, VAO, EBO, texture, texture2;

	Camera cam;
	QTimer* timer = new QTimer(this);
};

void compileShader(QOpenGLShaderProgram &shaderProgram, const QString vert_shader, const QString frag_shader);
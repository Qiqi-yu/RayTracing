#include "OpenGLWidget.h"
#include <QDebug>
#include <iostream>
#include<fstream>
#include <cassert>


CoreFunctionWidget::CoreFunctionWidget(QWidget *parent) : QOpenGLWidget(parent)
{
	this->setFocusPolicy(Qt::StrongFocus);
	
	this->version = "rayTracing"; 
	/*connect(timer, SIGNAL(timeout()), this, SLOT(updateObject()));*/
}

CoreFunctionWidget::~CoreFunctionWidget()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}


void CoreFunctionWidget::keyPressEvent(QKeyEvent *e) {
	/*if (this->version == "full") {*/
		if (e->key() == Qt::Key_A) {
			this->cam.translate_left(-0.2);
		}
		else if (e->key() == Qt::Key_D) {
			this->cam.translate_left(0.2);
		}
		else if (e->key() == Qt::Key_W) {
			this->cam.translate_up(0.2);
		}
		else if (e->key() == Qt::Key_S) {
			this->cam.translate_up(-0.2);
		}
		else if (e->key() == Qt::Key_F) {
			this->cam.translate_forward(0.2);
		}
		else if (e->key() == Qt::Key_B) {
			this->cam.translate_forward(-0.2);;
		}
		else if (e->key() == Qt::Key_Z) {
			this->cam.zoom_near(0.1);
		}
		else if (e->key() == Qt::Key_X) {
			this->cam.zoom_near(-0.1);
		}

		update();
	/*}*/
}

void compileShader(QOpenGLShaderProgram &shaderProgram, const QString vert_shader, const QString frag_shader) {
	bool success = shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, vert_shader);
	if (!success) {
		qDebug() << "shaderProgram addShaderFromSourceFile failed!" << shaderProgram.log();
		return;
	}

	success = shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, frag_shader);
	if (!success) {
		qDebug() << "shaderProgram addShaderFromSourceFile failed!" << shaderProgram.log();
		return;
	}

	success = shaderProgram.link();
	if (!success) {
		qDebug() << "shaderProgram link failed!" << shaderProgram.log();
	}
}

void CoreFunctionWidget::initializeGL() {
	this->initializeOpenGLFunctions(); 
	this->cam.set_projection_params({ 90, 1.0, 0.01, 50.0 });
	glEnable(GL_DEPTH_TEST);
	this->cam.set_initial_distance_ratio(3.0);
	
	initRayTracing();
}


void CoreFunctionWidget::resizeGL(int w, int h) {
	glViewport(0, 0, w, h);
}
void CoreFunctionWidget::initRayTracing()
{
	// 此处编写光追代码
	float point[] = { 0,0,0 };
	compileShader(this->shaderProgram, "./shaders/rayTracing.vert", "./shaders/rayTracing.frag");
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void CoreFunctionWidget::paintGL() {
	
		// 此处编写光追代码
		/*initializeGL();*/
		shaderProgram.bind();
		{
			for (unsigned int i = 0; i < 300; i++) {
				for (unsigned int j = 0; j < 300; j++) {
					// （i,j）映射到像素坐标
					if (i == 150 && j == 150) {
						bool flag = true;
					}
					QVector4D pos((float(i) * 2) / 300 - 1.0f,(float(j) * 2)/ 300 - 1.0f, 0.5f, 1.0f);
					glm::vec2 pos_xy = glm::vec2(pos.x(), pos.y());
					glUniform2fv(shaderProgram.uniformLocation("screenPos"), 1, &pos_xy[0]);

					bool invertible;
					pos =(cam.get_projection_matrix() * cam.get_camera_matrix()).inverted(&invertible) * pos;
					pos = pos / pos.w();
					glm::vec3 worldPos = glm::vec3(pos.x(), pos.y(), pos.z());
					assert(invertible);

					QVector3D eye = cam.get_eye();					
					glm::vec3 viewPos = glm::vec3(eye.x(), eye.y(), eye.z());
					glm::vec3 dir = glm::normalize(worldPos - viewPos);
					RayTracing::Ray ray(viewPos, dir);
					RayTracing::Scene scene;
					glm::vec3 color = scene.rayTracing(ray, 0);


					glUniform3fv(shaderProgram.uniformLocation("vertexColor"), 1, &color[0]);
					glDrawArrays(GL_POINTS, 0, 1);
				}
			}
		}
		shaderProgram.release();
}

void CoreFunctionWidget::mousePressEvent(QMouseEvent *e) {
	/*if (this->version == "full") {*/
		mouse_x = e->x();
		mouse_y = e->y();
	/*}*/
}

void CoreFunctionWidget::mouseMoveEvent(QMouseEvent *e) {
	/*if (this->version == "full") {*/
		int x = e->x();
		int y = e->y();

		if (abs(x - mouse_x) >= 10) {
			if (x > mouse_x) {
				this->cam.rotate_left(5.0);
			}
			else {
				this->cam.rotate_left(-5.0);
			}
			mouse_x = x;
		}

		if (abs(y - mouse_y) >= 10) {
			if (y > mouse_y) {
				this->cam.rotate_up(-5.0);
			}
			else {
				this->cam.rotate_up(5.0);
			}
			mouse_y = y;
		}

		update();
	/*}*/
}

//void CoreFunctionWidget::setProjection(QString type) {
//	if (type == "perspective") {
//		
//	}
//	else if (type == "ortho") {
//		this->cam.set_projection_type("ortho");
//		this->cam.set_projection_params({ -2, 2, -2, 2, 0.01, 50.0 });
//	}
//}
//
//void CoreFunctionWidget::changeProjection() {
//	if (this->cam.get_projection_type() == "perspective") {
//		this->setProjection("ortho");
//	}
//	else {
//		this->setProjection("perspective");
//	}
//}
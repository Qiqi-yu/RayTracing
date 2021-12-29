#pragma once

#include <QMatrix4x4>
#include <QVector3D>
#include <QMatrix3x3>

class Camera {
public:
	Camera() : eye(0, 0, -1), up(0, 1, 0), center(0, 0, 0), zoom(1.0) { 
		set_initial_distance_ratio(1.0); 
		set_projection_type("perspective");
		set_projection_params({ 90, 1.0, 0.01, 50.0 });
	}
	Camera(QVector3D a, QVector3D b, QVector3D c) : eye(a), up(b), center(c), zoom(1.0) { 
		set_initial_distance_ratio(1.0); 
		set_projection_type("perspective");
		set_projection_params({ 90, 1.0, 0.01, 50.0 });
	}
	Camera(QVector3D a, QVector3D b, QVector3D c, float dis): eye(a), up(b), center(c), zoom(1.0) { 
		set_initial_distance_ratio(dis);
		set_projection_type("perspective");
		set_projection_params({ 90, 1.0, 0.01, 50.0 });
	}
	~Camera() {}
	QVector3D eye;
private:
	
	QVector3D up;
	QVector3D center;
	float zoom;
	float distance_r;
	QString projection_type;
	QVector<double> projection_params;

public:
	void set_initial_distance_ratio(float r);
	void set_projection_type(QString type);
	inline QString get_projection_type() { return this->projection_type; }
	void set_projection_params(QVector<double> params);
	QMatrix4x4 get_camera_matrix();
	QMatrix4x4 get_projection_matrix();
	void translate_left(float dis);
	void translate_up(float dis);
	void rotate_left(float degree);
	void rotate_up(float degree);
	void zoom_near(float degree);
	void translate_forward(float dis);
	QMatrix4x4 get_model_matrix();
	QVector3D get_pos();
	QVector3D get_eye();
};

QMatrix4x4 rotate_mat(const float degree, const QVector3D axis);
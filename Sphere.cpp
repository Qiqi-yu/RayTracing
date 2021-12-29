#include "Sphere.h"

RayTracing::Sphere::Sphere(const glm::vec3 center, float radius,const Material* material)
{
	this->sCenter = center;
	this->sRadius = radius;
	this->material = material;
}

// 场景内的物体无相交关系
float RayTracing::Sphere::intersectRayDis(Ray ray)
{
	glm::vec3 p_c = ray.getStart() - this->sCenter;
	auto a = glm::dot(ray.getDir(), ray.getDir());
	auto b = 2 * glm::dot(ray.getDir(), p_c);
	auto c = glm::dot(p_c, p_c) - sRadius * sRadius;
	auto delta = b * b - 4 * a * c;
	if (delta < EPSINON) {
		return -1;
	}
	auto k = sqrt(delta);
	// 求出两解
	auto t1 = (-b + k) / (2 * a);
	auto t2 = (-b - k) / (2 * a);
	//射线
	if (t1 < EPSINON && t2 < EPSINON) {
		return -1;
	}
	if (t2 < EPSINON) {
		return t1;
	} 
	// 优先取近处
	return t2;

}

glm::vec3 RayTracing::Sphere::getNormal(glm::vec3 point)
{
	return glm::normalize(point - this->sCenter);
}

bool RayTracing::Sphere::inObject(glm::vec3 point)
{
	float dis = glm::distance(point, sCenter);
	return  dis- sRadius < FLT_EPSILON;
}

//void RayTracing::Sphere::setMaterial(Material* m)
//{
//	this->material = m;
//}
//
//const RayTracing::Material& RayTracing::Sphere::getMaterial() const 
//{
//	return *this->material;
//}

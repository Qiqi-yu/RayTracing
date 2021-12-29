#include "Plane.h"

RayTracing::Plane::Plane(const glm::vec3 normal, const glm::vec3 point, const Material* material)
{
	pNormal = normal;
	pPoint = point;
	this->material = material;
}

float RayTracing::Plane::intersectRayDis(Ray ray)
{
	float v1 = -glm::dot((ray.getStart() - pPoint), pNormal);
	float v2 = glm::dot(ray.getDir(), pNormal);
	if (abs(v2) < FLT_EPSILON) {
		return -1;
	}
	else {
		return v1 / v2;
	}
}

glm::vec3 RayTracing::Plane::getNormal(glm::vec3 point)
{
	return pNormal;
}

bool RayTracing::Plane::inObject(glm::vec3 point)
{
	return false;
}

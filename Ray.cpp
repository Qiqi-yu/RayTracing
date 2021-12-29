#include "Ray.h"

RayTracing::Ray::Ray(glm::vec3 start, glm::vec3 dir)
{
	this->dir = dir;
	this->start = start;
}

glm::vec3 RayTracing::Ray::getStart()
{
	return this->start;
}

glm::vec3 RayTracing::Ray::getDir()
{
	return glm::normalize(this->dir);
}

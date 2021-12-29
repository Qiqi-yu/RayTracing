#pragma once
#include "Object.h"
namespace RayTracing {
	class Plane:public Object
	{
	public:
		Plane(const glm::vec3 normal, const glm::vec3 point, const Material* material);
		float intersectRayDis(Ray ray) ;
		glm::vec3 getNormal(glm::vec3 point);
		bool inObject(glm::vec3 point);
	private:
		glm::vec3 pNormal;
		glm::vec3 pPoint;
	};
};


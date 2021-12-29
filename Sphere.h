#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 
#include"Ray.h"
#include "Material.h"
#include "Object.h"
constexpr auto EPSINON = 0.00001f;

namespace RayTracing {
	class Sphere: public Object
	{
	public:
		Sphere(const glm::vec3 center, float radius,const Material* material);
		float intersectRayDis(Ray ray);
		glm::vec3 getNormal(glm::vec3 point);
		bool inObject(glm::vec3 point);
		/*void setMaterial(Material* m);
		const Material& getMaterial() const;*/
	private:
		glm::vec3 sCenter;
		float sRadius;
		/*const Material* material;*/
	};
};

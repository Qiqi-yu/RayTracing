#pragma once
#include"Ray.h"
#include"Material.h"
namespace RayTracing {
	class Object
	{
	public:
		virtual float intersectRayDis(Ray ray)  = 0;
		virtual glm::vec3 getNormal(glm::vec3 point) = 0;
		virtual bool inObject(glm::vec3 point) = 0;
		virtual void setMaterial(Material* m) { this->material = m; };
		virtual const Material& getMaterial() { return *material; };
	protected: 
		const Material* material;
	};
};


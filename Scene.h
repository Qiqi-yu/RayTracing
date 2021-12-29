#pragma once
#include<vector>
#include"Object.h"
#include"Sphere.h"
#include"Ray.h" 
#include"Plane.h"
constexpr auto MAX_DEPTH = 5;
struct Light {
	glm::vec3 position;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};
namespace RayTracing {
	class Scene
	{
	public:
		Scene();
		~Scene();
		void addObject(Object* sphere); 
		Object* getIntersectionPoint(Ray ray,glm::vec3 &pos);
		glm::vec3 computeDirectLight(Object* intersectObject, glm::vec3 intersectPoint, Ray ray, glm::vec3 normal);
		bool shadeDetect(glm::vec3 intersectPoint);
		glm::vec3 rayTracing(Ray ray, int depth);
	private:
		std::vector<Object*> sObjects;
		Light light;
		// ¹â×·Ö÷³ÌÐò
		

		

	};
};

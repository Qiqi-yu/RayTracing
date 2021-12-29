#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
namespace RayTracing {
	class Ray
	{
	public:
		Ray(glm::vec3 start, glm::vec3 dir);
		glm::vec3 getStart();
		glm::vec3 getDir();
	private:
		glm::vec3 start;
		glm::vec3 dir;
	};
};


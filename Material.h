#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <functional>
namespace RayTracing {
	class Material
	{
	public:
		// 材质对应的参数
		std::function<glm::vec3(const glm::vec3& pos)> ambient;
		std::function<glm::vec3(const glm::vec3& pos)> diffuse;
		std::function<glm::vec3(const glm::vec3& pos)> specular;
		float shininess;

		// 反射因子 0-1 0代表完全不反射
		float reflectiveRate;
		// 折射因子 0-1 0代表完全不折射
		float refractRate;
		// 折射率 
		float refractIndex;
	};
};


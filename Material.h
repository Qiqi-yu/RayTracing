#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <functional>
namespace RayTracing {
	class Material
	{
	public:
		// ���ʶ�Ӧ�Ĳ���
		std::function<glm::vec3(const glm::vec3& pos)> ambient;
		std::function<glm::vec3(const glm::vec3& pos)> diffuse;
		std::function<glm::vec3(const glm::vec3& pos)> specular;
		float shininess;

		// �������� 0-1 0������ȫ������
		float reflectiveRate;
		// �������� 0-1 0������ȫ������
		float refractRate;
		// ������ 
		float refractIndex;
	};
};


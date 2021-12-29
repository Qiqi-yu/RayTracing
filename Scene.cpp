#include "Scene.h" 


RayTracing::Scene::Scene()
{
	Material* ballMaterial = new Material();
	ballMaterial->reflectiveRate = 0.1f;
	ballMaterial->refractRate = 0.0f;
	ballMaterial->refractIndex = 1.5f;
	ballMaterial->ambient = [=](const glm::vec3& pos) -> glm::vec3
	{
		return glm::vec3(1.0f, 0.5f, 0.31f);
	};
	ballMaterial->diffuse = [=](const glm::vec3& pos) -> glm::vec3
	{
		return glm::vec3(1.0f, 0.5f, 0.31f);
	};
	ballMaterial->specular = [=](const glm::vec3& pos) -> glm::vec3
	{
		return glm::vec3(0.6f, 0.6f, 0.6f);
	};
	ballMaterial->shininess = 32.0f;
	
	Material* Material_mirror = new Material();
	Material_mirror->reflectiveRate = 1.0f;
	Material_mirror->refractRate = 0.0f;
	Material_mirror->refractIndex = 1.5f;
	Material_mirror->ambient = [=](const glm::vec3& pos)->glm::vec3
	{
		return glm::vec3(0.0f, 0.0f, 0.0f); 
	};
	Material_mirror->diffuse = [=](const glm::vec3& pos)->glm::vec3
	{
		return glm::vec3(0.0f, 0.0f, 0.0f);
	};
	Material_mirror->specular = [=](const glm::vec3& pos)->glm::vec3
	{
		return glm::vec3(0.0f, 0.0f, 0.0f);
	};
	Material_mirror->shininess = 32.0f;
	/*Sphere* ball_mirror = new Sphere(glm::vec3(1.0f, 0.5f, 2.0f), 0.5f, Material_mirror);*/
	
	/*Material* ballMaterial_transparent = new Material();
	ballMaterial_transparent->reflectiveRate = 0.0f;
	ballMaterial_transparent->refractRate = 1.0f;
	ballMaterial_transparent->refractIndex = 1.5f;
	ballMaterial_transparent->ambient = [=](const glm::vec3& pos)->glm::vec3
	{
		return glm::vec3(0.5f, 0.5f, 0.5f);
	};
	ballMaterial_transparent->diffuse = [=](const glm::vec3& pos)->glm::vec3
	{
		return glm::vec3(0.0f, 0.0f, 0.0f);
	};
	ballMaterial_transparent->specular = [=](const glm::vec3& pos)->glm::vec3
	{
		return glm::vec3(0.0f, 0.0f, 0.0f); 
	};
	ballMaterial_transparent->shininess = 32.0f;*/
	Material* texture = new Material();
	auto isWhite = [](const glm::vec3& pos) {
		return fmod(floor(pos.x) + floor(pos.z), 2) != 0;

	};
	texture->ambient = [=](const glm::vec3& pos) -> glm::vec3
	{
		if (isWhite(pos)) {
			return glm::vec3(0.9, 0.9, 0.9);
		}
		else {
			return glm::vec3(0.2, 0.3, 0.1);
		}
	};
	texture->diffuse= [=](const glm::vec3& pos) -> glm::vec3
	{
		if (isWhite(pos)) {
			return glm::vec3(0.9, 0.9, 0.9);
		}
		else {
			return glm::vec3(0.2, 0.3, 0.1);
		}
	};
	texture->specular = [=](const glm::vec3& pos) -> glm::vec3
	{
		if (isWhite(pos)) {
			return glm::vec3(0.9, 0.9, 0.9);
		}
		else {
			return glm::vec3(0.2, 0.3, 0.1);
		}
	};

	Material* mtransparent = new Material();
	mtransparent->reflectiveRate = 0.0f;
	mtransparent->refractRate = 1.0f;
	mtransparent->refractIndex = 1.5f;
	mtransparent->ambient = [=](const glm::vec3& pos)->glm::vec3
	{
		return glm::vec3(0.5f, 0.5f, 0.5f);
	};
	mtransparent->diffuse = [=](const glm::vec3& pos)->glm::vec3
	{
		return glm::vec3(0.0f, 0.0f, 0.0f);
	};
	mtransparent->specular = [=](const glm::vec3& pos)->glm::vec3
	{
		return glm::vec3(0.0f, 0.0f, 0.0f);
	};
	mtransparent->shininess = 32.0f;
	light.ambient = glm::vec3(0.4f, 0.4f, 0.4f);
	light.diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
	light.specular = glm::vec3(1.0f, 1.0f, 1.0f);
	light.position = glm::vec3(0.0f, 0.0f, -5.0f);
	Sphere* ball = new Sphere(glm::vec3(0.0f, 0.0f, 0.0f), 0.5f, ballMaterial);
	/*Sphere* transparent = new Sphere(glm::vec3(-1.5f, 0, 0.0f), 0.5f, ballMaterial_transparent);*/
	Plane* plane = new Plane(glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f),Material_mirror);
	Plane* texturePlane = new Plane(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0, -2.0f, 0.0f), texture);
	Plane* mPlane = new Plane(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0, 0.0f, -2.8f),mtransparent);
	this->addObject(ball);
	this->addObject(plane);
	/*this->addSphere(ball_mirror);*/
	/*this->addObject(transparent);*/
	this->addObject(texturePlane);
	this->addObject(mPlane);
}

RayTracing::Scene::~Scene()
{
	for (auto object : sObjects) {
		delete &object->getMaterial();
		delete object;
	}
}

void RayTracing::Scene::addObject(Object* object)
{
	this->sObjects.push_back(object);
}

RayTracing::Object* RayTracing::Scene::getIntersectionPoint(Ray ray, glm::vec3& pos)
{
	float min_dis = 10000000.0f;
	Object* intersectObject = nullptr;
	for (auto object : sObjects) {
		float dis = object->intersectRayDis(ray);
		if (dis > EPSINON) {
			if (dis < min_dis) {
				min_dis = dis;
				intersectObject = object;
			}
		}
	}

	if (intersectObject != nullptr) {
		pos = min_dis * ray.getDir() + ray.getStart();
	}
	return intersectObject;
}

float max(float a, float b) {
	if (a > b) {
		return a;
	}
	return b;
}

glm::vec3 RayTracing::Scene::computeDirectLight(Object* intersectObject, glm::vec3 intersectPoint, Ray ray,glm::vec3 normal)
{
	// 环境光
	glm::vec3 color = light.ambient * intersectObject->getMaterial().ambient(intersectPoint);
	bool shade = shadeDetect(intersectPoint);
	if (shade) {
		return color;
	}
	// 漫反射
	
	glm::vec3 lightDir = glm::normalize(light.position - intersectPoint);
	float diff = max(glm::dot(normal, lightDir), 0.0);
	glm::vec3 diffuse = light.diffuse * (diff * intersectObject->getMaterial().diffuse(intersectPoint));

	// 镜面光
	glm::vec3 viewDir = glm::normalize(ray.getDir());
	glm::vec3 reflectDir = glm::reflect(-lightDir, normal);
	/*reflectDir = glm::normalize(-viewDir + lightDir);*/
	float spec = glm::pow(max(glm::dot(viewDir, reflectDir), 0.0), intersectObject->getMaterial().shininess);
	glm::vec3 specular = light.specular * (spec * intersectObject->getMaterial().specular(intersectPoint));

	color = color + diffuse + specular;
	return color;
}

bool RayTracing::Scene::shadeDetect(glm::vec3 intersectPoint)
{
	glm::vec3 dir = glm::normalize(light.position - intersectPoint);
	Ray shadeRay(intersectPoint,dir);
	glm::vec3 pos; 
	Object* s = getIntersectionPoint(shadeRay, pos);
	if (s == nullptr||glm::distance(pos,intersectPoint) - glm::distance(light.position,intersectPoint)>FLT_EPSILON || s->getMaterial().refractRate > 0.9f||s->getMaterial().reflectiveRate>0.9f) {
		return false;
	}
	return true;
}

glm::vec3 RayTracing::Scene::rayTracing(RayTracing::Ray ray, int depth)
{
	glm::vec3 color(0.0f);
	if (depth >= MAX_DEPTH) {
		return color;
	}
	// 计算光线与所有物体的交点中离start最近的点；
	glm::vec3 intersectPos(0.0f);
	
	auto intersectObject = getIntersectionPoint(ray, intersectPos);
	if (intersectObject == nullptr) {
		return color;
	}
	bool inObject = intersectObject->inObject(intersectPos);
	glm::vec3 norm = intersectObject->getNormal(intersectPos);
	/*norm = -norm;*/
	// 光照强度第一部分：局部光照强度
	color = computeDirectLight(intersectObject, intersectPos, ray, norm);

	// 如果光线从物体内部射出
	if (inObject) {
		norm = -norm;
	}

	// 光照强度第二部分：反射光照强度
	glm::vec3 reflectDir = glm::reflect(ray.getDir(), norm);
	if (intersectObject->getMaterial().reflectiveRate > EPSINON) {
		color += intersectObject->getMaterial().reflectiveRate * rayTracing(RayTracing::Ray(intersectPos, reflectDir), depth + 1);
	}
	
	// 光照强度第三部分： 折射光照强度
	// 折射率
	float inIndex = 1.0f;
	float outIndex = intersectObject->getMaterial().refractIndex;
	if (inObject) {
		std::swap(inIndex, outIndex);
	} 

	glm::vec3 refractDir = glm::refract(ray.getDir(), norm, inIndex / outIndex);
	if (intersectObject->getMaterial().refractRate > EPSINON && refractDir!=glm::vec3(0.0f)) {
		color += intersectObject->getMaterial().refractRate * (rayTracing(RayTracing::Ray(intersectPos, refractDir), depth + 1));
	}
	
	return color;
}

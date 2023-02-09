#pragma once
#include "CollisionPrimitive.h"

class Collision
{
public:
	//���C�ƕ��ʂ̓����蔻��
	//<summary>
	//<param name="lay">���C</param>
	//<param name="plane">����</param>
	//<param name="inter">����(�o�͗p)</param>
	//<param name="inter">����(�o�͗p)</param>
	//<returns>�������Ă��邩�ۂ�</returns>
	static bool CheckRay2Plane(const Ray& ray, Ray& nextRay, const Plane& plane, float* distance);

	static bool CheckRay2Mirror(const Ray& ray,Ray& nextRay, const Plane& plane, float* distance);

	static bool CheckSphere2Plane(const Sphere& sphere, const Plane& plane, Vector3* inter);

};
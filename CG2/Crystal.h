#pragma once
#include "GameObject3D.h"
#include"CollisionPrimitive.h"

class Crystal {
public:
	//�R���X�g���N�^
	Crystal();
	//�f�X�g���N�^
	~Crystal();

	void Initialize(ViewProjection* viewProjection, XMMATRIX* matProjection, WorldTransform& worldTransform);

	void Update();

	void CheckCollision(Ray* ray, int i, float* dis);

	void Draw();


	GameObject3D* obj;

	Plane frontPlane;
	Plane backPlane;
	Plane leftPlane;
	Plane rightPlane;
	Plane upPlane;
	Plane downPlane;

};
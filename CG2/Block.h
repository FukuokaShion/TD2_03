#pragma once
#include "GameObject3D.h"
#include"CollisionPrimitive.h"

class Block {
public:
	//コンストラクタ
	Block();
	//デストラクタ
	~Block();

	void Initialize(ViewProjection* viewProjection, XMMATRIX* matProjection, WorldTransform& worldTransform);

	void Update();

	void CheckCollision(Ray* ray,int i,float* dis);

	void Draw();


	GameObject3D* obj;

	Plane frontPlane;
	Plane backPlane;
	Plane leftPlane;
	Plane rightPlane;
	Plane upPlane;
	Plane downPlane;

};
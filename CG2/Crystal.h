#pragma once
#include "GameObject3D.h"
#include"CollisionPrimitive.h"
#include "DX12base.h"

class Crystal {
public:
	//コンストラクタ
	Crystal();
	//デストラクタ
	~Crystal();

	void Initialize(ViewProjection* viewProjection, XMMATRIX* matProjection, WorldTransform& worldTransform);

	void Update();

	bool CheckCollision(Ray* ray, int i, float* dis);

	void Draw();


	GameObject3D* obj;
	DX12base& dx12base_ = DX12base::GetInstance();
	Plane frontPlane;
	Plane backPlane;
	Plane leftPlane;
	Plane rightPlane;
	Plane upPlane;
	Plane downPlane;

};
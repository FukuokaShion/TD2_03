#pragma once
#include "GameObject3D.h"
#include"CollisionPrimitive.h"
#include "DX12base.h"

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

	DX12base& dx12base_ = DX12base::GetInstance();

	GameObject3D* obj;

	Plane frontPlane;
	Plane backPlane;
	Plane leftPlane;
	Plane rightPlane;
	Plane upPlane;
	Plane downPlane;

};
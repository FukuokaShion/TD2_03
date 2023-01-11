#pragma once
#include "GameObject3D.h"
#include"CollisionPrimitive.h"

class Mirror {
public:
	//コンストラクタ
	Mirror();
	//デストラクタ
	~Mirror();

	void Initialize(ViewProjection* viewProjection, XMMATRIX* matProjection, WorldTransform& worldTransform);

	void Update();

	//rayと平面判定
	void CheckCollision(Ray* ray, int i, float* dis);

	void Draw();

	//オブジェクト
	GameObject3D* obj;

	//当たり判定
	Plane frontPlane;
	Plane backPlane;
	Plane leftPlane;
	Plane rightPlane;
	Plane upPlane;
	Plane downPlane;

};
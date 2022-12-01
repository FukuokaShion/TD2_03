#pragma once
#include "GameObject3D.h"
#include "Input.h"
#include "MathFunc.h"

class Laser {
public:
	//コンストラクタ
	Laser();
	//デストラクタ
	~Laser();

	void Initialize(ViewProjection* viewProjection, XMMATRIX* matProjection,int colour);

	void Update();

	void Rotate();

	void Draw();

	void Reset();

	WorldTransform GetWorldTransform() { return device_->worldTransform; }

	Vector3 GetAimPos();

	Vector3 bVelocity(Vector3& velocity, WorldTransform& worldTransform);

	void OnCollision();

	//ゲッター
	float GetRadius() { return laser_->worldTransform.scale.y; }
	Vector3 GetAngle() { return angle; };

	//メンバ関数
private:

	//メンバ変数
private:
	//キー入力
	Input& input = Input::GetInstance();
	POINT mousePos;
	POINT oldMousePos;
	int cursorTimer;
	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);
	Vector3 angle = {};

	//マウス感度
	Vector2 sensitivity = { 450,450 };

	//本体
	GameObject3D* device_ = nullptr;


	//----攻撃----
	GameObject3D* laser_ = nullptr;

	Vector3 viewTarget;
	Matrix4 viewMat;


	//-----制限-----
	const float aimDistance = 10;
	float theta;

};
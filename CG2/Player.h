#pragma once
#include "GameObject3D.h"
#include "Input.h"
#include "MathFunc.h"

class Player {
public:
	//コンストラクタ
	Player();
	//デストラクタ
	~Player();

	void Initialize(ViewProjection* viewProjection, XMMATRIX* matProjection);

	void Update();

	void Attack();
	void Rotate();
	void Move();


	void Draw();

	void Reset();

	int GetIsDead() { return isDead; }

	WorldTransform GetWorldTransform() { return player_->worldTransform; }

	Vector3 GetAimPos();

	Vector3 bVelocity(Vector3& velocity, WorldTransform& worldTransform);

	void OnCollision();
	void bulletEnemyOncollision();
	void bulletBulletOnCollision();

	//ゲッター
	Vector3 GetAngle() { return angle; }
	float GetR() { return r; }

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
	Vector2 sensitivity = { 450,450};

	//本体
	GameObject3D* player_ = nullptr;
	Vector3 pos = { 0, 0, 0 };
	int isDead = false;
	float r = 1;
	//移動速度
	const float moveSpeed = 0.5f;

//----攻撃----
	Vector3 viewTarget; 
	Matrix4 viewMat;


//-----制限-----
	const float aimDistance = 10;
	float theta;
};
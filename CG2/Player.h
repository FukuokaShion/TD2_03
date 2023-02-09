#pragma once
#include "GameObject3D.h"
#include "Input.h"
#include "MathFunc.h"
#include "ViewProjection.h"
#include"CollisionPrimitive.h"

class Map;

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
	WorldTransform SetWorldTransform(WorldTransform trans) { return player_->worldTransform=trans; }


	Vector3 bVelocity(Vector3& velocity, WorldTransform& worldTransform);

	void OnCollision();
	void bulletEnemyOncollision();
	void bulletBulletOnCollision();


	void SetMap(Map* map) { map_ = map; };

	//ゲッター
	Vector3 GetAngle() { return angle; }
	float GetR() { return r; }
	ViewProjection GetView() { return viewProjection_; }
	Vector3 GetAimPos();

	//メンバ関数
private:
	//メンバ変数
private:
	Map* map_;
	//キー入力
	Input& input = Input::GetInstance();
	POINT mousePos;
	POINT oldMousePos;
	int cursorTimer;
	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);
	Vector3 angle = {};


	//マウス感度
	Vector2 sensitivity = { 650,650};

	//本体
	GameObject3D* player_ = nullptr;
	Vector3 pos = { 0, 0, 0 };
	int isDead = false;
	float r = 1;

	Sphere collision_;
	//移動速度
	const float moveSpeed = 0.5f;

//----view----
	ViewProjection viewProjection_;
	Vector3 viewTarget; 
	Matrix4 viewTargetMat;


//-----制限-----
	const float aimDistance = 10;
	float theta;
};
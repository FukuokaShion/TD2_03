#pragma once
#include "GameObject3D.h"
#include "Input.h"
#include "MathFunc.h"
#include "ViewProjection.h"
#include"CollisionPrimitive.h"

class Map;

class Player {
public:
	//�R���X�g���N�^
	Player();
	//�f�X�g���N�^
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

	//�Q�b�^�[
	Vector3 GetAngle() { return angle; }
	float GetR() { return r; }
	ViewProjection GetView() { return viewProjection_; }
	Vector3 GetAimPos();

	//�����o�֐�
private:
	//�����o�ϐ�
private:
	Map* map_;
	//�L�[����
	Input& input = Input::GetInstance();
	POINT mousePos;
	POINT oldMousePos;
	int cursorTimer;
	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);
	Vector3 angle = {};


	//�}�E�X���x
	Vector2 sensitivity = { 650,650};

	//�{��
	GameObject3D* player_ = nullptr;
	Vector3 pos = { 0, 0, 0 };
	int isDead = false;
	float r = 1;

	Sphere collision_;
	//�ړ����x
	const float moveSpeed = 0.5f;

//----view----
	ViewProjection viewProjection_;
	Vector3 viewTarget; 
	Matrix4 viewTargetMat;


//-----����-----
	const float aimDistance = 10;
	float theta;
};
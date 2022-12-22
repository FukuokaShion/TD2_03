#pragma once
#include "GameObject3D.h"
#include "Input.h"
#include "MathFunc.h"
#include "ViewProjection.h"
#include"CollisionPrimitive.h"

#include"Block.h"
#include"Mirror.h"


class Laser {
public:
	//�R���X�g���N�^
	Laser();
	//�f�X�g���N�^
	~Laser();

	void Initialize(ViewProjection* viewProjection, XMMATRIX* matProjection,int colour);

	void Update();

	void Rotate();

	void Affine();

	void Draw();

	void Reset();

	WorldTransform GetWorldTransform() { return device_->worldTransform; }

	Vector3 GetAimPos();

	Vector3 bVelocity(Vector3& velocity, WorldTransform& worldTransform);

	void OnCollision();


	//�Q�b�^�[
	float GetRadius() { return laser_[0]->worldTransform.scale.y; }
	Vector3 GetAngle() { return angle; };
	ViewProjection GetView() { return viewProjection_; }
	Ray *GetRay() { return ray; }

	//�����o�֐�
private:


public:

	int reflection;
	//�����o�ϐ�
private:
	//�L�[����
	Input& input = Input::GetInstance();
	POINT mousePos;
	POINT oldMousePos;
	int cursorTimer;
	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);
	Vector3 angle = {};

	//�}�E�X���x
	Vector2 sensitivity = { 450,450 };

	//�{��
	GameObject3D* device_ = nullptr;


	//----�U��----
	GameObject3D* laser_[10];
	bool isLaserDead = true;

	ViewProjection viewProjection_;
	Vector3 viewTarget;
	Matrix4 viewTargetMat;


	//-----����-----
	const float aimDistance = 10;
	float theta;


	//-------
	//Plane frontPlane;
	//Plane backPlane;
	//Plane leftPlane;
	//Plane rightPlane;
	//Plane upPlane;
	//Plane downPlane;

	Ray ray[10];


	//Block* block;
	//Mirror* mirror;
};
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

	void Initialize(ViewProjection* viewProjection, XMMATRIX* matProjection,int colour,Vector3 pos);

	void Update();

	void Rotate();

	void Affine();

	void Draw();

	void Reset();

	void SetTransJson(Vector3 trans);

	//�����Ă�������Ƀx�N�g���ύX
	Vector3 bVelocity(Vector3& velocity, WorldTransform& worldTransform);

	//�Փˌ㏈��
	void OnCollision();


	//�Q�b�^�[
	Vector3 GetAimPos();
	WorldTransform GetWorldTransform() { return device_->worldTransform; }
	float GetRadius() { return laser_[0]->worldTransform.scale.y; }
	Vector3 GetAngle() { return angle; };
	ViewProjection GetView() { return viewProjection_; }
	Ray *GetRay() { return ray; }
	Vector3 GetPos() { return device_->worldTransform.translation; }

	//�����o�֐�
private:


public:
	//���ˉ�
	int reflection;

	//�����o�ϐ�
private:
	//����
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

	//���_
	ViewProjection viewProjection_;
	Vector3 viewTarget;
	Matrix4 viewTargetMat;


	//-----����-----
	const float aimDistance = 10;
	float theta;


	//-------

	Ray ray[10];
};
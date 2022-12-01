#pragma once
#include "GameObject3D.h"
#include "Input.h"
#include "MathFunc.h"

class Laser {
public:
	//�R���X�g���N�^
	Laser();
	//�f�X�g���N�^
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

	//�Q�b�^�[
	float GetRadius() { return laser_->worldTransform.scale.y; }
	Vector3 GetAngle() { return angle; };

	//�����o�֐�
private:

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
	GameObject3D* laser_ = nullptr;

	Vector3 viewTarget;
	Matrix4 viewMat;


	//-----����-----
	const float aimDistance = 10;
	float theta;

};
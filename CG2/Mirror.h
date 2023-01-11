#pragma once
#include "GameObject3D.h"
#include"CollisionPrimitive.h"

class Mirror {
public:
	//�R���X�g���N�^
	Mirror();
	//�f�X�g���N�^
	~Mirror();

	void Initialize(ViewProjection* viewProjection, XMMATRIX* matProjection, WorldTransform& worldTransform);

	void Update();

	//ray�ƕ��ʔ���
	void CheckCollision(Ray* ray, int i, float* dis);

	void Draw();

	//�I�u�W�F�N�g
	GameObject3D* obj;

	//�����蔻��
	Plane frontPlane;
	Plane backPlane;
	Plane leftPlane;
	Plane rightPlane;
	Plane upPlane;
	Plane downPlane;

};
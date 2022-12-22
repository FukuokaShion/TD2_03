#pragma once
#include<cmath>
#include"Vector3.h"

///����

struct Plane
{
	//�@���x�N�g��
	Vector3 normal = { 0,1,0 };

	//���_����̋���
	float distance = 0.0f;

	//�ʂ̒��S���W
	Vector3 pos = { 0,0,0 };

	//�ʂ̑傫��
	Vector3 size = { 1,1,1 };
};


//���C
struct Ray
{
	//�n�_���W
	Vector3 start = { 0,0,0 };
	//����
	//DirectX::XMVECTOR dir = { 1,0,0,0 };
	Vector3 dir = { 1,0,0 };

	bool isReflection = false;
};
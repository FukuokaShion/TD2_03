#pragma once
#include "Matrix4.h"
#include "Vector3.h"
#include "MathFunc.h"
#include"WorldTransform.h"

class ViewProjection
{
public:
	Matrix4 matView;
	Vector3 eye;	//���_���W
	Vector3 target;	//�����_���W
	Vector3 up;		//������x�N�g��

public:
	void Initialize();
	void UpdateView();
	void UpdateView(Vector3 target, WorldTransform worldTransform);
};


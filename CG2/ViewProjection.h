#pragma once
#include "Matrix4.h"
#include "Vector3.h"
#include "MathFunc.h"
#include"WorldTransform.h"

class ViewProjection
{
public:
	Matrix4 matView;
	Vector3 eye;	//視点座標
	Vector3 target;	//注視点座標
	Vector3 up;		//上方向ベクトル

public:
	void Initialize();
	void UpdateView();
	void UpdateView(Vector3 target, WorldTransform worldTransform);
};


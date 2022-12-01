#include "ViewProjection.h"

void ViewProjection::Initialize() {
	eye = {0 , 0 , -50};	//視点座標
	target = {0 , 0 , 0};	//注視点座標
	up = {0 , 1 , 0};		//上方向ベクトル
	UpdateView();
}

void ViewProjection::UpdateView() {
	matView = MathFunc::Utility::CreatMatView(eye , target , up);
}


void ViewProjection::UpdateView(Vector3 target, WorldTransform worldTransform) {
	Matrix4 affineMat;
	affineMat.SetIdentityMatrix();
	affineMat.m[3][0] = eye.x;
	affineMat.m[3][1] = eye.y;
	affineMat.m[3][2] = eye.z;

	affineMat *= worldTransform.matWorld;

	Vector3 newEye;
	newEye.x = affineMat.m[3][0];
	newEye.y = affineMat.m[3][1];
	newEye.z = affineMat.m[3][2];

	matView = MathFunc::Utility::CreatMatView(newEye, target, up);
}
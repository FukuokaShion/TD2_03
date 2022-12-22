#include "Laser.h"
#include <cmath>
#include"Collision.h"


Vector3 BulletRota(Vector3 pos1, Vector3 pos2);
Vector3 BulletTrans(Vector3 pos1, Vector3 pos2);
float BulletScale(Vector3 pos1, Vector3 pos2);


Laser::Laser() {

}

Laser::~Laser() {
	delete device_;
}

void Laser::Initialize(ViewProjection* viewProjection, XMMATRIX* matProjection, int colour) {
	GetCursorPos(&mousePos);
	viewProjection_.Initialize();
	viewProjection_.eye = Vector3{ 0,1.5f,0 };
	viewTargetMat.SetIdentityMatrix();

	device_ = new GameObject3D();
	device_->PreLoadModel("Resources/tofu/tofu.obj");
	device_->PreLoadTexture(L"Resources/tofu/enemy.png");
	device_->SetViewProjection(viewProjection);
	device_->SetMatProjection(matProjection);
	device_->Initialize();
	device_->worldTransform.translation = { 0,0,0 };

	for (int i = 0; i < 10; i++) {
		laser_[i] = new GameObject3D();
		laser_[i]->PreLoadModel("Resources/tofu/tofu.obj");
		laser_[i]->PreLoadTexture(L"Resources/redLaser.png");
		laser_[i]->SetViewProjection(viewProjection);
		laser_[i]->SetMatProjection(matProjection);
		laser_[i]->Initialize();
		laser_[i]->worldTransform.scale = { 1,0.3f ,0.3f };
		
	}


	//frontPlane.normal = { 0, 0, -1 };
	//frontPlane.distance = -40.0f;
	//frontPlane.pos = { 0,20,40 };
	//frontPlane.size = { 40,20,0 };


	//backPlane.normal = { 0, 0, 1 };
	//backPlane.distance = -40.0f;
	//backPlane.pos = { 0,20,-40 };
	//backPlane.size = { 40,20,0 };

	//leftPlane.normal = { 1, 0, 0};
	//leftPlane.distance = -40.0f;
	//leftPlane.pos = { -40,20,0 };
	//leftPlane.size = { 0,20,40 };

	//rightPlane.normal = { -1, 0, 0 };
	//rightPlane.distance = -40.0f;
	//rightPlane.pos = { 40,20,0 };
	//rightPlane.size = { 0,20,40 };

	//upPlane.normal = { 0, -1, 0 };
	//upPlane.distance = -40.0f;
	//upPlane.pos = { 0,40,0 };
	//upPlane.size = { 40,0,40 };

	//downPlane.normal = { 0, 1, 0};
	//downPlane.distance = -1.0f;
	//downPlane.pos = { 0,-1,0 };
	//downPlane.size = { 40,0,40 };

	////----------
	//block = new Block();
	//WorldTransform blockworld;
	//blockworld.initialize();
	//blockworld.translation = { -5,0,15 };
	//blockworld.scale = { 1,1,1 };
	//block->Initialize(viewProjection, matProjection, blockworld);



	//mirror = new Mirror();
	//WorldTransform mirrorworld;
	//mirrorworld.initialize();
	//mirrorworld.translation = { 5,0,15 };
	//mirrorworld.scale = { 1,1,1 };
	//mirror->Initialize(viewProjection, matProjection, mirrorworld);
}

void Laser::Reset() {
	device_->worldTransform.rotation = { 0 , 0 , 0 };
	//aimは本体の子
	viewTarget = { 0,0,10 };
	for (int i = 0; i < 10; i++) {
		laser_[i]->worldTransform.translation = {0 , 0 , 0};
	}
	theta = 0;
}

void Laser::Update() {
	device_->Update();

	viewTargetMat.SetIdentityMatrix();
	viewTargetMat.m[3][0] = viewTarget.x;
	viewTargetMat.m[3][1] = viewTarget.y;
	viewTargetMat.m[3][2] = viewTarget.z;

	viewTargetMat *= device_->worldTransform.matWorld;

	viewProjection_.target.x = viewTargetMat.m[3][0];
	viewProjection_.target.y = viewTargetMat.m[3][1];
	viewProjection_.target.z = viewTargetMat.m[3][2];

	viewProjection_.UpdateView(GetAimPos(), device_->worldTransform);
	for (int i = 0; i < 10; i++) {
		laser_[i]->Update();
	}
	

	/*block->Update();
	mirror->Update();*/
}

void Laser::Draw() {
	device_->Draw();
	for (int i = 0; i < reflection + 1; i++) {
		laser_[i]->Draw();
	}
	
	//block->Draw();
	//mirror->Draw();
}

void Laser::Rotate() {
	const float PI = 3.141592;

	//マウスのモニター座標の取得
	oldMousePos = mousePos;
	GetCursorPos(&mousePos);

	//一定時間でカーソルをモニターの中心に移動
	cursorTimer++;
	if (cursorTimer > 30) {
		//カーソルの位置移動
		SetCursorPos(width / 2, height / 2);
		//保存してるマウス位置も中心に変更
		mousePos = { width / 2, height / 2 };
		oldMousePos = { width / 2, height / 2 };

		//タイマーのリセット
		cursorTimer = 0;
	}

	//GameSceneでカメラのターゲットをaimの座標にしているため
	//マウスのy座標に一定の変化がある時
	if (abs(mousePos.y - oldMousePos.y) > 0) {
		theta += -PI / sensitivity.y * (mousePos.y - oldMousePos.y);
		//角度制限
		if (theta < -PI / 5 * 2) {//下の制限
			theta = -PI / 5 * 2;
		}
		else if (theta > PI / 3) { //上の制限
			theta = PI / 3;
		}
		//aimのy座標を変化
		viewTarget.z = cos(theta) * aimDistance;
		viewTarget.y = sin(theta) * aimDistance;
	}
	//マウスのx座標に一定の変化がある時
	if (abs(mousePos.x - oldMousePos.x) > 0) {
		//本体を回転(子のaimも回転する)
		device_->worldTransform.rotation.y += (float)(mousePos.x - oldMousePos.x) / sensitivity.x;
	}



//-------------------------
	ray[0].start = device_->worldTransform.translation;
	Vector3 vec;
	vec.x = viewTargetMat.m[3][0] - device_->worldTransform.translation.x;
	vec.y = viewTargetMat.m[3][1] - device_->worldTransform.translation.y;
	vec.z = viewTargetMat.m[3][2] - device_->worldTransform.translation.z;
	vec.nomalize();

	ray[0].dir = vec;

	float dis;

	/*for (int i = 0; i < 9; i++) {
		dis = 512.0f;

		Collision::CheckRay2Plane(ray[i], ray[i + 1], frontPlane, &dis);
		Collision::CheckRay2Plane(ray[i], ray[i + 1], backPlane, &dis);
		Collision::CheckRay2Plane(ray[i], ray[i + 1], leftPlane, &dis);
		Collision::CheckRay2Plane(ray[i], ray[i + 1], rightPlane, &dis);
		Collision::CheckRay2Plane(ray[i], ray[i + 1], upPlane, &dis);
		Collision::CheckRay2Plane(ray[i], ray[i + 1], downPlane, &dis);

		block->CheckCollision(ray, i, &dis);
		mirror->CheckCollision(ray, i, &dis);


		laser_[i]->worldTransform.rotation = BulletRota(ray[i].start, ray[i + 1].start);
		laser_[i]->worldTransform.scale.x = BulletScale(ray[i].start, ray[i + 1].start);
		laser_[i]->worldTransform.translation = BulletTrans(ray[i].start, ray[i + 1].start);

		if (ray[i + 1].isReflection == false) {
			reflection = i;
			break;
		}
	}*/

}

void Laser::Affine() {
	for (int i = 0; i < reflection + 1; i++) {
		laser_[i]->worldTransform.rotation = BulletRota(ray[i].start, ray[i + 1].start);
		laser_[i]->worldTransform.scale.x = BulletScale(ray[i].start, ray[i + 1].start);
		laser_[i]->worldTransform.translation = BulletTrans(ray[i].start, ray[i + 1].start);
	}
}

Vector3 Laser::bVelocity(Vector3& velocity, WorldTransform& worldTransform)
{
	Vector3 result = { 0,0,0 };

	//内積
	result.z = velocity.x * worldTransform.matWorld.m[0][2] +
		velocity.y * worldTransform.matWorld.m[1][2] +
		velocity.z * worldTransform.matWorld.m[2][2];

	result.x = velocity.x * worldTransform.matWorld.m[0][0] +
		velocity.y * worldTransform.matWorld.m[1][0] +
		velocity.z * worldTransform.matWorld.m[2][0];

	result.y = velocity.x * worldTransform.matWorld.m[0][1] +
		velocity.y * worldTransform.matWorld.m[1][1] +
		velocity.z * worldTransform.matWorld.m[2][1];

	return result;
}

void Laser::OnCollision()
{

}

Vector3 Laser::GetAimPos() {
	//子の為worldTransformではなくワールド行列から取得
	Vector3 pos;

	pos.x = viewTargetMat.m[3][0];
	pos.y = viewTargetMat.m[3][1];
	pos.z = viewTargetMat.m[3][2];

	return pos;
}


Vector3 BulletRota(Vector3 pos1, Vector3 pos2) {
	Vector3 rota;
	float PI = 3.141592;

	//アークタンジェントで角度の計算
	//向く面は同じ
	if (abs(pos2.z - pos1.z) <= abs(pos2.x - pos1.x) && pos2.x - pos1.x > 0) {
		rota.z = atan2(pos2.y - pos1.y, pos2.x - pos1.x);
		rota.y = -atan2(pos2.z - pos1.z, pos2.x - pos1.x);
		rota.x = 0;
	}
	else if (abs(pos2.z - pos1.z) <= abs(pos2.x - pos1.x) && pos2.x - pos1.x < 0) {
		rota.z = -atan2(pos2.y - pos1.y, pos2.x - pos1.x) + PI;
		rota.y = -atan2(pos2.z - pos1.z, pos2.x - pos1.x);
		rota.x = 0;
	}
	else if (abs(pos2.z - pos1.z) > abs(pos2.x - pos1.x) && pos2.z - pos1.z > 0) {
		rota.z = atan2(pos2.y - pos1.y, pos2.z - pos1.z);
		rota.y = -atan2(pos2.z - pos1.z, pos2.x - pos1.x);
		rota.x = 0;
	}
	else if (abs(pos2.z - pos1.z) > abs(pos2.x - pos1.x) && pos2.z - pos1.z < 0) {
		rota.z = -atan2(pos2.y - pos1.y, pos2.z - pos1.z) + PI;
		rota.y = -atan2(pos2.z - pos1.z, pos2.x - pos1.x);
		rota.x = 0;
	}


	return rota;
}

Vector3 BulletTrans(Vector3 pos1, Vector3 pos2) {
	Vector3 trans;

	trans = pos1 + ((pos2 - pos1) / 2);

	return trans;
}

float BulletScale(Vector3 pos1, Vector3 pos2) {
	float length;
	length = sqrt(pow(pos2.x - pos1.x, 2) + pow(pos2.y - pos1.y, 2) + pow(pos2.z - pos1.z, 2)) - 1;

	float scale;
	scale = length / 2;

	return scale;
}
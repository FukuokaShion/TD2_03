#include "Laser.h"
#include <cmath>

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

	device_ = new GameObject3D();
	device_->PreLoadModel("Resources/tofu/player.obj");
	device_->PreLoadTexture(L"Resources/tofu/player.png");
	device_->SetViewProjection(viewProjection);
	device_->SetMatProjection(matProjection);
	device_->Initialize();

	
	laser_ = new GameObject3D();
	laser_->PreLoadModel("Resources/tofu/tofu.obj");
	laser_->PreLoadTexture(L"Resources/bullet.png");
	laser_->SetViewProjection(viewProjection);
	laser_->SetMatProjection(matProjection);
	laser_->Initialize();
	laser_->worldTransform.scale = { 1,0.6f ,0.6f };

}

void Laser::Reset() {
	device_->worldTransform.rotation = { 0 , 0 , 0 };
	//aimは本体の子
	viewTarget = { 0,0,10 };
	laser_->worldTransform.translation = { 0 , 0 , 0 };
	theta = 0;
}

void Laser::Update() {
	device_->Update();

	viewMat.SetIdentityMatrix();
	viewMat.m[3][0] = viewTarget.x;
	viewMat.m[3][1] = viewTarget.y;
	viewMat.m[3][2] = viewTarget.z;

	viewMat *= device_->worldTransform.matWorld;


	laser_->Update();
}

void Laser::Draw() {
	device_->Draw();
	laser_->Draw();
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


	laser_->worldTransform.rotation = BulletRota(device_->worldTransform.translation, Vector3(viewMat.m[3][0], viewMat.m[3][1], viewMat.m[3][2]));
	laser_->worldTransform.scale.x = BulletScale(device_->worldTransform.translation, Vector3(viewMat.m[3][0], viewMat.m[3][1], viewMat.m[3][2]));
	laser_->worldTransform.translation = BulletTrans(device_->worldTransform.translation, Vector3(viewMat.m[3][0], viewMat.m[3][1], viewMat.m[3][2]));

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

	pos.x = viewMat.m[3][0];
	pos.y = viewMat.m[3][1];
	pos.z = viewMat.m[3][2];

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
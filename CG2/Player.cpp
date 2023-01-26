#include "Player.h"
#include"Map.h"
#include<cmath>

Player::Player() {

}

Player::~Player() {
	delete player_;
}

void Player::Initialize(ViewProjection* viewProjection, XMMATRIX* matProjection) {
	GetCursorPos(&mousePos);
	viewProjection_.Initialize();
	viewProjection_.eye = Vector3{ 0,3,-8 };
	viewTargetMat.SetIdentityMatrix();

	player_ = new GameObject3D();
	player_->PreLoadModel("Resources/tofu/player.obj");
	player_->PreLoadTexture(L"Resources/tofu/player.png");
	player_->SetViewProjection(viewProjection);
	player_->SetMatProjection(matProjection);
	player_->Initialize();



	Reset();
}

void Player::Reset() {
	player_->worldTransform.translation = pos;
	player_->worldTransform.rotation = { 0 , 0 , 0 };
	//aimは本体の子
	viewTarget = { 0,0,10 };
	isDead = false;
	theta = 0;
}

void Player::Update() {

	Attack();
	viewTargetMat.m[3][0] = viewTarget.x;
	viewTargetMat.m[3][1] = viewTarget.y;
	viewTargetMat.m[3][2] = viewTarget.z;
	viewTargetMat *= player_->worldTransform.matWorld;
	//aimの制限
	//y方向の制限
	if (viewTargetMat.m[3][1] < 0) {
		viewTargetMat.m[3][1] = 0;
	}

	viewProjection_.target.x = viewTargetMat.m[3][0];
	viewProjection_.target.y = viewTargetMat.m[3][1];
	viewProjection_.target.z = viewTargetMat.m[3][2];

	viewProjection_.UpdateView(GetAimPos(), player_->worldTransform);

	player_->Update();
}

void Player::Draw() {
	player_->Draw();
	
}

void Player::Rotate() {
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
		}else if (theta > PI / 3) { //上の制限
			theta = PI / 3;
		}
		//aimのy座標を変化
		viewTarget.z = cos(theta) * aimDistance;
		viewTarget.y = sin(theta) * aimDistance;
	}
	//マウスのx座標に一定の変化がある時
	if (abs(mousePos.x - oldMousePos.x) > 0) {
		//本体を回転(子のaimも回転する)
		player_->worldTransform.rotation.y += (float)(mousePos.x - oldMousePos.x) / sensitivity.x;
	}
}

void Player::Move() {
	Vector3 velocity = { 0,0,0 };

	if (input.PushKey(DIK_A)) {
		velocity.x -= moveSpeed;
	}
	if (input.PushKey(DIK_D)) {
		velocity.x += moveSpeed;
	}
	if (input.PushKey(DIK_W)) {
		velocity.z += moveSpeed;
	}
	if (input.PushKey(DIK_S)) {
		velocity.z -= moveSpeed;
	}

	//速度ベクトルを自機の向きに合わせて回転させる
	velocity = bVelocity(velocity, player_->worldTransform);

	WorldTransform preMovePos = player_->worldTransform;
	preMovePos.translation += velocity;
	if (map_->CheckCollisionPlayer2map(preMovePos, velocity) == false) {
		//移動
		player_->worldTransform.translation += velocity;
	}
}

void Player::Attack() {
	
}

Vector3 Player::bVelocity(Vector3& velocity, WorldTransform& worldTransform)
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

void Player::OnCollision()
{
}
void Player::bulletEnemyOncollision()
{
}

void Player::bulletBulletOnCollision()
{
}

Vector3 Player::GetAimPos() {
	//子の為worldTransformではなくワールド行列から取得
	Vector3 pos;

	pos.x = viewTargetMat.m[3][0];
	pos.y = viewTargetMat.m[3][1];
	pos.z = viewTargetMat.m[3][2];

	return pos;
}
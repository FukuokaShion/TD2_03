#include"Enemy.h"
#include<cmath>

Enemy::Enemy() {
}

Enemy::~Enemy() {
	delete gameObject;
}

void Enemy::Initialize(ViewProjection* viewProjection, XMMATRIX* matProjection) {
	//敵本体生成
	gameObject = new GameObject3D();
	gameObject->PreLoadModel("Resources/tofu/tofu.obj");
	gameObject->PreLoadTexture(L"Resources/tofu/tofu.png");
	gameObject->SetViewProjection(viewProjection);
	gameObject->SetMatProjection(matProjection);
	gameObject->Initialize();

	//弾生成
	for (int i = 0; i < bulletNum; i++) {
		bullets_[i] = new GameObject3D();
		bullets_[i]->PreLoadModel("Resources/tofu/tofu.obj");
		bullets_[i]->PreLoadTexture(L"Resources/tofu.png");
		bullets_[i]->SetViewProjection(viewProjection);
		bullets_[i]->SetMatProjection(matProjection);
		bullets_[i]->Initialize();
	}

	Reset();
}

void Enemy::Reset() {
	//本体の座標初期
	gameObject->worldTransform.translation = pos;

	hp = hpMax;

	isInvincible = false;
	invincibleTimer = invincibleTime;

	//弾のフラグリセット
	for (int i = 0; i < bulletNum; i++) {
		bulletIsDead[i] = true;
	}
	num = { 0,0,0 };
	time = 60;
}

 
void Enemy::Update() {
	Rota();
	Attack();
	Move();

	//出てる弾の処理
	for (int i = 0; i < bulletNum; i++) {
		if (bulletIsDead[i] == false) {
			//時間経過で弾を削除
			if (--deathTimer_[i] <= 0)
			{
				bulletIsDead[i] = true;
			}
			//弾の移動
			bullets_[i]->worldTransform.translation += velocity[i];
			bullets_[i]->Update();
			//x
			if (bullets_[i]->worldTransform.translation.x > stageEdge) {
				bulletIsDead[i] = true;
			}
			else if (bullets_[i]->worldTransform.translation.x < -stageEdge) {
				bulletIsDead[i] = true;
			}
			//z
			if (bullets_[i]->worldTransform.translation.z> stageEdge) {
				bulletIsDead[i] = true;
			}
			else if (bullets_[i]->worldTransform.translation.z < -stageEdge) {
				bulletIsDead[i] = true;
			}
		}
	}

	if (isInvincible == true) {
		invincibleTimer--;
		if (invincibleTimer <= 0) {
			isInvincible = false;
		}
	}

	gameObject->Update();
}

void Enemy::Attack() {
	attackTimer--;
	//一定時間で弾発射
	if (attackTimer <= 0)
	{
		for (int i = 0; i < bulletNum; i++) {
			//出ていない弾を選ぶ
			if (bulletIsDead[i] == true) {
				bulletIsDead[i] = false;
				//弾の寿命をセット
				deathTimer_[i] = kLiteTime;
				//弾の速度
				const float kBulletSpeed = 0.6f;
				velocity[i] = { kBulletSpeed, 0, 0 };
				//速度ベクトルを自機の向きに合わせて回転させる
				velocity[i] = bVelocity(velocity[i], gameObject->worldTransform);

				//弾の初期位置を敵と同じに
				bullets_[i]->worldTransform.translation = gameObject->worldTransform.translation;

				break;
			}
		}
		//攻撃の時間リセット
		attackTimer = delayTime;
	}
}

void Enemy::Move()
{
	time--;
	//Vector3 num = {0,0,0};
	/*WorldTransform pPos = player_->GetWorldTransform();
	Vector3 num = pPos.translation - gameObject->worldTransform.translation;*/
	if (time <= 10)
	{
		speed = 0.5f;
	}
	if (time <= 0)
	{
		pPos = player_->GetWorldTransform();
		num = pPos.translation - gameObject->worldTransform.translation;
		num.nomalize();
		//num = num / 20;
		time = 60;
		speed = 0.2f;
	}
	else
	{
		//num = num/10;
		gameObject->worldTransform.translation += num * speed;
	}
	
	//x
	if (gameObject->worldTransform.translation.x > stageEdge) {
		gameObject->worldTransform.translation.x = stageEdge;
	}
	else if (gameObject->worldTransform.translation.x < -stageEdge) {
		gameObject->worldTransform.translation.x = -stageEdge;
	}
	//z
	if (gameObject->worldTransform.translation.z > stageEdge) {
		gameObject->worldTransform.translation.z = stageEdge;
	}
	else if (gameObject->worldTransform.translation.z < -stageEdge) {
		gameObject->worldTransform.translation.z = -stageEdge;
	}
	


}

//プレイヤーのほうを向く
void Enemy::Rota() {
	WorldTransform playerWorldTransform = player_->GetWorldTransform();

	gameObject->worldTransform.rotation.y = -atan2(playerWorldTransform.translation.z - gameObject->worldTransform.translation.z, playerWorldTransform.translation.x - gameObject->worldTransform.translation.x);
}


void Enemy::Draw() {
	if (invincibleTimer % 2 == 0) {
		gameObject->Draw();
	}
	for (int i = 0; i < bulletNum; i++) {
		if (bulletIsDead[i] == false) {
			bullets_[i]->Draw();
		}
	}
}

void Enemy::OnCollision() {
	if (isInvincible == false) {
		hp--;
		invincibleTimer = invincibleTime;
		isInvincible = true;
	}
	//gameObject->worldTransform.translation.x += 10;
}

Vector3 Enemy::bVelocity(Vector3& velocity, WorldTransform& worldTransform) {
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
#include "GameScene.h"
#include <cassert>


GameScene::GameScene() {

}

GameScene::~GameScene() {

}

void GameScene::Initialize(WinApp* winApp) {
	scene = Scene::Title;

	//透視投影変換行列の計算
	matProjection_ = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(45.0) ,
		(float)winApp->window_width / winApp->window_height ,
		0.1f , 1000.0f
	);

	viewProjection_.Initialize();
	viewProjection_.eye = Vector3{ 0,3,-8 };

	//XAudioエンジンのインスタンスを生成
	soundManager_.Initialize();

	//プレイヤー
	player_ = new Player();
	player_->Initialize(&viewProjection_, &matProjection_);

	map = new Map();
	map->Initialize(&viewProjection_, &matProjection_);

	map->SetPlayer(player_);
	player_->SetMap(map);
//----------------
	//スプライト読み込み
	Sprite::LoadTexture(1, L"Resources/title.png");
	Sprite::LoadTexture(2, L"Resources/GameClear.png");
	Sprite::LoadTexture(3, L"Resources/GameOver.png");

	//スプライトの設定
	title_ = Sprite::Create(1, { 0 , 0 });
	clear_ = Sprite::Create(2, { 0 , 0 });
	gameOver_ = Sprite::Create(3, { 0 , 0 });

}

void GameScene::Update() {


	switch (scene)
	{
	case Scene::Title:

		if (input_.TriggerKey(DIK_0)) {
			//カーソルの非表示
			ShowCursor(FALSE);
			player_->Reset();
			map->Reset(0);
			scene = Scene::Play; 
		}else if (input_.TriggerKey(DIK_1)) {
			//カーソルの非表示
			ShowCursor(FALSE);
			player_->Reset();
			map->Reset(1);
			scene = Scene::Play;
		}
		
		break;
	case Scene::Play:

		map->Update();

		//------カメラ-----
			//情報取得
		if (map->GetIsControlLaser()) {
			player_->Update();
			viewProjection_ = map->GetView();
		}else {
			//プレイヤー
			player_->Move();

			player_->Rotate();
			viewProjection_ = player_->GetView();
			player_->Update();
		}

		//全てのレーザーがクリスタルに当たっているなら
		if (map->IsHitRLaser() && map->IsHitGLaser() && map->IsHitBLaser()) {
			//クリア
			scene = Scene::Clear;
		}

		break;
	case Scene::Clear:
		if (input_.TriggerKey(DIK_SPACE)) {
			scene = Scene::Title;
		}

		break;
	case Scene::Gameover:
		if (input_.TriggerKey(DIK_SPACE)) {
			scene = Scene::Title;
		}

		break;
	}
}

void GameScene::Draw() {

	//3D描画
	switch (scene)
	{
	case Scene::Title:
		
		break;
	case Scene::Play:
		map->Draw();
		player_->Draw();

		break;
	case Scene::Clear:

		break;
	case Scene::Gameover:

		break;
	}


	//スプライト描画
	Sprite::PreDraw(dx12base_.GetCmdList().Get());
	switch (scene)
	{
	case Scene::Title:
		title_->Draw();

		break;
	case Scene::Play:

		break;
	case Scene::Clear:
		clear_->Draw();

		break;
	case Scene::Gameover:
		gameOver_->Draw();

		break;
	}

	Sprite::PostDraw();
}


//void GameScene::CheckAllCollisions() {
//	//敵と自弾
//	//情報の取得
//	WorldTransform playerWorldTransform = player_->GetWorldTransform();
//	Vector3 bulletStart = player_->GetStart();
//	Vector3 bulletEnd = player_->GetEnd();
//	float bulletRadius = player_->GetRadius();
//	WorldTransform enemyWorldTransform = enemy_->GetWorldTransform();
//	float enemyRadius = enemy_->GetRadius();
////------弾の当たり判定生成--------
//	//棒の長さ
//	float bulletLength = sqrt(pow(bulletEnd.x - bulletStart.x, 2) + pow(bulletEnd.y - bulletStart.y, 2) + pow(bulletEnd.z - bulletStart.z, 2));
//	//球の必要数
//	int colliderNum = bulletLength / bulletRadius;
//	//球の同士の間隔
//	Vector3 Distance = { (bulletEnd.x - bulletStart.x) / colliderNum, (bulletEnd.y - bulletStart.y) / colliderNum, (bulletEnd.z - bulletStart.z) / colliderNum };
//	//球の位置設定
//	Vector3 bulletCollider[256];
//	for (int i = 0; i < colliderNum; i++) {
//		bulletCollider[i] = bulletStart + Distance * i;
//	}
//
////-------------自弾と敵の当たり判定------------------
//	//自弾と敵の半径の合計
//	float length = bulletRadius + enemyRadius;
//
//	//自機弾が存在するなら
//	if (player_->GetIsBulletDead() == false) {
//		//弾の球全てに対して
//		for (int i = 0; i < colliderNum; i++) {
//			//球と敵の距離
//			float Distance = sqrt(
//				pow(enemyWorldTransform.translation.x - bulletCollider[i].x, 2) +
//				pow(enemyWorldTransform.translation.y - bulletCollider[i].y, 2) +
//				pow(enemyWorldTransform.translation.z - bulletCollider[i].z, 2));
//
//
//			if (Distance <= length) {
//				enemy_->OnCollision();
//				player_->bulletEnemyOncollision();
//				break;
//			}
//		}
//	}
//
////---------------敵弾と自機の判定-----------------------
//	//自機と敵弾の半径の合計
//	length = playerWorldTransform.scale.x + enemy_->bullets_[0]->worldTransform.scale.x;
//
//	for (int i = 0; i < enemy_->bulletNum; i++) {
//		//出てる弾のみ
//		if (enemy_->bulletIsDead[i] == false) {
//			//自機と敵弾の距離
//			float Distance = sqrt(
//				pow(playerWorldTransform.translation.x - enemy_->bullets_[i]->worldTransform.translation.x, 2) +
//				pow(playerWorldTransform.translation.y - enemy_->bullets_[i]->worldTransform.translation.y, 2) +
//				pow(playerWorldTransform.translation.z - enemy_->bullets_[i]->worldTransform.translation.z, 2));
//
//			//当たってるなら
//			if (Distance <= length) {
//				enemy_->bulletIsDead[i] = true;
//				player_->OnCollision();
//			}
//		}
//	}
//
//
//	//---------------敵弾と自弾の判定-----------------------
//	//敵の弾の半径と自機の半径の合計
//	length = enemy_->bullets_[0]->worldTransform.scale.x + bulletRadius;
//
//	if (player_->GetIsBulletDead() == false) {
//		for (int i = 0; i < enemy_->bulletNum; i++)
//		{
//			if (enemy_->bulletIsDead[i] == false) {
//				for (int j = 0; j < colliderNum; j++)
//				{
//					//球と敵の距離
//					float Distance = sqrt(
//						pow(enemy_->bullets_[i]->worldTransform.translation.x - bulletCollider[j].x, 2) +
//						pow(enemy_->bullets_[i]->worldTransform.translation.y - bulletCollider[j].y, 2) +
//						pow(enemy_->bullets_[i]->worldTransform.translation.z - bulletCollider[j].z, 2));
//					if (Distance <= length) {
//						enemy_->bulletIsDead[i] = true;
//						player_->bulletBulletOnCollision();
//						break;
//					}
//				}
//			}
//		}
//	}
//	
//}
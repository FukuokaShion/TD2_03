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
		XMConvertToRadians(45.0),
		(float)winApp->window_width / winApp->window_height,
		0.1f, 1000.0f
	);
	
	viewProjection_.Initialize();
	viewProjection_.eye = Vector3{ 0,3,-8 };

	lookdown_.Initialize();
	lookdown_.eye = Vector3{ 0,30,-50 };
	lookdown_.target = Vector3{ 0,0,0 };
	lookdown_.UpdateView();

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
	Sprite::LoadTexture(2, L"Resources/option.png");
	Sprite::LoadTexture(3, L"Resources/stage.png");
	Sprite::LoadTexture(4, L"Resources/GameClear.png");
	Sprite::LoadTexture(5, L"Resources/GameOver.png");
	Sprite::LoadTexture(6, L"Resources/point.png");
	Sprite::LoadTexture(7, L"Resources/optionButtom.png");
	Sprite::LoadTexture(8, L"Resources/stageButtom.png");
	Sprite::LoadTexture(9, L"Resources/1.png");
	Sprite::LoadTexture(10, L"Resources/2.png");
	Sprite::LoadTexture(11, L"Resources/esc.png");
	Sprite::LoadTexture(12, L"Resources/pause.png");
	Sprite::LoadTexture(13, L"Resources/titleButtom.png");
	Sprite::LoadTexture(14, L"Resources/back.png");
	Sprite::LoadTexture(15, L"Resources/tutorial1.png");
	Sprite::LoadTexture(16, L"Resources/tutorial2.png");
	Sprite::LoadTexture(17, L"Resources/tutorial3.png");
	Sprite::LoadTexture(18, L"Resources/tutorial4.png");
	Sprite::LoadTexture(19, L"Resources/tutorial5.png");
	Sprite::LoadTexture(20, L"Resources/laserEffect.png");
	Sprite::LoadTexture(21, L"Resources/cam1.png");
	Sprite::LoadTexture(22, L"Resources/cam2.png");
	Sprite::LoadTexture(23, L"Resources/3.png");
	Sprite::LoadTexture(24, L"Resources/4.png");



	//スプライトの設定
	title_ = Sprite::Create(1, { 0 , 0 });
	option_ = Sprite::Create(2, { 0,0 });
	stageSelect_ = Sprite::Create(3, { 0,0 });
	clear_ = Sprite::Create(4, { 0 , 0 });
	gameOver_ = Sprite::Create(5, { 0 , 0 });
	point_ = Sprite::Create(6, { 800,480 });
	point_->SetAnchorPoint({ 0.5f,0.5f });
	stageButton_ = Sprite::Create(8, { 1000,480 });
	stageButton_->SetAnchorPoint({ 0.5f,0.5f });
	optionButton_ = Sprite::Create(7, { 1000,600 });
	optionButton_->SetAnchorPoint({ 0.5f,0.5f });
	number_[1] = Sprite::Create(9, { 490,360 });
	number_[1]->SetAnchorPoint({ 0.5f, 0.5f });
	number_[2] = Sprite::Create(10, { 590,360 });
	number_[2]->SetAnchorPoint({ 0.5f, 0.5f });
	number_[3] = Sprite::Create(23, { 690,360 });
	number_[3]->SetAnchorPoint({ 0.5f, 0.5f });
	number_[4] = Sprite::Create(24, { 790,360 });
	number_[4]->SetAnchorPoint({ 0.5f, 0.5f });
	ESC_ = Sprite::Create(11, { 70,40 });
	ESC_->SetAnchorPoint({ 0.5f,0.5f });
	pause_ = Sprite::Create(12, { 0, 0 });
	titleButtom_ = Sprite::Create(13, { 0,0 });
	titleButtom_->SetAnchorPoint({ 0.5f,0.5f });
	back_ = Sprite::Create(14, { 711,360 });
	back_->SetAnchorPoint({ 0.5f,0.5f });
	tutorial_[0] = Sprite::Create(15, { 0,0 });
	tutorial_[1] = Sprite::Create(16, { 0,0 });
	tutorial_[2] = Sprite::Create(17, { 0,0 });
	tutorial_[3] = Sprite::Create(18, { 0,0 });
	tutorial_[4] = Sprite::Create(19, { 0,0 });
  laserEffect_ = Sprite::Create(20, { 0,0 });
	cam_[0] = Sprite::Create(21, { 0,0 });
	cam_[1] = Sprite::Create(22, { 0,0 });
	//ステージの最大数
	max = 3;
}

void GameScene::Update() {

	switch (scene)
	{
	case Scene::Title:
		//選択
		if (input_.TriggerKey(DIK_S)|| input_.TriggerKey(DIK_DOWNARROW)) {
			button = 1;
			point_->SetPosition({ 800,600 });
			
		}else if (input_.TriggerKey(DIK_W) || input_.TriggerKey(DIK_UPARROW)) {
			button = 0;
			point_->SetPosition({ 800,480 });
		}
		
		//決定
		if (input_.TriggerKey(DIK_SPACE)|| input_.TriggerKey(DIK_RETURN)) {
			if (button == 0) {
				scene = Scene::Select;
				point_->SetPosition({ 568,450 });
			}else if (button == 1) {
				scene = Scene::Option;
			}
			Reset();
		}

		break;

	case Scene::Option:
		if (input_.TriggerKey(DIK_SPACE)) {
			scene = Scene::Title;
			Reset();
		}

		break;

	case Scene::Select:

		if (input_.TriggerKey(DIK_A) && button != 0) {
			button -= 1;

		}else if (input_.TriggerKey(DIK_D)&& button != max) {
			button += 1;
			//point_->SetPosition({ 711,450 });
		}
		
		point_->SetPosition({ (490+(button*100.0f)),450});


		if (input_.TriggerKey(DIK_SPACE)) {
			ShowCursor(FALSE);
			stage = button;
			map->Reset(button);
			scene = Scene::Play;
			Reset();
		}


		break;

	case Scene::Play:

		if (isClear == false) {
			if (isPause == false) {
				map->Update();
				//------カメラ-----
					//情報取得
				if (map->GetIsControlLaser()) {

					if (input_.TriggerKey(DIK_F)) {
						if (isLookdown) {
							isLookdown = false;
						}
						else if (isLookdown == false) {
							isLookdown = true;
							angle = 0.0f;
							lookdown_.UpdateView();
						}
					}

					player_->Update();
					if (isLookdown == false) {
						viewProjection_ = map->GetView();
						map->controlRaser();
						map->CheckCollionPlayer2Device();

					}
					else {
						if (input_.PushKey(DIK_Q) || input_.PushKey(DIK_E))
						{
							if (input_.PushKey(DIK_Q)) { angle += XMConvertToRadians(1.0f); }
							else if (input_.PushKey(DIK_E)) { angle -= XMConvertToRadians(1.0f); }

							//angleラジアンだけY軸まわりに回転。半径は-100
							lookdown_.eye.x = -50 * sinf(angle);
							lookdown_.eye.z = -50 * cosf(angle);
							lookdown_.UpdateView();
						}

						viewProjection_ = lookdown_;
					}
				}
				else {
					//プレイヤー
					player_->Move();
					map->CheckCollionPlayer2Device();
					player_->Rotate();
					viewProjection_ = player_->GetView();
					player_->Update();
				}

				//全てのレーザーがクリスタルに当たっているなら
				if (map->IsHitRLaser() && map->IsHitGLaser() && map->IsHitBLaser()) {
					//クリア
					isClear = true;
				}

				if (input_.TriggerKey(DIK_ESCAPE)) {
					isPause = true;
				}

				//チュートリアル
				if (stage == 0) {
					//WASDで移動
					if (tutorialNum == 0) {
						if (input_.PushKey(DIK_W) || input_.PushKey(DIK_A) || input_.PushKey(DIK_S) || input_.PushKey(DIK_D)) {
							tutorialSwitch = true;
						}
						if (tutorialSwitch) {
							tutorialTimer--;
							if (tutorialTimer < 0) {
								tutorialNum = 1;
								tutorialTimer = tutorialTime;
								tutorialSwitch = false;
							}
						}
					}
					//マウスで視点移動
					else if (tutorialNum == 1) {
						tutorialTimer--;
						if (tutorialTimer < 0) {
							tutorialNum = 2;
							tutorialTimer = tutorialTime;
						}
					}
					//赤球を目指そう
					else if (tutorialNum == 2) {
						if (map->IsHitRDevice()) {
							tutorialNum = 3;
						}
					}
					//スペースで操作
					else if (tutorialNum == 3) {
						if (map->GetIsControlLaser()) {
							tutorialNum = 4;
						}

					}
					//全てのレーザーを当ててクリア
					else if (tutorialNum == 4) {
						tutorialTimer--;
						if (tutorialTimer < 0) {
							tutorialNum = 5;
							tutorialTimer = tutorialTime;
						}
					}
				}

			}
			else if (isPause) {

				if (input_.TriggerKey(DIK_SPACE)) {
					scene = Scene::Title;
					Reset();
				}
				if (input_.TriggerKey(DIK_ESCAPE)) {
					isPause = false;
				}
			}
		}
		else {
			if (R >= 1 && G >= 1 && B >= 1) {
				scene = Scene::Clear;
			}
		}

		//ちょっとしたエフェクト
		if (map->IsHitRLaser()){
			if (R < 1) {
				R += 0.02f;
			}
		}else {
			if (R > 0) {
				R -= 0.05f;
			}
		}
		if (map->IsHitGLaser()){
			if (G < 1) {
				G += 0.02f;
			}
		}else {
			if (G > 0) {
				G -= 0.05f;
			}
		}
		if (map->IsHitBLaser()){
			if (B < 1) {
				B += 0.02f;
			}
		}else {
			if (B > 0) {
				B -= 0.05f;
			}
		}
		laserEffect_->SetColor(XMFLOAT4(R, G, B, 1));


		break;
	case Scene::Clear:
		if (input_.TriggerKey(DIK_SPACE)) {
			scene = Scene::Title;
			Reset();
		}

		break;
	case Scene::Gameover:
		if (input_.TriggerKey(DIK_SPACE)) {
			scene = Scene::Title;
			Reset();
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
		point_->Draw();
		optionButton_->Draw();
		stageButton_->Draw();

		break;

	case Scene::Option:
		option_->Draw();

		break;

	case Scene::Select:
		stageSelect_->Draw();
		number_[1]->Draw();
		number_[2]->Draw();
		number_[3]->Draw();
		number_[4]->Draw();
		point_->Draw();

		break;

	case Scene::Play:
		if (map->IsHitRLaser() || map->IsHitGLaser() || map->IsHitBLaser()) {
			laserEffect_->Draw();
		}
		if (stage == 0) {
			if (tutorialNum == 0) {
				tutorial_[0]->Draw();
			}else if (tutorialNum == 1) {
				tutorial_[1]->Draw();
			}
			else if (tutorialNum == 2) {
				tutorial_[2]->Draw();
			}
			else if (tutorialNum == 3) {
				tutorial_[3]->Draw();
			}
			else if (tutorialNum == 4) {
				tutorial_[4]->Draw();
			}
		}
		
		if (map->GetIsControlLaser()) {
			if (isLookdown) {
				cam_[1]->Draw();
			}else {
				cam_[0]->Draw();
			}
		}


		if (isPause) {
			pause_->Draw();
			titleButtom_->Draw();
			point_->Draw();
		}

		map->Draw2D();

		ESC_->Draw();
		
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

void GameScene::Reset() {
	switch (scene)
	{
	case Scene::Title:
		ShowCursor(TRUE);
		button = 0;
		point_->SetPosition({ 800,480 });
		optionButton_->SetPosition({ 1000,600 });
		stageButton_->SetPosition({ 1000,480 });

		break;

	case Scene::Option:
		ShowCursor(TRUE);

		break;

	case Scene::Select:
		ShowCursor(TRUE);
		button = 0;
		point_->SetPosition({ 568,450 });
		
		break;

	case Scene::Play:
		ShowCursor(false);
		isPause = false;
		point_->SetPosition({ 568,480 });
		titleButtom_->SetPosition({ 711,480 });
		tutorialNum = 0;
		tutorialTimer = tutorialTime;
		tutorialSwitch = false;
		isLookdown = false;
		R = 0;
		G = 0;
		B = 0;
		isClear = false;

		player_->Reset();
		map->Update();
		player_->Update();
		viewProjection_ = player_->GetView();

		break;
	case Scene::Clear:


		break;
	case Scene::Gameover:


		break;
	}

}
#include"Map.h"
#include"Collision.h"

Map::Map() {

}

Map::~Map() {

}

void Map::Initialize(ViewProjection* viewProjection, XMMATRIX* matProjection) {
//------------デバッグ用壁----------------
	wallObject = new GameObject3D();
	wallObject->PreLoadModel("Resources/box/box.obj");
	wallObject->PreLoadTexture(L"Resources/box/box.png");
	wallObject->SetViewProjection(viewProjection);
	wallObject->SetMatProjection(matProjection);
	wallObject->Initialize();
	wallObject->worldTransform.translation.y = -1;
	wallObject->worldTransform.scale.x = 40;
	wallObject->worldTransform.scale.y = 20;
	wallObject->worldTransform.scale.z = 40;
	wallObject->worldTransform.UpdateMatWorld();

	frontPlane.normal = { 0, 0, -1 };
	frontPlane.distance = -40.0f;
	frontPlane.pos = { 0,20,40 };
	frontPlane.size = { 40,20,0 };

	backPlane.normal = { 0, 0, 1 };
	backPlane.distance = -40.0f;
	backPlane.pos = { 0,20,-40 };
	backPlane.size = { 40,20,0 };

	leftPlane.normal = { 1, 0, 0 };
	leftPlane.distance = -40.0f;
	leftPlane.pos = { -40,20,0 };
	leftPlane.size = { 0,20,40 };

	rightPlane.normal = { -1, 0, 0 };
	rightPlane.distance = -40.0f;
	rightPlane.pos = { 40,20,0 };
	rightPlane.size = { 0,20,40 };

	upPlane.normal = { 0, -1, 0 };
	upPlane.distance = -40.0f;
	upPlane.pos = { 0,40,0 };
	upPlane.size = { 40,0,40 };

	downPlane.normal = { 0, 1, 0 };
	downPlane.distance = -1.0f;
	downPlane.pos = { 0,-1,0 };
	downPlane.size = { 40,0,40 };

//----------------------------
	//レーザー
	rLaser = new Laser();
	rLaser->Initialize(viewProjection, matProjection, Colour::RED, { 0,0,8 });
	gLaser = new Laser();
	gLaser->Initialize(viewProjection, matProjection, Colour::GREEN, { 16,0,0 });
	bLaser = new Laser();
	bLaser->Initialize(viewProjection, matProjection, Colour::BLUE, { -20,0,0 });


	//ブロック
	block = new Block();
	WorldTransform blockworld;
	blockworld.initialize();
	blockworld.translation = { 7,0,0 };
	blockworld.scale = { 1,6,13 };
	block->Initialize(viewProjection, matProjection, blockworld);

	block2 = new Block();
	WorldTransform blockworld2;
	blockworld2.initialize();
	blockworld2.translation = { -16,0,3 };
	blockworld2.scale = { 1,4,7 };
	block2->Initialize(viewProjection, matProjection, blockworld2);

	//鏡
	mirror = new Mirror();
	WorldTransform mirrorworld;
	mirrorworld.initialize();
	mirrorworld.translation = { 8,4,40 };
	mirrorworld.scale = { 3,3,0.1f };
	mirror->Initialize(viewProjection, matProjection, mirrorworld);


	mirror2 = new Mirror();
	WorldTransform mirrorworld2;
	mirrorworld2.initialize();
	mirrorworld2.translation = { -40,5,20 };
	mirrorworld2.scale = { 0.1f,3,3 };
	mirror2->Initialize(viewProjection, matProjection, mirrorworld2);

	mirror3 = new Mirror();
	WorldTransform mirrorworld3;
	mirrorworld3.initialize();
	mirrorworld3.translation = { -20,5,40 };
	mirrorworld3.scale = { 3,3,0.1f };
	mirror3->Initialize(viewProjection, matProjection, mirrorworld3);

	mirror4 = new Mirror();
	WorldTransform mirrorworld4;
	mirrorworld4.initialize();
	mirrorworld4.translation = { 80,40,40 };
	mirrorworld4.scale = { 3,3,0.1f };
	mirror4->Initialize(viewProjection, matProjection, mirrorworld4);

	//クリスタル
	crystal = new Crystal();
	WorldTransform crystalworld;
	crystalworld.initialize();
	crystalworld.translation = { 0,8,20 };
	crystalworld.scale = { 1,1,1 };
	crystal->Initialize(viewProjection, matProjection, crystalworld);
}


void Map::Reset(int stage) {
	rLaser->Reset();
	gLaser->Reset();
	bLaser->Reset();
	isHitRLaser = false;
	isHitGLaser = false;
	isHitBLaser = false;
}

void Map::Update() {
	//デバッグ用壁
	wallObject->Update();
	
	//プレイヤーの情報取得
	//プレイヤー座標
	WorldTransform playerWoorldTransform = player_->GetWorldTransform();
	//プレイヤーサイズ
	float playerR = player_->GetR();

//------------------------------レーザー処理-------------------------
	//レーザー装置座標取得
	Vector3 rPos = rLaser->GetPos();
	//レーザー装置とプレイヤーが接触しているか
	if (playerWoorldTransform.translation.x + playerR >= rPos.x-1 && playerWoorldTransform.translation.x-playerR<= rPos.x + 1&&
		playerWoorldTransform.translation.z + playerR >= rPos.z -1 && playerWoorldTransform.translation.z - playerR <= rPos.z + 1){
		//スペースを押したか(トリガー)
		if (input.TriggerKey(DIK_SPACE)) {
			//直前で操作しているなら
			if (isControlRLaser) {
				//操作をやめる
				isControlRLaser = false;
			}
			//直前で操作していないなら
			else if (isControlRLaser == false) {
				//操作する
				isControlRLaser = true;
			}
		}
	}else {
		//接触していないなら操作はできない
		isControlRLaser = false;
	}

//-----レーザーの更新--------
	//操作しているなら
	if (isControlRLaser) {
		//レーザー装置の回転
		rLaser->Rotate();

		float dis;

		//レーザー全てのレイにおいて
		for (int i = 0; i < 9; i++) {
			dis = 512.0f;

			//レイを取得
			Ray* ray = rLaser->GetRay();

			//レイと壁の当たり判定
			Collision::CheckRay2Plane(ray[i], ray[i + 1], frontPlane, &dis);
			Collision::CheckRay2Plane(ray[i], ray[i + 1], backPlane, &dis);
			Collision::CheckRay2Plane(ray[i], ray[i + 1], leftPlane, &dis);
			Collision::CheckRay2Plane(ray[i], ray[i + 1], rightPlane, &dis);
			Collision::CheckRay2Plane(ray[i], ray[i + 1], upPlane, &dis);
			Collision::CheckRay2Plane(ray[i], ray[i + 1], downPlane, &dis);

			//レイとブロックの当たり判定
			block->CheckCollision(ray, i, &dis);

			//レイと鏡の当たり判定
			mirror->CheckCollision(ray, i, &dis);
			mirror2->CheckCollision(ray, i, &dis);
			mirror3->CheckCollision(ray, i, &dis);
			mirror4->CheckCollision(ray, i, &dis);

			//レイとクリスタルの当たり判定
			isHitRLaser = crystal->CheckCollision(ray, i, &dis);

			//反射回数を更新
			rLaser->reflection = i;

			//反射できていなかったら
			if (ray[i + 1].isReflection == false) {
				break;
			}
		}
		//レーザー更新
		rLaser->Affine();
	}


	Vector3 gPos = gLaser->GetPos();
	if (playerWoorldTransform.translation.x + playerR >= gPos.x - 1 && playerWoorldTransform.translation.x - playerR <= gPos.x + 1 &&
		playerWoorldTransform.translation.z + playerR >= gPos.z - 1 && playerWoorldTransform.translation.z - playerR <= gPos.z + 1) {
		if (input.TriggerKey(DIK_SPACE)) {
			if (isControlGLaser) {
				isControlGLaser = false;
			}
			else if (isControlGLaser == false) {
				isControlGLaser = true;
			}
		}
	}
	else {
		isControlGLaser = false;
	}

	if (isControlGLaser) {
		gLaser->Rotate();
		float dis;
		for (int i = 0; i < 9; i++) {
			dis = 512.0f;

			Ray* ray = gLaser->GetRay();

			Collision::CheckRay2Plane(ray[i], ray[i + 1], frontPlane, &dis);
			Collision::CheckRay2Plane(ray[i], ray[i + 1], backPlane, &dis);
			Collision::CheckRay2Plane(ray[i], ray[i + 1], leftPlane, &dis);
			Collision::CheckRay2Plane(ray[i], ray[i + 1], rightPlane, &dis);
			Collision::CheckRay2Plane(ray[i], ray[i + 1], upPlane, &dis);
			Collision::CheckRay2Plane(ray[i], ray[i + 1], downPlane, &dis);

			block->CheckCollision(ray, i, &dis);
			mirror->CheckCollision(ray, i, &dis);
			mirror2->CheckCollision(ray, i, &dis);
			mirror3->CheckCollision(ray, i, &dis);
			mirror4->CheckCollision(ray, i, &dis);

			isHitGLaser = crystal->CheckCollision(ray, i, &dis);

			gLaser->reflection = i;

			if (ray[i + 1].isReflection == false) {
				break;
			}
		}

		gLaser->Affine();
	}

	Vector3 bPos = bLaser->GetPos();
	if (playerWoorldTransform.translation.x + playerR >= bPos.x - 1 && playerWoorldTransform.translation.x - playerR <= bPos.x + 1 &&
		playerWoorldTransform.translation.z + playerR >= bPos.z - 1 && playerWoorldTransform.translation.z - playerR <= bPos.z + 1) {
		if (input.TriggerKey(DIK_SPACE)) {
			if (isControlBLaser) {
				isControlBLaser = false;
			}
			else if (isControlBLaser == false) {
				isControlBLaser = true;
			}
		}
	}
	else {
		isControlBLaser = false;
	}

	if (isControlBLaser) {
		bLaser->Rotate();
		float dis;
		for (int i = 0; i < 9; i++) {
			dis = 512.0f;

			Ray* ray = bLaser->GetRay();

			Collision::CheckRay2Plane(ray[i], ray[i + 1], frontPlane, &dis);
			Collision::CheckRay2Plane(ray[i], ray[i + 1], backPlane, &dis);
			Collision::CheckRay2Plane(ray[i], ray[i + 1], leftPlane, &dis);
			Collision::CheckRay2Plane(ray[i], ray[i + 1], rightPlane, &dis);
			Collision::CheckRay2Plane(ray[i], ray[i + 1], upPlane, &dis);
			Collision::CheckRay2Plane(ray[i], ray[i + 1], downPlane, &dis);

			block->CheckCollision(ray, i, &dis);
			mirror->CheckCollision(ray, i, &dis);
			mirror2->CheckCollision(ray, i, &dis);
			mirror3->CheckCollision(ray, i, &dis);
			mirror4->CheckCollision(ray, i, &dis);

			isHitBLaser = crystal->CheckCollision(ray, i, &dis);

			bLaser->reflection = i;

			if (ray[i + 1].isReflection == false) {
				break;
			}
		}

		bLaser->Affine();
	}


	//更新
	rLaser->Update();
	gLaser->Update();
	bLaser->Update();

	block->Update();
	block2->Update();
	mirror->Update();
	mirror2->Update();
	mirror3->Update();
	mirror4->Update();
	crystal->Update();
}

void Map::Draw() {
	rLaser->Draw();
	gLaser->Draw();
	bLaser->Draw();
	wallObject->Draw();
	block->Draw();
	block2->Draw();
	mirror->Draw();
	mirror2->Draw();
	mirror3->Draw();
	mirror4->Draw();
	crystal->Draw();
}

//操作しているか
bool Map::GetIsControlLaser() {
	if (isControlRLaser) {
		return true;
	}if (isControlGLaser) {
		return true;
	}if (isControlBLaser) {
		return true;
	}
	return false;
}

//始点切り替え
ViewProjection Map::GetView() {
	ViewProjection viewProjection;

	//操作している装置の視点に切り替え
	if (isControlRLaser == true) {
		viewProjection = rLaser->GetView();
	}
	if (isControlGLaser == true) {
		viewProjection = gLaser->GetView();
	}
	if (isControlBLaser == true) {
		viewProjection = bLaser->GetView();
	}
	return viewProjection;
}
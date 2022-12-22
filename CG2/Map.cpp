#include"Map.h"
#include"Collision.h"

Map::Map() {

}

Map::~Map() {

}

void Map::Initialize(ViewProjection* viewProjection, XMMATRIX* matProjection) {
	rLaser = new Laser();
	rLaser->Initialize(viewProjection, matProjection, Colour::RED);

	wallObject = new GameObject3D();
	wallObject->PreLoadModel("Resources/colosseum/colosseum_Ver2.obj");
	wallObject->PreLoadTexture(L"Resources/colosseum/wall.png");
	wallObject->SetViewProjection(viewProjection);
	wallObject->SetMatProjection(matProjection);
	wallObject->Initialize();
	wallObject->worldTransform.translation.y = -1;
	wallObject->worldTransform.scale.x = 5;
	wallObject->worldTransform.scale.y = 5;
	wallObject->worldTransform.scale.z = 5;
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



	block = new Block();
	WorldTransform blockworld;
	blockworld.initialize();
	blockworld.translation = { -5,0,15 };
	blockworld.scale = { 1,1,1 };
	block->Initialize(viewProjection, matProjection, blockworld);



	mirror = new Mirror();
	WorldTransform mirrorworld;
	mirrorworld.initialize();
	mirrorworld.translation = { 5,0,15 };
	mirrorworld.scale = { 1,1,1 };
	mirror->Initialize(viewProjection, matProjection, mirrorworld);
}

void Map::Reset(int stage) {
	rLaser->Reset();

}

void Map::Update() {
	wallObject->Update();
	WorldTransform playerWoorldTransform = player_->GetWorldTransform();
	float playerR = player_->GetR();

	if (playerWoorldTransform.translation.x + playerR >= -1 && playerWoorldTransform.translation.x-playerR<=1&&
		playerWoorldTransform.translation.z + playerR >= -1 && playerWoorldTransform.translation.z - playerR <= 1){
		if (input.TriggerKey(DIK_SPACE)) {
			if (isControlRLaser) {
				isControlRLaser = false;
			}else if (isControlRLaser == false) {
				isControlRLaser = true;
			}
		}
	}else {
		isControlRLaser = false;
	}

	if (isControlRLaser) {
		rLaser->Rotate();
		float dis;
		for (int i = 0; i < 9; i++) {
			dis = 512.0f;

			Ray* ray = rLaser->GetRay();

			Collision::CheckRay2Plane(ray[i], ray[i + 1], frontPlane, &dis);
			Collision::CheckRay2Plane(ray[i], ray[i + 1], backPlane, &dis);
			Collision::CheckRay2Plane(ray[i], ray[i + 1], leftPlane, &dis);
			Collision::CheckRay2Plane(ray[i], ray[i + 1], rightPlane, &dis);
			Collision::CheckRay2Plane(ray[i], ray[i + 1], upPlane, &dis);
			Collision::CheckRay2Plane(ray[i], ray[i + 1], downPlane, &dis);

			block->CheckCollision(ray, i, &dis);
			mirror->CheckCollision(ray, i, &dis);


			rLaser->reflection = i;

			if (ray[i + 1].isReflection == false) {
				break;
			}
		}

		rLaser->Affine();
	}
	rLaser->Update();


	block->Update();
	mirror->Update();
}

void Map::Draw() {
	rLaser->Draw();
	wallObject->Draw();
	block->Draw();
	mirror->Draw();
}

ViewProjection Map::GetView() {
	ViewProjection viewProjection;

	if (isControlRLaser) {
		viewProjection = rLaser->GetView();
	}

	return viewProjection;
}
#include"Map.h"

Map::Map() {

}

Map::~Map() {

}

void Map::Initialize(ViewProjection* viewProjection, XMMATRIX* matProjection) {
	rLaser = new Laser();
	rLaser->Initialize(viewProjection, matProjection, Colour::RED);

}

void Map::Reset(int stage) {
	rLaser->Reset();

}

void Map::Update() {
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
	}

	rLaser->Update();



}

void Map::Draw() {
	rLaser->Draw();

}


Vector3 Map::GetViewTarget() {
	Vector3 viewTarget;

	if (isControlRLaser) {
		viewTarget = rLaser->GetAimPos();
	}

	return viewTarget;
}


WorldTransform Map::GetViewWorldTransform() {
	WorldTransform viewWorldTransform;

	if (isControlRLaser) {
		viewWorldTransform = rLaser->GetWorldTransform();
	}

	return viewWorldTransform;
}
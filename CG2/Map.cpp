#include"Map.h"
#include"Collision.h"

Map::Map() {

}

Map::~Map() {

}

void Map::Initialize(ViewProjection* viewProjection, XMMATRIX* matProjection) {
	//���[�U�[
	rLaser = new Laser();
	rLaser->Initialize(viewProjection, matProjection, Colour::RED, { -8,0,0 });
	gLaser = new Laser();
	gLaser->Initialize(viewProjection, matProjection, Colour::GREEN,{ 0,0,0 });
	bLaser = new Laser();
	bLaser->Initialize(viewProjection, matProjection, Colour::BLUE, { 8,0,0 });

//------------�f�o�b�O�p��----------------
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

//----------------------------

	//�u���b�N
	block = new Block();
	WorldTransform blockworld;
	blockworld.initialize();
	blockworld.translation = { -5,0,15 };
	blockworld.scale = { 1,1,1 };
	block->Initialize(viewProjection, matProjection, blockworld);

	//��
	mirror = new Mirror();
	WorldTransform mirrorworld;
	mirrorworld.initialize();
	mirrorworld.translation = { 5,0,15 };
	mirrorworld.scale = { 1,1,1 };
	mirror->Initialize(viewProjection, matProjection, mirrorworld);

	//�N���X�^��
	crystal = new Crystal();
	WorldTransform crystalworld;
	crystalworld.initialize();
	crystalworld.translation = { 0,4,18 };
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
	//�f�o�b�O�p��
	wallObject->Update();
	
	//�v���C���[�̏��擾
	//�v���C���[���W
	WorldTransform playerWoorldTransform = player_->GetWorldTransform();
	//�v���C���[�T�C�Y
	float playerR = player_->GetR();

//------------------------------���[�U�[����-------------------------
	//���[�U�[���u���W�擾
	Vector3 rPos = rLaser->GetPos();
	//���[�U�[���u�ƃv���C���[���ڐG���Ă��邩
	if (playerWoorldTransform.translation.x + playerR >= rPos.x-1 && playerWoorldTransform.translation.x-playerR<= rPos.x + 1&&
		playerWoorldTransform.translation.z + playerR >= rPos.z -1 && playerWoorldTransform.translation.z - playerR <= rPos.z + 1){
		//�X�y�[�X����������(�g���K�[)
		if (input.TriggerKey(DIK_SPACE)) {
			//���O�ő��삵�Ă���Ȃ�
			if (isControlRLaser) {
				//�������߂�
				isControlRLaser = false;
			}
			//���O�ő��삵�Ă��Ȃ��Ȃ�
			else if (isControlRLaser == false) {
				//���삷��
				isControlRLaser = true;
			}
		}
	}else {
		//�ڐG���Ă��Ȃ��Ȃ瑀��͂ł��Ȃ�
		isControlRLaser = false;
	}

//-----���[�U�[�̍X�V--------
	//���삵�Ă���Ȃ�
	if (isControlRLaser) {
		//���[�U�[���u�̉�]
		rLaser->Rotate();

		float dis;

		//���[�U�[�S�Ẵ��C�ɂ�����
		for (int i = 0; i < 9; i++) {
			dis = 512.0f;

			//���C���擾
			Ray* ray = rLaser->GetRay();

			//���C�ƕǂ̓����蔻��
			Collision::CheckRay2Plane(ray[i], ray[i + 1], frontPlane, &dis);
			Collision::CheckRay2Plane(ray[i], ray[i + 1], backPlane, &dis);
			Collision::CheckRay2Plane(ray[i], ray[i + 1], leftPlane, &dis);
			Collision::CheckRay2Plane(ray[i], ray[i + 1], rightPlane, &dis);
			Collision::CheckRay2Plane(ray[i], ray[i + 1], upPlane, &dis);
			Collision::CheckRay2Plane(ray[i], ray[i + 1], downPlane, &dis);

			//���C�ƃu���b�N�̓����蔻��
			block->CheckCollision(ray, i, &dis);

			//���C�Ƌ��̓����蔻��
			mirror->CheckCollision(ray, i, &dis);

			//���C�ƃN���X�^���̓����蔻��
			isHitRLaser = crystal->CheckCollision(ray, i, &dis);

			//���ˉ񐔂��X�V
			rLaser->reflection = i;

			//���˂ł��Ă��Ȃ�������
			if (ray[i + 1].isReflection == false) {
				break;
			}
		}
		//���[�U�[�X�V
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

			isHitBLaser = crystal->CheckCollision(ray, i, &dis);

			bLaser->reflection = i;

			if (ray[i + 1].isReflection == false) {
				break;
			}
		}

		bLaser->Affine();
	}

	//�X�V
	rLaser->Update();
	gLaser->Update();
	bLaser->Update();

	block->Update();
	mirror->Update();
	crystal->Update();
}

void Map::Draw() {
	rLaser->Draw();
	gLaser->Draw();
	bLaser->Draw();
	wallObject->Draw();
	block->Draw();
	mirror->Draw();
	crystal->Draw();
}

//���삵�Ă��邩
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

//�n�_�؂�ւ�
ViewProjection Map::GetView() {
	ViewProjection viewProjection;

	//���삵�Ă��鑕�u�̎��_�ɐ؂�ւ�
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
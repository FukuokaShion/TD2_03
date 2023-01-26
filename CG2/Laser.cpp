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

void Laser::Initialize(ViewProjection* viewProjection, XMMATRIX* matProjection, int colour,Vector3 pos) {
	GetCursorPos(&mousePos);
	viewProjection_.Initialize();
	viewProjection_.eye = Vector3{ 0,1.5f,-5 };
	viewTargetMat.SetIdentityMatrix();

	//���u���f�������ݒ�
	device_ = new GameObject3D();
	device_->PreLoadModel("Resources/tofu/tofu.obj");
	device_->PreLoadTexture(L"Resources/tofu/enemy.png");
	device_->SetViewProjection(viewProjection);
	device_->SetMatProjection(matProjection);
	device_->Initialize();
	device_->worldTransform.translation = pos;

//---------���[�U�[���f�������ݒ�------------
	//Red���[�U�[
	if (colour == 0) {
		for (int i = 0; i < 10; i++) {
			laser_[i] = new GameObject3D();
			laser_[i]->PreLoadModel("Resources/cylinder/cylinder.obj");
			laser_[i]->PreLoadTexture(L"Resources/redLaser.png");
			laser_[i]->SetViewProjection(viewProjection);
			laser_[i]->SetMatProjection(matProjection);
			laser_[i]->Initialize();
			laser_[i]->worldTransform.scale = { 1,0.3f ,0.3f };
		}
	}
	//Green���[�U�[
	if (colour == 1) {
		for (int i = 0; i < 10; i++) {
			laser_[i] = new GameObject3D();
			laser_[i]->PreLoadModel("Resources/cylinder/cylinder.obj");
			laser_[i]->PreLoadTexture(L"Resources/greenLaser.png");
			laser_[i]->SetViewProjection(viewProjection);
			laser_[i]->SetMatProjection(matProjection);
			laser_[i]->Initialize();
			laser_[i]->worldTransform.scale = { 1,0.3f ,0.3f };
		}
	}
	//Blue���[�U�[
	if (colour == 2) {
		for (int i = 0; i < 10; i++) {
			laser_[i] = new GameObject3D();
			laser_[i]->PreLoadModel("Resources/cylinder/cylinder.obj");
			laser_[i]->PreLoadTexture(L"Resources/blueLaser.png");
			laser_[i]->SetViewProjection(viewProjection);
			laser_[i]->SetMatProjection(matProjection);
			laser_[i]->Initialize();
			laser_[i]->worldTransform.scale = { 1,0.3f ,0.3f };
		}
	}

}

//������
void Laser::Reset() {
	device_->worldTransform.rotation = { 0 , 0 , 0 };
	//aim�͖{�̂̎q
	viewTarget = { 0,0,10 };
	for (int i = 0; i < 10; i++) {
		laser_[i]->worldTransform.translation = { 0, -50, 0 };
	}
	reflection = 0;
	theta = 0;
}

void Laser::Update() {
	device_->Update();

//--------���_�ύX----------
	//�����_�s��
	viewTargetMat.SetIdentityMatrix();
	//�����_�̃��[�J�����W����
	viewTargetMat.m[3][0] = viewTarget.x;
	viewTargetMat.m[3][1] = viewTarget.y;
	viewTargetMat.m[3][2] = viewTarget.z;
	//�q�����瑕�u�̃��[���h�s���������
	viewTargetMat *= device_->worldTransform.matWorld;

	//���������_���W��view�ɕۑ�
	viewProjection_.target.x = viewTargetMat.m[3][0];
	viewProjection_.target.y = viewTargetMat.m[3][1];
	viewProjection_.target.z = viewTargetMat.m[3][2];

	//view�X�V
	viewProjection_.UpdateView(GetAimPos(), device_->worldTransform);
//----------------------

	//���[�U�[�X�V
	for (int i = 0; i < 10; i++) {
		laser_[i]->Update();
	}
	
}

void Laser::Draw() {
	device_->Draw();
	for (int i = 0; i < reflection + 1; i++) {
		laser_[i]->Draw();
	}
	
}

void Laser::Rotate() {
	const float PI = 3.141592;

	//�}�E�X�̃��j�^�[���W�̎擾
	oldMousePos = mousePos;
	GetCursorPos(&mousePos);

	//��莞�ԂŃJ�[�\�������j�^�[�̒��S�Ɉړ�
	cursorTimer++;
	if (cursorTimer > 30) {
		//�J�[�\���̈ʒu�ړ�
		SetCursorPos(width / 2, height / 2);
		//�ۑ����Ă�}�E�X�ʒu�����S�ɕύX
		mousePos = { width / 2, height / 2 };
		oldMousePos = { width / 2, height / 2 };

		//�^�C�}�[�̃��Z�b�g
		cursorTimer = 0;
	}

	//GameScene�ŃJ�����̃^�[�Q�b�g��aim�̍��W�ɂ��Ă��邽��
	//�}�E�X��y���W�Ɉ��̕ω������鎞
	if (abs(mousePos.y - oldMousePos.y) > 0) {
		theta += -PI / sensitivity.y * (mousePos.y - oldMousePos.y);
		//�p�x����
		if (theta < -PI / 5 * 2) {//���̐���
			theta = -PI / 5 * 2;
		}
		else if (theta > PI / 3) { //��̐���
			theta = PI / 3;
		}
		//aim��y���W��ω�
		viewTarget.z = cos(theta) * aimDistance;
		viewTarget.y = sin(theta) * aimDistance;
	}
	//�}�E�X��x���W�Ɉ��̕ω������鎞
	if (abs(mousePos.x - oldMousePos.x) > 0) {
		//�{�̂���](�q��aim����]����)
		device_->worldTransform.rotation.y += (float)(mousePos.x - oldMousePos.x) / sensitivity.x;
	}



//-------------------------
	//���_�ɍ��킹�Ĉ�Ԗڂ̃��C���X�V
	ray[0].start = device_->worldTransform.translation;
	Vector3 vec;
	vec.x = viewTargetMat.m[3][0] - device_->worldTransform.translation.x;
	vec.y = viewTargetMat.m[3][1] - device_->worldTransform.translation.y;
	vec.z = viewTargetMat.m[3][2] - device_->worldTransform.translation.z;
	vec.nomalize();

	ray[0].dir = vec;

	float dis;
}

void Laser::Affine() {
	//���˂��Ă��郌�[�U�[�S�Ă��A�t�B���ϊ�
	for (int i = 0; i < reflection + 1; i++) {
		laser_[i]->worldTransform.rotation = BulletRota(ray[i].start, ray[i + 1].start);
		laser_[i]->worldTransform.scale.x = BulletScale(ray[i].start, ray[i + 1].start);
		laser_[i]->worldTransform.translation = ray[i].start;
		//laser_[i]->worldTransform.translation = BulletTrans(ray[i].start, ray[i + 1].start);
	}
}

Vector3 Laser::bVelocity(Vector3& velocity, WorldTransform& worldTransform)
{
	Vector3 result = { 0,0,0 };

	//����
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
	//�q�̈�worldTransform�ł͂Ȃ����[���h�s�񂩂�擾
	Vector3 pos;

	pos.x = viewTargetMat.m[3][0];
	pos.y = viewTargetMat.m[3][1];
	pos.z = viewTargetMat.m[3][2];

	return pos;
}


Vector3 BulletRota(Vector3 pos1, Vector3 pos2) {
	Vector3 rota;
	float PI = 3.141592;

	//�A�[�N�^���W�F���g�Ŋp�x�̌v�Z
	//�����ʂ͓���
	//if (abs(pos2.z - pos1.z) <= abs(pos2.x - pos1.x) && pos2.x - pos1.x > 0) {
	//	rota.z = atan2(pos2.y - pos1.y, pos2.x - pos1.x);
	//	rota.y = -atan2(pos2.z - pos1.z, pos2.x - pos1.x);
	//	rota.x = 0;
	//}
	//else if (abs(pos2.z - pos1.z) <= abs(pos2.x - pos1.x) && pos2.x - pos1.x < 0) {
	//	rota.z = -atan2(pos2.y - pos1.y, pos2.x - pos1.x) + PI;
	//	rota.y = -atan2(pos2.z - pos1.z, pos2.x - pos1.x);
	//	rota.x = 0;
	//}
	//else if (abs(pos2.z - pos1.z) > abs(pos2.x - pos1.x) && pos2.z - pos1.z > 0) {
	//	rota.z = atan2(pos2.y - pos1.y, pos2.z - pos1.z);
	//	rota.y = -atan2(pos2.z - pos1.z, pos2.x - pos1.x);
	//	rota.x = 0;
	//}
	//else if (abs(pos2.z - pos1.z) > abs(pos2.x - pos1.x) && pos2.z - pos1.z < 0) {
	//	rota.z = -atan2(pos2.y - pos1.y, pos2.z - pos1.z) + PI;
	//	rota.y = -atan2(pos2.z - pos1.z, pos2.x - pos1.x);
	//	rota.x = 0;
	//}

	rota.y = atan2(pos2.x - pos1.x, pos2.z - pos1.z) - (PI / 2);
	rota.z = atan2(pos2.y - pos1.y, sqrt(pow(pos2.x - pos1.x, 2) + pow(pos2.z - pos1.z, 2)));
	rota.x = 0;



	return rota;
}

Vector3 BulletTrans(Vector3 pos1, Vector3 pos2) {
	Vector3 trans;

	trans = pos1 + ((pos2 - pos1) / 2);

	return trans;
}

float BulletScale(Vector3 pos1, Vector3 pos2) {
	float length;
	length = sqrtf(pow(pos2.x - pos1.x, 2) + pow(pos2.y - pos1.y, 2) + pow(pos2.z - pos1.z, 2));

	float scale;
	scale = length / 2;

	return scale;
}
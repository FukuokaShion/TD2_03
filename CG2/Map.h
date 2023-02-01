#pragma once
#include<memory>
#include<list>
#include"Laser.h"
#include"Player.h"

#include"Block.h"
#include"Crystal.h"

class Player;

class Map {
public:
	Map();
	~Map();

	void Initialize(ViewProjection* viewProjection, XMMATRIX* matProjection);

	void Reset(int stage);

	void Update();

	void Draw();

	void SetPlayer(Player* player) { player_ = player; };

	void CheckCollisionPlayer2map(WorldTransform* playerPos,Vector3 velocity);

	//���[�U�[�𑀍삵�Ă��邩
	bool GetIsControlLaser();
	//���[�U�[���쎞�̎n�_�؂�ւ�
	ViewProjection GetView();
	//���[�U�[���N���X�^���ɓ������Ă��邩
	bool IsHitRLaser() { return isHitRLaser; };
	bool IsHitGLaser() { return isHitGLaser; };
	bool IsHitBLaser() { return isHitBLaser; };

private:
	enum Colour
	{
		RED,
		GREEN,
		BLUE
	};
	//�L�[����
	Input& input = Input::GetInstance();

	//�v���C���[
	Player* player_ = nullptr;

//-----���[�U�[-------
	//���f��
	Laser* rLaser = nullptr;
	//���삵�Ă��邩
	bool isControlRLaser = false;
	//���f��
	Laser* gLaser = nullptr;
	//���삵�Ă��邩
	bool isControlGLaser = false;
	//���f��
	Laser* bLaser = nullptr;
	//���삵�Ă��邩
	bool isControlBLaser = false;

	//�N���X�^���ɓ������Ă��邩
	bool isHitRLaser = false;
	bool isHitGLaser = false;
	bool isHitBLaser = false;

//--------------------
	//�f�o�b�O�p�t�B�[���h
	GameObject3D* wallObject = nullptr;
	Plane frontPlane;
	Plane backPlane;
	Plane leftPlane;
	Plane rightPlane;
	Plane upPlane;
	Plane downPlane;


	XMMATRIX* matProjection_;
	//�r���[�v���W�F�N�V����
	ViewProjection* viewProjection_;

	//�I�u�W�F�N�g
	Crystal* crystal;

	std::list<std::unique_ptr<Block>> blocks_;
	std::list<std::unique_ptr<Mirror>> mirrors_;

};
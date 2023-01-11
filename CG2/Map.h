#pragma once
#include"Laser.h"
#include"Player.h"

#include"Block.h"

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

	//���[�U�[�𑀍삵�Ă��邩
	bool GetIsControlLaser();
	//���[�U�[���쎞�̎n�_�؂�ւ�
	ViewProjection GetView();

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

//--------------------
	
	Block* block;
	Mirror* mirror;

	//�f�o�b�O�p�t�B�[���h
	GameObject3D* wallObject = nullptr;
	Plane frontPlane;
	Plane backPlane;
	Plane leftPlane;
	Plane rightPlane;
	Plane upPlane;
	Plane downPlane;
};
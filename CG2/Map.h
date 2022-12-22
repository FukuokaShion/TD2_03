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

	bool GetIsControlRLaser() { return isControlRLaser; }

	ViewProjection GetView();

private:
	//ÉLÅ[ì¸óÕ
	Input& input = Input::GetInstance();

	Player* player_ = nullptr;


	GameObject3D* wallObject = nullptr;

	enum Colour
	{
		RED,
		GREEN,
		BLUE
	};

	Laser* rLaser = nullptr;
	bool isControlRLaser = false;



	Plane frontPlane;
	Plane backPlane;
	Plane leftPlane;
	Plane rightPlane;
	Plane upPlane;
	Plane downPlane;


	Block* block;
	Mirror* mirror;

};
#pragma once
#include"Laser.h"
#include"Player.h"

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

	enum Colour
	{
		RED,
		GREEN,
		BLUE
	};

	Laser* rLaser = nullptr;
	bool isControlRLaser = false;



};
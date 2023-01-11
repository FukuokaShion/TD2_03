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

	//レーザーを操作しているか
	bool GetIsControlLaser();
	//レーザー操作時の始点切り替え
	ViewProjection GetView();

private:
	enum Colour
	{
		RED,
		GREEN,
		BLUE
	};
	//キー入力
	Input& input = Input::GetInstance();

	//プレイヤー
	Player* player_ = nullptr;

//-----レーザー-------
	//モデル
	Laser* rLaser = nullptr;
	//操作しているか
	bool isControlRLaser = false;
	//モデル
	Laser* gLaser = nullptr;
	//操作しているか
	bool isControlGLaser = false;
	//モデル
	Laser* bLaser = nullptr;
	//操作しているか
	bool isControlBLaser = false;

//--------------------
	
	Block* block;
	Mirror* mirror;

	//デバッグ用フィールド
	GameObject3D* wallObject = nullptr;
	Plane frontPlane;
	Plane backPlane;
	Plane leftPlane;
	Plane rightPlane;
	Plane upPlane;
	Plane downPlane;
};
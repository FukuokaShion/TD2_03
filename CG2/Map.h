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

	//レーザーを操作しているか
	bool GetIsControlLaser();
	//レーザー操作時の始点切り替え
	ViewProjection GetView();
	//レーザーがクリスタルに当たっているか
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

	//クリスタルに当たっているか
	bool isHitRLaser = false;
	bool isHitGLaser = false;
	bool isHitBLaser = false;

//--------------------
	//デバッグ用フィールド
	GameObject3D* wallObject = nullptr;
	Plane frontPlane;
	Plane backPlane;
	Plane leftPlane;
	Plane rightPlane;
	Plane upPlane;
	Plane downPlane;


	XMMATRIX* matProjection_;
	//ビュープロジェクション
	ViewProjection* viewProjection_;

	//オブジェクト
	Crystal* crystal;

	std::list<std::unique_ptr<Block>> blocks_;
	std::list<std::unique_ptr<Mirror>> mirrors_;

};
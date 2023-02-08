#pragma once
#include<vector>
#include<list>
#include<memory>
#include"Laser.h"
#include"Player.h"

#include"Block.h"
#include"Crystal.h"
#include"Sprite.h"
#include"LoadJson.h"

class Player;

class Map {
public:
	Map();
	~Map();

	void Initialize(ViewProjection* viewProjection, XMMATRIX* matProjection);

	void Reset(int  stage);

	void Update();

	void CheckCollionPlayer2Device();
	void controlRaser();

	void Draw();

	void Draw2D();

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
	bool IsHitRDevice() { return isHitRDevice; };

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
	//プレイヤーとレーザー装置が当たってる時のスプライト 
	Sprite* commandSpace = nullptr;
	bool isPlayer = false;
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

	bool isHitRDevice = false;
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


	//json読み込み
	LoadJson loadJson;

};
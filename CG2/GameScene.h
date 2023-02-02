#pragma once
#include "Input.h"
#include "DX12base.h"
#include"GameObject3D.h"
#include "WinApp.h"
#include "ViewProjection.h"

#include "Audio.h"
#include <xaudio2.h>
#pragma comment(lib,"xaudio2.lib")
#include "Sprite.h"

#include "Player.h"
#include "Particle.h"

#include"Map.h"

class GameScene {

public: // メンバ関数

	//コンストラクタ
	GameScene();

	/// デストラクタ
	~GameScene();

	//初期化
	void Initialize(WinApp* winApp);

	//毎フレーム処理
	void Update();

	//描画処理
	void Draw();

	void Reset();

private: // メンバ変数
	WinApp* winApp_ = nullptr;
	DX12base& dx12base_ = DX12base::GetInstance();
	Input& input_ = Input::GetInstance();
	XMMATRIX matProjection_ = {};
	SoundManager soundManager_;

	ViewProjection viewProjection_;

	enum class Scene
	{
		Title,
		Option,
		Select,
		Play,
		Clear,
		Gameover,
	};
	Scene scene;
	
	int button;
	bool isPause = false;
	
//-------
	Sprite* title_ = nullptr;
	Sprite* point_ = nullptr;
	Sprite* optionButton_ = nullptr;
	Sprite* stageButton_ = nullptr;
	Sprite* titleButtom_ = nullptr;
	Sprite* option_ = nullptr;
	Sprite* stageSelect_ = nullptr;
	Sprite* clear_ = nullptr;
	Sprite* gameOver_ = nullptr;
	Sprite* number_[10];
	Sprite* ESC_ = nullptr;
	Sprite* pause_ = nullptr;
	Sprite* back_ = nullptr;

//-------

	//プレイヤー
	Player* player_ = nullptr;
	WorldTransform playerWorldTransform;

	//マップ
	Map* map = nullptr;
	
};
#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Player.h"
#include "DebugCamera.h"
#include"RailCamera.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	std::unique_ptr<Model> model_ = nullptr;
	//ワールドトランスフォーム
	WorldTransform worldTransform_;
	//ビュープロジェクション
	ViewProjection viewProjection_;
	
	// 3Dモデル
	std::unique_ptr<Model> playerModel_ = nullptr;
	// 自キャラ
	std::unique_ptr<Player> player_;
	
	// デバックカメラ
	std::unique_ptr<DebugCamera> debugCamera_;
	int isDebugCameraActive_;

	// レールカメラをゲームシーンに持たせる
	RailCamera* railCamera_ = nullptr;
	Vector3 worldPos;
	Vector3 rotate;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};

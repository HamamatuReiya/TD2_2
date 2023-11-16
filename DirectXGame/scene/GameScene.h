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
#include "Enemy.h"
#include "DebugCamera.h"
#include "Ground.h"
#include "FollowCamera.h"
#include "Item.h"
#include "Object.h"
#include <Scene.h>

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


	// シーンのリセット
	void sceneReset();

	bool isSceneEnd = false;

	bool IsSceneEnd() { return isSceneEnd; }
	SceneType NextScene() { return SceneType::kTitle; }

	void Room();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	//ワールドトランスフォーム
	WorldTransform worldTransform_;
	//ビュープロジェクション
	ViewProjection viewProjection_;

	
	

private:
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	std::unique_ptr<Model> model_ = nullptr;

	// 3Dモデル
	std::unique_ptr<Model> playerModel_ = nullptr;
	// 自キャラ
	std::unique_ptr<Player> player_;


	//敵キャラの3Dモデル
	std::unique_ptr<Model> enemyModel_ = nullptr;
	//敵キャラ
	std::unique_ptr<Enemy> enemy_;


	// デバックカメラ
	std::unique_ptr<DebugCamera> debugCamera_;
	bool isDebugCameraActive_;

	// 3Dモデル
	std::unique_ptr<Model> groundModel_ = nullptr;
	// 地面
	std::unique_ptr<Ground> ground_;

	//追従カメラ
	std::unique_ptr<FollowCamera> followCamera_;

	// 3Dモデル
	std::unique_ptr<Model> KeyModel_ = nullptr;
	// 鍵
	std::unique_ptr<Item> Key_;

	// 3Dモデル
	std::unique_ptr<Model> RoomModel_R_00 = nullptr;
	// 部屋00
	std::unique_ptr<Object> Room_00_;

	// 3Dモデル
	std::unique_ptr<Model> RoomModel_R_01 = nullptr;
	// 部屋01
	std::unique_ptr<Object> Room_01_;

	// 3Dモデル
	std::unique_ptr<Model> RoomModel_R_02 = nullptr;
	// 部屋02
	std::unique_ptr<Object> Room_02_;

	// 3Dモデル
	std::unique_ptr<Model> RoomModel_R_03 = nullptr;
	// 部屋03
	std::unique_ptr<Object> Room_03_;

	// 3Dモデル
	std::unique_ptr<Model> RoomModel_R_04 = nullptr;
	// 部屋04
	std::unique_ptr<Object> Room_04_;

	// 3Dモデル
	std::unique_ptr<Model> RoomModel_R_05 = nullptr;
	// 部屋05
	std::unique_ptr<Object> Room_05_;

	// 3Dモデル
	std::unique_ptr<Model> RoomModel_R_06 = nullptr;
	// 部屋06
	std::unique_ptr<Object> Room_06_;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};

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

	/// <summary>
	/// 衝突判定と応答
	/// </summary>
	void CheakCollisions();

	// シーンのリセット
	void sceneReset();

	bool isSceneEnd = false;

	bool IsSceneEnd() { return isSceneEnd; }
	SceneType NextScene() { return SceneType::kTitle; }

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
	// 3Dモデル
	std::unique_ptr<Model> KeyUpModel_ = nullptr;
	// 3Dモデル
	std::unique_ptr<Model> KeyDownModel_ = nullptr;
	// 鍵
	std::unique_ptr<Item> Key_;

	// 3Dモデル
	std::unique_ptr<Model> RoomModel_R_00 = nullptr;
	// 部屋00
	std::unique_ptr<Object> Room_00_;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};

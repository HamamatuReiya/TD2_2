﻿#include "Model.h"
#include "WorldTransform.h"
#include <Input.h>
#include"ViewProjection.h"


class Player {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model);

	/// <summary>
	/// 自キャラ
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection& viewProjection);

	// ワールド座標を取得
	Vector3 GetWorldPosition();

	// コールバック関数
	void OnCollision();

	WorldTransform& GetWorldTransform() { return worldTransform_; };

	void SetViewProjection(const ViewProjection* viewProjection)
	{
		viewProjection_ = viewProjection;
	}

	//鍵に触れたかどうか
	bool isKeytouch() const { return isKeytouch_; }

	enum CollisionType {
		START, // スタート地点の部屋(0)
		LOAD00,// スタート地点から右の道(1)
		ROOM00,// 右上の部屋(2)
		ROOM01,// 右上の部屋の隣(3)
	};

	void SetType(int collisionType);

	int GetType();


private:
	WorldTransform worldTransform_;
	// ビュープロジェクション
	const ViewProjection*viewProjection_=nullptr;
	Model* model_ = nullptr;
	Input* input_ = nullptr;
	
	//部屋関数
	void StartRoomCollision();
	void Room00Collision();
	void Room01Collision();
	void Room02Collision();
	//道関数
	void Load00Collision();
	void Load01Collision();
	void Load02Collision();

	//回転スピード
	float kRotateSpeed;
	// 鍵に触れたかどうかフラグ
	bool isKeytouch_ = false;
	//スタミナ
	float StaminaTimer_ = 0;
	////スタミナクールタイム
	//float Cooltime_ = 0;
	
	CollisionType collisionType_;
};
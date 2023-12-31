﻿#include<time.h>
#include "Model.h"
#include "WorldTransform.h"
#include <Input.h>

class Key 
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* keyupModel, Model* keydownModel, Model* keymoldModel);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection& viewProjection);
	
	// コールバック関数
	void OnKeyCollision();
	// コールバック関数
	void OnKeyUpCollision();
	// コールバック関数
	void OnKeyDownCollision();

	// ワールド座標を取得
	Vector3 GetKeyWorldPosition(); 
	// ワールド座標を取得
	Vector3 GetKeyUpWorldPosition(); 
	// ワールド座標を取得
	Vector3 GetKeyDownWorldPosition(); 

private:
	//鍵用のランダム変数
	float Keynumber = 0;
	//デスフラグ
	bool isHummerDead_ = false;
	bool isKeyUpDead_ = false;
	bool isKeyDownDead_ = false;

private:
	WorldTransform worldTransform_[3];
	Model* keyupModel_ = nullptr;
	Model* keydownModel_ = nullptr;
	Model* hummerModel_ = nullptr;
	Input* input_ = nullptr;
	float RandTime_ = 0;
	
};

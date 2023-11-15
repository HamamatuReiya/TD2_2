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

	WorldTransform& GetWorldTransform() { return worldTransform_; };

	void SetViewProjection(const ViewProjection* viewProjection)
	{
		viewProjection_ = viewProjection;
	}

	//鍵に触れたかどうか
	bool isKeytouch() const { return isKeytouch_; }

private:
	WorldTransform worldTransform_;
	// ビュープロジェクション
	const ViewProjection*viewProjection_=nullptr;
	Model* model_ = nullptr;
	Input* input_ = nullptr;
	//回転スピード
	float kRotateSpeed;
	// 鍵に触れたかどうかフラグ
	bool isKeytouch_ = false;
	//ジャンプ

};
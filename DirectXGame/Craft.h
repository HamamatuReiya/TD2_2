#pragma once
#include "Model.h"
#include "WorldTransform.h"

class Craft {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection& viewProjection);
	// ワールド座標を取得
	Vector3 GetCraftWorldPosition();
	// コールバック関数
	void OnCraftCollision();

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
};

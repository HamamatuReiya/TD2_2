#include<time.h>
#include "Model.h"
#include "WorldTransform.h"
#include <Input.h>

class Item 
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
	void OnCollision();

	// ワールド座標を取得
	Vector3 GetWorldPosition();

	bool IsDead() const { return isKeyDead_; }

private:
	//鍵用のランダム変数
	float Keynumber = 0;
	//デスフラグ
	bool isKeyDead_ = false;

private:
	WorldTransform worldTransform_[3];
	Model* keyupModel_ = nullptr;
	Model* keydownModel_ = nullptr;
	Model* keymoldModel_ = nullptr;
	Input* input_ = nullptr;
	float RandTime_ = 0;
	
};

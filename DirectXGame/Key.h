#include<time.h>
#include "Model.h"
#include "WorldTransform.h"
#include <Input.h>
#include "Enemy.h"

class Enemy;

class Key 
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* keyupModel, Model* keydownModel, Model* keymoldModel);

	void RoopInitialize();

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

	float GetkeyNumber() { return Keynumber; }
	bool GetisHummerDead() { return isHummerDead_; }
	bool GetisKeyUpDead() { return isKeyUpDead_; }
	bool GetisDownDead() { return isKeyDownDead_; }

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

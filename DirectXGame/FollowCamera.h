#include"ViewProjection.h"
#include <WorldTransform.h>
#include <Input.h>

class FollowCamera 
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	void SetTarget(const WorldTransform* target) { target_ = target; };

	const ViewProjection&GetViewProjection() { return viewProjection_; };

private:
	// ビュープロジェクション
	ViewProjection viewProjection_;
	// ワールドトランスフォーム
	WorldTransform worldTransform_;
	//キーボード
	Input* input_ = nullptr;
	//回転
	float RotateSpeed_RL = 0.0f;
	float RotateSpeed_UD = 0.0f;

private:
	//追従対象
	const WorldTransform* target_ = nullptr;
};

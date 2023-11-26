#include "ViewProjection.h"
#include <Input.h>
#include <WorldTransform.h>

class EnemyFollowCamera {
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

	const ViewProjection& GetViewProjection() { return viewProjection_; };

private:
	// ビュープロジェクション
	ViewProjection viewProjection_;
	// ワールドトランスフォーム
	WorldTransform worldTransform_;
	// キーボード
	Input* input_ = nullptr;

private:
	// 追従対象
	const WorldTransform* target_ = nullptr;
};

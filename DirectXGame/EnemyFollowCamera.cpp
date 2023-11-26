#include "EnemyFollowCamera.h"
#include "ImGuiManager.h"
#include "Mymath.h"

void EnemyFollowCamera::Initialize() {
	// ワールドトランスフォーム
	worldTransform_.Initialize();
	// ビュープロジェクション
	viewProjection_.Initialize();

	input_ = Input::GetInstance();
}

void EnemyFollowCamera::Update() {
	Vector3 Rotate = {90, 0, 0};
	worldTransform_.rotation_ = Add(worldTransform_.rotation_, Rotate);

	if (target_) {
		// 追従対象からカメラまでのオフセット
		Vector3 offset = {0.0f, 2.5f, -6.0f};
		offset = TransformNormal(offset, MakeRotateYMatrix(viewProjection_.rotation_.y)); // 途中
		// 座標をコピーしてオフセット分ずらす
		viewProjection_.translation_ = Add(target_->translation_, offset);
	}
	// ビュー行列の更新と転送
	viewProjection_.UpdateMatrix();
}

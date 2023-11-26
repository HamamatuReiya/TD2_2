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
	viewProjection_.rotation_.y = -18.0f;
	viewProjection_.rotation_.z = -90.0f;

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

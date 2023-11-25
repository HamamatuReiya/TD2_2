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
	Vector3 Rotate = {0, 0, 0};
	worldTransform_.translation_ = Add(worldTransform_.translation_, Rotate);

	if (target_) {
		// 追従対象からカメラまでのオフセット
		Vector3 offset = {0.0f, 3.0f, -4.0f};
		offset = TransformNormal(offset, MakeRotateYMatrix(viewProjection_.rotation_.y)); // 途中
		// 座標をコピーしてオフセット分ずらす
		viewProjection_.translation_ = Add(target_->translation_, offset);
	}


	// ビュー行列の更新と転送
	viewProjection_.UpdateMatrix();
}

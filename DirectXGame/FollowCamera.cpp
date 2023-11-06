#include "FollowCamera.h"
#include"Mymath.h"

void FollowCamera::Initialize() 
{ 
	// ワールドトランスフォーム
	worldTransform_.Initialize();
	viewProjection_.Initialize();
	input_ = Input::GetInstance();
}

void FollowCamera::Update() 
{ 
	Vector3 Rotate = {0, 0, 0};
	worldTransform_.translation_ = Add(worldTransform_.translation_, Rotate);
	
	if (target_)
	{
		//追従対象からカメラまでのオフセット
		Vector3 offset = {0.0f, 0.0f, 10.0f};

		//座標をコピーしてオフセット分ずらす
		viewProjection_.translation_ = Add(target_->translation_, offset);
	}

	//回転
	RotateSpeed = 0.02f;
	if (input_->PushKey(DIK_A)) {
		viewProjection_.rotation_.y = viewProjection_.rotation_.y - RotateSpeed;
	}
	if (input_->PushKey(DIK_D)) {
		viewProjection_.rotation_.y = viewProjection_.rotation_.y + RotateSpeed;
	}
	
	////ビュー行列の更新と転送
	viewProjection_.UpdateMatrix();
}

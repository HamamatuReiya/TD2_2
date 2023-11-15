#include "FollowCamera.h"
#include"Mymath.h"
#include"ImGuiManager.h"

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
		Vector3 offset = {0.0f, -1.0f, 0.0f};
		offset = TransformNormal(offset,MakeRotateYMatrix(viewProjection_.rotation_.y));//途中
		//座標をコピーしてオフセット分ずらす
		viewProjection_.translation_ = Add(target_->translation_, offset);
	}

#pragma region プレイヤーのカメラ回転
	//回転
	RotateSpeed_RL = 0.05f;
	RotateSpeed_UD = 0.015f;
	

	if (input_->PushKey(DIK_LEFT)) {
		viewProjection_.rotation_.y = viewProjection_.rotation_.y - RotateSpeed_RL;
	}
	if (input_->PushKey(DIK_RIGHT)) {
		viewProjection_.rotation_.y = viewProjection_.rotation_.y + RotateSpeed_RL;
	}
	if (input_->PushKey(DIK_UP)) {
		viewProjection_.rotation_.x = viewProjection_.rotation_.x - RotateSpeed_UD;
	}
	if (input_->PushKey(DIK_DOWN)) {
		viewProjection_.rotation_.x = viewProjection_.rotation_.x + RotateSpeed_UD;
	}

	//上下回転制限
	if (viewProjection_.rotation_.x <= -0.3f){
		viewProjection_.rotation_.x = -0.3f;
	}
	if (viewProjection_.rotation_.x >= 0.5f) {
		viewProjection_.rotation_.x = 0.5f;
	}

#pragma endregion

	// デバック
	float RotateDebug[3] = {
	    viewProjection_.rotation_.x, viewProjection_.rotation_.y, viewProjection_.rotation_.z};

	// 画面の座標を表示
	ImGui::Begin("PlayerRotate");
	ImGui::SliderFloat3("PlayerRotate", RotateDebug, -28.0f, 28.0f);
	ImGui::Text("UP,DOWN,LEFT,RIGHT...CAMERA\n");
	ImGui::End();

	viewProjection_.rotation_.x = RotateDebug[0];
	viewProjection_.rotation_.y = RotateDebug[1];
	viewProjection_.rotation_.z = RotateDebug[2];


	
	
	//ビュー行列の更新と転送
	viewProjection_.UpdateMatrix();
}

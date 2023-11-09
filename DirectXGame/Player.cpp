#include "Player.h"
#include"Mymath.h"
#include"ImGuiManager.h"
#include <math.h>

void Player::Initialize(Model* model) {
	assert(model);
	model_ = model;
	input_ = Input::GetInstance();
	worldTransform_.Initialize();
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = {0.0f, 3.0f, 0.0f};
}

void Player::Update() {
	Vector3 move_ = {0, 0, 0};
	Vector3 rotate = {0, 0, 0};
	
	// 移動処理
	if (input_->PushKey(DIK_UP)) {
		move_ = {0.0f,0.0f,0.2f};
	} else if (input_->PushKey(DIK_DOWN)) {
		move_ = {0.0f, 0.0f, -0.2f};
	}
	if (input_->PushKey(DIK_RIGHT)) {
		move_ = {0.1f, 0.0f, 0.0f};
	} else if (input_->PushKey(DIK_LEFT)) {
		move_ = {-0.1f, 0.0f, 0.0f};
	}
	//Dash
	if (input_->PushKey(DIK_LSHIFT)&&input_->PushKey(DIK_UP)) {
		move_ = {0.0f, 0.0f, 0.4f};
	}

	
	// カメラの角度から回転行列を計算する
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(viewProjection_->rotation_.y);
	//カメラとリンク
	move_ = TransformNormal(move_, MakeRotateYMatrix(viewProjection_->rotation_.y));
	
	if (move_.z != 0 || move_.y != 0) {
		worldTransform_.rotation_.y = std::atan2(move_.x, move_.z);
	}

	worldTransform_.translation_ = Add(worldTransform_.translation_, move_);

	// 行列の更新
	worldTransform_.UpdateMatrix();

	

	//デバック
	float playerPos[3] = {
	    worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z};

	// 画面の座標を表示
	ImGui::Begin("Player");
	ImGui::SliderFloat3("playerPos", playerPos, -28.0f, 28.0f);
	ImGui::Text("AorD...CAMERA\nUP,DOWN,LEFT,RIGHT...MOVE\nShift...Dash\n");
	ImGui::End();

	worldTransform_.translation_.x = playerPos[0];
	worldTransform_.translation_.y = playerPos[1];
	worldTransform_.translation_.z = playerPos[2];
}

void Player::Draw(ViewProjection& viewProjection) 
{
	model_->Draw(worldTransform_, viewProjection); 
}

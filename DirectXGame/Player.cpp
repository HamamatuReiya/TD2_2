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
	if (input_->PushKey(DIK_W)) {
		move_ = {0.0f,0.0f,0.2f};
	} else if (input_->PushKey(DIK_S)) {
		move_ = {0.0f, 0.0f, -0.2f};
	}
	if (input_->PushKey(DIK_D)) {
		move_ = {0.1f, 0.0f, 0.0f};
	} else if (input_->PushKey(DIK_A)) {
		move_ = {-0.1f, 0.0f, 0.0f};
	}
	//Dash
	if (input_->PushKey(DIK_LSHIFT)&&input_->PushKey(DIK_W)) {
		StaminaTimer_++;
		if (StaminaTimer_ <= 120)
		{
		    move_ = {0.0f, 0.0f, 0.35f};
		}
	} else {
		StaminaTimer_ = 0;
	}

	RoomCollision();


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
	ImGui::Text("W,A,S,D...MOVE\nShift...Dash\n");
	ImGui::End();

	worldTransform_.translation_.x = playerPos[0];
	worldTransform_.translation_.y = playerPos[1];
	worldTransform_.translation_.z = playerPos[2];
}

void Player::Draw(ViewProjection& viewProjection) 
{
	model_->Draw(worldTransform_, viewProjection); 
}

void Player::RoomCollision() {
	for (int i = 0; i < 7; i++) {
		Room[i] = false;
	}
	if (worldTransform_.translation_.z <= 8.4f) {
		Room[0] = true;
	}
	if (Room[0] == true)
	//部屋0
	if (worldTransform_.translation_.x <=-8.6f) {//左
		worldTransform_.translation_.x = -8.6f;
	}
	if (worldTransform_.translation_.z <= -8.8f) {//下
		worldTransform_.translation_.z = -8.8f;
	}
	if (worldTransform_.translation_.x >= 8.6f) {//右
		worldTransform_.translation_.x = 8.6f;
	}
	if (worldTransform_.translation_.z >= 8.2f) {//上
		worldTransform_.translation_.z = 8.2f;
	}

	
}
Vector3 Player::GetWorldPosition() {
	Vector3 worldPos;

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Player::OnCollision() {}



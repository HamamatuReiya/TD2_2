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
	// 行列の更新
	worldTransform_.UpdateMatrix();
	Vector3 move = {0, 0, 0};
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);
	Vector3 rotate = {0, 0, 0};
	kCharacterSpeed = 0.08f;

	move = TransformNormal(move, &MakeRotateXMatrix());

	//移動処理
	if (input_->PushKey(DIK_UP)) {
		 worldTransform_.translation_.z = worldTransform_.translation_.z + kCharacterSpeed;
	} else if (input_->PushKey(DIK_DOWN)) {

		worldTransform_.translation_.z = worldTransform_.translation_.z - kCharacterSpeed;
	}


	//デバック
	float playerPos[3] = {
	    worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z};

	// 画面の座標を表示
	ImGui::Begin("Player");
	ImGui::SliderFloat3("playerPos", playerPos, -28.0f, 28.0f);
	ImGui::Text("A&D...CAMERA\nUP&DOWN&RIGHT&LEFT...MOVE\n");
	ImGui::End();

	worldTransform_.translation_.x = playerPos[0];
	worldTransform_.translation_.y = playerPos[1];
	worldTransform_.translation_.z = playerPos[2];
}

void Player::Draw(ViewProjection& viewProjection) 
{
	model_->Draw(worldTransform_, viewProjection); 
}

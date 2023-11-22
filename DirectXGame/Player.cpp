﻿#include "Player.h"
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
	worldTransform_.translation_ = {-6.0f, 3.0f, 40.0f};
	collisionType_ = START;
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

	//部屋の当たり判定の関数
	if (collisionType_==START){
		StartRoomCollision();
	} else if (collisionType_ == LOAD00) {
		Load00Collision();
	} else if (collisionType_ == ROOM00) {
		Room00Collision();
	} else if (collisionType_ == ROOM01) {
		Room01Collision();
	} else if (collisionType_ == ROOM02) {
		Room02Collision();
	} else if (collisionType_ == ROOM03) {
		Room03Collision();
	} else if (collisionType_ == ROOM04) {
		Room04Collision();
	} else if (collisionType_ == LOAD01) {
		Room04Collision();
	} else if (collisionType_ == LOAD03) {
		Load03Collision();
	} else if (collisionType_ == ROOM08) {
		Room08Collision();
	} else if (collisionType_ == LOAD05) {
		Load05Collision();
	} else if (collisionType_ == ROOM09) {
		Room09Collision();
	} else if (collisionType_ == ROOM10) {
		Room10Collision();
	} else if (collisionType_ == ROOM11) {
		Room11Collision();
	} else if (collisionType_ == ROOM12) {
		Room12Collision();
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
	ImGui::Text("W,A,S,D...MOVE\nShift...Dash\n");
	ImGui::End();

	worldTransform_.translation_.x = playerPos[0];
	worldTransform_.translation_.y = playerPos[1];
	worldTransform_.translation_.z = playerPos[2];

	// 画面の座標を表示
	ImGui::Begin("PLACE");
	ImGui::Text("%d\n",collisionType_);
	ImGui::End();
}

void Player::Draw(ViewProjection& viewProjection) 
{
	model_->Draw(worldTransform_, viewProjection); 
}

void Player::SetType(int collisionType) {
	collisionType_ = static_cast<CollisionType>(collisionType);
}

int Player::GetType() { return collisionType_; }

void Player::StartRoomCollision() {
	if (worldTransform_.translation_.z >= 29.368f && worldTransform_.translation_.z <= 34.357f &&
	    worldTransform_.translation_.x <= -8.705f) {  // 出口側の左壁 
		worldTransform_.translation_.x = -8.705f;
	}
	if (worldTransform_.translation_.z >= 45.669f && worldTransform_.translation_.z <= 49.463f &&
	    worldTransform_.translation_.x <= -8.705f) {  // 出口側の右壁
		worldTransform_.translation_.x = -8.705f;
	}
	if (worldTransform_.translation_.x >= -8.705f && worldTransform_.translation_.x <= -5.705f &&
	    worldTransform_.translation_.z >= 48.558f) {// 左の左壁
		worldTransform_.translation_.z = 48.558f;
	}
	if (worldTransform_.translation_.x >= -2.087f && worldTransform_.translation_.x <= 6.008f &&
	    worldTransform_.translation_.z >= 48.558f) {// 左の右壁
		worldTransform_.translation_.z = 48.558f;
	}
	if (worldTransform_.translation_.z <= 38.067f && worldTransform_.translation_.z >= 30.000f &&
	    worldTransform_.translation_.x >= 4.961f) { // 手前の左壁
		worldTransform_.translation_.x = 4.961f;
	}
	if (worldTransform_.translation_.z >= 41.721f && worldTransform_.translation_.z <= 49.463f &&
	    worldTransform_.translation_.x >= 4.961f) { // 手前の右壁
		worldTransform_.translation_.x = 4.961f;
	}
	if (worldTransform_.translation_.x >= -8.705f && worldTransform_.translation_.x <= -5.705f &&
	    worldTransform_.translation_.z <= 30.804f) { // 右の左壁
		worldTransform_.translation_.z = 30.804f;
	}
	if (worldTransform_.translation_.x >= -2.087f && worldTransform_.translation_.x <= 6.008f &&
	    worldTransform_.translation_.z <= 30.804f) { // 右の右壁
		worldTransform_.translation_.z = 30.804f;
	}

	//道00に移動
	if (worldTransform_.translation_.z < 29.859f) {
		collisionType_ = LOAD00;
	}

	// 道03に移動
	if (worldTransform_.translation_.z > 49.0f) {
		collisionType_ = LOAD03;
	}
}

void Player::Room00Collision() {
	// 部屋0
	if (worldTransform_.translation_.x <= -8.6f) { // 左
		worldTransform_.translation_.x = -8.6f;
	}
	if (worldTransform_.translation_.z <= -8.8f) { // 下
		worldTransform_.translation_.z = -8.8f;
	}
	if (worldTransform_.translation_.z >= -8.2f && worldTransform_.translation_.x <= -5.925f &&
	    worldTransform_.translation_.x <= 8.6f && worldTransform_.translation_.z >= 8.100f) { // 上左
		worldTransform_.translation_.z = 8.2f;
	}
	if (worldTransform_.translation_.z >= 8.2f && worldTransform_.translation_.x >= -2.652f &&
	    worldTransform_.translation_.x <= 9.2f && worldTransform_.translation_.z <= 9.082f) { // 上右 
		worldTransform_.translation_.z = 8.2f;
	}
	if (worldTransform_.translation_.x >= 8.737f && worldTransform_.translation_.z <= -1.888f) { // 左壁
		worldTransform_.translation_.x = 8.737f;
	}
	if (worldTransform_.translation_.x >= 8.737f && worldTransform_.translation_.z >= 1.190) { // 右壁
		worldTransform_.translation_.x = 8.737f;
	}
	// 道00に移動
	if (worldTransform_.translation_.z > 9.974f) {
		collisionType_ = LOAD00;
	}
	// 部屋01に移動
	if (worldTransform_.translation_.x > 10.209f) {
		collisionType_ = ROOM01;
	}
}

void Player::Room01Collision() {
	if (worldTransform_.translation_.z <= -8.8f) { // 下
		worldTransform_.translation_.z = -8.8f;
	}
	if (worldTransform_.translation_.x <= 10.926f &&
	    worldTransform_.translation_.z >= 1.592f) { // 左壁
		worldTransform_.translation_.x = 10.926f;
	}
	if (worldTransform_.translation_.x <= 10.926f &&
	    worldTransform_.translation_.z <= -1.511f) { // 右壁
		worldTransform_.translation_.x = 10.926f;
	}
	if (worldTransform_.translation_.z >= 8.128 && worldTransform_.translation_.x >= 10.926f &&
	    worldTransform_.translation_.x <= 22.411f) { // 
		worldTransform_.translation_.z = 8.128f;
	}
	if (worldTransform_.translation_.z >= 8.128f && worldTransform_.translation_.x >= 25.742f &&
	    worldTransform_.translation_.x <= 35.468f) { // 
		worldTransform_.translation_.z = 8.128f;
	}
	if (worldTransform_.translation_.z <= 10.328f && worldTransform_.translation_.z >= -6.171f &&
	    worldTransform_.translation_.x >= 32.468f) { // 奥壁
		worldTransform_.translation_.x = 32.468f;
	}
	// 部屋00に移動
	if (worldTransform_.translation_.x < 10.639f) {
		collisionType_ = ROOM00;
	}
	// 部屋02に移動
	if (worldTransform_.translation_.z > 10.162f) {
		collisionType_ = ROOM02;
	}
	// 部屋03に移動
	if (worldTransform_.translation_.x > 34.949f) {
		collisionType_ = ROOM03;
	}
}

void Player::Room02Collision() {
	if (worldTransform_.translation_.z <= 11.723f && worldTransform_.translation_.x >= 8.926f &&
	    worldTransform_.translation_.x <= 22.411f) { //
		worldTransform_.translation_.z = 11.723f;
	}
	if (worldTransform_.translation_.z <= 11.723 && worldTransform_.translation_.x >= 25.742f &&
	    worldTransform_.translation_.x <= 33.468f) { //
		worldTransform_.translation_.z = 11.723f;
	}
	if (worldTransform_.translation_.x <= 10.855f) { // 
		worldTransform_.translation_.x = 10.855f;
	}
	if (worldTransform_.translation_.z >= 25.025f) { //
		worldTransform_.translation_.z = 25.025f;
	}
	if (worldTransform_.translation_.z <= 26.0f && worldTransform_.translation_.z >= 21.633f &&
	    worldTransform_.translation_.x >= 32.392f) { // 手前の左壁
		worldTransform_.translation_.x = 32.392f;
	}
	if (worldTransform_.translation_.z >= 10.0f && worldTransform_.translation_.z <= 18.722f &&
	    worldTransform_.translation_.x >= 32.392f) { // 手前の右壁
		worldTransform_.translation_.x = 32.392f;
	}
	// 部屋01に移動
	if (worldTransform_.translation_.z < 10.162f) {
		collisionType_ = ROOM01;
	}
	// 部屋04に移動
	if (worldTransform_.translation_.x > 34.153f) {
		collisionType_ = ROOM04;
	}
}

void Player::Room03Collision() {
	if (worldTransform_.translation_.z <= -8.8f) { // 下
		worldTransform_.translation_.z = -8.8f;
	}
	if (worldTransform_.translation_.z >= -6.570f && worldTransform_.translation_.z <= -1.554f &&
	    worldTransform_.translation_.x <= 35.481f) { // ROOM01側の右壁
		worldTransform_.translation_.x = 35.481f;
	}
	if (worldTransform_.translation_.z >= -3.371f && worldTransform_.translation_.x >= 35.371f &&
	    worldTransform_.translation_.x <= 46.381f) { //　ROOM04側の左壁
		worldTransform_.translation_.z = -3.371f;
	}
	if (worldTransform_.translation_.z >= -3.371f && worldTransform_.translation_.x >= 49.533f &&
	    worldTransform_.translation_.x <= 58.0f) { // ROOM04側の右壁
		worldTransform_.translation_.z = -3.371f;
	}
	if (worldTransform_.translation_.x >= 56.526f) { // 奥側
		worldTransform_.translation_.x = 56.526f;
	}
	// 部屋01に移動
	if (worldTransform_.translation_.x < 34.949f) {
		collisionType_ = ROOM01;
	}
	// 部屋04に移動
	if (worldTransform_.translation_.z > -1.882f) {
		collisionType_ = ROOM04;
	}
}

void Player::Room04Collision() {
	if (worldTransform_.translation_.z <= 26.0f && worldTransform_.translation_.z >= 21.633f &&
	    worldTransform_.translation_.x <= 35.532f) { // ROOM02側の左壁
		worldTransform_.translation_.x = 35.532f;
	}
	if (worldTransform_.translation_.z >= -1.5f && worldTransform_.translation_.z <= 18.722f &&
	    worldTransform_.translation_.x <= 35.532f) { // ROOM02側の右壁
		worldTransform_.translation_.x = 35.532f;
	}
	if (worldTransform_.translation_.z <= -0.701f && worldTransform_.translation_.x >= 35.371f &&
	    worldTransform_.translation_.x <= 46.381f) { // ROOM03側の左壁
		worldTransform_.translation_.z = -0.701f;
	}
	if (worldTransform_.translation_.z <= -0.701f && worldTransform_.translation_.x >= 49.533f &&
	    worldTransform_.translation_.x <= 58.0f) { // ROOM03側の右壁
		worldTransform_.translation_.z = -0.701f;
	}
	if (worldTransform_.translation_.z >= -0.8f && worldTransform_.translation_.z <= 2.386f &&
	    worldTransform_.translation_.x >= 56.761f) { // Load2側の右壁
		worldTransform_.translation_.x = 56.761f;
	}
	if (worldTransform_.translation_.z <= 26.0f && worldTransform_.translation_.z >= 5.632f &&
	    worldTransform_.translation_.x >= 56.761f) { // Load2側の左壁
		worldTransform_.translation_.x = 56.761f;
	}
	if (worldTransform_.translation_.z >= 25.011f) { // 左壁
		worldTransform_.translation_.z = 25.011f;
	}
	// 部屋02に移動
	if (worldTransform_.translation_.x < 34.153f) {
		collisionType_ = ROOM02;
	}
	// 部屋03に移動
	if (worldTransform_.translation_.z < -1.882f) {
		collisionType_ = ROOM03;
	}
}

void Player::Room05Collision() {}

void Player::Room06Collision() {}

void Player::Room07Collision() {}

void Player::Room08Collision() {
	// 道03に移動
	if (worldTransform_.translation_.z < 62.0f) {
		collisionType_ = LOAD03;
	}
	if (worldTransform_.translation_.z <= 62.5f && worldTransform_.translation_.x>=-2.7f) { //
		worldTransform_.translation_.z = 62.5f;
	}
	if (worldTransform_.translation_.z >= 81.0f ) { //
		worldTransform_.translation_.z = 81.0f;
	}
	if (worldTransform_.translation_.x <= -5.0f) { // 左壁
		worldTransform_.translation_.x = -5.0f;
	}
	if (worldTransform_.translation_.x >= 13.53f && worldTransform_.translation_.z<=74.429f) { // 左壁
		worldTransform_.translation_.x = 13.53f;
	}
	if (worldTransform_.translation_.x >= 13.53f &&
	    worldTransform_.translation_.z >= 77.3f) { // 左壁
		worldTransform_.translation_.x = 13.53f;
	}
	if (worldTransform_.translation_.x > 13.8f) {
		collisionType_ = LOAD05;
	}
}

void Player::Room09Collision() {
	if (worldTransform_.translation_.x < 22.645f && worldTransform_.translation_.z <= 74.429f) {
		worldTransform_.translation_.x = 22.645f;
	}
	if (worldTransform_.translation_.x < 22.645f && worldTransform_.translation_.z >= 77.3f) {
		worldTransform_.translation_.x = 22.645f;
	}
	if (worldTransform_.translation_.z <= 66.5f) { //
		worldTransform_.translation_.z = 66.5f;
	}
	if (worldTransform_.translation_.z >= 85.0f) { //
		worldTransform_.translation_.z = 85.0f;
	}
	if (worldTransform_.translation_.x > 33.2f && worldTransform_.translation_.z <= 70.5f) {
		worldTransform_.translation_.x = 33.2f;
	}
	if (worldTransform_.translation_.x > 33.2f && worldTransform_.translation_.z >= 73.0f) {
		worldTransform_.translation_.x = 33.2f;
	}
	if (worldTransform_.translation_.x < 22.0f) {
		collisionType_ = LOAD05;
	}
	if (worldTransform_.translation_.x > 33.6f) {
		collisionType_ = ROOM10;
	}
}

void Player::Room10Collision() {
	if (worldTransform_.translation_.x < 33.6f) {
		collisionType_ = ROOM09;
	}
	if (worldTransform_.translation_.x > 33.2f &&
	    worldTransform_.translation_.x < 34.8f&&worldTransform_.translation_.z<=70.5f) {
		worldTransform_.translation_.z = 70.5f;
	}
	if (worldTransform_.translation_.x < 35.2f && worldTransform_.translation_.z <= 70.0f) {
		worldTransform_.translation_.x = 35.2f;
	}
	if (worldTransform_.translation_.x > 33.2f && worldTransform_.translation_.x < 34.8f &&
	    worldTransform_.translation_.z >= 73.0f) {
		worldTransform_.translation_.z = 73.0f;
	}
	if (worldTransform_.translation_.x < 35.2f && worldTransform_.translation_.z >= 73.5f) {
		worldTransform_.translation_.x = 35.2f;
	}
	if (worldTransform_.translation_.z <= 66.5f) { //
		worldTransform_.translation_.z = 66.5f;
	}
	if (worldTransform_.translation_.z >= 74.9f) { //
		worldTransform_.translation_.z = 74.9f;
	}
	if (worldTransform_.translation_.x > 49.4f && worldTransform_.translation_.x < 50.3f &&
	    worldTransform_.translation_.z <= 70.5f) {
		worldTransform_.translation_.z = 70.5f;
	}
	if (worldTransform_.translation_.x > 49.0f && worldTransform_.translation_.z <= 70.0f) {
		worldTransform_.translation_.x = 49.0f;
	}
	if (worldTransform_.translation_.x > 49.4f && worldTransform_.translation_.x < 50.3f &&
	    worldTransform_.translation_.z >= 73.0f) {
		worldTransform_.translation_.z = 73.0f;
	}
	if (worldTransform_.translation_.x > 49.0f && worldTransform_.translation_.z >= 73.5f) {
		worldTransform_.translation_.x = 49.0f;
	}
	if (worldTransform_.translation_.x >= 50.3) {
		collisionType_ = ROOM12;
	}
}

void Player::Room11Collision() {}

void Player::Room12Collision() {
	if (worldTransform_.translation_.x <= 50.3) {
		collisionType_ = ROOM10;
	}
}

void Player::Load00Collision() {
	if (worldTransform_.translation_.x >= -2.614f) { // 左壁
		worldTransform_.translation_.x = -2.614f;
	}
	if (worldTransform_.translation_.x <= -5.419f) { // 右壁
		worldTransform_.translation_.x = -5.419f;
	}

	// スタートの部屋に移動
	if (worldTransform_.translation_.z > 29.859f) {
		collisionType_ = START;
	}
	// 部屋00に移動
	if (worldTransform_.translation_.z < 9.974f) {
		collisionType_ = ROOM00;
	}
}

void Player::Load01Collision() {}

void Player::Load02Collision() {}

void Player::Load03Collision() {// 部屋00に移動
	// 道03に移動
	if (worldTransform_.translation_.z < 49.0f) {
		collisionType_ = START;
	}
	if (worldTransform_.translation_.x <= -5.0f) { // 左壁
		worldTransform_.translation_.x = -5.0f;
	}
	if (worldTransform_.translation_.x >= -2.7f) { // 右壁
		worldTransform_.translation_.x = -2.7f;
	}
	if (worldTransform_.translation_.z > 62.0f) {
		collisionType_ = ROOM08;
	}
}

void Player::Load04Collision() {}

void Player::Load05Collision() {
	if (worldTransform_.translation_.x < 13.8f) {
		collisionType_ = ROOM08;
	}
	if (worldTransform_.translation_.z <= 74.429f) {
		worldTransform_.translation_.z = 74.429f;
	}
	if (worldTransform_.translation_.z >= 77.3f) {
		worldTransform_.translation_.z = 77.3f;
	}
	if (worldTransform_.translation_.x >22.0f) {
		collisionType_ = ROOM09;
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




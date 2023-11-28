#include "Player.h"
#include "ImGuiManager.h"
#include "Mymath.h"
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
	isRun = true;
}

void Player::Update() {
	Vector3 move_ = {0, 0, 0};
	Vector3 rotate = {0, 0, 0};
	// 移動処理
	if (input_->PushKey(DIK_W)) {
		move_ = {0.0f, 0.0f, 0.2f};
	} else if (input_->PushKey(DIK_S)) {
		move_ = {0.0f, 0.0f, -0.2f};
	}
	if (input_->PushKey(DIK_D)) {
		move_ = {0.1f, 0.0f, 0.0f};
	} else if (input_->PushKey(DIK_A)) {
		move_ = {-0.1f, 0.0f, 0.0f};
	}
	// Dash
	if (input_->PushKey(DIK_LSHIFT) && input_->PushKey(DIK_W)) {
		if (isRun == true && stamina_ > 0) {
			stamina_--;
			move_ = {0.0f, 0.0f, 0.35f};
		}
	} else {
		stamina_ = 100;
	}
	

	// 部屋の当たり判定の関数
	if (collisionType_ == START) {
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
		Load01Collision();
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
	} else if (collisionType_ == ROOM15) {
		Room15Collision();
	} else if (collisionType_ == ROOM05) {
		Room05Collision();
	} else if (collisionType_ == LOAD04) {
		Load04Collision();
	} else if (collisionType_ == ROOM06) {
		Room06Collision();
	} else if (collisionType_ == ROOM07) {
		Room07Collision();
	} else if (collisionType_ == LOAD06) {
		Load06Collision();
	} else if (collisionType_ == LOAD02) {
		Load02Collision();
	}

	// カメラの角度から回転行列を計算する
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(viewProjection_->rotation_.y);
	// カメラとリンク
	move_ = TransformNormal(move_, MakeRotateYMatrix(viewProjection_->rotation_.y));

	if (move_.z != 0 || move_.y != 0) {
		worldTransform_.rotation_.y = std::atan2(move_.x, move_.z);
	}

	worldTransform_.translation_ = Add(worldTransform_.translation_, move_);

	// 行列の更新
	worldTransform_.UpdateMatrix();

	// デバック
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
	ImGui::Text("%d\n", collisionType_);
	ImGui::End();
}

void Player::Draw(ViewProjection& viewProjection) { model_->Draw(worldTransform_, viewProjection); }

void Player::SetType(int collisionType) {
	collisionType_ = static_cast<CollisionType>(collisionType);
}

int Player::GetType() { return collisionType_; }

void Player::StartRoomCollision() {
	if (worldTransform_.translation_.z >= 29.368f && worldTransform_.translation_.z <= 38.174f &&
	    worldTransform_.translation_.x <= -8.705f) { // 出口側の左壁
		worldTransform_.translation_.x = -8.705f;
	}
	if (worldTransform_.translation_.z >= 41.974f && worldTransform_.translation_.z <= 49.463f &&
	    worldTransform_.translation_.x <= -8.705f) { // 出口側の右壁
		worldTransform_.translation_.x = -8.705f;
	}
	if (worldTransform_.translation_.x >= -8.705f && worldTransform_.translation_.x <= -5.705f &&
	    worldTransform_.translation_.z >= 48.558f) { // 左の左壁
		worldTransform_.translation_.z = 48.558f;
	}
	if (worldTransform_.translation_.x >= -2.087f && worldTransform_.translation_.x <= 6.008f &&
	    worldTransform_.translation_.z >= 48.558f) { // 左の右壁
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

	// 道00に移動
	if (worldTransform_.translation_.z < 29.859f) {
		collisionType_ = LOAD00;
	}

	// 道03に移動
	if (worldTransform_.translation_.z > 49.0f) {
		collisionType_ = LOAD03;
	}
	//  Load2
	if (worldTransform_.translation_.x > 5.929f) {
		collisionType_ = LOAD02;
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
	    worldTransform_.translation_.x <= 8.6f &&
	    worldTransform_.translation_.z >= 8.100f) { // 上左
		worldTransform_.translation_.z = 8.2f;
	}
	if (worldTransform_.translation_.z >= 8.2f && worldTransform_.translation_.x >= -2.652f &&
	    worldTransform_.translation_.x <= 9.2f &&
	    worldTransform_.translation_.z <= 9.082f) { // 上右
		worldTransform_.translation_.z = 8.2f;
	}
	if (worldTransform_.translation_.x >= 8.737f &&
	    worldTransform_.translation_.z <= -1.888f) { // 左壁
		worldTransform_.translation_.x = 8.737f;
	}
	if (worldTransform_.translation_.x >= 8.737f &&
	    worldTransform_.translation_.z >= 1.190) { // 右壁
		worldTransform_.translation_.x = 8.737f;
	}
	

	// 道00に移動
	if (worldTransform_.translation_.z > 9.974f) {
		collisionType_ = LOAD00;
	}
	// 部屋01に移動
	if (worldTransform_.translation_.x > 9.2f) {
		collisionType_ = ROOM01;
	}
}

void Player::Room01Collision() {
	if (worldTransform_.translation_.z <= -8.8f) { // 下
		worldTransform_.translation_.z = -8.8f;
	}
	if (worldTransform_.translation_.x <= 11.3f &&
	    worldTransform_.translation_.z >= 2.0f) { // 左壁
		worldTransform_.translation_.x = 11.3f;
	}
	if (worldTransform_.translation_.x <= 10.8f &&
	    worldTransform_.translation_.z >= 1.592f) { // 左壁
		worldTransform_.translation_.z = 1.592f;
	}

	if (worldTransform_.translation_.x <= 11.3f &&
	    worldTransform_.translation_.z <= -2.0f) { // 右壁
		worldTransform_.translation_.x = 11.3f;
	}
	if (worldTransform_.translation_.x <= 10.8f &&
	    worldTransform_.translation_.z <= -1.511f) { // 右壁
		worldTransform_.translation_.z = -1.511f;
	}

	if (worldTransform_.translation_.z >= 8.5 && worldTransform_.translation_.x >= 10.926f &&
	    worldTransform_.translation_.x <= 21.9f) { //
		worldTransform_.translation_.z = 8.5f;
	}
	if (worldTransform_.translation_.z >= 9.0f && worldTransform_.translation_.x >= 10.926f &&
	    worldTransform_.translation_.x <= 22.411f) { //
		worldTransform_.translation_.x = 22.411f;
	}

	if (worldTransform_.translation_.z >= 8.5f && worldTransform_.translation_.x >= 26.242f &&
	    worldTransform_.translation_.x <= 35.468f) { //
		worldTransform_.translation_.z = 8.5f;
	}
	if (worldTransform_.translation_.z >= 9.0f && worldTransform_.translation_.x >= 25.742f &&
	    worldTransform_.translation_.x <= 35.468f) { //
		worldTransform_.translation_.x = 25.742f;
	}

	if (worldTransform_.translation_.z <= 10.328f && worldTransform_.translation_.z >= -6.171f &&
	    worldTransform_.translation_.x >= 32.5f) { // 奥壁
		worldTransform_.translation_.x = 32.5f;
	}
	// 部屋00に移動
	if (worldTransform_.translation_.x < 9.2f) {
		collisionType_ = ROOM00;
	}
	// 部屋02に移動
	if (worldTransform_.translation_.z > 11.2f) {
		collisionType_ = ROOM02;
	}
	// 部屋03に移動
	if (worldTransform_.translation_.x > 33.0f) {
		collisionType_ = ROOM03;
	}
}

void Player::Room02Collision() {
	if (worldTransform_.translation_.z <= 11.7f && worldTransform_.translation_.x >= 8.926f &&
	    worldTransform_.translation_.x <= 22.411f) { //
		worldTransform_.translation_.z = 11.7f;
	}
	if (worldTransform_.translation_.z <= 11.7 && worldTransform_.translation_.x >= 25.742f &&
	    worldTransform_.translation_.x <= 33.468f) { //
		worldTransform_.translation_.z = 11.7f;
	}
	if (worldTransform_.translation_.x <= 10.855f) { //
		worldTransform_.translation_.x = 10.855f;
	}
	if (worldTransform_.translation_.z >= 25.025f) { //
		worldTransform_.translation_.z = 25.025f;
	}

	if (worldTransform_.translation_.z <= 26.0f && worldTransform_.translation_.z >= 22.133f &&
	    worldTransform_.translation_.x >= 32.3f) { // 手前の左壁
		worldTransform_.translation_.x = 32.3f;
	}
	if (worldTransform_.translation_.z <= 26.0f && worldTransform_.translation_.z >= 21.633f &&
	    worldTransform_.translation_.x >= 32.8f) { // 手前の左壁
		worldTransform_.translation_.z = 21.633f;
	}

	if (worldTransform_.translation_.z >= 10.0f && worldTransform_.translation_.z <= 18.222f &&
	    worldTransform_.translation_.x >= 32.3f) { // 手前の右壁
		worldTransform_.translation_.x = 32.3f;
	}
	if (worldTransform_.translation_.z >= 10.0f && worldTransform_.translation_.z <= 18.722f &&
	    worldTransform_.translation_.x >= 32.8f) { // 手前の右壁
		worldTransform_.translation_.z = 18.722f;
	}

	// 部屋01に移動
	if (worldTransform_.translation_.z < 11.2f) {
		collisionType_ = ROOM01;
	}
	// 部屋04に移動
	if (worldTransform_.translation_.x > 34.5f) {
		collisionType_ = ROOM04;
	}
}

void Player::Room03Collision() {
	if (worldTransform_.translation_.z <= -8.8f) { // 下
		worldTransform_.translation_.z = -8.8f;
	}
	if (worldTransform_.translation_.z >= -6.070f && worldTransform_.translation_.z <= -1.554f &&
	    worldTransform_.translation_.x <= 35.5f) { // ROOM01側の右壁
		worldTransform_.translation_.x = 35.5f;
	}
	if (worldTransform_.translation_.z >= -6.570f && worldTransform_.translation_.z <= -1.554f &&
	    worldTransform_.translation_.x <= 35.0f) { // ROOM01側の右壁
		worldTransform_.translation_.z = -6.570f;
	}

	if (worldTransform_.translation_.z >= -3.0f && worldTransform_.translation_.x >= 35.371f &&
	    worldTransform_.translation_.x <= 45.881f) { // 　ROOM04側の左壁
		worldTransform_.translation_.z = -3.0f;
	}
	if (worldTransform_.translation_.z >= -2.5f && worldTransform_.translation_.x >= 35.371f &&
	    worldTransform_.translation_.x <= 46.381f) { // 　ROOM04側の左壁
		worldTransform_.translation_.x = 46.381f;
	}

	if (worldTransform_.translation_.z >= -3.0f && worldTransform_.translation_.x >= 50.033f &&
	    worldTransform_.translation_.x <= 58.0f) { // ROOM04側の右壁
		worldTransform_.translation_.z = -3.0f;
	}
	if (worldTransform_.translation_.z >= -2.5f && worldTransform_.translation_.x >= 49.533f &&
	    worldTransform_.translation_.x <= 58.0f) { // ROOM04側の右壁
		worldTransform_.translation_.x = 49.533f;
	}

	if (worldTransform_.translation_.x >= 56.526f) { // 奥側
		worldTransform_.translation_.x = 56.526f;
	}
	// 部屋01に移動
	if (worldTransform_.translation_.x < 33.0f) {
		collisionType_ = ROOM01;
	}
	// 部屋04に移動
	if (worldTransform_.translation_.z > -1.882f) {
		collisionType_ = ROOM04;
	}
}

void Player::Room04Collision() {
	if (worldTransform_.translation_.z <= 26.0f && worldTransform_.translation_.z >= 21.633f &&
	    worldTransform_.translation_.x <= 35.0f) { // ROOM02側の左壁
		worldTransform_.translation_.x = 35.0f;
	}
	if (worldTransform_.translation_.z >= -1.5f && worldTransform_.translation_.z <= 18.722f &&
	    worldTransform_.translation_.x <= 35.0f) { // ROOM02側の右壁
		worldTransform_.translation_.x = 35.0f;
	}
	if (worldTransform_.translation_.z <= -0.7f && worldTransform_.translation_.x >= 35.371f &&
	    worldTransform_.translation_.x <= 46.381f) { // ROOM03側の左壁
		worldTransform_.translation_.z = -0.7f;
	}
	if (worldTransform_.translation_.z <= -0.7f && worldTransform_.translation_.x >= 49.533f &&
	    worldTransform_.translation_.x <= 58.0f) { // ROOM03側の右壁
		worldTransform_.translation_.z = -0.7f;
	}
	if (worldTransform_.translation_.z >= -0.8f && worldTransform_.translation_.z <= 2.386f &&
	    worldTransform_.translation_.x >= 56.761f) { // Load1側の右壁
		worldTransform_.translation_.x = 56.761f;
	}
	if (worldTransform_.translation_.z <= 26.0f && worldTransform_.translation_.z >= 5.520f &&
	    worldTransform_.translation_.x >= 56.761f) { // Load1側の左壁
		worldTransform_.translation_.x = 56.761f;
	}
	if (worldTransform_.translation_.z >= 25.011f) { // 左壁
		worldTransform_.translation_.z = 25.011f;
	}
	// 部屋02に移動
	if (worldTransform_.translation_.x < 34.5f) {
		collisionType_ = ROOM02;
	}
	// Load1に移動
	if (worldTransform_.translation_.x > 57.874f) {
		collisionType_ = LOAD01;
	}
	// 部屋03に移動
	if (worldTransform_.translation_.z < -1.2f) {
		collisionType_ = ROOM03;
	}
	// 道1に移動
	if (worldTransform_.translation_.x > 58.028f) {
		collisionType_ = LOAD01;
	}
}

void Player::Room05Collision() {
	if (worldTransform_.translation_.z <= 47.227f && worldTransform_.translation_.x >= 73.744f &&
	    worldTransform_.translation_.x <= 84.746f) { // LOAD1側左壁
		worldTransform_.translation_.z = 47.227f;
	}
	if (worldTransform_.translation_.z >= 49.183f) { // 右壁
		worldTransform_.translation_.z = 49.183f;
	}
	if (worldTransform_.translation_.z <= 30.951f) { // 左壁
		worldTransform_.translation_.z = 30.951f;
	}
	if (worldTransform_.translation_.z >= 41.527f && worldTransform_.translation_.z <= 50.0f &&
	    worldTransform_.translation_.x <= 58.714f) { // LOAD4側右壁
		worldTransform_.translation_.x = 58.714f;
	}
	if (worldTransform_.translation_.z <= 38.422f && worldTransform_.translation_.z >= 30.0f &&
	    worldTransform_.translation_.x <= 58.714f) { // LOAD4側左壁
		worldTransform_.translation_.x = 58.714f;
	}
	if (worldTransform_.translation_.z <= 46.267f && worldTransform_.translation_.z >= 30.0f &&
	    worldTransform_.translation_.x >= 73.394f) { // 後ろ壁
		worldTransform_.translation_.x = 73.394f;
	}

	// 部屋05への道
	if (worldTransform_.translation_.z >= 46.065f && worldTransform_.translation_.z <= 49.960f &&
	    worldTransform_.translation_.x >= 82.994f) {
		collisionType_ = LOAD01;
	}
	// LOAD04への道
	if (worldTransform_.translation_.x < 58.122f) {
		collisionType_ = LOAD04;
	}
}

void Player::Room06Collision() {
	if (worldTransform_.translation_.z >= 33.624f && worldTransform_.translation_.x >= 37.485f &&
	    worldTransform_.translation_.z <= 60.0f) { // したかべ
		worldTransform_.translation_.x = 37.485f;
	}

	if (worldTransform_.translation_.z <= 53.988f && worldTransform_.translation_.z >= 29.0f &&
	    worldTransform_.translation_.x <= 29.5f) { // 
		worldTransform_.translation_.x = 29.5f;
	}
	if (worldTransform_.translation_.z <= 54.488f && worldTransform_.translation_.z >= 29.0f &&
	    worldTransform_.translation_.x <= 29.0f) { //
		worldTransform_.translation_.z = 54.488f;
	} 

	if (worldTransform_.translation_.z >= 57.219f) { //
		worldTransform_.translation_.z = 57.219f;
	}
	if (worldTransform_.translation_.z <= 30.528f) {
		worldTransform_.translation_.z = 30.528f;
	}
	// 部屋07
	if (worldTransform_.translation_.x < 27.9f) {
		collisionType_ = ROOM07;
	}
	// Load06
	if (worldTransform_.translation_.x > 37.921f) {
		collisionType_ = LOAD06;
	}
}

void Player::Room07Collision() {
	if (worldTransform_.translation_.z <= 54.488f && worldTransform_.translation_.z >= 29.0f &&
	    worldTransform_.translation_.x >= 27.4f) { // 
		worldTransform_.translation_.x = 27.4f;
	}
	if (worldTransform_.translation_.z <= 58.0f && worldTransform_.translation_.z >= 41.634f &&
	    worldTransform_.translation_.x <= 18.830f) { // 
		worldTransform_.translation_.x = 18.830f;
	}
	if (worldTransform_.translation_.z <= 38.229f && worldTransform_.translation_.z >= 29.5f &&
	    worldTransform_.translation_.x <= 18.830f) { //
		worldTransform_.translation_.x = 18.830f;
	}
	if (worldTransform_.translation_.z <= 30.528f) {
		worldTransform_.translation_.z = 30.528f;
	}
	if (worldTransform_.translation_.z >= 57.219f) { 
		worldTransform_.translation_.z = 57.219f;
	}
	//  Load2
	if (worldTransform_.translation_.x < 17.968f) {
		collisionType_ = LOAD02;
	}
	//  部屋07
	if (worldTransform_.translation_.x > 27.9f) {
		collisionType_ = ROOM06;
	}
}

void Player::Room08Collision() {
	// 道03に移動
	if (worldTransform_.translation_.z < 62.0f) {
		collisionType_ = LOAD03;
	}
	if (worldTransform_.translation_.z <= 62.5f && worldTransform_.translation_.x >= -2.7f) { //
		worldTransform_.translation_.z = 62.5f;
	}
	if (worldTransform_.translation_.z >= 81.0f) { //
		worldTransform_.translation_.z = 81.0f;
	}
	if (worldTransform_.translation_.x <= -5.0f) { // 左壁
		worldTransform_.translation_.x = -5.0f;
	}
	if (worldTransform_.translation_.x >= 13.53f && worldTransform_.translation_.z<=75.0f) { // 左壁
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
	if (worldTransform_.translation_.x < 22.645f && worldTransform_.translation_.z <= 75.0f) {
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
	// ルーム9側の上の敷居
	if (worldTransform_.translation_.x > 33.2f && worldTransform_.translation_.x < 34.8f &&
	    worldTransform_.translation_.z <= 70.5f) {
		worldTransform_.translation_.z = 70.5f;
	}
	////
	if (worldTransform_.translation_.x < 35.2f && worldTransform_.translation_.z <= 70.0f) {
		worldTransform_.translation_.x = 35.2f;
	}
	// ルーム9側の下の敷居
	if (worldTransform_.translation_.x > 33.2f && worldTransform_.translation_.x < 34.8f &&
	    worldTransform_.translation_.z >= 73.0f) {
		worldTransform_.translation_.z = 73.0f;
	}
	////
	if (worldTransform_.translation_.x < 35.2f && worldTransform_.translation_.z >= 73.5f) {
		worldTransform_.translation_.x = 35.2f;
	}
	if (worldTransform_.translation_.z <= 66.5f) { //
		worldTransform_.translation_.z = 66.5f;
	}
	if (worldTransform_.translation_.z >= 74.9f) { //
		worldTransform_.translation_.z = 74.9f;
	}
	// ルーム12側の上の敷居
	if (worldTransform_.translation_.x > 49.4f && worldTransform_.translation_.x < 50.3f &&
	    worldTransform_.translation_.z <= 70.5f) {
		worldTransform_.translation_.z = 70.5f;
	}
	////
	if (worldTransform_.translation_.x > 49.0f && worldTransform_.translation_.z <= 70.0f) {
		worldTransform_.translation_.x = 49.0f;
	}
	// ルーム12側の下の敷居
	if (worldTransform_.translation_.x > 49.4f && worldTransform_.translation_.x < 50.3f &&
	    worldTransform_.translation_.z >= 73.0f) {
		worldTransform_.translation_.z = 73.0f;
	}
	////
	if (worldTransform_.translation_.x > 49.0f && worldTransform_.translation_.z >= 73.5f) {
		worldTransform_.translation_.x = 49.0f;
	}
	if (worldTransform_.translation_.x >= 50.3) {
		collisionType_ = ROOM12;
	}
}

void Player::Room11Collision() {
	if (worldTransform_.translation_.x >= 50.3 && worldTransform_.translation_.z >= 75.9f &&
	    worldTransform_.translation_.z <= 85.0f) {
		collisionType_ = ROOM12;
	}
	if (worldTransform_.translation_.z <= 77.0f) { //
		worldTransform_.translation_.z = 77.0f;
	}
	if (worldTransform_.translation_.z >= 85.0f) { //
		worldTransform_.translation_.z = 85.0f;
	}
	// ルーム12側の上の敷居
	if (worldTransform_.translation_.x > 49.4f && worldTransform_.translation_.x < 50.3f &&
	    worldTransform_.translation_.z <= 78.8f) {
		worldTransform_.translation_.z = 78.8f;
	}
	////
	if (worldTransform_.translation_.x > 49.0f && worldTransform_.translation_.z <= 78.3f) {
		worldTransform_.translation_.x = 49.0f;
	}
	// ルーム12側の下の敷居
	if (worldTransform_.translation_.x > 49.4f && worldTransform_.translation_.x < 50.3f &&
	    worldTransform_.translation_.z >= 81.5f) {
		worldTransform_.translation_.z = 81.5f;
	}
	////
	if (worldTransform_.translation_.x > 49.0f && worldTransform_.translation_.z >= 82.0f) {
		worldTransform_.translation_.x = 49.0f;
	}

	if (worldTransform_.translation_.x <= 35.0f) {
		worldTransform_.translation_.x = 35.0f;
	}
}

void Player::Room12Collision() {
	if (worldTransform_.translation_.x <= 50.3 && worldTransform_.translation_.z >= 66.5f &&
	    worldTransform_.translation_.z <= 74.9f) {
		collisionType_ = ROOM10;
	}
	if (worldTransform_.translation_.x <= 50.7f && worldTransform_.translation_.z <= 70.5f) {
		worldTransform_.translation_.x = 50.7f;
	}
	if (worldTransform_.translation_.x <= 50.7f && worldTransform_.translation_.z >= 73.0f &&
	    worldTransform_.translation_.z <= 78.8f) {
		worldTransform_.translation_.x = 50.7f;
	}
	if (worldTransform_.translation_.x <= 50.7f && worldTransform_.translation_.z >= 81.5f) {
		worldTransform_.translation_.x = 50.7f;
	}

	if (worldTransform_.translation_.z <= 66.5f) { //
		worldTransform_.translation_.z = 66.5f;
	}
	if (worldTransform_.translation_.z >= 85.0f) { //
		worldTransform_.translation_.z = 85.0f;
	}

	
	//道の左壁
	if (worldTransform_.translation_.x >= 57.4f && worldTransform_.translation_.z >= 77.0f) { //
		worldTransform_.translation_.z = 77.0f;
	}
	// 道の右壁
	if (worldTransform_.translation_.x >= 57.4f && worldTransform_.translation_.x <= 82.5f &&
	    worldTransform_.translation_.z <= 74.6f) { //
		worldTransform_.translation_.z = 74.6f;
	}
	if (worldTransform_.translation_.x >= 57.0f && worldTransform_.translation_.x <= 57.5f &&
	    worldTransform_.translation_.z >= 77.4f) { //
		worldTransform_.translation_.x = 57.0f;
	}
	if (worldTransform_.translation_.x >= 57.0f && worldTransform_.translation_.x <= 57.5f &&
	    worldTransform_.translation_.z <= 74.2f) { //
		worldTransform_.translation_.x = 57.0f;
	}

	if (worldTransform_.translation_.x <= 50.3 && worldTransform_.translation_.z >= 75.9f &&
	    worldTransform_.translation_.z <= 85.0f) {
		collisionType_ = ROOM11;
	}

	if (worldTransform_.translation_.x > 82.746f && worldTransform_.translation_.z <= 77.0f &&
	    worldTransform_.translation_.z >= 74.0f) {
		collisionType_ = LOAD01;
	}


	if (worldTransform_.translation_.x > 82.5f && worldTransform_.translation_.z <= 77.0f &&
	    worldTransform_.translation_.z >= 74.0f) {
		collisionType_ = LOAD01;
	}
}

void Player::Room15Collision() {
	if (worldTransform_.translation_.z >= -2.499f && worldTransform_.translation_.z <= 2.890f &&
	    worldTransform_.translation_.x >= 80.998f) { // 一番奥壁
		worldTransform_.translation_.x = 80.998f;
	}
	if (worldTransform_.translation_.z >= -3.230f && worldTransform_.translation_.x >= 81.872f &&
	    worldTransform_.translation_.x <= 86.0f) { // 一番奥壁裏
		worldTransform_.translation_.z = -3.230f;
	}
	if (worldTransform_.translation_.z >= -2.499f && worldTransform_.translation_.z <= 2.890f &&
	    worldTransform_.translation_.x <= 78.832f &&
	    worldTransform_.translation_.x >= 73.0f) { // 真ん中壁
		worldTransform_.translation_.x = 78.832f;
	}
	if (worldTransform_.translation_.z >= -3.230f && worldTransform_.translation_.x >= 69.788f &&
	    worldTransform_.translation_.x <= 78.288f) { // 真ん中壁裏
		worldTransform_.translation_.z = -3.230f;
	}
	if (worldTransform_.translation_.z >= -2.499f && worldTransform_.translation_.z <= 2.890f &&
	    worldTransform_.translation_.x >= 69.423f && worldTransform_.translation_.x <= 73.0f) { //
		worldTransform_.translation_.x = 69.423f;
	}
	if (worldTransform_.translation_.z >= -2.499f && worldTransform_.translation_.z <= 2.890f &&
	    worldTransform_.translation_.x <= 66.858f) { // 手前壁
		worldTransform_.translation_.x = 66.858f;
	}
	if (worldTransform_.translation_.z >= -3.230f && worldTransform_.translation_.x <= 66.298f &&
	    worldTransform_.translation_.x >= 61.662f) { // 手前壁裏
		worldTransform_.translation_.z = -3.230f;
	}
	if (worldTransform_.translation_.x >= 85.513f) { // 右壁
		worldTransform_.translation_.x = 85.513f;
	}
	if (worldTransform_.translation_.x <= 62.771f) { // 左壁
		worldTransform_.translation_.x = 62.771f;
	}
	if (worldTransform_.translation_.z <= -13.23f) { // 下壁
		worldTransform_.translation_.z = -13.23f;
	}

	// 部屋Load01に移動
	if (worldTransform_.translation_.z > 2.647f) {
		collisionType_ = LOAD01;
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

void Player::Load01Collision() {
	if (worldTransform_.translation_.z >= 4.781f && worldTransform_.translation_.x >= 57.874f &&
	    worldTransform_.translation_.x <= 82.295f) { // 左壁
		worldTransform_.translation_.z = 4.781f;
	}
	if (worldTransform_.translation_.z <= 3.010f && worldTransform_.translation_.x >= 57.874f &&
	    worldTransform_.translation_.x <= 66.410f) { // 右壁1
		worldTransform_.translation_.z = 3.010f;
	}
	if (worldTransform_.translation_.z <= 3.010f && worldTransform_.translation_.x >= 69.795f &&
	    worldTransform_.translation_.x <= 78.225f) { // 右壁2
		worldTransform_.translation_.z = 3.010f;
	}
	if (worldTransform_.translation_.z <= 3.010f && worldTransform_.translation_.x >= 81.872f &&
	    worldTransform_.translation_.x <= 86.0f) { // 右壁3
		worldTransform_.translation_.z = 3.010f;
	}
	if (worldTransform_.translation_.z >= 5.813f && worldTransform_.translation_.z <= 46.173f &&
	    worldTransform_.translation_.x <= 82.746f) { // 左曲がった左壁1
		worldTransform_.translation_.x = 82.746f;
	}
	if (worldTransform_.translation_.z >= 49.719f && worldTransform_.translation_.z <= 74.608f &&
	    worldTransform_.translation_.x <= 82.746f) { // 左曲がった左壁2
		worldTransform_.translation_.x = 82.746f;
	}
	if (worldTransform_.translation_.x >= 85.513f) { // 左曲がった右壁
		worldTransform_.translation_.x = 85.513f;
	}
	if (worldTransform_.translation_.z >= 77.0f) { // 
		worldTransform_.translation_.z = 77.0f;
	}
	// 部屋4に移動
	if (worldTransform_.translation_.x < 57.874f) {
		collisionType_ = ROOM04;
	}
	// 部屋15に移動
	if (worldTransform_.translation_.z < 2.647f) {
		collisionType_ = ROOM15;
	}
	//部屋05に移動
	if (worldTransform_.translation_.x < 82.746f && worldTransform_.translation_.z >= 46.173f &&
	    worldTransform_.translation_.z <= 49.719f) { 
		collisionType_ = ROOM05;
	}
	// 部屋12に移動
	if (worldTransform_.translation_.x < 82.5f && worldTransform_.translation_.z <= 77.0f &&
	    worldTransform_.translation_.z >= 74.0f) {
		collisionType_ = ROOM12;
	}
}

void Player::Load02Collision() {
	if (worldTransform_.translation_.z >= 41.266f && worldTransform_.translation_.x >= 6.000f &&
	    worldTransform_.translation_.x <= 18.144f) { // 
		worldTransform_.translation_.z = 41.266f;
	}
	if (worldTransform_.translation_.z <= 38.485f && worldTransform_.translation_.x >= 6.000f &&
	    worldTransform_.translation_.x <= 18.144f) { //
		worldTransform_.translation_.z = 38.485f;
	}
	//  部屋07
	if (worldTransform_.translation_.x > 17.968f) {
		collisionType_ = ROOM07;
	}
	//  スタート地点へ
	if (worldTransform_.translation_.x < 5.929f) {
		collisionType_ = START;
	}
}

void Player::Load03Collision() { // 部屋00に移動
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

void Player::Load04Collision() {
	// 部屋05から左への道
	if (worldTransform_.translation_.x <= 58.122f && worldTransform_.translation_.x >= 53.778f&&
	    worldTransform_.translation_.z <= 39.044f) {
		worldTransform_.translation_.z = 39.044f;
	}
	// 
	if (worldTransform_.translation_.z <= 45.0f && worldTransform_.translation_.z >= 33.75f &&
	    worldTransform_.translation_.x <= 50.792f) {
		worldTransform_.translation_.x = 50.792f;
	}
	if (worldTransform_.translation_.z >= 29.0f && worldTransform_.translation_.z <= 38.329f &&
	    worldTransform_.translation_.x >= 53.324f) {
		worldTransform_.translation_.x = 53.324f;
	}
	if (worldTransform_.translation_.z <= 30.528f) {
		worldTransform_.translation_.z = 30.528f;
	}
	// 右壁
	if (worldTransform_.translation_.z >= 41.241f) {
		worldTransform_.translation_.z = 41.241f;
	}
	// 部屋05への道
	if (worldTransform_.translation_.x > 58.122f) {
		collisionType_ = ROOM05;
	}
	// 道06
	if (worldTransform_.translation_.x < 50.461f) {
		collisionType_ = LOAD06;
	}
}

void Player::Load05Collision() {
	if (worldTransform_.translation_.x < 13.8f) {
		collisionType_ = ROOM08;
	}
	if (worldTransform_.translation_.z <= 75.0f) {
		worldTransform_.translation_.z = 75.0f;
	}
	if (worldTransform_.translation_.z >= 77.3f) {
		worldTransform_.translation_.z = 77.3f;
	}
	if (worldTransform_.translation_.x > 22.0f) {
		collisionType_ = ROOM09;
	}
}

void Player::Load06Collision() {
	//左壁
	if (worldTransform_.translation_.z <= 30.528f) {
		worldTransform_.translation_.z = 30.528f;
	}
	if (worldTransform_.translation_.x <= 50.378f && worldTransform_.translation_.x >= 37.378f &&
	    worldTransform_.translation_.z >= 33.137f) {
		worldTransform_.translation_.z = 33.137f;
	}
	// 道04へ
	if (worldTransform_.translation_.x > 50.461f) {
		collisionType_ = LOAD04;
	}
	// 部屋06
	if (worldTransform_.translation_.x < 37.921f) {
		collisionType_ = ROOM06;
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

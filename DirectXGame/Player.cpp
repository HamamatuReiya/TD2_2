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
	    worldTransform_.translation_.x >= 5.623f) { // 手前の左壁
		worldTransform_.translation_.x = 5.623f;
	}
	if (worldTransform_.translation_.z >= 41.721f && worldTransform_.translation_.z <= 49.463f &&
	    worldTransform_.translation_.x >= 5.623f) { // 手前の右壁
		worldTransform_.translation_.x = 5.623f;
	}
	if (worldTransform_.translation_.x >= -8.705f && worldTransform_.translation_.x <= -5.705f &&
	    worldTransform_.translation_.z <= 30.338f) { // 右の左壁
		worldTransform_.translation_.z = 30.338f;
	}
	if (worldTransform_.translation_.x >= -2.087f && worldTransform_.translation_.x <= 6.008f &&
	    worldTransform_.translation_.z <= 30.338f) { // 右の右壁
		worldTransform_.translation_.z = 30.338f;
	}

	//道00に移動
	if (worldTransform_.translation_.z < 29.859f) {
		collisionType_ = LOAD00;
	}
}

void Player::Load00Collision() {
	if (worldTransform_.translation_.x >= -2.419f) { // 左壁
		worldTransform_.translation_.x = -2.419f;
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
	if (worldTransform_.translation_.z <= 11.723f && worldTransform_.translation_.x >= 10.926f &&
	    worldTransform_.translation_.x <= 22.411f) { //
		worldTransform_.translation_.z = 11.723f;
	}
	if (worldTransform_.translation_.z <= 11.723 && worldTransform_.translation_.x >= 25.742f &&
	    worldTransform_.translation_.x <= 33.468f) { //
		worldTransform_.translation_.z = 11.723f;
	}


	// 部屋01に移動
	if (worldTransform_.translation_.z < 10.162f) {
		collisionType_ = ROOM01;
	}
}

void Player::Room03Collision() {
	// 部屋01に移動
	if (worldTransform_.translation_.x < 34.949f) {
		collisionType_ = ROOM01;
	}
}

void Player::Load01Collision() {}

void Player::Load02Collision() {}



Vector3 Player::GetWorldPosition() {
	Vector3 worldPos;

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Player::OnCollision() {}




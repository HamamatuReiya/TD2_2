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
	} else if (collisionType_ == ROOM04) {
		Room04Collision();
	} else if (collisionType_ == LOAD01) {
		Load01Collision();
	} else if (collisionType_ == ROOM15) {
		Room15Collision();
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
	    worldTransform_.translation_.x >= 56.761f) { // Load1側の右壁
		worldTransform_.translation_.x = 56.761f;
	}
	if (worldTransform_.translation_.z <= 26.0f && worldTransform_.translation_.z >= 5.632f &&
	    worldTransform_.translation_.x >= 56.761f) { // Load1側の左壁
		worldTransform_.translation_.x = 56.761f;
	}
	if (worldTransform_.translation_.z >= 25.011f) { // 左壁
		worldTransform_.translation_.z = 25.011f;
	}
	// 部屋02に移動
	if (worldTransform_.translation_.x < 34.153f) {
		collisionType_ = ROOM02;
	}
	// Load1に移動
	if (worldTransform_.translation_.x > 57.874f) {
		collisionType_ = LOAD01;
	}
	// 部屋03に移動
	if (worldTransform_.translation_.z < -1.798f) {
		collisionType_ = ROOM03;
	}
}

void Player::Room05Collision() {}

void Player::Room06Collision() {}

void Player::Room07Collision() {}

void Player::Room08Collision() {}

void Player::Room09Collision() {}

void Player::Room10Collision() {}

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
	if (worldTransform_.translation_.z >= -2.499f && worldTransform_.translation_.z <= 2.890f &&
	    worldTransform_.translation_.x >= 69.022f) { // 真ん中壁裏
		worldTransform_.translation_.x = 69.022f;
	}
	if (worldTransform_.translation_.z >= -3.230f && worldTransform_.translation_.x >= 69.395f &&
	    worldTransform_.translation_.x <= 78.068f) { //// 真ん中壁裏
		worldTransform_.translation_.z = -3.230f;
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
	if (worldTransform_.translation_.z >= 77.421f) { // 
		worldTransform_.translation_.z = 77.421f;
	}
	// 部屋4に移動
	if (worldTransform_.translation_.x < 57.874f) {
		collisionType_ = ROOM04;
	}
	// 部屋15に移動
	if (worldTransform_.translation_.z < 2.647f) {
		collisionType_ = ROOM15;
	}
	
}

void Player::Load02Collision() {}



Vector3 Player::GetWorldPosition() {
	Vector3 worldPos;

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Player::OnCollision() {}




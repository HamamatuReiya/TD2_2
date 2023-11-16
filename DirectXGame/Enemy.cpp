#include "Enemy.h"
#include"ImGuiManager.h"
#include "Player.h"

void Enemy::Initialize(Model* model) {
	model_ = model;
	worldTransform_.Initialize();
	move_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.rotation_ = {0.0f, -1.6f, 0.0f};
	worldTransform_.translation_ = {52.0f, 0.7f, 19.5f};
	encountFlag = false;
	kEnemySpeed_ = 0.0f;
	rotateSpeed_ = 0.05f;
	phase_ = phase1;
	phase1State = search;
	phase2State = search;
	phase3State = search;
	phase1Move = move1;
	flag = false;
}

void Enemy::Update() { 
	switch (phase_) {
	case Enemy::phase1:
		kEnemySpeed_ = 0.2f;
		switch (phase1State) { 
		case search:
			switch (phase1Move) {
			case (move1):
				move_.x = -kEnemySpeed_;
				if (worldTransform_.translation_.x <= 23.8f) {
					worldTransform_.translation_.x = 23.8f;
					worldTransform_.translation_.z = 19.5f;
					worldTransform_.rotation_.y -= rotateSpeed_;
					move_.x = 0;
					if (worldTransform_.rotation_.y <= -3.2f) {
						worldTransform_.rotation_.y = -3.2f;
						phase1Move = move2;
					}
				}
				break;
			case (move2):
				move_.z =- kEnemySpeed_;
				if (worldTransform_.translation_.z <= -7.8f) {
					worldTransform_.translation_.z = -7.8f;
					worldTransform_.translation_.x = 23.8f;
					move_.z = 0;
					worldTransform_.rotation_.y -= rotateSpeed_;
					if (worldTransform_.rotation_.y <= 1.6f) {
						worldTransform_.rotation_.y = 1.6f;
						phase1Move = move3;
					}
				}
				break;
			case (move3):
				move_.x = kEnemySpeed_;
				if (worldTransform_.translation_.x >= 48.0f) {
					worldTransform_.translation_.x = 48.0f;
					worldTransform_.translation_.z = -7.8f;
					worldTransform_.rotation_.y -= rotateSpeed_;
					move_.x = 0;
					if (worldTransform_.rotation_.y <= 0.0f) {
						worldTransform_.rotation_.y = 0.0f;
						phase1Move = move4;
					}
				}
				break;
				case (move4):
				if (flag == false) {
					move_.z = kEnemySpeed_;
				}
				if (worldTransform_.translation_.z >= 1.0f) {
					if (flag == false) {
						worldTransform_.translation_.z = 1.0f;
						move_.z = 0;
					}
					worldTransform_.rotation_.y += rotateSpeed_;
					if (worldTransform_.rotation_.y >= 0.8f) {
						flag = true;
						worldTransform_.rotation_.y = 0.8f;
						move_.x = kEnemySpeed_/2;
						move_.z = kEnemySpeed_/2;
					}
					if (worldTransform_.translation_.x > 52.0f&&worldTransform_.translation_.z>5.0f) {
						worldTransform_.translation_.x = 52.0f;
						worldTransform_.translation_.z = 5.0f;
						move_.x = 0; 
						move_.z = 0;
						phase1Move =move5;
					}
				}
				break;
			    case (move5):
				flag = false;
				worldTransform_.rotation_.y -= rotateSpeed_;
				if (worldTransform_.rotation_.y <= 0.0f) {
					move_.z = kEnemySpeed_;
					if (worldTransform_.translation_.z > 19.5) {
						worldTransform_.translation_.z = 19.5;
						move_.z = 0;
						phase1Move = move6;
					}
				}
					break;
				case(move6):
				    worldTransform_.rotation_.y -= rotateSpeed_;
				    if (worldTransform_.rotation_.y <= -1.6f) {
					worldTransform_.rotation_.y = -1.6f;
					phase1Move = move1;
				    }
					break;
			}
			break;
		case Chase:
			
			Homing(kEnemySpeed_);
			break;
		case posReset:

			break;
		}
		break;
	case Enemy::phase2:
		kEnemySpeed_ = 0.34f;
		switch (phase2State) {
		case search:

			break;
		case Chase:

			if (move_.z != 0 || move_.y != 0) {
				worldTransform_.rotation_.y = std::atan2(move_.x, move_.z);
			}
			break;
		case posReset:

			break;
		}
		break;
	case Enemy::phase3:
		kEnemySpeed_ = 0.38f;
		switch (phase1State) {
		case search:

			break;
		case Chase:

			if (move_.z != 0 || move_.y != 0) {
				worldTransform_.rotation_.y = std::atan2(move_.x, move_.z);
			}
			break;
		case posReset:

			break;
		}
		break;
	}

	float enemyMove[2] = {move_.x, move_.z};
	ImGui::Begin("EnemyMove");
	ImGui::SliderFloat2("EnemyMove", enemyMove, -0.3f, 0.3f);
	ImGui::End();
	move_.x = enemyMove[0];
	move_.z = enemyMove[1];

	float enemyRotate[2] = {worldTransform_.rotation_.x, worldTransform_.rotation_.y};
	ImGui::Begin("EnemyRotate");
	ImGui::SliderFloat2("EnemyRotate", enemyRotate, -0.3f, 0.3f);
	ImGui::End();
	worldTransform_.rotation_.x = enemyRotate[0];
	worldTransform_.rotation_.y = enemyRotate[1];

	if (move_.z != 0 || move_.y != 0) {
		worldTransform_.rotation_.y = std::atan2(move_.x, move_.z);
	}
	//move_ = Multiply(kEnemySpeed_, Normalize(move_));
	worldTransform_.translation_ = Add(worldTransform_.translation_, move_);
	worldTransform_.UpdateMatrix();
	
}

void Enemy::Homing(float enemySpeed_) {
	Vector3 A = player_->GetWorldPosition();
	Vector3 B = Enemy::GetWorldPosition();
	Vector3 C = Subtract(A, B);
	Vector3 vector = Normalize(C);
	vector = Multiply(enemySpeed_, vector);
	move_.x = vector.x;
	move_.z = vector.z;
}

void Enemy::Draw(ViewProjection& viewProjection) { model_->Draw(worldTransform_, viewProjection); }


Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

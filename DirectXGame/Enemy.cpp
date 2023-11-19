#include "Enemy.h"
#include"ImGuiManager.h"
#include "Player.h"

void Enemy::Initialize(
    Model* model, Model* model2, Model* model3, Model* model4, Model* model5, Model* model6,
    Model* model7, Model* model8, Model* model9, Model* model10, Model* model11, Model* model12,
    Model* model13, Model* model14, Model* model15) {
	model_ = model;
	model2_ = model2;
	model3_ = model3;
	model4_ = model4;
	model5_ = model5;
	model6_ = model6;
	model7_ = model7;
	model8_ = model8;
	model9_ = model9;
	model10_ = model10;
	model11_ = model11;
	model12_ = model12;
	model13_ = model13;
	model14_ = model14;
	model15_ = model15;

	worldTransform_.Initialize();
	move_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.rotation_ = {0.0f, 1.6f, 0.0f};
	worldTransform_.translation_ = {63.0f, 0.7f, 48.0f};
	encountFlag = false;
	kEnemySpeed_ = 0.0f;
	rotateSpeed_ = 0.05f;
	phase_ = phase1;
	phase1State = search;
	phase2State = search;
	phase3State = search;
	phase1Move = move1;
	stateFlag1 = false;
}

void Enemy::Update() { 
	switch (phase_) {
	case Enemy::phase1:
		kEnemySpeed_ = 0.2f;
		switch (phase1State) { 
		case search:
			switch (phase1Move) {
			case (move1):
				move_.x = kEnemySpeed_;
				if (worldTransform_.translation_.x >= 84.0f) {
					worldTransform_.translation_.x = 84.0f;
					worldTransform_.translation_.z = 48.5f;
					worldTransform_.rotation_.y -= rotateSpeed_;
					move_.x = 0.0f;
					if (worldTransform_.rotation_.y <= 0.0f) {
						worldTransform_.rotation_.y = 0.0f;
						phase1Move = move2;
					}
				}
				break;
			case (move2):
				move_.z = kEnemySpeed_;
				if (worldTransform_.translation_.z >= 76.0f) {
					worldTransform_.translation_.z = 76.0f;
					worldTransform_.rotation_.y -= rotateSpeed_;
					move_.z = 0.0f;
					if (worldTransform_.rotation_.y <= -1.6f) {
						worldTransform_.rotation_.y = -1.6f;
						phase1Move = move3;
					}
				}
				break;
			case (move3):
				move_.x = -kEnemySpeed_;
				if (worldTransform_.translation_.x <= 56.0f) {
					worldTransform_.translation_.x = 56.0f;
					move_.x = 0.0f;
					if (stateFlag1 == false) {
						worldTransform_.rotation_.y += rotateSpeed_;
						if (worldTransform_.rotation_.y >= -0.8f) {
							worldTransform_.rotation_.y = -0.8f;
							stateFlag1 = true;
						}
					}
					if (stateFlag1 == true) {
						worldTransform_.rotation_.y -= rotateSpeed_;
						if (worldTransform_.rotation_.y <= -2.4f) {
							worldTransform_.rotation_.y = -2.4f;
							phase1Move = move4;
						}
					}
				}
				break;
			case (move4):
				stateFlag1 = false;
				move_.x = -kEnemySpeed_ / 2;
				move_.z = -kEnemySpeed_ / 2;
				if (worldTransform_.translation_.x <= 52.0f &&
				    worldTransform_.translation_.z <= 72.0f) {
					worldTransform_.translation_.x = 52.0f;
					worldTransform_.translation_.z = 72.0f;
					move_.x = 0.0f;
					move_.z = 0.0f;
					worldTransform_.rotation_.y += rotateSpeed_;
					if (worldTransform_.rotation_.y >= -1.6f) {
						worldTransform_.rotation_.y = -1.6f;
						phase1Move = move5;
					}
				}
				break;
			case (move5):
				move_.x = -kEnemySpeed_;
				if (worldTransform_.translation_.x <= 31.0f) {
					worldTransform_.translation_.x = 31.0f;
					move_.x = 0;
					worldTransform_.rotation_.y += rotateSpeed_;
					if (worldTransform_.rotation_.y >= -0.8f) {
						worldTransform_.rotation_.y = -0.8f;
						phase1Move = move6;
					}
				}
				break;
			case (move6):
				move_.x = (- kEnemySpeed_) / 2;
				move_.z = kEnemySpeed_;
				if (worldTransform_.translation_.x <= 27.0f &&
				    worldTransform_.translation_.z >= 76.0f) {
					worldTransform_.translation_.x = 27.0f;
					worldTransform_.translation_.z = 76.0f;
					move_.x = 0;
					move_.z = 0;
					worldTransform_.rotation_.y -= rotateSpeed_;
					if (worldTransform_.rotation_.y <= -1.6f) {
						worldTransform_.rotation_.y = -1.6f;
						phase1Move = move7;
					}
					break;
				}
			case (move7):
				move_.x = -kEnemySpeed_;
				if (worldTransform_.translation_.x <= -4.0f) {
					worldTransform_.translation_.x = -4.0f;
					move_.x = 0;
				}
				break;
			case (move8):

				break;
			case (move9):

				break;
			case (move10):

				break;
			case (move11):

				break;
			case (move12):

				break;
			case (move13):

				break;
			case (move14):

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
	float enemyRotate[2] = {worldTransform_.rotation_.x, worldTransform_.rotation_.y};
	ImGui::Begin("EnemyRotate");
	ImGui::SliderFloat2("EnemyRotate", enemyRotate, -0.3f, 0.3f);
	ImGui::End();
	float enemyPos[2] = {worldTransform_.translation_.x, worldTransform_.translation_.z};
	ImGui::Begin("EnemyPos");
	ImGui::SliderFloat2("EnemyPos", enemyPos, -300.0f, 300.0f);
	ImGui::End();
	worldTransform_.translation_.x = enemyPos[0];
	worldTransform_.translation_.z = enemyPos[1];
	move_.x = enemyMove[0];
	move_.z = enemyMove[1];
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

void Enemy::Draw(ViewProjection& viewProjection) { 
	model_->Draw(worldTransform_, viewProjection);
	model2_->Draw(worldTransform_, viewProjection);
	model3_->Draw(worldTransform_, viewProjection);
	model4_->Draw(worldTransform_, viewProjection);
	model5_->Draw(worldTransform_, viewProjection);
	model6_->Draw(worldTransform_, viewProjection);
	model7_->Draw(worldTransform_, viewProjection);
	model8_->Draw(worldTransform_, viewProjection);
	model9_->Draw(worldTransform_, viewProjection);
	model10_->Draw(worldTransform_, viewProjection);
	model11_->Draw(worldTransform_, viewProjection);
	model12_->Draw(worldTransform_, viewProjection);
	model13_->Draw(worldTransform_, viewProjection);
	model14_->Draw(worldTransform_, viewProjection);
	model15_->Draw(worldTransform_, viewProjection);

}


Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

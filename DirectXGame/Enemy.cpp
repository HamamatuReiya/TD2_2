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
	state1Flag1 = false;
	state1Flag2 = false;
	state1Flag3 = false;
	state1Flag4 = false;
	state1Flag5 = false;
	state1Flag6 = false;
}

void Enemy::Update() { 
	switch (phase_) {
	case Enemy::phase1:
		kEnemySpeed_ = 0.3f;
		switch (phase1State) { 
		case search:
			switch (phase1Move) {
			case (move1):
				move_.x = kEnemySpeed_;
				if (worldTransform_.translation_.x >= 84.0f) {
					worldTransform_.translation_.x = 84.0f;
					worldTransform_.translation_.z = 48.0f;
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
					if (state1Flag1 == false) {
						worldTransform_.rotation_.y += rotateSpeed_;
						if (worldTransform_.rotation_.y >= -0.8f) {
							worldTransform_.rotation_.y = -0.8f;
							state1Flag1 = true;
						}
					}
					if (state1Flag1 == true) {
						worldTransform_.rotation_.y -= rotateSpeed_;
						if (worldTransform_.rotation_.y <= -2.4f) {
							worldTransform_.rotation_.y = -2.4f;
							phase1Move = move4;
						}
					}
				}
				break;
			case (move4):
				state1Flag1 = false;
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
					if (state1Flag2 == false) {
						worldTransform_.rotation_.y -= rotateSpeed_;
						if (worldTransform_.rotation_.y <= -6.4f) {
							worldTransform_.rotation_.y = -6.4f;
							state1Flag2 = true;
						}
					}
					if (state1Flag2 == true) {
						worldTransform_.rotation_.y += rotateSpeed_;
						if (worldTransform_.rotation_.y >= -3.2f) {
							worldTransform_.rotation_.y = -3.2f;
							phase1Move = move8;
						}
					}
				}
				break;
			case (move8):
				state1Flag2 = false;
				move_.z = -kEnemySpeed_;
				if (worldTransform_.translation_.z <= 40.0f) {
					worldTransform_.translation_.z = 40.0f;
					move_.z = 0;
					worldTransform_.rotation_.y -= rotateSpeed_;
					if (worldTransform_.rotation_.y <= 1.6f) {
						worldTransform_.rotation_.y = 1.6f;
						phase1Move = move9;
					}
				}
				break;
			case (move9):
				move_.x = kEnemySpeed_;
				if (worldTransform_.translation_.x >= 23.0f) {
					worldTransform_.translation_.x = 23.0f;
					move_.x = 0.0f;
					if (state1Flag3 == false) {
						worldTransform_.rotation_.y += rotateSpeed_;
						if (worldTransform_.rotation_.y >= 3.8f) {
							worldTransform_.rotation_.y = 3.8f;
							state1Flag3 = true;
						}
					}
					if (state1Flag3 == true) {
						worldTransform_.rotation_.y -= rotateSpeed_;
						if (worldTransform_.rotation_.y <= 0.0f) {
							worldTransform_.rotation_.y = 0.0f;
							phase1Move =move10;
						}
					}
				}
				break;
			case (move10):
				state1Flag3 = false;
				move_.z = kEnemySpeed_;
				if (worldTransform_.translation_.z >= 56.0f) {
					worldTransform_.translation_.z = 56.0f;
					move_.z = 0.0f;
					worldTransform_.rotation_.y += rotateSpeed_;
					if (worldTransform_.rotation_.y >= 1.6f) {
						worldTransform_.rotation_.y = 1.6f;
						phase1Move = move11;
					}
				}
				break;
			case (move11):
				move_.x = kEnemySpeed_;
				if (worldTransform_.translation_.x >= 34.0f) {
					worldTransform_.translation_.x = 34.0f;
					move_.x = 0.0f;
					worldTransform_.rotation_.y += rotateSpeed_;
					if (worldTransform_.rotation_.y >= 3.2f) {
						worldTransform_.rotation_.y = 3.2f;
						phase1Move = move12;
					}
				}
				break;
			case (move12):
				move_.z = -kEnemySpeed_;
				if (worldTransform_.translation_.z <=32.0f) {
					worldTransform_.translation_.z = 32.0f;
					move_.z = 0.0f;
					worldTransform_.rotation_.y -= rotateSpeed_;
					if (worldTransform_.rotation_.y <= 1.6f) {
						worldTransform_.rotation_.y = 1.6f;
						phase1Move = move13;
					}
				}
				break;
			case (move13):
				move_.x = +kEnemySpeed_;
				if (worldTransform_.translation_.x >= 51.8f) {
					worldTransform_.translation_.x = 51.8f;
					move_.x = 0.0f;
					worldTransform_.rotation_.y -= rotateSpeed_;
					if (worldTransform_.rotation_.y <= 0.0f) {
						worldTransform_.rotation_.y = 0.0f;
						phase1Move = move14;
					}
				}
				break;
			case (move14):
				move_.z = kEnemySpeed_;
				if (worldTransform_.translation_.z >= 39.7f) {
					worldTransform_.translation_.z = 39.7f;
					move_.z = 0.0f;
					worldTransform_.rotation_.y += rotateSpeed_;
					if (worldTransform_.rotation_.y >= 1.6f) {
						worldTransform_.rotation_.y = 1.6f;
						phase1Move = move15;
					}
				}
				break;
			case (move15):
				move_.x = kEnemySpeed_;
				if (worldTransform_.translation_.x >= 65.0f) {
					worldTransform_.translation_.x = 65.0f;
					move_.x = 0.0f;
					worldTransform_.rotation_.y -= rotateSpeed_;
					if (worldTransform_.rotation_.y <= 0.0f) {
						worldTransform_.rotation_.y = 0.0f;
						phase1Move = move16;
					}
				}
				break;
			case (move16):
				move_.z = kEnemySpeed_;
				if (worldTransform_.translation_.z >= 48.0f) {
					worldTransform_.translation_.z = 48.0f;
					move_.z = 0.0f;
					worldTransform_.rotation_.y += rotateSpeed_;
					if (worldTransform_.rotation_.y >= 1.6f) {
						worldTransform_.rotation_.y = 1.6f;
						phase1Move = move17;
					}
				}
				break;
			case (move17):
				move_.x = kEnemySpeed_;
				if (worldTransform_.translation_.x >= 84.0f) {
					worldTransform_.translation_.x = 84.0f;
					move_.x = 0.0f;
					worldTransform_.rotation_.y += rotateSpeed_;
					if (worldTransform_.rotation_.y >= 3.1f) {
						worldTransform_.rotation_.y = 3.1f;
						phase1Move = move18;
					}
				}
				break;
			case (move18):
				move_.z = -kEnemySpeed_;
				if (worldTransform_.translation_.z <= 4.0f) {
					worldTransform_.translation_.z = 4.0f;
					move_.z = 0.0f;
					worldTransform_.rotation_.y += rotateSpeed_;
					if (worldTransform_.rotation_.y >= 4.8f) {
						worldTransform_.rotation_.y = 4.8f;
						phase1Move = move19;
					}
				}
				break;
			case (move19):
				move_.x = -kEnemySpeed_;
				if (worldTransform_.translation_.x <= 80.0f) {
					worldTransform_.translation_.x = 80.0f;
					move_.x = 0.0f;
					worldTransform_.rotation_.y -= rotateSpeed_;
					if (worldTransform_.rotation_.y <= 3.2f) {
						worldTransform_.rotation_.y = 3.2f;
						phase1Move = move20;
					}
				}
				break;
			case (move20):
				move_.z = -kEnemySpeed_;
				if (worldTransform_.translation_.z <= -7.9f) {
					worldTransform_.translation_.z = -7.9f;
					move_.z = 0.0f;
					worldTransform_.rotation_.y += rotateSpeed_;
					if (worldTransform_.rotation_.y >= 4.7f) {
						worldTransform_.rotation_.y = 4.7f;
						phase1Move = move21;
					}
				} 
				break;
			case (move21):
				move_.x = -kEnemySpeed_;
				if (worldTransform_.translation_.x <= 68.0f) {
					worldTransform_.translation_.x = 68.0f;
					move_.x = 0.0f;
					worldTransform_.rotation_.y += rotateSpeed_;
					if (worldTransform_.rotation_.y >= 6.3f) {
						worldTransform_.rotation_.y = 6.3f;
						phase1Move = move22;
					}
				}
				break;
			case (move22):
				move_.z = kEnemySpeed_;
				if (worldTransform_.translation_.z >= 4.0f) {
					worldTransform_.translation_.z = 4.0f;
					move_.z = 0.0f;
					worldTransform_.rotation_.y -= rotateSpeed_;
					if (worldTransform_.rotation_.y <= -1.6f) {
						worldTransform_.rotation_.y = -1.6f;
						phase1Move = move23;
					}
				}
				break;
			case (move23):
				move_.x = -kEnemySpeed_;
				if (worldTransform_.translation_.x <= 56.0f) {
					worldTransform_.translation_.x =56.0f;
					move_.x = 0.0f;
					if (state1Flag4 == false) {
						worldTransform_.rotation_.y -= rotateSpeed_;
						if (worldTransform_.rotation_.y <= -2.3f) {
							worldTransform_.rotation_.y = -2.3f;
							state1Flag4 = true;
						}
					}
					if (state1Flag4 == true) {
						if (state1Flag5 == false) {
							worldTransform_.rotation_.y += rotateSpeed_;
						}
						if (worldTransform_.rotation_.y >= 0.0f) {
							worldTransform_.rotation_.y = 0.0f;
							state1Flag5 = true;
						}
					}
					 if (state1Flag5 == true) {
						worldTransform_.rotation_.y -= rotateSpeed_;
						if (worldTransform_.rotation_.y <= -0.8f) {
							worldTransform_.rotation_.y = -0.8f;
							phase1Move = move24;
						}
					}
				}
				break;
			case (move24):
				state1Flag4 = false;
				state1Flag5 = false;
				move_.x = (-kEnemySpeed_)/2;
				move_.z = kEnemySpeed_/2;
				if (worldTransform_.translation_.x <= 40.0f &&
				    worldTransform_.translation_.z >= 20.0f) {
					worldTransform_.translation_.x = 40.0f;
					worldTransform_.translation_.z = 20.0f;
					move_.x = 0;
					move_.z = 0;
					worldTransform_.rotation_.y -= rotateSpeed_;
					if (worldTransform_.rotation_.y <= -1.6f) {
						worldTransform_.rotation_.y = -1.6f;
						phase1Move = move25;
					}
				}
				break;
			case (move25):
				move_.x = -kEnemySpeed_;
				if (worldTransform_.translation_.x <= 24.0f) {
					worldTransform_.translation_.x = 24.0f;
					move_.x = 0.0f;
					worldTransform_.rotation_.y -= rotateSpeed_;
					if (worldTransform_.rotation_.y <= -3.2f) {
						worldTransform_.rotation_.y = -3.2f;
						phase1Move = move26;
					}
				}
				break;
			case (move26):
				move_.z = -kEnemySpeed_;
				if (worldTransform_.translation_.z <= 0.0f) {
					worldTransform_.translation_.z = 0.0f;
					move_.z = 0.0f;
					worldTransform_.rotation_.y += rotateSpeed_;
					if (worldTransform_.rotation_.y >= 4.8f) {
						worldTransform_.rotation_.y = 4.8f;
						phase1Move = move27;
					}
				} 
				break;
			case (move27):
				move_.x = -kEnemySpeed_;
				if (worldTransform_.translation_.x <= -4.0f) {
					worldTransform_.translation_.x = -4.0f;
					move_.x = 0.0f;
					worldTransform_.rotation_.y += rotateSpeed_;
					if (worldTransform_.rotation_.y >= 6.4f) {
						worldTransform_.rotation_.y = 6.4f;
						phase1Move = move28;
					}
				}
				break;
			case (move28):
				move_.z = kEnemySpeed_;
				if (worldTransform_.translation_.z >= 40.0f) {
					worldTransform_.translation_.z = 40.0f;
					move_.z = 0.0f;
					worldTransform_.rotation_.y += rotateSpeed_;
					if (worldTransform_.rotation_.y >= 1.6f) {
						worldTransform_.rotation_.y = 1.6f;
						phase1Move = move29;
					}
				} 
				break;
			case (move29):
				move_.x = kEnemySpeed_;
				if (worldTransform_.translation_.x >= 23.0f) {
					worldTransform_.translation_.x = 23.0f;
					move_.x = 0.0f;
					if (state1Flag3 == false) {
						worldTransform_.rotation_.y += rotateSpeed_;
						if (worldTransform_.rotation_.y >= 3.8f) {
							worldTransform_.rotation_.y = 3.8f;
							state1Flag3 = true;
						}
					}
					if (state1Flag3 == true) {
						worldTransform_.rotation_.y -= rotateSpeed_;
						if (worldTransform_.rotation_.y <= 0.0f) {
							worldTransform_.rotation_.y = 0.0f;
							phase1Move = move30;
						}
					}
				}
				break;
			case (move30):
				state1Flag3 = false;
				move_.z = kEnemySpeed_;
				if (worldTransform_.translation_.z >= 56.0f) {
					worldTransform_.translation_.z = 56.0f;
					move_.z = 0.0f;
					worldTransform_.rotation_.y += rotateSpeed_;
					if (worldTransform_.rotation_.y >= 1.6f) {
						worldTransform_.rotation_.y = 1.6f;
						phase1Move = move31;
					}
				}
				break;
			case (move31):
				move_.x = kEnemySpeed_;
				if (worldTransform_.translation_.x >= 34.0f) {
					worldTransform_.translation_.x = 34.0f;
					move_.x = 0.0f;
					worldTransform_.rotation_.y += rotateSpeed_;
					if (worldTransform_.rotation_.y >= 3.2f) {
						worldTransform_.rotation_.y = 3.2f;
						phase1Move = move32;
					}
				}
				break;
			case (move32):
				move_.z = -kEnemySpeed_;
				if (worldTransform_.translation_.z <= 32.0f) {
					worldTransform_.translation_.z = 32.0f;
					move_.z = 0.0f;
					worldTransform_.rotation_.y -= rotateSpeed_;
					if (worldTransform_.rotation_.y <= 1.6f) {
						worldTransform_.rotation_.y = 1.6f;
						phase1Move = move33;
					}
				}
				break;
			case (move33):
				move_.x = +kEnemySpeed_;
				if (worldTransform_.translation_.x >= 51.8f) {
					worldTransform_.translation_.x = 51.8f;
					move_.x = 0.0f;
					worldTransform_.rotation_.y -= rotateSpeed_;
					if (worldTransform_.rotation_.y <= 0.0f) {
						worldTransform_.rotation_.y = 0.0f;
						phase1Move = move34;
					}
				}
				break;
			case (move34):
				move_.z = kEnemySpeed_;
				if (worldTransform_.translation_.z >= 39.7f) {
					worldTransform_.translation_.z = 39.7f;
					move_.z = 0.0f;
					worldTransform_.rotation_.y += rotateSpeed_;
					if (worldTransform_.rotation_.y >= 1.6f) {
						worldTransform_.rotation_.y = 1.6f;
						phase1Move = move35;
					}
				}
				break;
			case (move35):
				move_.x = kEnemySpeed_;
				if (worldTransform_.translation_.x >= 63.0f) {
					worldTransform_.translation_.x = 63.0f;
					move_.x = 0.0f;
					worldTransform_.rotation_.y -= rotateSpeed_;
					if (worldTransform_.rotation_.y <= 0.0f) {
						worldTransform_.rotation_.y = 0.0f;
						phase1Move = move36;
					}
				}
				break;
			case (move36):
				move_.z = kEnemySpeed_;
				if (worldTransform_.translation_.z >= 48.0f) {
					worldTransform_.translation_.z = 48.0f;
					move_.z = 0.0f;
					worldTransform_.rotation_.y += rotateSpeed_;
					if (worldTransform_.rotation_.y >= 1.6f) {
						worldTransform_.rotation_.y = 1.6f;
						phase1Move = move1;
					}
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
	ImGui::SliderFloat2("EnemyRotate", enemyRotate, -6.4f, 6.4f);
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

void Enemy::StartRoomCollision() {}

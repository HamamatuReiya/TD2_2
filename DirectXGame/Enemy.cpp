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
	rotateSpeed_ = 0.10f;
	phase_ = phase1;
	phase1State = Chase;
	collisionType_ = ROOM05;
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
		kEnemySpeed_ = 0.22f; 
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

	/*float enemyMove[2] = {move_.x, move_.z};
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
	worldTransform_.rotation_.y = enemyRotate[1];*/

	// カメラの角度から回転行列を計算する
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(viewProjection_->rotation_.y);
	// カメラとリンク
	move_ = TransformNormal(move_, MakeRotateYMatrix(viewProjection_->rotation_.y));

	if (move_.z != 0 || move_.y != 0) {
		worldTransform_.rotation_.y = std::atan2(move_.x, move_.z);
	}

	worldTransform_.translation_ = Add(worldTransform_.translation_, move_);

	//move_ = Multiply(kEnemySpeed_, Normalize(move_));
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

void Enemy::StartRoomCollision() {
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
		move_.x = kEnemySpeed_;
		move_.z = 0;
		worldTransform_.rotation_.y = 1.5f;
	}
	if (worldTransform_.translation_.x >= -2.087f && worldTransform_.translation_.x <= 6.008f &&
	    worldTransform_.translation_.z >= 48.558f) { // 左の右壁
		worldTransform_.translation_.z = 48.558f;
		move_.x = -kEnemySpeed_;
		move_.z = 0;
		worldTransform_.rotation_.y = -1.5f;
	}
	if (worldTransform_.translation_.z <= 38.067f && worldTransform_.translation_.z >= 30.000f &&
	    worldTransform_.translation_.x >= 4.961f) { // 手前の左壁
		worldTransform_.translation_.x = 4.961f;
		move_.z = kEnemySpeed_;
		move_.x = 0.0f;
		worldTransform_.rotation_.y = 0.0f;
	}
	if (worldTransform_.translation_.z >= 41.721f && worldTransform_.translation_.z <= 49.463f &&
	    worldTransform_.translation_.x >= 4.961f) { // 手前の右壁
		worldTransform_.translation_.x = 4.961f;
		move_.z = -kEnemySpeed_;
		move_.x = 0.0f;
		worldTransform_.rotation_.y = -3.0f;
	}
	if (worldTransform_.translation_.x >= -8.705f && worldTransform_.translation_.x <= -5.705f &&
	    worldTransform_.translation_.z <= 30.804f) { // 右の左壁
		worldTransform_.translation_.z = 30.804f;
		move_.x = kEnemySpeed_;
		move_.z = 0;
		worldTransform_.rotation_.y = 1.5f;
	}
	if (worldTransform_.translation_.x >= -2.087f && worldTransform_.translation_.x <= 6.008f &&
	    worldTransform_.translation_.z <= 30.804f) { // 右の右壁
		worldTransform_.translation_.z = 30.804f;
		move_.x = -kEnemySpeed_;
		move_.z = 0;
		worldTransform_.rotation_.y = -1.5f;
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

void Enemy::Room00Collision() {
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
		move_.x = kEnemySpeed_;
		move_.z = 0;
		worldTransform_.rotation_.y = 1.5f;
	}
	if (worldTransform_.translation_.z >= 8.2f && worldTransform_.translation_.x >= -2.652f &&
	    worldTransform_.translation_.x <= 9.2f &&
	    worldTransform_.translation_.z <= 9.082f) { // 上右
		worldTransform_.translation_.z = 8.2f;
		move_.x = -kEnemySpeed_;
		move_.z = 0;
		worldTransform_.rotation_.y = -1.5f;
	}
	if (worldTransform_.translation_.x >= 8.737f &&
	    worldTransform_.translation_.z <= -1.888f) { // 左壁
		worldTransform_.translation_.x = 8.737f;
		move_.z = kEnemySpeed_;
		move_.x = 0.0f;
		worldTransform_.rotation_.y = 0.0f;
	}
	if (worldTransform_.translation_.x >= 8.737f &&
	    worldTransform_.translation_.z >= 1.190) { // 右壁
		worldTransform_.translation_.x = 8.737f;
		move_.z = -kEnemySpeed_;
		move_.x = 0.0f;
		worldTransform_.rotation_.y = -3.0f;
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

void Enemy::Room01Collision() {
	if (worldTransform_.translation_.z <= -8.8f) { // 下
		worldTransform_.translation_.z = -8.8f;
	}
	if (worldTransform_.translation_.x <= 11.3f && worldTransform_.translation_.z >= 2.0f) { // 左壁
		worldTransform_.translation_.x = 11.3f;
		move_.z = -kEnemySpeed_;
		move_.x = 0.0f;
		worldTransform_.rotation_.y = -3.0f;
	}
	if (worldTransform_.translation_.x <= 10.8f &&
	    worldTransform_.translation_.z >= 1.592f) { // 左壁
		worldTransform_.translation_.z = 1.592f;
		// 右に行く処理
		if (player_->GetWorldTransform().translation_.x >= worldTransform_.translation_.x) {
			move_.x = kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = 1.5f;
		}
		// 左に行く処理
		else if (player_->GetWorldTransform().translation_.x <= worldTransform_.translation_.x) {
			move_.x = -kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = -1.5f;
		}
	}

	if (worldTransform_.translation_.x <= 11.3f &&
	    worldTransform_.translation_.z <= -2.0f) { // 右壁
		worldTransform_.translation_.x = 11.3f;
		move_.z = kEnemySpeed_;
		move_.x = 0.0f;
		worldTransform_.rotation_.y = 0.0f;
	}
	if (worldTransform_.translation_.x <= 10.8f &&
	    worldTransform_.translation_.z <= -1.511f) { // 右壁
		worldTransform_.translation_.z = -1.511f;
		// 右に行く処理
		if (player_->GetWorldTransform().translation_.x >= worldTransform_.translation_.x) {
			move_.x = kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = 1.5f;
		}
		// 左に行く処理
		else if (player_->GetWorldTransform().translation_.x <= worldTransform_.translation_.x) {
			move_.x = -kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = -1.5f;
		}
	}

	if (worldTransform_.translation_.z >= 8.5 && worldTransform_.translation_.x >= 10.926f &&
	    worldTransform_.translation_.x <= 21.9f) { //
		worldTransform_.translation_.z = 8.5f;
		move_.x = kEnemySpeed_;
		move_.z = 0;
		worldTransform_.rotation_.y = 1.5f;
	}
	if (worldTransform_.translation_.z >= 9.0f && worldTransform_.translation_.x >= 10.926f &&
	    worldTransform_.translation_.x <= 22.411f) { //
		worldTransform_.translation_.x = 22.411f;
		// 上に行く処理
		if (player_->GetWorldTransform().translation_.z >= worldTransform_.translation_.z) {
			move_.z = kEnemySpeed_;
			move_.x = 0.0f;
			worldTransform_.rotation_.y = 0.0f;
		}
		// 下に行く処理
		else if (player_->GetWorldTransform().translation_.z <= worldTransform_.translation_.z) {
			move_.z = -kEnemySpeed_;
			move_.x = 0.0f;
			worldTransform_.rotation_.y = -3.0f;
		}
	}

	if (worldTransform_.translation_.z >= 8.5f && worldTransform_.translation_.x >= 26.242f &&
	    worldTransform_.translation_.x <= 35.468f) { //
		worldTransform_.translation_.z = 8.5f;
		move_.x = -kEnemySpeed_;
		move_.z = 0;
		worldTransform_.rotation_.y = -1.5f;
	}
	if (worldTransform_.translation_.z >= 9.0f && worldTransform_.translation_.x >= 25.742f &&
	    worldTransform_.translation_.x <= 35.468f) { //
		worldTransform_.translation_.x = 25.742f;
		// 上に行く処理
		if (player_->GetWorldTransform().translation_.z >= worldTransform_.translation_.z) {
			move_.z = kEnemySpeed_;
			move_.x = 0.0f;
			worldTransform_.rotation_.y = 0.0f;
		}
		// 下に行く処理
		else if (player_->GetWorldTransform().translation_.z <= worldTransform_.translation_.z) {
			move_.z = -kEnemySpeed_;
			move_.x = 0.0f;
			worldTransform_.rotation_.y = -3.0f;
		}
	}

	if (worldTransform_.translation_.z <= 10.328f && worldTransform_.translation_.z >= -6.171f &&
	    worldTransform_.translation_.x >= 32.5f) { // 奥壁
		worldTransform_.translation_.x = 32.5f;
		move_.z = -kEnemySpeed_;
		move_.x = 0.0f;
		worldTransform_.rotation_.y = -3.0f;
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

void Enemy::Room02Collision() {
	if (worldTransform_.translation_.z <= 11.7f && worldTransform_.translation_.x >= 8.926f &&
	    worldTransform_.translation_.x <= 22.411f) { //
		worldTransform_.translation_.z = 11.7f;
		move_.x = kEnemySpeed_;
		move_.z = 0;
		worldTransform_.rotation_.y = 1.5f;
	}
	if (worldTransform_.translation_.z <= 11.7 && worldTransform_.translation_.x >= 25.742f &&
	    worldTransform_.translation_.x <= 33.468f) { //
		worldTransform_.translation_.z = 11.7f;
			move_.x = -kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = -1.5f;
	
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
		move_.z = -kEnemySpeed_;
		move_.x = 0.0f;
		worldTransform_.rotation_.y = -3.0f;
	}
	if (worldTransform_.translation_.z <= 26.0f && worldTransform_.translation_.z >= 21.633f &&
	    worldTransform_.translation_.x >= 32.8f) { // 手前の左壁
		worldTransform_.translation_.z = 21.633f;
		// 右に行く処理
		if (player_->GetWorldTransform().translation_.x >= worldTransform_.translation_.x) {
			move_.x = kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = 1.5f;
		}
		// 左に行く処理
		else if (player_->GetWorldTransform().translation_.x <= worldTransform_.translation_.x) {
			move_.x = -kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = -1.5f;
		}
	}

	if (worldTransform_.translation_.z >= 10.0f && worldTransform_.translation_.z <= 18.222f &&
	    worldTransform_.translation_.x >= 32.3f) { // 手前の右壁
		worldTransform_.translation_.x = 32.3f;
		move_.z = kEnemySpeed_;
		move_.x = 0.0f;
		worldTransform_.rotation_.y = 0.0f;
	}
	if (worldTransform_.translation_.z >= 10.0f && worldTransform_.translation_.z <= 18.722f &&
	    worldTransform_.translation_.x >= 32.8f) { // 手前の右壁
		worldTransform_.translation_.z = 18.722f;
		// 右に行く処理
		if (player_->GetWorldTransform().translation_.x >= worldTransform_.translation_.x) {
			move_.x = kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = 1.5f;
		}
		// 左に行く処理
		else if (player_->GetWorldTransform().translation_.x <= worldTransform_.translation_.x) {
			move_.x = -kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = -1.5f;
		}
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

void Enemy::Room03Collision() {
	if (worldTransform_.translation_.z <= -8.8f) { // 下
		worldTransform_.translation_.z = -8.8f;
	}
	
	if (worldTransform_.translation_.x >= 56.526f) { // 奥側
		worldTransform_.translation_.x = 56.526f;
		move_.z = kEnemySpeed_;
		move_.x = 0.0f;
		worldTransform_.rotation_.y = 0.0f;
	}

	if (worldTransform_.translation_.z >= -3.0f && worldTransform_.translation_.x >= 35.371f &&
	    worldTransform_.translation_.x <= 45.881f) { // 　ROOM04側の左壁
		worldTransform_.translation_.z = -3.0f;
		// 右に行く処理
		if (player_->GetWorldTransform().translation_.x >= worldTransform_.translation_.x) {
			move_.x = kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = 1.5f;
		}
		// 左に行く処理
		else if (player_->GetWorldTransform().translation_.x <= worldTransform_.translation_.x) {
			move_.x = -kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = -1.5f;
		}
	}
	if (worldTransform_.translation_.z >= -2.5f && worldTransform_.translation_.x >= 35.371f &&
	    worldTransform_.translation_.x <= 46.381f) { // 　ROOM04側の左壁
		worldTransform_.translation_.x = 46.381f;
		// 上に行く処理
		if (player_->GetWorldTransform().translation_.z >= worldTransform_.translation_.z) {
			move_.z = kEnemySpeed_;
			move_.x = 0.0f;
			worldTransform_.rotation_.y = 0.0f;
		}
		// 下に行く処理
		else if (player_->GetWorldTransform().translation_.z <= worldTransform_.translation_.z) {
			move_.z = -kEnemySpeed_;
			move_.x = 0.0f;
			worldTransform_.rotation_.y = -3.0f;
		}
	}

	if (worldTransform_.translation_.z >= -3.0f && worldTransform_.translation_.x >= 50.033f &&
	    worldTransform_.translation_.x <= 58.0f) { // ROOM04側の右壁
		worldTransform_.translation_.z = -3.0f;
		move_.x = -kEnemySpeed_;
		move_.z = 0;
		worldTransform_.rotation_.y = -1.5f;
	}
	if (worldTransform_.translation_.z >= -2.5f && worldTransform_.translation_.x >= 49.533f &&
	    worldTransform_.translation_.x <= 58.0f) { // ROOM04側の右壁
		worldTransform_.translation_.x = 49.533f;
		// 上に行く処理
		if (player_->GetWorldTransform().translation_.z >= worldTransform_.translation_.z) {
			move_.z = kEnemySpeed_;
			move_.x = 0.0f;
			worldTransform_.rotation_.y = 0.0f;
		}
		// 下に行く処理
		else if (player_->GetWorldTransform().translation_.z <= worldTransform_.translation_.z) {
			move_.z = -kEnemySpeed_;
			move_.x = 0.0f;
			worldTransform_.rotation_.y = -3.0f;
		}
	}

	

	if (worldTransform_.translation_.z >= -6.070f && worldTransform_.translation_.z <= -1.554f &&
	    worldTransform_.translation_.x <= 35.5f) { // ROOM01側の右壁
		worldTransform_.translation_.x = 35.5f;
		move_.z = -kEnemySpeed_;
		move_.x = 0.0f;
		worldTransform_.rotation_.y = -3.0f;
	}
	if (worldTransform_.translation_.z >= -6.570f && worldTransform_.translation_.z <= -1.554f &&
	    worldTransform_.translation_.x <= 35.0f) { // ROOM01側の右壁
		worldTransform_.translation_.z = -6.570f;
		// 右に行く処理
		if (player_->GetWorldTransform().translation_.x >= worldTransform_.translation_.x) {
			move_.x = kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = 1.5f;
		}
		// 左に行く処理
		else if (player_->GetWorldTransform().translation_.x <= worldTransform_.translation_.x) {
			move_.x = -kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = -1.5f;
		}
	}

	// 部屋01に移動
	if (worldTransform_.translation_.x < 33.0f) {
		collisionType_ = ROOM01;
	}
	// 部屋04に移動
	if (worldTransform_.translation_.z > -1.2f) {
		collisionType_ = ROOM04;
	}
}

void Enemy::Room04Collision() {
	if (worldTransform_.translation_.z <= 26.0f && worldTransform_.translation_.z >= 21.633f &&
	    worldTransform_.translation_.x <= 35.0f) { // ROOM02側の左壁
		worldTransform_.translation_.x = 35.0f;
		move_.z = -kEnemySpeed_;
		move_.x = 0.0f;
		worldTransform_.rotation_.y = -3.0f;
	}
	if (worldTransform_.translation_.z >= -1.5f && worldTransform_.translation_.z <= 18.722f &&
	    worldTransform_.translation_.x <= 35.0f) { // ROOM02側の右壁
		worldTransform_.translation_.x = 35.0f;
		move_.z = kEnemySpeed_;
		move_.x = 0.0f;
		worldTransform_.rotation_.y = 0.0f;
	}
	if (worldTransform_.translation_.z <= -0.7f && worldTransform_.translation_.x >= 35.371f &&
	    worldTransform_.translation_.x <= 46.381f) { // ROOM03側の左壁
		worldTransform_.translation_.z = -0.7f;

			move_.x = kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = 1.5f;
		
	}
	if (worldTransform_.translation_.z <= -0.7f && worldTransform_.translation_.x >= 49.533f &&
	    worldTransform_.translation_.x <= 58.0f) { // ROOM03側の右壁
		worldTransform_.translation_.z = -0.7f;
			move_.x = -kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = -1.5f;
		
	}
	if (worldTransform_.translation_.z >= -0.8f && worldTransform_.translation_.z <= 2.386f &&
	    worldTransform_.translation_.x >= 56.761f) { // Load1側の右壁
		worldTransform_.translation_.x = 56.761f;
		move_.z = kEnemySpeed_;
		move_.x = 0.0f;
		worldTransform_.rotation_.y = 0.0f;
	}
	if (worldTransform_.translation_.z <= 26.0f && worldTransform_.translation_.z >= 5.520f &&
	    worldTransform_.translation_.x >= 56.761f) { // Load1側の左壁
		worldTransform_.translation_.x = 56.761f;
		move_.z = -kEnemySpeed_;
		move_.x = 0.0f;
		worldTransform_.rotation_.y = -3.0f;
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

void Enemy::Room05Collision() {
	if (worldTransform_.translation_.z <= 47.227f && worldTransform_.translation_.x >= 73.744f &&
	    worldTransform_.translation_.x <= 84.746f) { // LOAD1側左壁
		worldTransform_.translation_.z = 47.227f;
		if (player_->GetWorldTransform().translation_.x >= worldTransform_.translation_.x ||
		    player_->GetWorldTransform().translation_.z <= 26.0f) {
			move_.x = kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = 1.5f;
		} else if (player_->GetWorldTransform().translation_.x <= worldTransform_.translation_.x) {
			move_.x = -kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = -1.5f;
		}
	}
	if (worldTransform_.translation_.z >= 49.183f) { // 右壁
		worldTransform_.translation_.z = 49.183f;
		if (player_->GetWorldTransform().translation_.x >= worldTransform_.translation_.x) {
			move_.x = kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = 1.5f;
		} else if (player_->GetWorldTransform().translation_.x <= worldTransform_.translation_.x) {
			move_.x = kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = 1.5f;
		}

	}
	if (worldTransform_.translation_.z <= 30.951f) { // 左壁
		worldTransform_.translation_.z = 30.951f;
		if (player_->GetWorldTransform().translation_.x >= worldTransform_.translation_.x ||
		    player_->GetWorldTransform().translation_.z <= 26.0f) {
			move_.x = kEnemySpeed_;
			worldTransform_.rotation_.y = 1.5f;
		} else if (player_->GetWorldTransform().translation_.x <= worldTransform_.translation_.x) {
			move_.x = -kEnemySpeed_;
			worldTransform_.rotation_.y = -1.5f;
		}
	}
	if (worldTransform_.translation_.z >= 41.527f && worldTransform_.translation_.z <= 50.0f &&
	    worldTransform_.translation_.x <= 58.714f) { // LOAD4側右壁
		worldTransform_.translation_.x = 58.714f;
		if (player_->GetWorldTransform().translation_.x <= worldTransform_.translation_.x) {
			move_.z = -kEnemySpeed_;
			move_.x = 0.0f;
			worldTransform_.rotation_.y = -3.0f;
		}
	}
	if (worldTransform_.translation_.z <= 38.422f && worldTransform_.translation_.z >= 30.0f &&
	    worldTransform_.translation_.x <= 58.714f) { // LOAD4側左壁
		worldTransform_.translation_.x = 58.714f;
		if (player_->GetWorldTransform().translation_.x <= worldTransform_.translation_.x) {
			move_.z = kEnemySpeed_;
			move_.x = 0.0f;
			worldTransform_.rotation_.y = 0.0f;
		}
	}
	if (worldTransform_.translation_.z <= 46.267f && worldTransform_.translation_.z >= 30.0f &&
	    worldTransform_.translation_.x >= 73.394f) { // 後ろ壁
		worldTransform_.translation_.x = 73.394f;
		if (player_->GetWorldTransform().translation_.x >= worldTransform_.translation_.x) {
			move_.z = kEnemySpeed_;
			worldTransform_.rotation_.y = 0.0f;
		}
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

void Enemy::Room06Collision() {
	if (worldTransform_.translation_.z >= 33.624f && worldTransform_.translation_.x >= 37.485f &&
	    worldTransform_.translation_.z <= 60.0f) { // したかべ
		worldTransform_.translation_.x = 37.485f;
		if (player_->GetWorldTransform().translation_.x >= 43.0f) {
			move_.z = -kEnemySpeed_;
			move_.x = 0.0f;
			worldTransform_.rotation_.y = -3.0f;
		}
	}

	if (worldTransform_.translation_.z <= 53.988f && worldTransform_.translation_.z >= 29.0f &&
	    worldTransform_.translation_.x <= 29.5f) { //
		worldTransform_.translation_.x = 29.5f;
		if (player_->GetWorldTransform().translation_.x <= 25.0f) {
			move_.z = kEnemySpeed_;
			move_.x = 0.0f;
			worldTransform_.rotation_.y = 0.0f;
		}
	}
	if (worldTransform_.translation_.z <= 54.488f && worldTransform_.translation_.z >= 29.0f &&
	    worldTransform_.translation_.x <= 29.0f) { //
		worldTransform_.translation_.z = 54.488f;//右に行く処理
		if (player_->GetWorldTransform().translation_.x >= worldTransform_.translation_.x) {
			move_.x = kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = 1.5f;
		}
		// 左に行く処理
		else if (player_->GetWorldTransform().translation_.x <= worldTransform_.translation_.x) {
			move_.x = -kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = -1.5f;
		}
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

void Enemy::Room07Collision() {
	if (worldTransform_.translation_.z <= 54.488f && worldTransform_.translation_.z >= 29.0f &&
	    worldTransform_.translation_.x >= 27.4f) { //
		worldTransform_.translation_.x = 27.4f;
		if (player_->GetWorldTransform().translation_.x >= 30) {	
			move_.z = kEnemySpeed_;
			move_.x = 0.0f;
			worldTransform_.rotation_.y = 0.0f;
		}
	}
	if (worldTransform_.translation_.z <= 58.0f && worldTransform_.translation_.z >= 41.634f &&
	    worldTransform_.translation_.x <= 18.830f) { //
		worldTransform_.translation_.x = 18.830f;
		move_.z = -kEnemySpeed_;
		move_.x = 0.0f;
		worldTransform_.rotation_.y = -3.0f;
	}
	if (worldTransform_.translation_.z <= 38.229f && worldTransform_.translation_.z >= 29.5f &&
	    worldTransform_.translation_.x <= 18.830f) { //
		worldTransform_.translation_.x = 18.830f;
		move_.z = kEnemySpeed_;
		move_.x = 0.0f;
		worldTransform_.rotation_.y = 0.0f;
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

void Enemy::Room08Collision() {
	// 道03に移動
	if (worldTransform_.translation_.z < 62.0f) {
		collisionType_ = LOAD03;
	}
	if (worldTransform_.translation_.z <= 62.5f && worldTransform_.translation_.x >= -2.7f) { //
		worldTransform_.translation_.z = 62.5f;
		if (player_->GetWorldTransform().translation_.z <= 59.0f) {

			move_.x = -kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = -1.5f;
		}
	}
	if (worldTransform_.translation_.z >= 81.0f) { //
		worldTransform_.translation_.z = 81.0f;
	}
	if (worldTransform_.translation_.x <= -5.0f) { // 左壁
		worldTransform_.translation_.x = -5.0f;
	}
	if (worldTransform_.translation_.x >= 13.53f &&
	    worldTransform_.translation_.z <= 75.0f) { // 左壁
		worldTransform_.translation_.x = 13.53f;
		if (player_->GetWorldTransform().translation_.x >= 25.0f) {

			move_.z = kEnemySpeed_;
			move_.x = 0.0f;
			worldTransform_.rotation_.y = 0.0f;
		}
	}
	if (worldTransform_.translation_.x >= 13.53f &&
	    worldTransform_.translation_.z >= 77.3f) { // 左壁
		worldTransform_.translation_.x = 13.53f;
		if (player_->GetWorldTransform().translation_.x >= 25.0f) {
			move_.z = -kEnemySpeed_;
			move_.x = 0.0f;
			worldTransform_.rotation_.y = -3.0f;
		}
	}
	if (worldTransform_.translation_.x > 13.8f) {
		collisionType_ = LOAD05;
	}
}

void Enemy::Room09Collision() {

	if (worldTransform_.translation_.x < 22.0f) {
		collisionType_ = LOAD05;
	}
	if (worldTransform_.translation_.x > 33.6f) {
		collisionType_ = ROOM10;
	}

	if (worldTransform_.translation_.x <= 22.645f && worldTransform_.translation_.z <= 75.0f) {
		worldTransform_.translation_.x = 22.645f;
		if (player_->GetWorldTransform().translation_.x <= 12.0f) {
			
			move_.z = kEnemySpeed_;
			move_.x = 0.0f;
			worldTransform_.rotation_.y = 0.0f;
		}
	}
	if (worldTransform_.translation_.x <= 22.645f && worldTransform_.translation_.z >= 77.3f) {
		worldTransform_.translation_.x = 22.645f;
		if (player_->GetWorldTransform().translation_.x <= 12.0f) {
			move_.z = -kEnemySpeed_;
			move_.x = 0.0f;
			worldTransform_.rotation_.y = -3.0f;
			
		}
	}
	if (worldTransform_.translation_.z <= 66.5f) { //
		worldTransform_.translation_.z = 66.5f;
	}
	if (worldTransform_.translation_.z >= 85.0f) { //
		worldTransform_.translation_.z = 85.0f;
	}
	if (worldTransform_.translation_.x >= 33.2f && worldTransform_.translation_.z <= 70.5f) {
		worldTransform_.translation_.x = 33.2f;
		if (player_->GetWorldTransform().translation_.x >= 40.0f) {
			
			move_.z = kEnemySpeed_;
			move_.x = 0.0f;
			worldTransform_.rotation_.y = 0.0f;
		}
	}
	if (worldTransform_.translation_.x >= 33.2f && worldTransform_.translation_.z >= 73.0f) {
		worldTransform_.translation_.x = 33.2f;
		if (player_->GetWorldTransform().translation_.x >= 40.0f) {
			move_.z = -kEnemySpeed_;
			move_.x = 0.0f;
			worldTransform_.rotation_.y = -3.0f;
		}
	}
	
}

void Enemy::Room10Collision() {
	if (worldTransform_.translation_.x <= 33.6f) {
		collisionType_ = ROOM09;
	}
	// ルーム9側の上の敷居
	if (worldTransform_.translation_.x >= 33.2f && worldTransform_.translation_.x <= 34.8f &&
	    worldTransform_.translation_.z <= 70.5f) {
		worldTransform_.translation_.z = 70.5f;
		// 右に行く処理
		if (player_->GetWorldTransform().translation_.x >= worldTransform_.translation_.x) {
			move_.x = kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = 1.5f;
		}
		// 左に行く処理
		else if (player_->GetWorldTransform().translation_.x <= worldTransform_.translation_.x) {
			move_.x = -kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = -1.5f;
		}
	}
	////
	if (worldTransform_.translation_.x <= 35.2f && worldTransform_.translation_.z <= 70.0f) {
		worldTransform_.translation_.x = 35.2f;
		if (player_->GetWorldTransform().translation_.x <= 30.0f) {

			move_.z = kEnemySpeed_;
			move_.x = 0.0f;
			worldTransform_.rotation_.y = 0.0f;
		}
	}
	// ルーム9側の下の敷居
	if (worldTransform_.translation_.x >= 33.2f && worldTransform_.translation_.x <= 34.8f &&
	    worldTransform_.translation_.z >= 73.0f) {
		worldTransform_.translation_.z = 73.0f;
		// 右に行く処理
		if (player_->GetWorldTransform().translation_.x >= worldTransform_.translation_.x) {
			move_.x = kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = 1.5f;
		}
		// 左に行く処理
		else if (player_->GetWorldTransform().translation_.x <= worldTransform_.translation_.x) {
			move_.x = -kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = -1.5f;
		}
	}
	////
	if (worldTransform_.translation_.x <= 35.2f && worldTransform_.translation_.z >= 73.5f) {
		worldTransform_.translation_.x = 35.2f;
		if (player_->GetWorldTransform().translation_.x <= 30.0f) {
			move_.z = -kEnemySpeed_;
			move_.x = 0.0f;
			worldTransform_.rotation_.y = -3.0f;
		}
	}
	if (worldTransform_.translation_.z <= 66.5f) { //
		worldTransform_.translation_.z = 66.5f;
	}
	if (worldTransform_.translation_.z >= 74.9f) { //
		worldTransform_.translation_.z = 74.9f;
	}
	// ルーム12側の上の敷居
	if (worldTransform_.translation_.x >= 49.4f && worldTransform_.translation_.x <= 50.3f &&
	    worldTransform_.translation_.z <= 70.5f) {
		worldTransform_.translation_.z = 70.5f;
		// 右に行く処理
		if (player_->GetWorldTransform().translation_.x >= worldTransform_.translation_.x) {
			move_.x = kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = 1.5f;
		}
		// 左に行く処理
		else if (player_->GetWorldTransform().translation_.x <= worldTransform_.translation_.x) {
			move_.x = -kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = -1.5f;
		}
	}
	////
	if (worldTransform_.translation_.x >= 49.0f && worldTransform_.translation_.z <= 70.0f) {
		worldTransform_.translation_.x = 49.0f;
		if (player_->GetWorldTransform().translation_.x >= 52.0f) {
			move_.z = kEnemySpeed_;
			move_.x = 0.0f;
			worldTransform_.rotation_.y = 0.0f;
		}
	}
	// ルーム12側の下の敷居
	if (worldTransform_.translation_.x >= 49.4f && worldTransform_.translation_.x <= 50.3f &&
	    worldTransform_.translation_.z >= 73.0f) {
		worldTransform_.translation_.z = 73.0f;
		// 右に行く処理
		if (player_->GetWorldTransform().translation_.x >= worldTransform_.translation_.x) {
			move_.x = kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = 1.5f;
		}
		// 左に行く処理
		else if (player_->GetWorldTransform().translation_.x <= worldTransform_.translation_.x) {
			move_.x = -kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = -1.5f;
		}
	}
	////
	if (worldTransform_.translation_.x >= 49.0f && worldTransform_.translation_.z >= 73.5f) {
		worldTransform_.translation_.x = 49.0f;
		if (player_->GetWorldTransform().translation_.x >= 52.0f) {
			move_.z = -kEnemySpeed_;
			move_.x = 0.0f;
			worldTransform_.rotation_.y = -3.0f;
		}
	}
	if (worldTransform_.translation_.x >= 50.3) {
		collisionType_ = ROOM12;
	}
}

void Enemy::Room11Collision() {
	if (worldTransform_.translation_.x >= 50.3 && worldTransform_.translation_.z >= 75.9f &&
	    worldTransform_.translation_.z <= 85.0f) {
		collisionType_ = ROOM12;
	}
	if (worldTransform_.translation_.z <= 77.0f) { //
		worldTransform_.translation_.z = 77.0f;
		move_.x = kEnemySpeed_;
		move_.z = 0;
		worldTransform_.rotation_.y = 1.5f;
	}
	if (worldTransform_.translation_.z >= 85.0f) { //
		worldTransform_.translation_.z = 85.0f;
	}
	// ルーム12側の上の敷居
	if (worldTransform_.translation_.x > 49.4f && worldTransform_.translation_.x < 50.3f &&
	    worldTransform_.translation_.z <= 78.8f) {
		worldTransform_.translation_.z = 78.8f;
		// 右に行く処理
		if (player_->GetWorldTransform().translation_.x >= worldTransform_.translation_.x) {
			move_.x = kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = 1.5f;
		}
		// 左に行く処理
		else if (player_->GetWorldTransform().translation_.x <= worldTransform_.translation_.x) {
			move_.x = -kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = -1.5f;
		}
	}
	////
	if (worldTransform_.translation_.x > 49.0f && worldTransform_.translation_.z <= 78.3f) {
		worldTransform_.translation_.x = 49.0f;
		move_.z = kEnemySpeed_;
		move_.x = 0.0f;
		worldTransform_.rotation_.y = 0.0f;
	}
	// ルーム12側の下の敷居
	if (worldTransform_.translation_.x > 49.4f && worldTransform_.translation_.x < 50.3f &&
	    worldTransform_.translation_.z >= 81.5f) {
		worldTransform_.translation_.z = 81.5f;
		// 右に行く処理
		if (player_->GetWorldTransform().translation_.x >= worldTransform_.translation_.x) {
			move_.x = kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = 1.5f;
		}
		// 左に行く処理
		else if (player_->GetWorldTransform().translation_.x <= worldTransform_.translation_.x) {
			move_.x = -kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = -1.5f;
		}
	}
	////
	if (worldTransform_.translation_.x > 49.0f && worldTransform_.translation_.z >= 82.0f) {
		worldTransform_.translation_.x = 49.0f;
		move_.z = -kEnemySpeed_;
		move_.x = 0.0f;
		worldTransform_.rotation_.y = -3.0f;
	}

	if (worldTransform_.translation_.x <= 35.0f) {
		worldTransform_.translation_.x = 35.0f;
	}
}

void Enemy::Room12Collision() {
	if (worldTransform_.translation_.x <= 50.3 && worldTransform_.translation_.z >= 66.5f &&
	    worldTransform_.translation_.z <= 74.9f) {
		collisionType_ = ROOM10;
	}
	if (worldTransform_.translation_.x <= 50.7f && worldTransform_.translation_.z <= 70.5f) {
		worldTransform_.translation_.x = 50.7f;
		if (player_->GetWorldTransform().translation_.x <= 47.0f) {
			move_.z = kEnemySpeed_;
			move_.x = 0.0f;
			worldTransform_.rotation_.y = 0.0f;
		}
	}
	if (worldTransform_.translation_.x <= 50.7f && worldTransform_.translation_.z >= 73.0f &&
	    worldTransform_.translation_.z <= 78.8f) {
		worldTransform_.translation_.x = 50.7f;
		if (player_->GetWorldTransform().translation_.x <= 47.0f) {
			// 上に行く処理
			if (player_->GetWorldTransform().translation_.z >= worldTransform_.translation_.z) {
				move_.z = kEnemySpeed_;
				move_.x = 0.0f;
				worldTransform_.rotation_.y = 0.0f;
			}
			// 下に行く処理
			else if (
			    player_->GetWorldTransform().translation_.z <= worldTransform_.translation_.z) {
				move_.z = -kEnemySpeed_;
				move_.x = 0.0f;
				worldTransform_.rotation_.y = -3.0f;
			}
		}
	}
	if (worldTransform_.translation_.x <= 50.7f && worldTransform_.translation_.z >= 81.5f) {
		worldTransform_.translation_.x = 50.7f;
		if (player_->GetWorldTransform().translation_.x <= 47.0f) {
			move_.z = -kEnemySpeed_;
			move_.x = 0.0f;
			worldTransform_.rotation_.y = -3.0f;
		}
	}

	if (worldTransform_.translation_.z <= 66.5f) { //
		worldTransform_.translation_.z = 66.5f;
	}
	if (worldTransform_.translation_.z >= 85.0f) { //
		worldTransform_.translation_.z = 85.0f;
	}

	// 道の左壁
	if (worldTransform_.translation_.x >= 57.4f && worldTransform_.translation_.z >= 77.0f) { //
		worldTransform_.translation_.z = 77.0f;
		// 右に行く処理
		if (player_->GetWorldTransform().translation_.x >= worldTransform_.translation_.x) {
			move_.x = kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = 1.5f;
		}
		// 左に行く処理
		else if (player_->GetWorldTransform().translation_.x <= worldTransform_.translation_.x) {
			move_.x = -kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = -1.5f;
		}
	}
	// 道の右壁
	if (worldTransform_.translation_.x >= 57.4f && worldTransform_.translation_.x <= 82.5f &&
	    worldTransform_.translation_.z <= 74.6f) { //
		worldTransform_.translation_.z = 74.6f;
		// 右に行く処理
		if (player_->GetWorldTransform().translation_.x >= worldTransform_.translation_.x) {
			move_.x = kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = 1.5f;
		}
		// 左に行く処理
		else if (player_->GetWorldTransform().translation_.x <= worldTransform_.translation_.x) {
			move_.x = -kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = -1.5f;
		}
	}
	if (worldTransform_.translation_.x >= 57.0f && worldTransform_.translation_.x <= 57.5f &&
	    worldTransform_.translation_.z >= 77.4f) { //
		worldTransform_.translation_.x = 57.0f;
		if (player_->GetWorldTransform().translation_.x >= 60.0f) {
			move_.z = -kEnemySpeed_;
			move_.x = 0.0f;
			worldTransform_.rotation_.y = -3.0f;

		}
	}
	if (worldTransform_.translation_.x >= 57.0f && worldTransform_.translation_.x <= 57.5f &&
	    worldTransform_.translation_.z <= 74.2f) { //
		worldTransform_.translation_.x = 57.0f;
		if (player_->GetWorldTransform().translation_.x >= 60.0f) {
			move_.z = kEnemySpeed_;
			move_.x = 0.0f;
			worldTransform_.rotation_.y = 0.0f;
		}
	}

	if (worldTransform_.translation_.x <= 50.3 && worldTransform_.translation_.z >= 75.9f &&
	    worldTransform_.translation_.z <= 85.0f) {
		collisionType_ = ROOM11;
	}

	if (worldTransform_.translation_.x > 82.746f && worldTransform_.translation_.z <= 77.0f &&
	    worldTransform_.translation_.z >= 74.0f) {
		collisionType_ = LOAD01;
	}
	//
	if (worldTransform_.translation_.x > 82.5f && worldTransform_.translation_.z <= 77.0f &&
	    worldTransform_.translation_.z >= 74.0f) {
		collisionType_ = LOAD01;
	}
}

void Enemy::Room15Collision() {

	if (worldTransform_.translation_.x >= 85.513f) { // 右壁
		worldTransform_.translation_.x = 85.513f;
	}
	if (worldTransform_.translation_.x <= 62.771f) { // 左壁
		worldTransform_.translation_.x = 62.771f;
		move_.z = kEnemySpeed_;
		move_.x = 0.0f;
		worldTransform_.rotation_.y = 0.0f;
	}
	if (worldTransform_.translation_.z <= -13.23f) { // 下壁
		worldTransform_.translation_.z = -13.23f;
	}

	if (worldTransform_.translation_.z >= -2.499f && worldTransform_.translation_.z <= 2.890f &&
	    worldTransform_.translation_.x >= 80.998f) { // 一番奥壁
		worldTransform_.translation_.x = 80.998f;
		// 上に行く処理
		if (player_->GetWorldTransform().translation_.z >= worldTransform_.translation_.z) {
			move_.z = kEnemySpeed_;
			worldTransform_.rotation_.y = 0.0f;
		}
		// 下に行く処理
		else if (player_->GetWorldTransform().translation_.z <= worldTransform_.translation_.z) {
			move_.z = -kEnemySpeed_;
			worldTransform_.rotation_.y = -3.0f;
		}
	}
	if (worldTransform_.translation_.z >= -3.230f && worldTransform_.translation_.x >= 81.872f &&
	    worldTransform_.translation_.x <= 86.0f) { // 一番奥壁裏
		worldTransform_.translation_.z = -3.230f;
		move_.x = -kEnemySpeed_;
		move_.z = 0;
		worldTransform_.rotation_.y = -1.5f;
	}
	if (worldTransform_.translation_.z >= -2.499f && worldTransform_.translation_.z <= 2.890f &&
	    worldTransform_.translation_.x <= 78.832f &&
	    worldTransform_.translation_.x >= 73.0f) { // 真ん中壁
		worldTransform_.translation_.x = 78.832f;
		// 上に行く処理
		if (player_->GetWorldTransform().translation_.z >= worldTransform_.translation_.z) {
			move_.z = kEnemySpeed_;
			worldTransform_.rotation_.y = 0.0f;
		}
		// 下に行く処理
		else if (player_->GetWorldTransform().translation_.z <= worldTransform_.translation_.z) {
			move_.z = -kEnemySpeed_;
			worldTransform_.rotation_.y = -3.0f;
		}
	}
	if (worldTransform_.translation_.z >= -3.230f && worldTransform_.translation_.x >= 69.788f &&
	    worldTransform_.translation_.x <= 78.288f) { // 真ん中壁裏
		worldTransform_.translation_.z = -3.230f;
		if (player_->GetWorldTransform().translation_.z >= worldTransform_.translation_.z) {
			move_.x = kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = 1.5f;
		}
		
	}
	if (worldTransform_.translation_.z >= -2.499f && worldTransform_.translation_.z <= 2.890f &&
	    worldTransform_.translation_.x >= 69.423f && worldTransform_.translation_.x <= 73.0f) { //
		worldTransform_.translation_.x = 69.423f;
		// 上に行く処理
		if (player_->GetWorldTransform().translation_.z >= worldTransform_.translation_.z) {
			move_.z = kEnemySpeed_;
			worldTransform_.rotation_.y = 0.0f;
		}
		// 下に行く処理
		else if (player_->GetWorldTransform().translation_.z <= worldTransform_.translation_.z) {
			move_.z = -kEnemySpeed_;
			worldTransform_.rotation_.y = -3.0f;
		}
	}
	if (worldTransform_.translation_.z >= -2.499f && worldTransform_.translation_.z <= 2.890f &&
	    worldTransform_.translation_.x <= 66.858f) { // 手前壁
		worldTransform_.translation_.x = 66.858f;
		// 上に行く処理
		if (player_->GetWorldTransform().translation_.z >= worldTransform_.translation_.z) {
			move_.z = kEnemySpeed_;
			worldTransform_.rotation_.y = 0.0f;
		}
		// 下に行く処理
		else if (
		    player_->GetWorldTransform().translation_.z <= worldTransform_.translation_.z &&
		    player_->GetWorldTransform().translation_.x<=60.0f) {
			move_.z = -kEnemySpeed_;
			worldTransform_.rotation_.y = -3.0f;
		}
	}
	if (worldTransform_.translation_.z >= -3.230f && worldTransform_.translation_.x <= 66.298f &&
	    worldTransform_.translation_.x >= 61.662f) { // 手前壁裏
		worldTransform_.translation_.z = -3.230f;
		move_.x = kEnemySpeed_;
		move_.z = 0;
		worldTransform_.rotation_.y = 1.5f;
	}
	

	// 部屋Load01に移動
	if (worldTransform_.translation_.z > 2.647f) {
		collisionType_ = LOAD01;
	}
}

void Enemy::Load00Collision() {
	if (worldTransform_.translation_.x >= -2.614f) { // 左壁
		worldTransform_.translation_.x = -2.614f;
		// 上に行く処理
		if (player_->GetWorldTransform().translation_.z >= worldTransform_.translation_.z) {
			move_.z = kEnemySpeed_;
			move_.x = 0.0f;
			worldTransform_.rotation_.y = 0.0f;
		}
		// 下に行く処理
		else if (player_->GetWorldTransform().translation_.z <= worldTransform_.translation_.z) {
			move_.z = -kEnemySpeed_;
			move_.x = 0.0f;
			worldTransform_.rotation_.y = -3.0f;
		}
	}
	if (worldTransform_.translation_.x <= -5.419f) { // 右壁
		worldTransform_.translation_.x = -5.419f;
		// 上に行く処理
		if (player_->GetWorldTransform().translation_.z >= worldTransform_.translation_.z) {
			move_.z = kEnemySpeed_;
			move_.x = 0.0f;
			worldTransform_.rotation_.y = 0.0f;
		}
		// 下に行く処理
		else if (player_->GetWorldTransform().translation_.z <= worldTransform_.translation_.z) {
			move_.z = -kEnemySpeed_;
			move_.x = 0.0f;
			worldTransform_.rotation_.y = -3.0f;
		}
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

void Enemy::Load01Collision() {
	if (worldTransform_.translation_.z >= 4.781f && worldTransform_.translation_.x >= 57.874f &&
	    worldTransform_.translation_.x <= 82.295f) { // 左壁
		worldTransform_.translation_.z = 4.781f;
		// 右に行く処理
		if (player_->GetWorldTransform().translation_.x >= worldTransform_.translation_.x) {
			move_.x = kEnemySpeed_;
			worldTransform_.rotation_.y = 1.5f;
			if (player_->GetWorldTransform().translation_.z >= worldTransform_.translation_.z) {
				move_.z = 0;
			}
		}
		// 左に行く処理
		else if (player_->GetWorldTransform().translation_.x <= worldTransform_.translation_.x) {
			move_.x = -kEnemySpeed_;
			worldTransform_.rotation_.y = -1.5f;
			if (player_->GetWorldTransform().translation_.z >= worldTransform_.translation_.z) {
				move_.z = 0;
			}
		}
	}
	if (worldTransform_.translation_.z <= 3.010f && worldTransform_.translation_.x >= 57.874f &&
	    worldTransform_.translation_.x <= 66.410f) { // 右壁1
		worldTransform_.translation_.z = 3.010f;
		// 右に行く処理
		if (player_->GetWorldTransform().translation_.x >= worldTransform_.translation_.x) {
			move_.x = kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = 1.5f;
		}
		// 左に行く処理
		else if (player_->GetWorldTransform().translation_.x <= worldTransform_.translation_.x) {
			move_.x = -kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = -1.5f;
		}
	}
	if (worldTransform_.translation_.z <= 3.010f && worldTransform_.translation_.x >= 69.795f &&
	    worldTransform_.translation_.x <= 78.225f) { // 右壁2
		worldTransform_.translation_.z = 3.010f;
		if (player_->GetWorldTransform().translation_.z >= worldTransform_.translation_.z &&
		    player_->GetWorldTransform().translation_.x>=60.0f) {
			move_.x = kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = 1.5f;
		}
		
	}
	if (worldTransform_.translation_.z <= 3.010f && worldTransform_.translation_.x >= 81.872f &&
	    worldTransform_.translation_.x <= 86.0f) { // 右壁3
		worldTransform_.translation_.z = 3.010f;

		    move_.x = -kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = -1.5f;
	}
	if (worldTransform_.translation_.z >= 5.813f && worldTransform_.translation_.z <= 46.173f &&
	    worldTransform_.translation_.x <= 82.746f) { // 左曲がった左壁1
		worldTransform_.translation_.x = 82.746f;
		// 上に行く処理
		if (player_->GetWorldTransform().translation_.z >= worldTransform_.translation_.z) {
			move_.z = kEnemySpeed_;
			move_.x = 0.0f;
			worldTransform_.rotation_.y = 0.0f;
		}
		// 下に行く処理
		else if (player_->GetWorldTransform().translation_.z <= worldTransform_.translation_.z) {
			move_.z = -kEnemySpeed_;
			move_.x = 0.0f;
			worldTransform_.rotation_.y = -3.0f;
		}
	}
	if (worldTransform_.translation_.z >= 49.719f && worldTransform_.translation_.z <= 74.608f &&
	    worldTransform_.translation_.x <= 82.746f) { // 左曲がった左壁2
		worldTransform_.translation_.x = 82.746f;
		// 上に行く処理
		if (player_->GetWorldTransform().translation_.z >= worldTransform_.translation_.z) {
			move_.z = kEnemySpeed_;
			move_.x = 0.0f;
			worldTransform_.rotation_.y = 0.0f;
		}
		// 下に行く処理
		else if (player_->GetWorldTransform().translation_.z <= worldTransform_.translation_.z) {
			move_.z = -kEnemySpeed_;
			move_.x = 0.0f;
			worldTransform_.rotation_.y = -3.0f;
		}
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
	// 部屋05に移動
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

void Enemy::Load02Collision() {
	if (worldTransform_.translation_.z >= 41.266f && worldTransform_.translation_.x >= 6.000f &&
	    worldTransform_.translation_.x <= 18.144f) { //
		worldTransform_.translation_.z = 41.266f;
		// 右に行く処理
		if (player_->GetWorldTransform().translation_.x >= worldTransform_.translation_.x) {
			move_.x = kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = 1.5f;
		}
		// 左に行く処理
		else if (player_->GetWorldTransform().translation_.x <= worldTransform_.translation_.x) {
			move_.x = -kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = -1.5f;
		}

	}
	if (worldTransform_.translation_.z <= 38.485f && worldTransform_.translation_.x >= 6.000f &&
	    worldTransform_.translation_.x <= 18.144f) { //
		worldTransform_.translation_.z = 38.485f;
		// 右に行く処理
		if (player_->GetWorldTransform().translation_.x >= worldTransform_.translation_.x) {
			move_.x = kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = 1.5f;
		}
		// 左に行く処理
		else if (player_->GetWorldTransform().translation_.x <= worldTransform_.translation_.x) {
			move_.x = -kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = -1.5f;
		}

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

void Enemy::Load03Collision() { // 部屋00に移動
	// 道03に移動
	if (worldTransform_.translation_.z < 49.0f) {
		collisionType_ = START;
	}
	if (worldTransform_.translation_.x <= -5.0f) { // 左壁
		worldTransform_.translation_.x = -5.0f;
	}
	if (worldTransform_.translation_.x >= -2.7f) { // 右壁
		worldTransform_.translation_.x = -2.7f;
		// 上に行く処理
		if (player_->GetWorldTransform().translation_.z >= worldTransform_.translation_.z) {
			move_.z = kEnemySpeed_;
			move_.x = 0.0f;
			worldTransform_.rotation_.y = 0.0f;
		}
		// 下に行く処理
		else if (player_->GetWorldTransform().translation_.z <= worldTransform_.translation_.z) {
			move_.z = -kEnemySpeed_;
			move_.x = 0.0f;
			worldTransform_.rotation_.y = -3.0f;
		}
	}
	if (worldTransform_.translation_.z > 62.0f) {
		collisionType_ = ROOM08;
	}
}

void Enemy::Load04Collision() {
	// 部屋05から左への道
	if (worldTransform_.translation_.x <= 58.122f && worldTransform_.translation_.x >= 53.778f &&
	    worldTransform_.translation_.z <= 39.044f) {
		worldTransform_.translation_.z = 39.044f;
	}
	//
	if (worldTransform_.translation_.z <= 45.0f && worldTransform_.translation_.z >= 33.75f &&
	    worldTransform_.translation_.x <= 50.792f) {
		worldTransform_.translation_.x = 50.792f;
		if (player_->GetWorldTransform().translation_.x <= 45.0f) {

			move_.z = -kEnemySpeed_;
			move_.x = 0.0f;
			worldTransform_.rotation_.y = -3.0f;
		}
	}
	if (worldTransform_.translation_.z >= 29.0f && worldTransform_.translation_.z <= 38.329f &&
	    worldTransform_.translation_.x >= 53.324f) {
		worldTransform_.translation_.x = 53.324f;
		if (player_->GetWorldTransform().translation_.x>=58.0f) {

			move_.z = kEnemySpeed_;
			move_.x = 0.0f;
			worldTransform_.rotation_.y = 0.0f;
		}
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

void Enemy::Load05Collision() {
	if (worldTransform_.translation_.x < 13.8f) {
		collisionType_ = ROOM08;
	}
	if (worldTransform_.translation_.z <= 75.0f) {
		worldTransform_.translation_.z = 75.0f;
		// 右に行く処理
		if (player_->GetWorldTransform().translation_.x >= worldTransform_.translation_.x) {
			move_.x = kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = 1.5f;
		}
		// 左に行く処理
		else if (player_->GetWorldTransform().translation_.x <= worldTransform_.translation_.x) {
			move_.x = -kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = -1.5f;
		}
	}
	if (worldTransform_.translation_.z >= 77.3f) {
		worldTransform_.translation_.z = 77.3f;
		// 右に行く処理
		if (player_->GetWorldTransform().translation_.x >= worldTransform_.translation_.x) {
			move_.x = kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = 1.5f;
		}
		// 左に行く処理
		else if (player_->GetWorldTransform().translation_.x <= worldTransform_.translation_.x) {
			move_.x = -kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = -1.5f;
		}
	}
	if (worldTransform_.translation_.x > 22.0f) {
		collisionType_ = ROOM09;
	}
}

void Enemy::Load06Collision() {
	// 左壁
	if (worldTransform_.translation_.z <= 30.528f) {
		worldTransform_.translation_.z = 30.528f;
	}
	if (worldTransform_.translation_.x <= 50.378f && worldTransform_.translation_.x >= 37.378f &&
	    worldTransform_.translation_.z >= 33.137f) {
		worldTransform_.translation_.z = 33.137f;
		// 右に行く処理
		if (player_->GetWorldTransform().translation_.x >= worldTransform_.translation_.x) {
			move_.x = kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = 1.5f;
		}
		// 左に行く処理
		else if (player_->GetWorldTransform().translation_.x <= worldTransform_.translation_.x) {
			move_.x = -kEnemySpeed_;
			move_.z = 0;
			worldTransform_.rotation_.y = -1.5f;
		}
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

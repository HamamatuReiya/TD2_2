#include "Enemy.h"

void Enemy::Initialize(Model* model) {
	model_ = model;
	worldTransform_.Initialize();
	move_ = {0, 0, 0};
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = {0.0f, 0.7f, 15.0f};
	kEnemySpeed_ = 0.1f;
	encountFlag = false;
	phase_ = phase1;
	move_.z = kEnemySpeed_;
	move_.x = kEnemySpeed_;
}

void Enemy::Update() { 
	switch (phase_) {
	case Enemy::phase1:
		
		move_.z -= 0.001f;
		if (move_.z < -0.1) {
			move_.z = float( - 0.1);
			move_.x = 0;
		}
		
		break;
	case Enemy::phase2:
		kEnemySpeed_ = 0.34f;
		break;
	case Enemy::phase3:
		kEnemySpeed_ = 0.38f;
		break;
	}
	
	if (move_.z != 0 || move_.y != 0) {
		worldTransform_.rotation_.y = std::atan2(move_.x, move_.z);
	}
	move_ = Multiply(kEnemySpeed_, Normalize(move_));
	worldTransform_.translation_ = Add(worldTransform_.translation_, move_);
	worldTransform_.UpdateMatrix(); 
}

void Enemy::Draw(ViewProjection& viewProjection) { model_->Draw(worldTransform_, viewProjection); }

void Enemy::Search(Vector3 move) {
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);
}

void Enemy::Chase(Vector3 move) {
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);
}

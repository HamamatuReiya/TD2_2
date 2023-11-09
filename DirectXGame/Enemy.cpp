#include "Enemy.h"

void Enemy::Initialize(Model* model) {
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = {0.0f, 0.7f, 15.0f};
	kEnemySpeed_ = 0.05f;
}

void Enemy::Update() { 
	
	Search(move_);
	if (move_.z != 0 || move_.y != 0) {
		worldTransform_.rotation_.y = std::atan2(move_.x, move_.z);
	}
	worldTransform_.UpdateMatrix(); }

void Enemy::Draw(ViewProjection& viewProjection) { model_->Draw(worldTransform_, viewProjection); }

void Enemy::Search(Vector3 move) {
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);
}

void Enemy::Chase(Vector3 move) {
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);
}

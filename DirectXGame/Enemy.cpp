#include "Enemy.h"
#include"ImGuiManager.h"

void Enemy::Initialize(Model* model) {
	model_ = model;
	worldTransform_.Initialize();
	move_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = {0.0f, 0.7f, 15.0f};
	encountFlag = false;
	kEnemySpeed_ = 0.3f;
	phase_ = phase1;
}

void Enemy::Update() { 
	switch (phase_) {
	case Enemy::phase1:
		kEnemySpeed_ += 0.05f;
		move_.z = kEnemySpeed_;
		
		break;
	case Enemy::phase2:
		kEnemySpeed_ = 0.34f;
		break;
	case Enemy::phase3:
		kEnemySpeed_ = 0.38f;
		break;
	}

	float enemyMove[2] = {move_.x, move_.z};
	ImGui::Begin("EnemyMove");
	ImGui::SliderFloat2("EnemyMove", enemyMove, -0.3f, 0.3f);
	ImGui::End();
	move_.x = enemyMove[0];
	move_.z = enemyMove[1];

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

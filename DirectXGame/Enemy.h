#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Mymath.h"

class Enemy {
public:
	void Initialize(Model* model);

	void Update();

	void Draw(ViewProjection& viewProjection);

	void Search(Vector3 move);

	void Chase(Vector3 move);

private:

	enum Phase {
		phase1,
		phase2,
		phase3,
	};

	Phase phase_;

	bool encountFlag;

	WorldTransform worldTransform_;

	ViewProjection viewProjection_;

	Model* model_ = nullptr;

	float kEnemySpeed_;

	Vector3 move_;

	Vector3 moveRotate_;
};

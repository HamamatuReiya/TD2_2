#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Mymath.h"
#include <math.h>

class Player;

class Enemy {
public:
	void Initialize(Model* model);

	void Update();

	void Draw(ViewProjection& viewProjection);

	void Homing(float enemySpeed);

	void SetPlayer(Player* player) { player_ = player; }

	Vector3 GetWorldPosition();

private:
	enum Phase {
		phase1,
		phase2,
		phase3,
	};
	Phase phase_;

	enum State {
		search,
		Chase,
		posReset,
	};
	State phase1State;
	State phase2State;
	State phase3State;

	enum Phase1Move {
		move1,
		move2,
		move3,
		move4,
		move5,
		move6
	};

	Phase1Move phase1Move;
	bool flag = false;

private:

	bool phase1SpeedFlag=true;

	bool encountFlag;

	WorldTransform worldTransform_;

	ViewProjection viewProjection_;

	Model* model_ = nullptr;

	float kEnemySpeed_;

	float rotateSpeed_;

	Vector3 move_ = {0.0f,0.0f,0.0f};

	Vector3 moveRotate_;

	Player* player_ = nullptr;

};

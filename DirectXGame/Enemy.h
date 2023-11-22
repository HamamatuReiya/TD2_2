#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Mymath.h"
#include <math.h>

class Player;

class Enemy {
public:
	void Initialize(
	    Model* model, Model* model2, Model* model3, Model* model4, Model* model5,
	    Model* model6, Model* model7, Model* model8, Model* model9, Model* model10, Model* model11,
	    Model* model12, Model* model13, Model* model14, Model* model15);

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
		move6,
		move7,
		move8,
		move9,
		move10,
		move11,
		move12,
		move13,
		move14,
		move15,
		move16,
		move17,
		move18,
		move19,
		move20,
		move21,
		move22,
		move23,
		move24,
		move25,
		move26,
		move27,
		move28,
		move29,
		move30,
		move31,
		move32,
		move33,
		move34,
		move35,
		move36,
	};

	Phase1Move phase1Move;
	bool state1Flag1 = false;
	bool state1Flag2 = false;
	bool state1Flag3 = false;
	bool state1Flag4 = false;
	bool state1Flag5 = false;
	bool state1Flag6 = false;

	// ïîâÆä÷êî
	void StartRoomCollision();
	void Room00Collision();
	void Room01Collision();
	void Room02Collision();
	void Room03Collision();
	void Room04Collision();
	void Room05Collision();
	void Room06Collision();
	void Room07Collision();
	void Room08Collision();
	void Room09Collision();
	void Room10Collision();
	// ìπä÷êî
	void Load00Collision();
	void Load01Collision();
	void Load02Collision();

private:

	bool phase1SpeedFlag=true;

	bool encountFlag;

	WorldTransform worldTransform_;

	ViewProjection viewProjection_;

	Model* model_ = nullptr;
	Model* model2_ = nullptr;
	Model* model3_ = nullptr;
	Model* model4_ = nullptr;
	Model* model5_ = nullptr;
	Model* model6_ = nullptr;
	Model* model7_ = nullptr;
	Model* model8_ = nullptr;
	Model* model9_ = nullptr;
	Model* model10_ = nullptr;
	Model* model11_ = nullptr;
	Model* model12_ = nullptr;
	Model* model13_ = nullptr;
	Model* model14_ = nullptr;
	Model* model15_ = nullptr;

	float kEnemySpeed_;

	float rotateSpeed_;

	Vector3 move_ = {0.0f,0.0f,0.0f};

	Vector3 moveRotate_;

	Player* player_ = nullptr;

};

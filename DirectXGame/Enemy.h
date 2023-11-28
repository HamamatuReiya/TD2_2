#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Mymath.h"
#include <math.h>
#include "Sprite.h"
#include"ViewProjection.h"

class Player;

class Key;

enum State {
	search,
	Chase,
	direction,
};

class Enemy {
public:
	void Initialize(
	    Model* model, Model* model2, Model* model3, Model* model4, Model* model5,
	    Model* model6, Model* model7, Model* model8, Model* model9, Model* model10, Model* model11,
	    Model* model12, Model* model13, Model* model14, Model* model15);

	void Update();

	void Draw(ViewProjection& viewProjection);

	void EfectDraw();

	void Homing(float enemySpeed);

	void SetPlayer(Player* player) { player_ = player; }

	Vector3 GetWorldPosition();

	State Getphase1State() { return phase1State; }

	WorldTransform& GetWorldTransform() { return worldTransform_; };

	Vector3 SetTranslation(Vector3 translation) { worldTransform_.translation_ = translation; }

	void SetEnemySpeed(float kEnemySpeed) {kEnemySpeed_ = kEnemySpeed; }

	float GetEnemySpeed() { return kEnemySpeed_; }

	void EncountMove1();
	void EncountMove2();
	void EncountMove3();
	void EncountMove4();
	void EncountMove5();
	void EncountMove6();
	void EncountMove7();
	void EncountMove8();
	void EncountMove9();

	bool GetEncountMove1Flag() { return encountMove1; }
	bool GetEncountMove2Flag() { return encountMove2; }
	bool GetEncountMove3Flag() { return encountMove3; }
	bool GetEncountMove4Flag() { return encountMove4; }
	bool GetEncountMove5Flag() { return encountMove5; }
	bool GetEncountMove6Flag() { return encountMove6; }
	bool GetEncountMove7Flag() { return encountMove7; }
	bool GetEncountMove8Flag() { return encountMove8; }
	bool GetEncountMove9Flag() { return encountMove9; }

	bool GetSetStateFlag1() { return setStateFlag1; }
	bool GetSetStateFlag2() { return setStateFlag2; }
	bool GetSetStateFlag3() { return setStateFlag3; }
	bool GetSetStateFlag4() { return setStateFlag4; }
	bool GetSetStateFlag5() { return setStateFlag5; }
	bool GetSetStateFlag6() { return setStateFlag6; }
	bool GetSetStateFlag7() { return setStateFlag7; }
	bool GetSetStateFlag8() { return setStateFlag8; }
	bool GetSetStateFlag9() { return setStateFlag9; }

	void SetStateFlag1(bool setStateFlag1_) { setStateFlag1 = setStateFlag1_; }
	void SetStateFlag2(bool setStateFlag2_) { setStateFlag2 = setStateFlag2_; }
	void SetStateFlag3(bool setStateFlag3_) { setStateFlag3 = setStateFlag3_; }
	void SetStateFlag4(bool setStateFlag4_) { setStateFlag4 = setStateFlag4_; }
	void SetStateFlag5(bool setStateFlag5_) { setStateFlag5 = setStateFlag5_; }
	void SetStateFlag6(bool setStateFlag6_) { setStateFlag6 = setStateFlag6_; }
	void SetStateFlag7(bool setStateFlag7_) { setStateFlag7 = setStateFlag7_; }
	void SetStateFlag8(bool setStateFlag8_) { setStateFlag8 = setStateFlag8_; }
	void SetStateFlag9(bool setStateFlag9_) { setStateFlag9 = setStateFlag9_; }

	void SetState(State state) { phase1State = state; }

	void SetViewProjection(const ViewProjection* viewProjection) {
		viewProjection_ = viewProjection;
	}

	void PhaseCollision();

	bool GetEnemyVisibilityX() { return enemyVisibilityXFlag; }
	bool GetEnemyVisibility_X() { return enemyVisibility_XFlag; }
	bool GetEnemyVisibilityZ() { return enemyVisibilityZFlag; }
	bool GetEnemyVisibility_Z() { return enemyVisibility_ZFlag; }

	void PosReset1();
	void PosReset2();
	void PosReset3();
	void PosReset4();
									   
private:							   
	enum Phase {					   
		phase1,
		phase2,
		phase3,
	};
	Phase phase_;

	
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

	enum CollisionType {
		START,  // スタート地点の部屋(0)
		LOAD00, // スタート地点から右の道(1)
		ROOM00, // 右の部屋(2)
		ROOM01, // 右の部屋の隣(3)
		ROOM02, // 右の部屋の隣(4)
		ROOM03, // 右の部屋の隣(5)
		ROOM04, // (6)
		ROOM05,
		ROOM06,
		ROOM07,
		ROOM08,
		ROOM09,
		ROOM10,
		ROOM11,
		ROOM12,
		ROOM13,
		ROOM14,
		ROOM15,
		ROOM16,
		ROOM17,
		ROOM18,
		LOAD01,
		LOAD02,
		LOAD03,
		LOAD04,
		LOAD05,
		LOAD06,
	};

	// 部屋関数
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
	void Room11Collision();
	void Room12Collision();
	void Room13Collision();
	void Room14Collision();
	void Room15Collision();
	// 道関数
	void Load00Collision();
	void Load01Collision();
	void Load02Collision();
	void Load03Collision();
	void Load04Collision();
	void Load05Collision();
	void Load06Collision();

	

private:

	Sprite* efectSprite_ = nullptr;
	uint32_t efectTexture_ = 0;

	bool setStateFlag1 = true;
	bool setStateFlag2 = true;
	bool setStateFlag3 = true;
	bool setStateFlag4 = true;
	bool setStateFlag5 = true;
	bool setStateFlag6 = true;
	bool setStateFlag7 = true;
	bool setStateFlag8 = true;
	bool setStateFlag9 = true;

	bool encountMove1 = true;
	bool encountMove2 = true;
	bool encountMove3 = true;
	bool encountMove4 = true;
	bool encountMove5 = true;
	bool encountMove6 = true;
	bool encountMove7 = true;
	bool encountMove8 = true;
	bool encountMove9 = true;

	bool enemyVisibilityXFlag = false;
	bool enemyVisibility_XFlag = false;
	bool enemyVisibilityZFlag = false;
	bool enemyVisibility_ZFlag = false;

	bool phase1SpeedFlag=true;

	bool encountFlag;

	int phaseSwitchCount = 300;

	WorldTransform worldTransform_;

	// ビュープロジェクション
	const ViewProjection* viewProjection_ = nullptr;

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
	Key* key_ = nullptr;

	CollisionType collisionType_;

};

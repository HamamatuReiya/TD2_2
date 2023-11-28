#include "Key.h"
#include "ImGuiManager.h"

void Key::Initialize(Model* keyupModel, Model* keydownModel, Model* hummerModel) {
	//鍵モデル
	keyupModel_ = keyupModel;
	keydownModel_ = keydownModel;
	hummerModel_ = hummerModel;
	Keynumber = 0;
	for (int i = 0; i < 3; i++) {
		worldTransform_[i].Initialize();
		worldTransform_[i].scale_ = {0.5f, 0.5f, 0.5f};
		worldTransform_[i].rotation_ = {0.0f, -45.0f, 0.0f};
		worldTransform_[i].translation_ = {0.0f, -1.5f, 0.0f};
	}
	//// 乱数の初期化(シード値の設定)
	srand((unsigned int)time(nullptr));
	RandTime_ = 0;
	isHummerDead_ = false;
	isKeyUpDead_ = false;
	isKeyDownDead_ = false;
}

void Key::Update() {
	// ランダム
	Keynumber = {static_cast<float>(rand() % 3 + 1)};
	RandTime_++;
	if (RandTime_ > 0 && RandTime_ <= 5) {
		if (Keynumber == 1) {
			worldTransform_[0].translation_ = {13.5f, 1.5f, 19.4f};
			worldTransform_[1].translation_ = {32.4f, 1.5f, 40.8f};
			worldTransform_[2].translation_ = {11.3f, 1.5f, 67.65f};
		}
		if (Keynumber == 2) {
			worldTransform_[0].translation_ = {41.5, 1.5f, 9.45f};
			worldTransform_[1].translation_ = {75.6f, 1.5f, -11.95f};
			worldTransform_[2].translation_ = {52.8f, 1.5f, 81.35f};
		}
		if (Keynumber == 3) {
			worldTransform_[0].translation_ = {11.7f, 1.5f, -8.65f};
			worldTransform_[1].translation_ = {7.3f, 1.5f, 6.0f};
			worldTransform_[2].translation_ = {25.6f, 1.5f, 80.85f};
		}
	}
	for (int i = 0; i < 3; i++) {
		// 行列の更新
		worldTransform_[i].UpdateMatrix();
	}
	//// 画面の座標を表示
	//ImGui::Begin("Item");
	//ImGui::Text("%f",Keynumber);
	//ImGui::Text("%d\n%d\n%d\n", isKeyDead_, isKeyUpDead_, isKeyDownDead_);
	//ImGui::End();
}

void Key::Draw(ViewProjection& viewProjection) {
	if (isHummerDead_ == false) {
		keyupModel_->Draw(worldTransform_[0], viewProjection);
	}
	if (isKeyUpDead_ == false) {
		keydownModel_->Draw(worldTransform_[1], viewProjection);
	}
	if (isKeyDownDead_ == false) {
		hummerModel_->Draw(worldTransform_[2], viewProjection);
	}
}

void Key::OnKeyCollision() { isHummerDead_ = true; }
void Key::OnKeyUpCollision() { isKeyUpDead_ = true; }
void Key::OnKeyDownCollision() { isKeyDownDead_ = true; }

Vector3 Key::GetKeyWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_[0].matWorld_.m[3][0];
	worldPos.y = worldTransform_[0].matWorld_.m[3][1];
	worldPos.z = worldTransform_[0].matWorld_.m[3][2];

	return worldPos;
}
Vector3 Key::GetKeyUpWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_[1].matWorld_.m[3][0];
	worldPos.y = worldTransform_[1].matWorld_.m[3][1];
	worldPos.z = worldTransform_[1].matWorld_.m[3][2];

	return worldPos;
}
Vector3 Key::GetKeyDownWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_[2].matWorld_.m[3][0];
	worldPos.y = worldTransform_[2].matWorld_.m[3][1];
	worldPos.z = worldTransform_[2].matWorld_.m[3][2];

	return worldPos;
}

//Vector3 Item::GetKeyWorldPosition(int index) {
//	Vector3 worldPos;
//	worldPos.x = worldTransform_[index].matWorld_.m[3][0];
//	worldPos.y = worldTransform_[index].matWorld_.m[3][1];
//	worldPos.z = worldTransform_[index].matWorld_.m[3][2];
//
//	return worldPos;
//}

//for (int i = 0; i < 3; i++) {
//	GetKeyWorldPosition(i).x;
//	if (collision) {
//		OnCollision(i);
//	}
//}


#include "Item.h"
#include "ImGuiManager.h"

void Item::Initialize(Model* keyupModel, Model* keydownModel, Model* keymoldModel) {
	//鍵モデル
	keyupModel_ = keyupModel;
	keydownModel_ = keydownModel;
	keymoldModel_ = keymoldModel;
	for (int i = 0; i < 3; i++) {
		worldTransform_[i].Initialize();
		worldTransform_[i].scale_ = {1.0f, 1.0f, 1.0f};
		worldTransform_[i].rotation_ = {0.0f, -45.0f, 0.0f};
		worldTransform_[i].translation_ = {0.0f, -1.5f, 0.0f};
	}
	//// 乱数の初期化(シード値の設定)
	srand((unsigned int)time(nullptr));
}

void Item::Update() {
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
	// 画面の座標を表示
	ImGui::Begin("Item");
	ImGui::Text("%f",Keynumber);
	ImGui::End();
}

void Item::Draw(ViewProjection& viewProjection) {
	if (isKeyDead_ == false) {

		keyupModel_->Draw(worldTransform_[0], viewProjection);
	}
	if (isKeyUpDead_ == false) {
		keydownModel_->Draw(worldTransform_[1], viewProjection);
	}
	if (isKeyDownDead_ == false) {
		keymoldModel_->Draw(worldTransform_[2], viewProjection);
	}
}

void Item::OnKeyCollision() { isKeyDead_ = true; }
void Item::OnKeyUpCollision() { isKeyUpDead_ = true; }
void Item::OnKeyDownCollision() { isKeyDownDead_ = true; }

Vector3 Item::GetWorldPosition() {
	Vector3 worldPos;
	for (int i = 0; i < 3; i++) {
		worldPos.x = worldTransform_[i].matWorld_.m[3][0];
		worldPos.y = worldTransform_[i].matWorld_.m[3][1];
		worldPos.z = worldTransform_[i].matWorld_.m[3][2];
	}

	return worldPos;
}


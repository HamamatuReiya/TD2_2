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
		worldTransform_[i].translation_ = {0.0f, -1.0f, 0.0f};
	}
	//// 乱数の初期化(シード値の設定)
	srand((unsigned int)time(nullptr));
}

void Item::Update() {
	// ランダム
	Keynumber = {static_cast<float>(rand() % 3 + 1)};
	RandTime_++;
	if (RandTime_ > 0 && RandTime_ <= 30) {
		if (Keynumber == 1) {
			worldTransform_[0].translation_ = {-2.0f, -1.0f, 2.0f};
			worldTransform_[1].translation_ = {0.0f, -1.0f, 2.0f};
			worldTransform_[2].translation_ = {2.0f, -1.0f, 2.0f};
		}
		if (Keynumber == 2) {
			worldTransform_[0].translation_ = {-4.0f, -1.0f, 0.0f};
			worldTransform_[1].translation_ = {0.0f, -1.0f, 0.0f};
			worldTransform_[2].translation_ = {4.0f, -1.0f, 0.0f};
		}
		if (Keynumber == 3) {
			worldTransform_[0].translation_ = {-6.0f, -1.0f, -2.0f};
			worldTransform_[1].translation_ = {0.0f, -1.0f, -2.0f};
			worldTransform_[2].translation_ = {6.0f, -1.0f, -2.0f};
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
	for (int i = 0; i < 3; i++) {
		keyupModel_->Draw(worldTransform_[0], viewProjection);
		keydownModel_->Draw(worldTransform_[1], viewProjection);
		keymoldModel_->Draw(worldTransform_[2], viewProjection);
	}
}



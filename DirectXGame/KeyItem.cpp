#include "KeyItem.h"

void KeyItem::Initialize(Model* model) 
{
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.rotation_ = {0.0f, -45.0f, 0.0f};
	worldTransform_.translation_ = {0.0f, -1.0f, 0.0f};
}

void KeyItem::Update() {
	//鍵の配置
	if (itemType_ == KEYCRAFT){
		void KeyCraftUpdate();
		void KeyCraftDraw();
	}


	// 行列の更新
	worldTransform_.UpdateMatrix();
}

void KeyItem::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection); 
}

// 鍵作成エリア
void KeyItem::KeyCraftUpdate() {}

void KeyItem::KeyCraftDraw() {}
// 鍵上の部分
void KeyItem::KeyUpUpdate() {}

void KeyItem::KeyUpDraw() {}
// 鍵下の部分
void KeyItem::KeyDownUpdate() {}

void KeyItem::KeyDownDraw() {}
// 鍵の型
void KeyItem::KeyMoldUpdate() {}

void KeyItem::KeymoldDraw() {}

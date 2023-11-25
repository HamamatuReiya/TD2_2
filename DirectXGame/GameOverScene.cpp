#include "GameOverScene.h"

GameOverScene::GameOverScene() {}

GameOverScene::~GameOverScene() { delete spriteGameOver_; }

void GameOverScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	/*audio_ = Audio::GetInstance();*/

	// テクスチャ
	 uint32_t textureGameOver = TextureManager::Load("GameOver.png");

	// スプライト生成
	 spriteGameOver_ =
	     Sprite::Create(textureGameOver, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});

	// BGM
	/*bgmDataHandle_ = audio_->LoadWave("BGM/BGM.mp3");
	bgmHandle_ = audio_->PlayWave(bgmDataHandle_, false, 0.15f);*/
}

void GameOverScene::Update() {
	if (input_->TriggerKey(DIK_RETURN)) {
		isSceneEnd = true;
	}
}

void GameOverScene::Draw() {
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	spriteGameOver_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameOverScene::sceneReset() {
	isSceneEnd = false;
	// BGMの停止
	// audio_->StopWave(bgmHandle_);
}

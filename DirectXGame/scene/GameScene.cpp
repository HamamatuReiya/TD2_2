#include "GameScene.h"
#include "AxisIndicator.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// 3Dモデル生成
	model_.reset(Model::Create());
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

	// デバックカメラの生成
	debugCamera_ = std::make_unique<DebugCamera>(1280, 720);

	// 軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	// 自キャラの生成
	player_ = std::make_unique<Player>();
	// 3Dモデルの生成
	playerModel_.reset(Model::CreateFromOBJ("Player", true));

	// 自キャラの初期化
	player_->Initialize(playerModel_.get());

	// 敵キャラの生成
	enemy_ = std::make_unique<Enemy>();
	// モデルの生成
	enemyModel_.reset(Model::CreateFromOBJ("Robot", true));
	// モデルの生成
	enemyModel2_.reset(Model::CreateFromOBJ("Robot2", true));
	// モデルの生成
	enemyModel3_.reset(Model::CreateFromOBJ("Robot3", true));
	// モデルの生成
	enemyModel4_.reset(Model::CreateFromOBJ("Robot4", true));
	// モデルの生成
	enemyModel5_.reset(Model::CreateFromOBJ("Robot5", true));
	// モデルの生成
	enemyModel6_.reset(Model::CreateFromOBJ("Robot6", true));
	// モデルの生成
	enemyModel7_.reset(Model::CreateFromOBJ("Robot7", true));
	// モデルの生成
	enemyModel8_.reset(Model::CreateFromOBJ("Robot8", true));
	// モデルの生成
	enemyModel9_.reset(Model::CreateFromOBJ("Robot9", true));
	// モデルの生成
	enemyModel10_.reset(Model::CreateFromOBJ("Robot10", true));
	// モデルの生成
	enemyModel11_.reset(Model::CreateFromOBJ("Robot11", true));
	// モデルの生成
	enemyModel12_.reset(Model::CreateFromOBJ("Robot12", true));
	// モデルの生成
	enemyModel13_.reset(Model::CreateFromOBJ("Robot13", true));
	// モデルの生成
	enemyModel14_.reset(Model::CreateFromOBJ("Robot14", true));
	// モデルの生成
	enemyModel15_.reset(Model::CreateFromOBJ("Robot15", true));
	// 初期化
	enemy_->Initialize(
	    enemyModel_.get(), enemyModel2_.get(), enemyModel3_.get(), enemyModel4_.get(),
	    enemyModel5_.get(), enemyModel6_.get(), enemyModel7_.get(), enemyModel8_.get(),
	    enemyModel9_.get(), enemyModel10_.get(), enemyModel11_.get(), enemyModel12_.get(),
	    enemyModel13_.get(), enemyModel14_.get(), enemyModel15_.get() );

	// 追従カメラの生成
	followCamera_ = std::make_unique<FollowCamera>();
	followCamera_->Initialize();

	// 自キャラのワールドトランスフォームを追従カメラにセット
	followCamera_->SetTarget(&player_->GetWorldTransform());
	// Player&followCamera
	player_->SetViewProjection(&followCamera_->GetViewProjection());

	// 地面の生成
	ground_ = std::make_unique<Ground>();
	// 3Dモデルの生成
	groundModel_.reset(Model::CreateFromOBJ("ground", true));
	// 地面の初期化
	ground_->Initialize(groundModel_.get());

	// 鍵の生成
	Key_ = std::make_unique<Key>();
	// 3Dモデルの生成
	KeyModel_.reset(Model::CreateFromOBJ("key", true));
	// 3Dモデルの生成
	KeyUpModel_.reset(Model::CreateFromOBJ("KeyUp", true));
	// 3Dモデルの生成
	KeyDownModel_.reset(Model::CreateFromOBJ("KeyDown", true));
	// 鍵の初期化
	Key_->Initialize(KeyModel_.get(), KeyUpModel_.get(), KeyDownModel_.get());

	//部屋の生成,初期化
	RoomInitialize();

	//道の生成,初期化
	LoadInitialize();

}

void GameScene::Update() {
	CameraUpdate();
	player_->Update();
	enemy_->SetPlayer(player_.get());
	enemy_->Update();
	Key_->Update();
	//部屋の更新
	RoomUpdate();
	//道の更新
	LoadUpdate();

	CheakCollisions();
}

void GameScene::Draw() {

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
	player_->Draw(viewProjection_);
	ground_->Draw(viewProjection_);
	enemy_->Draw(viewProjection_);
	Key_->Draw(viewProjection_);
	//部屋の描画
	RoomDraw();
	//道の描画
	LoadDraw();

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
void GameScene::sceneReset() {
	// シーンの切り替えフラグ
	isSceneEnd = false;
	//// プレイヤーの体力

	//// BGMの停止
	// audio_->StopWave(bgmHandle_);
	// bgmHandle_ = audio_->PlayWave(bgmDataHandle_, true, 0.15f);
}

void GameScene::CheakCollisions() {
	// 判定対象AとBの座標
	Vector3 posA, posB,posC,posD;

	// 2間点の距離(自キャラと鍵の当たり判定)
	float posAB;
	float posAC;
	float posAD;

	// 自キャラの半径
	float playerRadius = 2.0f;
	// 鍵の半径
	float keyRadius = 1.0f;
	// 鍵の半径
	float keyUpRadius = 1.0f;
	// 鍵の半径
	float keyDounRadius = 1.0f;

#pragma region 自キャラと鍵の当たり判定
	// 自キャラのワールド座標
	posA = player_->GetWorldPosition();
	// 鍵上の座標
	posB = Key_->GetKeyUpWorldPosition();
	// 鍵型の座標
	posC = Key_->GetKeyWorldPosition();
	// 鍵下の座標
	posD = Key_->GetKeyDownWorldPosition();
	// AとBの距離を求める
	posAB = (posB.x - posA.x) * (posB.x - posA.x) + (posB.y - posA.y) * (posB.y - posA.y) +
	        (posB.z - posA.z) * (posB.z - posA.z);
	// プレイヤーと上鍵の当たり判定
	if (posAB <= (playerRadius + keyUpRadius) * (playerRadius + keyUpRadius)) {
		// 自キャラの衝突時コールバックを呼び出す
		player_->OnCollision();
		// 鍵の衝突時コールバックを呼び出す
		Key_->OnKeyUpCollision();
	}
	// AとCの距離を求める
	posAC = (posC.x - posA.x) * (posC.x - posA.x) + (posC.y - posA.y) * (posC.y - posA.y) +
	        (posC.z - posA.z) * (posC.z - posA.z);
	// プレイヤーと鍵型の当たり判定
	if (posAC <= (playerRadius + keyRadius) * (playerRadius + keyRadius)) {
		// 自キャラの衝突時コールバックを呼び出す
		player_->OnCollision();
		// 鍵の衝突時コールバックを呼び出す
		Key_->OnKeyCollision();
	}
	// AとDの距離を求める
	posAD = (posD.x - posA.x) * (posD.x - posA.x) + (posD.y - posA.y) * (posD.y - posA.y) +
	        (posD.z - posA.z) * (posD.z - posA.z);
	// プレイヤーと下鍵の当たり判定
	if (posAD <= (playerRadius + keyDounRadius) * (playerRadius + keyDounRadius)) {
		// 自キャラの衝突時コールバックを呼び出す
		player_->OnCollision();
		// 鍵の衝突時コールバックを呼び出す
		Key_->OnKeyDownCollision();
	}
#pragma endregion
}

void GameScene::CameraUpdate() {

#ifdef _DEBUG
	if (input_->TriggerKey(DIK_C)) {
		isDebugCameraActive_ = true;
	} else if (input_->TriggerKey(DIK_B)) {
		isDebugCameraActive_ = false;
	}
#endif
	if (isDebugCameraActive_) {
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();
	} else {
		// 追従カメラの更新
		followCamera_->Update();
		viewProjection_.matProjection = followCamera_->GetViewProjection().matProjection;
		viewProjection_.matView = followCamera_->GetViewProjection().matView;

		viewProjection_.TransferMatrix();
	}

}

void GameScene::RoomInitialize() {
	// 部屋00の生成
	Room_00_ = std::make_unique<Room>();
	// 3Dモデルの生成
	RoomModel_R_00.reset(Model::CreateFromOBJ("Stage", true));

	// 部屋01の生成
	Room_01_ = std::make_unique<Room>();
	// 3Dモデルの生成
	RoomModel_R_01.reset(Model::CreateFromOBJ("Stage1", true));

	// 部屋02の生成
	Room_02_ = std::make_unique<Room>();
	// 3Dモデルの生成
	RoomModel_R_02.reset(Model::CreateFromOBJ("Stage2", true));

	// 部屋03の生成
	Room_03_ = std::make_unique<Room>();
	// 3Dモデルの生成
	RoomModel_R_03.reset(Model::CreateFromOBJ("Stage3", true));

	// 部屋04の生成
	Room_04_ = std::make_unique<Room>();
	// 3Dモデルの生成
	RoomModel_R_04.reset(Model::CreateFromOBJ("Stage4", true));

	// 部屋05の生成
	Room_05_ = std::make_unique<Room>();
	// 3Dモデルの生成
	RoomModel_R_05.reset(Model::CreateFromOBJ("Stage5", true));

	// 部屋06の生成
	Room_06_ = std::make_unique<Room>();
	// 3Dモデルの生成
	RoomModel_R_06.reset(Model::CreateFromOBJ("Stage6", true));

	// 部屋00の初期化
	Room_00_->Initialize(
	    RoomModel_R_00.get(), RoomModel_R_01.get(), RoomModel_R_02.get(), RoomModel_R_03.get(),
	    RoomModel_R_04.get(), RoomModel_R_05.get(), RoomModel_R_06.get());

	// 部屋01の初期化
	Room_01_->Initialize(
	    RoomModel_R_00.get(), RoomModel_R_01.get(), RoomModel_R_02.get(), RoomModel_R_03.get(),
	    RoomModel_R_04.get(), RoomModel_R_05.get(), RoomModel_R_06.get());

	// 部屋02の初期化
	Room_02_->Initialize(
	    RoomModel_R_00.get(), RoomModel_R_01.get(), RoomModel_R_02.get(), RoomModel_R_03.get(),
	    RoomModel_R_04.get(), RoomModel_R_05.get(), RoomModel_R_06.get());

	// 部屋03の初期化
	Room_03_->Initialize(
	    RoomModel_R_00.get(), RoomModel_R_01.get(), RoomModel_R_02.get(), RoomModel_R_03.get(),
	    RoomModel_R_04.get(), RoomModel_R_05.get(), RoomModel_R_06.get());

	// 部屋04の初期化
	Room_04_->Initialize(
	    RoomModel_R_00.get(), RoomModel_R_01.get(), RoomModel_R_02.get(), RoomModel_R_03.get(),
	    RoomModel_R_04.get(), RoomModel_R_05.get(), RoomModel_R_06.get());

	// 部屋05の初期化
	Room_05_->Initialize(
	    RoomModel_R_00.get(), RoomModel_R_01.get(), RoomModel_R_02.get(), RoomModel_R_03.get(),
	    RoomModel_R_04.get(), RoomModel_R_05.get(), RoomModel_R_06.get());

	// 部屋06の初期化
	Room_06_->Initialize(
	    RoomModel_R_00.get(), RoomModel_R_01.get(), RoomModel_R_02.get(), RoomModel_R_03.get(),
	    RoomModel_R_04.get(), RoomModel_R_05.get(), RoomModel_R_06.get());
}

void GameScene::RoomUpdate() {
	// 部屋00
	Room_00_->Update();
	// 部屋01
	Room_01_->Update();
	// 部屋02
	Room_02_->Update();
	// 部屋03
	Room_03_->Update();
	// 部屋04
	Room_04_->Update();
	// 部屋05
	Room_05_->Update();
	// 部屋06
	Room_06_->Update();
}

void GameScene::RoomDraw() {
	Room_00_->Draw(viewProjection_);
	Room_01_->Draw(viewProjection_);
	Room_02_->Draw(viewProjection_);
	Room_03_->Draw(viewProjection_);
	Room_04_->Draw(viewProjection_);
	Room_05_->Draw(viewProjection_);
	Room_06_->Draw(viewProjection_);
}


void GameScene::LoadInitialize() {
	// 道0の生成
	Load_0_ = std::make_unique<Load>();
	// 3Dモデルの生成
	LoadModel0_.reset(Model::CreateFromOBJ("Load", true));

	// 道1の生成
	Load_1_ = std::make_unique<Load>();
	// 3Dモデルの生成
	LoadModel1_.reset(Model::CreateFromOBJ("Load1", true));

	// 道2の生成
	Load_2_ = std::make_unique<Load>();
	// 3Dモデルの生成
	LoadModel2_.reset(Model::CreateFromOBJ("Load2", true));

	// 道3の生成
	Load_3_ = std::make_unique<Load>();
	// 3Dモデルの生成
	LoadModel3_.reset(Model::CreateFromOBJ("Load3", true));

	// 道4の生成
	Load_4_ = std::make_unique<Load>();
	// 3Dモデルの生成
	LoadModel4_.reset(Model::CreateFromOBJ("Load4", true));

	// 道5の生成
	Load_5_ = std::make_unique<Load>();
	// 3Dモデルの生成
	LoadModel5_.reset(Model::CreateFromOBJ("Load5", true));


	// 道0の初期化
	Load_0_->Initialize(
	    LoadModel0_.get(), LoadModel1_.get(), LoadModel2_.get(), LoadModel3_.get(),
	    LoadModel4_.get(), LoadModel5_.get());

	// 道1の初期化
	Load_1_->Initialize(
	    LoadModel0_.get(), LoadModel1_.get(), LoadModel2_.get(), LoadModel3_.get(),
	    LoadModel4_.get(), LoadModel5_.get());

	// 道2の初期化
	Load_2_->Initialize(
	    LoadModel0_.get(), LoadModel1_.get(), LoadModel2_.get(), LoadModel3_.get(),
	    LoadModel4_.get(), LoadModel5_.get());

	// 道3の初期化
	Load_3_->Initialize(
	    LoadModel0_.get(), LoadModel1_.get(), LoadModel2_.get(), LoadModel3_.get(),
	    LoadModel4_.get(), LoadModel5_.get());

	// 道4の初期化
	Load_4_->Initialize(
	    LoadModel0_.get(), LoadModel1_.get(), LoadModel2_.get(), LoadModel3_.get(),
	    LoadModel4_.get(), LoadModel5_.get());

	// 道5の初期化
	Load_5_->Initialize(
	    LoadModel0_.get(), LoadModel1_.get(), LoadModel2_.get(), LoadModel3_.get(),
	    LoadModel4_.get(), LoadModel5_.get());

}

void GameScene::LoadUpdate() {
	Load_0_->Update();
	Load_1_->Update();
	Load_2_->Update();
	Load_3_->Update();
	Load_4_->Update();
	Load_5_->Update();
}

void GameScene::LoadDraw() {
	Load_0_->Draw(viewProjection_);
	//Load_1_->Draw(viewProjection_);
	//Load_2_->Draw(viewProjection_);
	//Load_3_->Draw(viewProjection_);
	//Load_4_->Draw(viewProjection_);
	//Load_5_->Draw(viewProjection_);
}

void GameScene::TableInitialize() {}

void GameScene::TableUpdate() {}

void GameScene::TableDraw() {}

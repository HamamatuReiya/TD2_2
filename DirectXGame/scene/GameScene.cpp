#include "GameScene.h"
#include "AxisIndicator.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() { delete buttonSprite_; }

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

	//// 軸方向表示の表示を有効にする
	//AxisIndicator::GetInstance()->SetVisible(true);
	//// 軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
	//AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

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
	// 敵追従カメラの生成
	enemyfollowCamera_ = std::make_unique<EnemyFollowCamera>();
	enemyfollowCamera_->Initialize();
	ActiveTime = 0.0f;
	EnemyCameraActive = false;

	// 自キャラのワールドトランスフォームを追従カメラにセット
	followCamera_->SetTarget(&player_->GetWorldTransform());
	// 敵キャラのワールドトランスフォームを追従カメラにセット
	enemyfollowCamera_->SetTarget(&enemy_->GetWorldTransform());
	// Player&followCamera
	player_->SetViewProjection(&followCamera_->GetViewProjection());
	// Player&followCamera
	enemy_->SetViewProjection(&enemyfollowCamera_->GetViewProjection());

	// 地面の生成
	ground_ = std::make_unique<Ground>();
	// 3Dモデルの生成
	groundModel_.reset(Model::CreateFromOBJ("ground", true));
	// 地面の初期化
	ground_->Initialize(groundModel_.get());

	// 鍵の生成
	Key_ = std::make_unique<Key>();
	// 3Dモデルの生成
	KeyModel_.reset(Model::CreateFromOBJ("Hammer", true));
	// 3Dモデルの生成
	KeyUpModel_.reset(Model::CreateFromOBJ("KeyUp", true));
	// 3Dモデルの生成
	KeyDownModel_.reset(Model::CreateFromOBJ("KeyDown", true));
	// 鍵の初期化
	Key_->Initialize(KeyModel_.get(), KeyUpModel_.get(), KeyDownModel_.get());

	iskeyup = true;
	isHummer = true;
	iskeydown = true;
	isCraft = true;

	//部屋の生成,初期化
	RoomInitialize();

	//道の生成,初期化
	LoadInitialize();

	//机の生成、初期化
	TableInitialize();

	// 天井の生成
	ceiling_ = std::make_unique<Ceiling>();
	//3Dモデルの生成
	CeilingModel_.reset(Model::CreateFromOBJ("Ceiling", true));
	// 天井の初期化
	ceiling_->Initialize(CeilingModel_.get());

	// 出口の生成
	exit_ = std::make_unique<Exit>();
	// 3Dモデルの生成
	ExitModel_.reset(Model::CreateFromOBJ("Exit", true));
	// 出口の初期化
	exit_->Initialize(ExitModel_.get());

	// 南京錠の生成
	lock_ = std::make_unique<Lock>();
	// 3Dモデルの生成
	LockModel_.reset(Model::CreateFromOBJ("Lock", true));
	// 南京錠の初期化
	lock_->Initialize(LockModel_.get());

	// ボタンのテクスチャ読み込み
	buttonTexture_ = TextureManager::Load("F.png");
	// スプライトの生成
	buttonSprite_ = Sprite::Create(buttonTexture_, {1250, 600});

	//操作方法のテクスチャ読み込み
	operationTexture_ = TextureManager::Load("Operation.png");
	// スプライトの生成
	operationSprite_ = Sprite::Create(operationTexture_, {0, 0});
	// ゴールのテクスチャ読み込み
	goalTexture = TextureManager::Load("CLEAR.png");
	// ゴールの生成
	goalSprite_ = Sprite::Create(goalTexture, {0, 0});

	// 作業机の生成
	craft_= std::make_unique<Craft>();
	// 3Dモデルの生成
	CraftModel_.reset(Model::CreateFromOBJ("craft", true));
	// 作業机の初期化
	craft_->Initialize(CraftModel_.get());
	//スタミナ
	staminaTexture = TextureManager::Load("Stamina.png");
	staminaSprite = Sprite::Create(staminaTexture, {600, 900});
	//ルール
	LuleInitialize();
	//クリアタイム
	ClearTimeInitialize();
	// 型
	MoldInitialize();
	//鍵制作
	isCompletion = false;
	
}

void GameScene::RoopInitialize() {
	// 3Dモデル生成
	model_.reset(Model::Create());
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();
	// 自キャラの初期化
	player_->Initialize(playerModel_.get());
	// ルール
	LuleInitialize();
	// 初期化
	enemy_->Initialize(
	    enemyModel_.get(), enemyModel2_.get(), enemyModel3_.get(), enemyModel4_.get(),
	    enemyModel5_.get(), enemyModel6_.get(), enemyModel7_.get(), enemyModel8_.get(),
	    enemyModel9_.get(), enemyModel10_.get(), enemyModel11_.get(), enemyModel12_.get(),
	    enemyModel13_.get(), enemyModel14_.get(), enemyModel15_.get());
	// 地面の初期化
	ground_->Initialize(groundModel_.get());
	// 鍵の初期化
	Key_->Initialize(KeyModel_.get(), KeyUpModel_.get(), KeyDownModel_.get());
	// 出口の初期化
	exit_->Initialize(ExitModel_.get());
	// クリアタイム
	ClearTimeInitialize();
	isClearTime_ = 0;
	iskeydown = true;
	iskeyup = true;
	isHummer = true;
	//型
	MoldInitialize();
	// 鍵制作
	isCompletion = false;
}

void GameScene::ClearUpdate() {
	if (isCompletion==true) {

	}
}

void GameScene::ClearDraw() {}

void GameScene::ClearTimeInitialize()
{
	// クリアタイムの画像
	// テクスチャ(0～9)
	uint32_t textureScore0 = TextureManager::Load("number/0.png");
	uint32_t textureScore1 = TextureManager::Load("number/1.png");
	uint32_t textureScore2 = TextureManager::Load("number/2.png");
	uint32_t textureScore3 = TextureManager::Load("number/3.png");
	uint32_t textureScore4 = TextureManager::Load("number/4.png");
	uint32_t textureScore5 = TextureManager::Load("number/5.png");
	uint32_t textureScore6 = TextureManager::Load("number/6.png");
	uint32_t textureScore7 = TextureManager::Load("number/7.png");
	uint32_t textureScore8 = TextureManager::Load("number/8.png");
	uint32_t textureScore9 = TextureManager::Load("number/9.png");
	// クリアタイム
	ClearTimeScore1_[0] =
	    Sprite::Create(textureScore0, {180.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	ClearTimeScore1_[1] =
	    Sprite::Create(textureScore1, {180.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	ClearTimeScore1_[2] =
	    Sprite::Create(textureScore2, {180.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	ClearTimeScore1_[3] =
	    Sprite::Create(textureScore3, {180.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	ClearTimeScore1_[4] =
	    Sprite::Create(textureScore4, {180.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	ClearTimeScore1_[5] =
	    Sprite::Create(textureScore5, {180.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	ClearTimeScore1_[6] =
	    Sprite::Create(textureScore6, {180.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	ClearTimeScore1_[7] =
	    Sprite::Create(textureScore7, {180.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	ClearTimeScore1_[8] =
	    Sprite::Create(textureScore8, {180.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	ClearTimeScore1_[9] =
	    Sprite::Create(textureScore9, {180.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});

	ClearTimeScore2_[0] =
	    Sprite::Create(textureScore0, {90.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	ClearTimeScore2_[1] =
	    Sprite::Create(textureScore1, {90.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	ClearTimeScore2_[2] =
	    Sprite::Create(textureScore2, {90.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	ClearTimeScore2_[3] =
	    Sprite::Create(textureScore3, {90.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	ClearTimeScore2_[4] =
	    Sprite::Create(textureScore4, {90.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	ClearTimeScore2_[5] =
	    Sprite::Create(textureScore5, {90.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	ClearTimeScore2_[6] =
	    Sprite::Create(textureScore6, {90.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	ClearTimeScore2_[7] =
	    Sprite::Create(textureScore7, {90.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	ClearTimeScore2_[8] =
	    Sprite::Create(textureScore8, {90.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	ClearTimeScore2_[9] =
	    Sprite::Create(textureScore9, {90.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});

	ClearTimeScore3_[0] =
	    Sprite::Create(textureScore0, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	ClearTimeScore3_[1] =
	    Sprite::Create(textureScore1, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	ClearTimeScore3_[2] =
	    Sprite::Create(textureScore2, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	ClearTimeScore3_[3] =
	    Sprite::Create(textureScore3, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	ClearTimeScore3_[4] =
	    Sprite::Create(textureScore4, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	ClearTimeScore3_[5] =
	    Sprite::Create(textureScore5, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	ClearTimeScore3_[6] =
	    Sprite::Create(textureScore6, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	ClearTimeScore3_[7] =
	    Sprite::Create(textureScore7, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	ClearTimeScore3_[8] =
	    Sprite::Create(textureScore8, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	ClearTimeScore3_[9] =
	    Sprite::Create(textureScore9, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
}

void GameScene::LuleInitialize() {
	// ルールのテクスチャ読み込み
	luleTexture_[0] = TextureManager::Load("Lule1p.png");
	luleTexture_[1] = TextureManager::Load("Lule2p.png");
	
	for (int i = 0; i < 2; i++) {
		// ルールの生成
		LuleSprite_[i] = Sprite::Create(luleTexture_[i], {0, 0});
	}
	LuleP1Frag = true;
	LuleP2Frag = false;
	isLule_ = true;
}

void GameScene::LuleUpdate() {
	if (isLule_ == true) {
		LuleP1Frag = true;
		if (input_->TriggerKey(DIK_RIGHT)&& LuleP1Frag == true) {
			LuleP1Frag = false;
			LuleP2Frag = true;
		}
		if (input_->TriggerKey(DIK_SPACE) && LuleP2Frag == true) {
			LuleP1Frag = false;
			LuleP2Frag = false;
			isLule_ = false;
		}
		if (input_->TriggerKey(DIK_LEFT) && LuleP2Frag == true) {
			LuleP1Frag = true;
			LuleP2Frag = false;
		}
	}
	if (isLule_ == false && input_->TriggerKey(DIK_M)) {
		isLule_ = true;
	}
}

void GameScene::LuleDraw() {
	if (LuleP1Frag == true) {
		LuleSprite_[0]->Draw();
	}
	if (LuleP2Frag == true) {
		LuleSprite_[1]->Draw();
	}
}

void GameScene::MoldInitialize() {
	// 型のテクスチャ読み込み
	moldTexture_[0] = TextureManager::Load("parts/Mold.png");
	moldTexture_[1] = TextureManager::Load("parts/OnHummer.png");
	moldTexture_[2] = TextureManager::Load("parts/OnKeyUp.png");
	moldTexture_[3] = TextureManager::Load("parts/OnKeyDown.png");

	for (int i = 0; i < 4; i++) {
		// ルールの生成
		MoldSprite_[i] = Sprite::Create(moldTexture_[i], {0, 0});
	}
	// 鍵とった
	Gettingkeyup = false;
	GettingHummer = false;
	Gettingkeydown = false;
}

void GameScene::MoldDraw() {
	MoldSprite_[0]->Draw();
	if (Gettingkeyup==true) {
		MoldSprite_[2]->Draw();
	}
	if (GettingHummer == true) {
		MoldSprite_[1]->Draw();
	}
	if (Gettingkeydown == true) {
		MoldSprite_[3]->Draw();
	}
}


void GameScene::Update() {
	LuleUpdate();
	// ゴール
	if (isCompletion == true) {
		
		
	}
	if (isLule_==false) {
		CameraUpdate();
		if (EnemyCameraActive == false) {
			player_->Update();
		}
		// ダッシュ
		size = staminaSprite->GetSize();
		size.x = player_->GetStamina();

		staminaSprite->SetSize(size);

		enemy_->SetPlayer(player_.get());
		enemy_->Update();
		Key_->Update();
		// 部屋の更新
		RoomUpdate();
		// 道の更新
		LoadUpdate();
		// 机の更新
		TableUpdate();
		// 地面の更新
		ground_->Update();
		// 天井の更新
		ceiling_->Update();
		// 出口の更新
		exit_->Update();

		GetButton = false;
		// 作業机の更新
		craft_->Update();
		//　南京錠の更新
		lock_->Update();

		ActiveTime++;
		CheakCollisions();

		// シーン切り替え
		if (input_->TriggerKey(DIK_RETURN)) {
			isSceneEnd = true;
			
		}

		ClearTimeUpdate();
	}
}


void GameScene::ClearTimeUpdate()
{
	TimeFrame++;
	if (TimeFrame>60) {
		isClearTime_+=1;
		TimeFrame=0;
	}
	
	// クリアタイム
	isClearTime_1 = (isClearTime_ / 1) % 10;   // 1の桁
	isClearTime_2 = (isClearTime_ / 10) % 10;  // 10の桁
	isClearTime_3 = (isClearTime_ / 100) % 10; // 100の桁
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
	//机の描画
	TableDraw();
	// 天井の描画
	ceiling_->Draw(viewProjection_);
	// 出口の描画
	exit_->Draw(viewProjection_);
	// 作業机の描画
	craft_->Draw(viewProjection_);
	//南京錠の描画
	lock_->Draw(viewProjection_);
	
	
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	if (GetButton == true) {
		buttonSprite_->Draw();
	}
	//クリアタイム
	ClearTimeScore1_[isClearTime_1]->Draw();
	ClearTimeScore2_[isClearTime_2]->Draw();
	ClearTimeScore3_[isClearTime_3]->Draw();

	//操作方法表示
	operationSprite_->Draw();
	//ルール
	LuleDraw();
	if (isLule_ == false) {
		// 型
		MoldDraw();
		// スタミナ
		staminaSprite->Draw();
	}
	
	
	
	enemy_->EfectDraw();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::sceneReset() {
	// シーンの切り替えフラグ
	isSceneEnd = false;
	RoopInitialize();

	//// BGMの停止
	// audio_->StopWave(bgmHandle_);
	// bgmHandle_ = audio_->PlayWave(bgmDataHandle_, true, 0.15f);
}

void GameScene::CheakCollisions() {
	// 判定対象AとBの座標
	Vector3 posA,posB,posC,posD,posE,posF;

	// 2間点の距離(自キャラと鍵の当たり判定)
	float posAB;
	float posAC;
	float posAD;
	//自機と金床
	float posAF;

	//自機と敵
	float posAE;
	// 自機と敵
	float posAEX;
	float posAE_X;
	float posAEZ;
	float posAE_Z;

	float enemyVisibilityShift = 12.0f;

	//敵にぶつかる半径
	//float enemyRadius = 3.0f;
	//敵に見つかる半径
	float enemySearchRadius = 10.0f;

	// 敵に見つかる半径
	float enemySearchRadiusXZ = 7.0f;

	// 自キャラの半径
	float playerRadius = 2.0f;
	// 鍵の半径
	float keyRadius = 1.0f;
	// 鍵の半径
	float keyUpRadius = 1.0f;
	// 鍵の半径
	float keyDounRadius = 1.0f;
	//金床の半径
	float CraftRadius = 1.0f;

#pragma region 自キャラと鍵の当たり判定
	// 自キャラのワールド座標
	posA = player_->GetWorldPosition();
	// 鍵上の座標
	posB = Key_->GetKeyUpWorldPosition();
	// 鍵型の座標
	posC = Key_->GetKeyWorldPosition();
	// 鍵下の座標
	posD = Key_->GetKeyDownWorldPosition();
	//敵キャラのワールド座標
	posE = enemy_->GetWorldPosition();
	//金床の座標
	posF = craft_->GetCraftWorldPosition();
	// AとBの距離を求める
	posAB = (posB.x - posA.x) * (posB.x - posA.x) + (posB.y - posA.y) * (posB.y - posA.y) +
	        (posB.z - posA.z) * (posB.z - posA.z);
	// プレイヤーと上鍵の当たり判定
	if (posAB <= (playerRadius + keyUpRadius) * (playerRadius + keyUpRadius)) {
		if (iskeyup == true) {
			GetButton = true;
		}
		if (input_->TriggerKey(DIK_F)&& iskeyup ==true) {
			Gettingkeyup = true;
			// 自キャラの衝突時コールバックを呼び出す
			player_->OnCollision();
			// 鍵の衝突時コールバックを呼び出す
			Key_->OnKeyUpCollision();
			ActiveTime = 0;
			// 敵にカメラを向ける
			EnemyCameraActive = true;
			iskeyup = false;
		}
		if (ActiveTime >= 120) {
			EnemyCameraActive = false;
		}
	}
	// AとCの距離を求める
	posAC = (posC.x - posA.x) * (posC.x - posA.x) + (posC.y - posA.y) * (posC.y - posA.y) +
	        (posC.z - posA.z) * (posC.z - posA.z);
	// プレイヤーと鍵型の当たり判定
	if (posAC <= (playerRadius + keyRadius) * (playerRadius + keyRadius)) {
		if (isHummer == true) {
			GetButton = true;
		}
		if (input_->TriggerKey(DIK_F) && isHummer == true) {
			GettingHummer = true;
			// 自キャラの衝突時コールバックを呼び出す
			player_->OnCollision();
			// 鍵の衝突時コールバックを呼び出す
			Key_->OnKeyCollision();
			ActiveTime = 0;
			// 敵にカメラを向ける
			EnemyCameraActive = true;
			isHummer = false;
		}
		if (ActiveTime >= 120) {
			EnemyCameraActive = false;
		}
	}
	// AとDの距離を求める
	posAD = (posD.x - posA.x) * (posD.x - posA.x) + (posD.y - posA.y) * (posD.y - posA.y) +
	        (posD.z - posA.z) * (posD.z - posA.z);
	// プレイヤーと下鍵の当たり判定
	if (posAD <= (playerRadius + keyDounRadius) * (playerRadius + keyDounRadius)) {
		if (iskeydown == true) {
			GetButton = true;
		}
		if (input_->TriggerKey(DIK_F) && iskeydown == true) {
			Gettingkeydown = true;
			// 自キャラの衝突時コールバックを呼び出す
			player_->OnCollision();
			// 鍵の衝突時コールバックを呼び出す
			Key_->OnKeyDownCollision();
			ActiveTime = 0;
			// 敵にカメラを向ける
			EnemyCameraActive = true;
			iskeydown = false;
		}
		if (ActiveTime >= 120) {
			EnemyCameraActive = false;
		}
	}
	// AとFの距離を求める
	posAF = (posF.x - posA.x) * (posF.x - posA.x) + (posF.y - posA.y) * (posF.y - posA.y) +
	        (posF.z - posA.z) * (posF.z - posA.z);
	// プレイヤーと金床の当たり判定
	if (posAF <= (playerRadius + CraftRadius) * (playerRadius + CraftRadius)) {
		if (isCraft == true) {
			GetButton = true;
		}
		if (input_->PushKey(DIK_F) && isCraft == true) {
			PushTime_++;
			if (PushTime_>= 300) {
				isCompletion = true;
			}
			craft_->OnCraftCollision();
			// 自キャラの衝突時コールバックを呼び出す
			player_->OnCollision();
		} else {
			PushTime_ = 0;
		}
	}

	//敵の視界
	// AとEの距離を求める
	//敵と自機の半径
	posAE = (posE.x - posA.x) * (posE.x - posA.x) + (posE.y - posA.y) * (posE.y - posA.y) +
	        ((posE.z) - posA.z) * ((posE.z) - posA.z);
	if (posAE <= (playerRadius + enemySearchRadius) * (playerRadius + enemySearchRadius)) {
		enemy_->PhaseCollision();
	}
	//左
	posAE_X =((posE.x - enemyVisibilityShift) - posA.x) * ((posE.x - enemyVisibilityShift) - posA.x) +
	         (posE.y - posA.y) * (posE.y - posA.y) +
	        ((posE.z) - posA.z) * ((posE.z) - posA.z);
	if (posAE_X <= (playerRadius + enemySearchRadiusXZ) * (playerRadius + enemySearchRadiusXZ)) {
		if (enemy_->GetEnemyVisibility_X() == true) {
			enemy_->PhaseCollision();
		}
	}
	// 右
	posAEX =
	    ((posE.x + enemyVisibilityShift) - posA.x) * ((posE.x + enemyVisibilityShift) - posA.x) +
	    (posE.y - posA.y) * (posE.y - posA.y) + ((posE.z) - posA.z) * ((posE.z) - posA.z);
	if (posAEX <= (playerRadius + enemySearchRadiusXZ) * (playerRadius + enemySearchRadiusXZ)) {
		if (enemy_->GetEnemyVisibilityX() == true) {
			enemy_->PhaseCollision();
		}
	}
	// 下
	posAE_Z =
	    ((posE.x) - posA.x) * ((posE.x) - posA.x) + (posE.y - posA.y) * (posE.y - posA.y) +
	    ((posE.z - enemyVisibilityShift) - posA.z) * ((posE.z - enemyVisibilityShift) - posA.z);
	if (posAE_Z <= (playerRadius + enemySearchRadiusXZ) * (playerRadius + enemySearchRadiusXZ)) {
		if (enemy_->GetEnemyVisibility_Z() == true) {
			enemy_->PhaseCollision();
		}
	}
	// 上
	posAEZ =
	    ((posE.x) - posA.x) * ((posE.x) - posA.x) + (posE.y - posA.y) * (posE.y - posA.y) +
	    ((posE.z + enemyVisibilityShift) - posA.z) * ((posE.z + enemyVisibilityShift) - posA.z);
	if (posAEZ <= (playerRadius + enemySearchRadiusXZ) * (playerRadius + enemySearchRadiusXZ)) {
		if (enemy_->GetEnemyVisibilityZ() == true) {
			enemy_->PhaseCollision();
		}
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
		if (EnemyCameraActive == true) {
			// 敵追従カメラの更新
			enemyfollowCamera_->Update();
			viewProjection_.matProjection = enemyfollowCamera_->GetViewProjection().matProjection;
			viewProjection_.matView = enemyfollowCamera_->GetViewProjection().matView;
		} 
		if (EnemyCameraActive == false) {
			// 追従カメラの更新
			followCamera_->Update();
			viewProjection_.matProjection = followCamera_->GetViewProjection().matProjection;
			viewProjection_.matView = followCamera_->GetViewProjection().matView;
		}

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
	Load_1_->Draw(viewProjection_);
	Load_2_->Draw(viewProjection_);
	Load_3_->Draw(viewProjection_);
	Load_4_->Draw(viewProjection_);
	Load_5_->Draw(viewProjection_);
}


void GameScene::TableInitialize() {
	// 机0の生成
	Table_0_ = std::make_unique<Table>();
	// 3Dモデルの生成
	TableModel0_.reset(Model::CreateFromOBJ("Table", true));

	// 机1の生成
	Table_1_ = std::make_unique<Table>();
	// 3Dモデルの生成
	TableModel1_.reset(Model::CreateFromOBJ("Table", true));

	// 机2の生成
	Table_2_ = std::make_unique<Table>();
	// 3Dモデルの生成
	TableModel2_.reset(Model::CreateFromOBJ("Table", true));

	// 机3の生成
	Table_3_ = std::make_unique<Table>();
	// 3Dモデルの生成
	TableModel3_.reset(Model::CreateFromOBJ("Table", true));

	// 机4の生成
	Table_4_ = std::make_unique<Table>();
	// 3Dモデルの生成
	TableModel4_.reset(Model::CreateFromOBJ("Table", true));

	// 机5の生成
	Table_5_ = std::make_unique<Table>();
	// 3Dモデルの生成
	TableModel5_.reset(Model::CreateFromOBJ("Table", true));

	// 机6の生成
	Table_6_ = std::make_unique<Table>();
	// 3Dモデルの生成
	TableModel6_.reset(Model::CreateFromOBJ("Table", true));

	// 机7の生成
	Table_7_ = std::make_unique<Table>();
	// 3Dモデルの生成
	TableModel7_.reset(Model::CreateFromOBJ("Table", true));

	// 机8の生成
	Table_8_ = std::make_unique<Table>();
	// 3Dモデルの生成
	TableModel8_.reset(Model::CreateFromOBJ("Table", true));

	// 机0の初期化
	Table_0_->Initialize(
	    TableModel0_.get(), TableModel1_.get(), TableModel2_.get(), TableModel3_.get(),
	    TableModel4_.get(), TableModel5_.get(), TableModel6_.get(), TableModel7_.get(),
	    TableModel8_.get());

	// 机1の初期化
	Table_1_->Initialize(
	    TableModel0_.get(), TableModel1_.get(), TableModel2_.get(), TableModel3_.get(),
	    TableModel4_.get(), TableModel5_.get(), TableModel6_.get(), TableModel7_.get(),
	    TableModel8_.get());

	// 机2の初期化
	Table_2_->Initialize(
	    TableModel0_.get(), TableModel1_.get(), TableModel2_.get(), TableModel3_.get(),
	    TableModel4_.get(), TableModel5_.get(), TableModel6_.get(), TableModel7_.get(),
	    TableModel8_.get());

	// 机3の初期化
	Table_3_->Initialize(
	    TableModel0_.get(), TableModel1_.get(), TableModel2_.get(), TableModel3_.get(),
	    TableModel4_.get(), TableModel5_.get(), TableModel6_.get(), TableModel7_.get(),
	    TableModel8_.get());

	// 机4の初期化
	Table_4_->Initialize(
	    TableModel0_.get(), TableModel1_.get(), TableModel2_.get(), TableModel3_.get(),
	    TableModel4_.get(), TableModel5_.get(), TableModel6_.get(), TableModel7_.get(),
	    TableModel8_.get());

	// 机5の初期化
	Table_5_->Initialize(
	    TableModel0_.get(), TableModel1_.get(), TableModel2_.get(), TableModel3_.get(),
	    TableModel4_.get(), TableModel5_.get(), TableModel6_.get(), TableModel7_.get(),
	    TableModel8_.get());

	// 机6の初期化
	Table_6_->Initialize(
	    TableModel0_.get(), TableModel1_.get(), TableModel2_.get(), TableModel3_.get(),
	    TableModel4_.get(), TableModel5_.get(), TableModel6_.get(), TableModel7_.get(),
	    TableModel8_.get());

	// 机7の初期化
	Table_7_->Initialize(
	    TableModel0_.get(), TableModel1_.get(), TableModel2_.get(), TableModel3_.get(),
	    TableModel4_.get(), TableModel5_.get(), TableModel6_.get(), TableModel7_.get(),
	    TableModel8_.get());

	// 机8の初期化
	Table_8_->Initialize(
	    TableModel0_.get(), TableModel1_.get(), TableModel2_.get(), TableModel3_.get(),
	    TableModel4_.get(), TableModel5_.get(), TableModel6_.get(), TableModel7_.get(),
	    TableModel8_.get());
}

void GameScene::TableUpdate() { 
	Table_0_->Update();
	Table_1_->Update();
	Table_2_->Update();
	Table_3_->Update();
	Table_4_->Update();
	Table_5_->Update();
	Table_6_->Update();
	Table_7_->Update();
	Table_8_->Update();
}

void GameScene::TableDraw() {
	Table_0_->Draw(viewProjection_);
	Table_1_->Draw(viewProjection_);
	Table_2_->Draw(viewProjection_);
	Table_3_->Draw(viewProjection_);
	Table_4_->Draw(viewProjection_);
	Table_5_->Draw(viewProjection_);
	Table_6_->Draw(viewProjection_);
	Table_7_->Draw(viewProjection_);
	Table_8_->Draw(viewProjection_);
}

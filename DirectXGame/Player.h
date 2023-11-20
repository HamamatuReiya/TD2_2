#include "Model.h"
#include "WorldTransform.h"
#include <Input.h>
#include"ViewProjection.h"


class Player {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model);

	/// <summary>
	/// 自キャラ
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection& viewProjection);

	// ワールド座標を取得
	Vector3 GetWorldPosition();

	// コールバック関数
	void OnCollision();

	WorldTransform& GetWorldTransform() { return worldTransform_; };

	void SetViewProjection(const ViewProjection* viewProjection)
	{
		viewProjection_ = viewProjection;
	}

	//鍵に触れたかどうか
	bool isKeytouch() const { return isKeytouch_; }

	enum CollisionType {
		START, // スタート地点の部屋(0)
		LOAD00,// スタート地点から右の道(1)
		ROOM00,// 右の部屋(2)
		ROOM01,// 右の部屋の隣(3)
		ROOM02,// 右の部屋の隣(4)
		ROOM03,// 右の部屋の隣(5)
		ROOM04,// (6)
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
	};

	void SetType(int collisionType);

	int GetType();


private:
	WorldTransform worldTransform_;
	// ビュープロジェクション
	const ViewProjection*viewProjection_=nullptr;
	Model* model_ = nullptr;
	Input* input_ = nullptr;
	
	//部屋関数
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
	//道関数
	void Load00Collision();
	void Load01Collision();
	void Load02Collision();

	//回転スピード
	float kRotateSpeed;
	// 鍵に触れたかどうかフラグ
	bool isKeytouch_ = false;
	//スタミナ
	float StaminaTimer_ = 0;
	////スタミナクールタイム
	//float Cooltime_ = 0;
	
	CollisionType collisionType_;
};
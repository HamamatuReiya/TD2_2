#include<time.h>
#include "Model.h"
#include "WorldTransform.h"

class KeyItem 
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection& viewProjection);

private:
	enum ItemType {
		KEYCRAFT, // 鍵作成エリア(0)
		KEYUP,    // 鍵上の部分(1)
		KEYDOWN,  // 鍵下の部分(2)
		MOLD,     // 鍵の型(3)
	};
private:
	ItemType itemType_;
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
};

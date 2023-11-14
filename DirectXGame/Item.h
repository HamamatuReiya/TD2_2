#include<time.h>
#include "Model.h"
#include "WorldTransform.h"

class Item 
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* keyupModel, Model* keydownModel, Model* keymoldModel);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection& viewProjection);

private:
	//鍵用のランダム変数
	float Keynumber = 0;

private:
	WorldTransform worldTransform_[3];
	Model* keyupModel_ = nullptr;
	Model* keydownModel_ = nullptr;
	Model* keymoldModel_ = nullptr;
};

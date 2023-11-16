#include "Model.h"
#include "WorldTransform.h"

class Object {

	public:
	/// <summary>
	/// 初期化
	/// </summary>
	    void Initialize(
	        Model* model, Model* model1, Model* model2, Model* model3, Model* model4, Model* model5,
	        Model* model6);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection& viewProjection);

private:
	WorldTransform worldTransform_[7];
	Model* model_ = nullptr;
	Model* model1_ = nullptr;
	Model* model2_ = nullptr;
	Model* model3_ = nullptr;
	Model* model4_ = nullptr;
	Model* model5_ = nullptr;
	Model* model6_ = nullptr;
};

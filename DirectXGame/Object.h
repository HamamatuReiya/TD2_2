#include "Model.h"
#include "WorldTransform.h"

class Object {

	public:
	/// <summary>
	/// ‰Šú‰»
	/// </summary>
	void Initialize(Model* model);

	/// <summary>
	/// XV
	/// </summary>
	void Update();

	/// <summary>
	/// •`‰æ
	/// </summary>
	void Draw(ViewProjection& viewProjection);

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
};

#include "ViewProjection.h"
#include "WorldTransform.h"

class RailCamera {
public:
	Vector3 GetWorldPosition();

	const ViewProjection& GetViewProjection() { return viewProjection_; }

	const WorldTransform& GetWorldTransform() { return worldTransform_; }

	void Initialize(Vector3& worldPos, Vector3& rotate);

	void Update();

private:
	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	// �r���[�v���W�F�N�V����
	ViewProjection viewProjection_;
};
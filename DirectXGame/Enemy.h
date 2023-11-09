#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Mymath.h"

class Enemy {
public:
	void Initialize(Model* model);

	void Update();

	void Draw(ViewProjection& viewProjection);

	void Search();

	void Chase();

private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;


};

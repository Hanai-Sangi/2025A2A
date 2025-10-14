#pragma once
#include "Object3D.h"

class Camera : public Object3D
{
public:
	Camera();
	~Camera();
	void Update() override;
private:
	float RStickX();
	float RStickY();
};
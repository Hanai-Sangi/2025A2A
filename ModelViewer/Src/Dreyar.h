#pragma once
#include "Object3D.h"
#include "Animator.h"

class Dreyar : public Object3D {
public:
	Dreyar();
	~Dreyar();
	void Update() override;
};
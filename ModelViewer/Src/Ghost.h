#pragma once
#include "Object3D.h"

class Ghost : public Object3D {
public:
	Ghost();
	~Ghost();
	void Update() override;
};
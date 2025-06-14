#pragma once
#include "Object3D.h"

class Player : public Object3D
{
public:
	Player();
	Player(VECTOR3 pos);
	~Player();
	void Update()override;
};

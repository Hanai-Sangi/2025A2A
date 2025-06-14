#pragma once
#include "GameObject.h"

class Camera : public GameObject {
public:
	Camera();
	~Camera();
	void Update() override;
	void Draw() override;
private:
	VECTOR3 position;
	VECTOR3 look;

};
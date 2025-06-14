#pragma once
#include "GameObject.h"

class Axis : public GameObject
{
public:
	Axis();
	~Axis();
	void Update() override;
	void Draw() override;
private:
	void WriteArrow(const VECTOR3& start, const VECTOR3& end, const DWORD& color);
};
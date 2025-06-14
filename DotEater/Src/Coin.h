#pragma once
#include "Object3D.h"

class Coin : public Object3D
{
public:
	Coin();
	Coin(VECTOR3 pos);
	~Coin();
	void Update()override;
private:
	bool gotten; // �擾����
	float velocityY; // �W�����v�̑��x
	int frameTime; // ����Ă���t���[�����iint�Łj
};

#pragma once
#include "Object3D.h"

class Player : public Object3D
{
public:
	Player();
	~Player();
	void Update() override;
private:
	VECTOR2 LStickVec();

	enum State {
		ST_NORMAL,
		ST_ATT1,
		ST_ATT2,
		ST_ATT3,
	};
	State state; //ó‘Ô‚ğ‚Â•Ï”
	void UpdateNormal();
	void UpdateAttack1();
	void UpdateAttack2();
	void UpdateAttack3();
};
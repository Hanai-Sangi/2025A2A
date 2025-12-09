#pragma once
#include "Object3D.h"

class Player : public Object3D
{
public:
	Player();
	~Player();
	void Update() override;
	void Draw() override;
	bool CollideCircle(VECTOR3 center, float radius);
private:
	VECTOR3 swordTop;
	VECTOR3 swordBtm;
	VECTOR2 LStickVec();

	enum State {
		ST_NORMAL,
		ST_ATT1,
		ST_ATT2,
		ST_ATT3,
		ST_DAMAGE,
	};
	State state; //ó‘Ô‚ğ‚Â•Ï”
	void UpdateNormal();
	void UpdateAttack1();
	void UpdateAttack2();
	void UpdateAttack3();
	void UpdateDamage();
	bool attackPushed;
};
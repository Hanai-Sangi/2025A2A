#pragma once
#include "Object3D.h"

class Golem : public Object3D
{
public:
	Golem(VECTOR3 pos, float rotY);
	~Golem();
	void Update() override;
	void Draw() override;

	/// <summary>
	/// 球と当たり判定する
	/// </summary>
	/// <param name="center">球の中心座標</param>
	/// <param name="radius">球の半径</param>
	/// <returns>押し返すベクトル</returns>
	VECTOR3 CollideSphere(VECTOR3 center, float radius);

	bool CollideSword(VECTOR3 top, VECTOR3 btm);
private:
	void UpdateIntention();
	enum Intent {
		INT_WALK = 0,
		INT_ATTACK,
		INT_BACK,
		INT_DEAD,
	};
	Intent intent;
	void ChangeIntention(Intent inte);
	void IntWalk();
	void IntAttack();
	void IntBack();
	void IntDead();

	void UpdateAction();
	enum Action {
		ACT_CHASE = 0,
		ACT_PUNCH,
		ACT_STAND,
		ACT_DEAD,
	};
	Action action;
	void ChangeAction(Action act);
	void ActChase();
	void ActPunch();
	void ActStand();
	void ActDead();

	bool InSight(VECTOR3 pos, float dist, float angle);

	VECTOR3 teritoriCenter;

	float deadTimer;
};
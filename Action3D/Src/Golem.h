#pragma once
#include "Object3D.h"

class Golem : public Object3D
{
public:
	Golem(VECTOR3 pos, float rotY);
	~Golem();
	void Update() override;

	/// <summary>
	/// 球と当たり判定する
	/// </summary>
	/// <param name="center">球の中心座標</param>
	/// <param name="radius">球の半径</param>
	/// <returns>押し返すベクトル</returns>
	VECTOR3 CollideSphere(VECTOR3 center, float radius);
private:
	void UpdateIntention();
	enum Intent {
		INT_WALK = 0,
		INT_ATTACK,
	};
	Intent intent;
	void ChangeIntention(Intent inte);
	void IntWalk();
	void IntAttack();

	void UpdateAction();
	enum Action {
		ACT_CHASE = 0,
		ACT_PUNCH,
		ACT_STAND,
	};
	Action action;
	void ChangeAction(Action act);
	void ActChase();
	void ActPunch();
	void ActStand();

	bool InSight(VECTOR3 pos, float dist, float angle);

};
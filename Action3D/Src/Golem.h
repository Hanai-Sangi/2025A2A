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
};
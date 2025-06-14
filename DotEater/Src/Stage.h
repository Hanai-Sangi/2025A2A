#pragma once
#include "Object3D.h"

class Stage : public Object3D
{
public:
	Stage();
	~Stage();
	void Update()override;
	void Draw()override;

	/// <summary>
	/// 球体と壁とのあたり判定をする
	/// 
	/// </summary>
	/// <param name="center">球の中心</param>
	/// <param name="radius">球の半径</param>
	/// <returns></returns>押し返すベクトル（当たってなければ0,0,0）
	VECTOR3 CollideSphere(VECTOR3 center, float radius); // 中心と半径
};

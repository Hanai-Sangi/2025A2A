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
	/// ���̂ƕǂƂ̂����蔻�������
	/// 
	/// </summary>
	/// <param name="center">���̒��S</param>
	/// <param name="radius">���̔��a</param>
	/// <returns></returns>�����Ԃ��x�N�g���i�������ĂȂ����0,0,0�j
	VECTOR3 CollideSphere(VECTOR3 center, float radius); // ���S�Ɣ��a
};

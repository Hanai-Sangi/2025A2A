#include "Axis.h"
#include "Sprite3D.h"

Axis::Axis()
{
}

Axis::~Axis()
{
}

void Axis::Update()
{
}

void Axis::Draw()
{
	WriteArrow(VECTOR3(-1, 0, 0), VECTOR3(4, 0, 0), RGB(255, 0, 0));
	WriteArrow(VECTOR3(0, -1, 0), VECTOR3(0, 4, 0), RGB(0, 255, 0));
	WriteArrow(VECTOR3(0, 0, -1), VECTOR3(0, 0, 4), RGB(0, 0, 255));
}

void Axis::WriteArrow(const VECTOR3& start, const VECTOR3& end, const DWORD& color)
{
	CSprite* spr = new CSprite();
	spr->DrawLine3D(start, end, color);
	VECTOR3 base = (start - end) / 50.0f;
	MATRIX4X4 m = XMMatrixRotationX(XM_PI / 6.0f); // 30‚Ì–îˆó‚ð‘‚­
	VECTOR3 v = base * m;
	spr->DrawLine3D(v + end, end, color);
	m = XMMatrixRotationX(-XM_PI / 6.0f);
	v = base * m;
	spr->DrawLine3D(v + end, end, color);

	m = XMMatrixRotationY(XM_PI / 6.0f);
	v = base * m;
	spr->DrawLine3D(v + end, end, color);
	m = XMMatrixRotationY(-XM_PI / 6.0f);
	v = base * m;
	spr->DrawLine3D(v + end, end, color);

	m = XMMatrixRotationZ(XM_PI / 6.0f);
	v = base * m;
	spr->DrawLine3D(v + end, end, color);
	m = XMMatrixRotationZ(-XM_PI / 6.0f);
	v = base * m;
	spr->DrawLine3D(v + end, end, color);

	delete spr;
}

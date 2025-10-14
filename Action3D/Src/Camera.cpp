#include "Camera.h"

Camera::Camera()
{
	VECTOR3 eye = VECTOR3(0, 2, -5);
	VECTOR3 look = VECTOR3(0, 1, 0);
	GameDevice()->m_vEyePt = eye; // カメラ座標
	GameDevice()->m_vLookatPt = look; // 注視点
	GameDevice()->m_mView = XMMatrixLookAtLH(     // ビューマトリックス
		eye, look,
		VECTOR3(0, 1, 0));
}

Camera::~Camera()
{
}

void Camera::Update()
{
	transform.rotation.y += RStickX() * 6.0f * DegToRad;
	transform.rotation.x += RStickY() * 6.0f * DegToRad;

	MATRIX4X4 matY = XMMatrixRotationY(
		transform.rotation.y);
	MATRIX4X4 matX = XMMatrixRotationX(
		transform.rotation.x);

	VECTOR3 eye = VECTOR3(0, 2, -5) * matX * matY 
			+ VECTOR3(0, 1.5f, 0);
	VECTOR3 look = VECTOR3(0, 2, 0);
	GameDevice()->m_vEyePt = eye; // カメラ座標
	GameDevice()->m_vLookatPt = look; // 注視点
	GameDevice()->m_mView = XMMatrixLookAtLH(     // ビューマトリックス
		eye, look,
		VECTOR3(0, 1, 0));

}

float Camera::RStickX()
{
	if (GameDevice()->m_pDI->CheckKey(KD_DAT, DIK_RIGHT)) {
		return 1.0f;
	}
	if (GameDevice()->m_pDI->CheckKey(KD_DAT, DIK_LEFT)) {
		return -1.0f;
	}
	if (GameDevice()->m_pDI->GetJoyNum() == 0)
		return 0.0f;
	auto inp = GameDevice()->m_pDI->GetJoyState();
	float x = inp.lRx;
	x = x / 65535.0f * 2.0f - 1.0f;
	return x;
}

float Camera::RStickY()
{
	if (GameDevice()->m_pDI->CheckKey(KD_DAT, DIK_DOWN)) {
		return 1.0f;
	}
	if (GameDevice()->m_pDI->CheckKey(KD_DAT, DIK_UP)) {
		return -1.0f;
	}
	if (GameDevice()->m_pDI->GetJoyNum() == 0)
		return 0.0f;
	auto inp = GameDevice()->m_pDI->GetJoyState();
	float y = inp.lRy;
	y = y / 65535.0f * 2.0f - 1.0f;
	return y;
}





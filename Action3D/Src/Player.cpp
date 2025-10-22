#include "Player.h"
#include "../Libs/Imgui/imgui.h"

Player::Player()
{
	mesh = new CFbxMesh();
	mesh->Load("Data/Player/PlayerChara.mesh");
	mesh->LoadAnimation(0, "Data/Player/Run.anmx", true);
	animator = new Animator();
	animator->SetModel(mesh);
	animator->Play(0);
}

Player::~Player()
{
}

void Player::Update()
{
	auto inp = GameDevice()->m_pDI->GetJoyState();
	int x = inp.lRx;
	int y = inp.lRy;
	int b = inp.rgbButtons[0];
	ImGui::Begin("Pad");
	ImGui::InputInt("RX", &x);
	ImGui::InputInt("RY", &y);
	ImGui::InputInt("BTN", &b);
	ImGui::End();

	animator->Update();

	VECTOR2 stick = LStickVec();
	VECTOR3 camVec = GameDevice()->m_vLookatPt -
							GameDevice()->m_vEyePt;
	float camAng = atan2f(camVec.x, camVec.z); // ƒJƒƒ‰‚ÌŠp“x
	VECTOR3 velocity = VECTOR3(stick.x, 0, -stick.y);
	if (magnitude(velocity) > 0) {
		velocity = velocity * XMMatrixRotationY(camAng);
		transform.rotation.y = atan2f(velocity.x, velocity.z);
		transform.position += velocity * 0.05f;
	}
	//ƒƒ‚
	XMMATRIX mat = XMMatrixRotationY(transform.rotation.y);
	VECTOR3 front = VECTOR3(0, 0, 1) * mat; // ³–Ê
	VECTOR3 right = VECTOR3(1, 0, 0) * mat; // ‰E
	VECTOR3 up = VECTOR3(0, 1, 0) * mat; // ã
}

VECTOR2 Player::LStickVec()
{
	auto inp = GameDevice()->m_pDI->GetJoyState();
	float x = inp.lX;
	float y = inp.lY;
	x = x / 1000.0f;
	y = y / 1000.0f;
	if (GameDevice()->m_pDI->CheckKey(KD_DAT, DIK_W)) {
		y = -1.0f;
	}
	if (GameDevice()->m_pDI->CheckKey(KD_DAT, DIK_S)) {
		y = 1.0f;
	}
	if (GameDevice()->m_pDI->CheckKey(KD_DAT, DIK_D)) {
		x = 1.0f;
	}
	if (GameDevice()->m_pDI->CheckKey(KD_DAT, DIK_A)) {
		x = -1.0f;
	}
	VECTOR2 ret = VECTOR2(x, y);
	if (magnitude(ret) > 1.0f) { // ’·‚³‚ª‚P‚ð’´‚¦‚Ä‚é‚Ì‚Å
		ret = normalize(ret); // ’·‚³‚ð‚P‚É‚·‚é
	}
	return ret;
}
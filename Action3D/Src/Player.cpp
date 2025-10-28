#include "Player.h"
#include "../Libs/Imgui/imgui.h"

enum ANIM_ID {
	A_RUN = 0,
	A_WAIT,
	A_ATTACK1,
	A_ATTACK2,
	A_ATTACK3,
};
	Player::Player()
{
	mesh = new CFbxMesh();
	mesh->Load("Data/Player/PlayerChara.mesh");
	mesh->LoadAnimation(A_RUN, "Data/Player/Run.anmx", true);
	mesh->LoadAnimation(A_ATTACK1, "Data/Player/attack1.anmx", false);
	mesh->LoadAnimation(A_ATTACK2, "Data/Player/attack2.anmx", false);
	mesh->LoadAnimation(A_ATTACK3, "Data/Player/attack3.anmx", false);
	animator = new Animator();
	animator->SetModel(mesh);
	animator->Play(A_RUN);
}

Player::~Player()
{
}

void Player::Update()
{
	switch (state) {
	case ST_NORMAL:
		UpdateNormal();
		break;
	case ST_ATT1:
		UpdateAttack1();
		break;
	case ST_ATT2:
		UpdateAttack2();
		break;
	case ST_ATT3:
		UpdateAttack3();
		break;
	}
	//auto inp = GameDevice()->m_pDI->GetJoyState();
	//int x = inp.lRx;
	//int y = inp.lRy;
	//int b = inp.rgbButtons[0];
	//ImGui::Begin("Pad");
	//ImGui::InputInt("RX", &x);
	//ImGui::InputInt("RY", &y);
	//ImGui::InputInt("BTN", &b);
	//ImGui::End();
	animator->Update();
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
	if (magnitude(ret) > 1.0f) { // �������P�𒴂��Ă�̂�
		ret = normalize(ret); // �������P�ɂ���
	}
	return ret;
}

void Player::UpdateNormal()
{
	VECTOR2 stick = LStickVec();
	VECTOR3 camVec = GameDevice()->m_vLookatPt -
		GameDevice()->m_vEyePt;
	float camAng = atan2f(camVec.x, camVec.z); // �J�����̊p�x
	VECTOR3 velocity = VECTOR3(stick.x, 0, -stick.y);
	if (magnitude(velocity) > 0) {
		velocity = velocity * XMMatrixRotationY(camAng);
#if false // �p�x�o�[�W����
		float ang = atan2f(velocity.x, velocity.z);
		float diff = ang - transform.rotation.y;
		while (diff < -180.0f * DegToRad) diff += 360.0f * DegToRad;
		while (diff > 180.0f * DegToRad) diff -= 360.0f * DegToRad;
		if (diff >= -30.0f * DegToRad && diff <= 30.0f * DegToRad) {
			transform.rotation.y = ang;
		} else if (diff > 0)
			transform.rotation.y += 30.0f * DegToRad;
		else if (diff < 0)
			transform.rotation.y -= 30.0f * DegToRad;
#else // ���σo�[�W����
		XMMATRIX mat = XMMatrixRotationY(transform.rotation.y);
		VECTOR3 foward = VECTOR3(0, 0, 1) * mat; // ����
		VECTOR3 velNorm = normalize(velocity); // �����P�ɂ���
		float ip = dot(foward, velNorm); // forward��velNorm�œ��ς�����cos�Ƃ����܂�
		if (ip > cos(30.0f * DegToRad)) {
			transform.rotation.y = atan2(velocity.x, velocity.z);// ���͕���������(atan2�ŋ��߂�
		} else {
			VECTOR3 right = VECTOR3(1, 0, 0) * mat; // �E
			float ip = dot(right, velocity); // ���ς����
			if (ip > 0) {
				transform.rotation.y += 30.0f * DegToRad;
			} else {
				transform.rotation.y -= 30.0f * DegToRad;
			}
		}
#endif
		transform.position += velocity * 0.5f;
	}
	//����
	XMMATRIX mat = XMMatrixRotationY(transform.rotation.y);
	VECTOR3 foward = VECTOR3(0, 0, 1) * mat; // ����
	VECTOR3 right = VECTOR3(1, 0, 0) * mat; // �E
	VECTOR3 up = VECTOR3(0, 1, 0) * mat; // ��

	if (GameDevice()->m_pDI->CheckKey(KD_TRG, DIK_M)) {
		animator->Play(A_ATTACK1);
		state = ST_ATT1;
	}
}

void Player::UpdateAttack1()
{
	if (animator->Finished())
	{
		animator->Play(A_RUN);
		state = ST_NORMAL;
	}
}

void Player::UpdateAttack2()
{
}

void Player::UpdateAttack3()
{
}

#include "Player.h"
#include "../Libs/Imgui/imgui.h"
#include "Golem.h"

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
	mesh->LoadAnimation(A_WAIT, "Data/Player/Idle.anmx", true);
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
	case ST_NORMAL:		UpdateNormal();		break;
	case ST_ATT1:		UpdateAttack1();	break;
	case ST_ATT2:		UpdateAttack2();	break;
	case ST_ATT3:		UpdateAttack3();	break;
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

void Player::Draw()
{
	Object3D::Draw();
	CSprite spr;
	MATRIX4X4 handMat = mesh->GetFrameMatrices(animator, 34);
	MATRIX4X4 mat = handMat * transform.matrix();
	VECTOR3 hand = VECTOR3(0,0,0) * mat;
	const VECTOR3 top = VECTOR3(0.9966, 0.6536, 0.14);
	VECTOR3 t = top * mat;
	spr.DrawLine3D(hand, t,	0x0000ff);
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
	if (magnitude(ret) > 1.0f) { // 長さが１を超えてるので
		ret = normalize(ret); // 長さを１にする
	}
	return ret;
}

void Player::UpdateNormal()
{
	VECTOR2 stick = LStickVec();
	VECTOR3 camVec = GameDevice()->m_vLookatPt -
		GameDevice()->m_vEyePt;
	float camAng = atan2f(camVec.x, camVec.z); // カメラの角度
	VECTOR3 velocity = VECTOR3(stick.x, 0, -stick.y);
	if (magnitude(velocity) > 0) {
		velocity = velocity * XMMatrixRotationY(camAng);
#if false // 角度バージョン
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
#else // 内積バージョン
		XMMATRIX mat = XMMatrixRotationY(transform.rotation.y);
		VECTOR3 foward = VECTOR3(0, 0, 1) * mat; // 正面
		VECTOR3 velNorm = normalize(velocity); // 長さ１にする
		float ip = dot(foward, velNorm); // forwardとvelNormで内積を取るとcosθが求まる
		if (ip > cos(30.0f * DegToRad)) {
			transform.rotation.y = atan2(velocity.x, velocity.z);// 入力方向を向く(atan2で求める
		} else {
			VECTOR3 right = VECTOR3(1, 0, 0) * mat; // 右
			float ip = dot(right, velocity); // 内積を取る
			if (ip > 0) {
				transform.rotation.y += 30.0f * DegToRad;
			} else {
				transform.rotation.y -= 30.0f * DegToRad;
			}
		}
#endif
		transform.position += velocity * 0.2f;
		Golem* gom = ObjectManager::FindGameObject<Golem>();
		transform.position += gom->CollideSphere(
					transform.position + VECTOR3(0,0.5,0), 0.5);
					//	足元の50cm上を中心に、半径50cm
		animator->Play(A_RUN);
	} else {
		animator->Play(A_WAIT);
	}
	//メモ
	XMMATRIX mat = XMMatrixRotationY(transform.rotation.y);
	VECTOR3 foward = VECTOR3(0, 0, 1) * mat; // 正面
	VECTOR3 right = VECTOR3(1, 0, 0) * mat; // 右
	VECTOR3 up = VECTOR3(0, 1, 0) * mat; // 上

	if (GameDevice()->m_pDI->CheckKey(KD_TRG, DIK_M)) {
		animator->MergePlay(A_ATTACK1);
		state = ST_ATT1;
		attackPushed = false;
	}
}

void Player::UpdateAttack1()
{
	if (animator->CurrentFrame() < 70.0f) {
		animator->SetPlaySpeed(2.0f);
	} else {
		animator->SetPlaySpeed(1.2f);
	}
	// 70フレームまでに攻撃ボタンを押したら{
	if (animator->CurrentFrame() < 70.0f) {
		if (GameDevice()->m_pDI->CheckKey(KD_TRG, DIK_M)) {
			attackPushed = true;
		}
	} else {
		if (attackPushed) {
			animator->Play(A_ATTACK2);
			state = ST_ATT2;
			attackPushed = false;
		}
	}

	if (animator->Finished())
	{
		animator->MergePlay(A_RUN);
		state = ST_NORMAL;
	}
}

void Player::UpdateAttack2()
{
	if (animator->CurrentFrame() < 70.0f) {
		animator->SetPlaySpeed(2.0f);
	} else {
		animator->SetPlaySpeed(1.2f);
	}
	// 70フレームまでに攻撃ボタンを押したら{
	if (animator->CurrentFrame() < 70.0f) {
		if (GameDevice()->m_pDI->CheckKey(KD_TRG, DIK_M)) {
			attackPushed = true;
		}
	} else {
		if (attackPushed) {
			animator->Play(A_ATTACK3);
			state = ST_ATT3;
			attackPushed = false;
		}
	}

	if (animator->Finished())
	{
		animator->Play(A_RUN);
		state = ST_NORMAL;
	}
}

void Player::UpdateAttack3()
{
	if (animator->Finished())
	{
		animator->Play(A_RUN);
		state = ST_NORMAL;
	}
}

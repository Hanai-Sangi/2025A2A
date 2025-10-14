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
}

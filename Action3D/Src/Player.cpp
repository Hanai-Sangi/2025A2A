#include "Player.h"

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
	animator->Update();
}

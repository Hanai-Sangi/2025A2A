#include "Player.h"

Player::Player()
{
	mesh = new CFbxMesh();
	mesh->Load("Data/Ghost/PacMan.mesh");
	animator = new Animator();
	animator->SetModel(mesh);
	mesh->LoadAnimation(0, "Data/Ghost/PacMan.anmx", true);
	animator->Play(0);
	animator->SetPlaySpeed(1.0f);
}

Player::~Player()
{
	if (animator != nullptr) {
		delete animator;
		animator = nullptr;
	}
	if (mesh != nullptr) {
		delete mesh;
		mesh = nullptr;
	}
}

void Player::Update()
{
	Object3D::Update();
}

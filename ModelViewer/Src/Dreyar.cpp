#include "Dreyar.h"

Dreyar::Dreyar()
{
	mesh = new CFbxMesh();
	mesh->Load("Data/Dreyar/Dreyar.mesh");
	animator = new Animator();
	animator->SetModel(mesh);
	mesh->LoadAnimation(0, "Data/Dreyar/Dreyar_Idle.anmx", true);
	animator->Play(0);
	animator->SetPlaySpeed(1.0f);
}

Dreyar::~Dreyar()
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

void Dreyar::Update()
{
	Object3D::Update();
}

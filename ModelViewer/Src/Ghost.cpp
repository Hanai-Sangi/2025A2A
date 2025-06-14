#include "Ghost.h"

Ghost::Ghost()
{
	mesh = new CFbxMesh();
	mesh->Load("Data/Ghost/Ghost.mesh");
}

Ghost::~Ghost()
{
	delete mesh;
	mesh = nullptr;
}

void Ghost::Update()
{
	CDirectInput* input = GameDevice()->m_pDI;
	if (input->CheckKey(KD_DAT, DIK_D)) {
		transform.position.x += 0.01f;
	}
	if (input->CheckKey(KD_DAT, DIK_A)) {
		transform.position.x -= 0.01f;
	}
	if (input->CheckKey(KD_DAT, DIK_W)) {
		transform.position.z += 0.05f;
	}
	if (input->CheckKey(KD_DAT, DIK_S)) {
		transform.position.z -= 0.05f;
	}
	if (input->CheckMouse(KD_DAT, DIM_RBUTTON)) {
		transform.rotation.y += 3.0f * DegToRad;
	}
	if (input->CheckMouse(KD_DAT, DIM_LBUTTON)) {
		transform.rotation.y -= 3.0f * DegToRad;
	}
	Object3D::Update();
}

#include "Golem.h"

enum ANIM_ID {
	A_IDLE = 0,
	A_WALK,
	A_ATTACK,
	A_DIE,
};

Golem::Golem(VECTOR3 pos, float rotY)
{
	mesh = new CFbxMesh();
	mesh->Load("Data/Golem/golem.mesh");
	mesh->LoadAnimation(A_IDLE, "Data/Golem/golem_stand.anmx", true);
	mesh->LoadAnimation(A_WALK, "Data/Golem/golem_walk.anmx", true);
	mesh->LoadAnimation(A_ATTACK, "Data/Golem/golem_attack.anmx", true);
	mesh->LoadAnimation(A_DIE, "Data/Golem/golem_die.anmx", true);
	animator = new Animator();
	animator->SetModel(mesh);
	animator->Play(A_WALK);

	transform.position = pos;
	transform.rotation = VECTOR3(0, rotY, 0);
	transform.scale = VECTOR3(0.3, 0.3, 0.3);
}

Golem::~Golem()
{
}

void Golem::Update()
{
	animator->Update();
}

VECTOR3 Golem::CollideSphere(VECTOR3 center, float radius)
{
	VECTOR3 myCenter = transform.position + VECTOR3(0, 0.5f, 0);
	float myRad = 1.0f;
	VECTOR3 dir = center - myCenter;
	float d = magnitude(dir);
	if ( d < radius + myRad ) {
		//押し返すベクトルを返す
		//dirの向きに、めり込んだ量を返す
		return normalize(dir) * (radius + myRad - d);
	}
	return VECTOR3(0, 0, 0);
}

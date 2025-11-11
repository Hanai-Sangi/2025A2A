#include "Golem.h"
#include "Player.h"

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
	mesh->LoadAnimation(A_ATTACK, "Data/Golem/golem_attack.anmx", false);
	mesh->LoadAnimation(A_DIE, "Data/Golem/golem_die.anmx", false);
	animator = new Animator();
	animator->SetModel(mesh);

	transform.position = pos;
	transform.rotation = VECTOR3(0, rotY, 0);
	transform.scale = VECTOR3(0.3, 0.3, 0.3);

	action = ACT_STAND;
	intent = INT_WALK;
	animator->Play(A_IDLE);
}

Golem::~Golem()
{
}

void Golem::Update()
{
	animator->Update();
	UpdateIntention();
	UpdateAction();
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

void Golem::UpdateIntention()
{
	switch (intent) {
	case INT_WALK:
		IntWalk();
		break;
	case INT_ATTACK:
		IntAttack();
		break;
	}
}

void Golem::ChangeIntention(Intent inte)
{
	if (intent == inte)
		return;
	switch (inte)
	{
	case INT_ATTACK:
		ChangeAction(ACT_CHASE);
	}
	intent = inte;
}

void Golem::IntWalk()
{
	if (Playerが視野に入った）{
		ChangeIntention(INT_ATTACK);
	}
}

void Golem::IntAttack()
{
}

void Golem::UpdateAction()
{
	switch (action) {
	case ACT_CHASE:
		ActChase();
		break;
	case ACT_PUNCH:
		ActPunch();
		break;
	case ACT_STAND:
		ActStand();
		break;
	}
}

void Golem::ChangeAction(Action act)
{
	if (action==act)
		return;

	switch (act) {
	case ACT_CHASE:
		animator->Play(A_WALK);
		animator->SetPlaySpeed(5.0f);
		break;
	case ACT_PUNCH:
		animator->Play(A_ATTACK);
		animator->SetPlaySpeed(1.0f);
		break;
	case ACT_STAND:
		animator->Play(A_IDLE);
		animator->SetPlaySpeed(1.0f);
		break;
	}
	action = act;
}

void Golem::ActChase()
{
	const float RotSpeed = 20 * DegToRad; // 回転の速さ
	float& rotY = transform.rotation.y;

	Player* pl = ObjectManager::FindGameObject<Player>();
	VECTOR3 plPos = pl->GetTransform().position;
	VECTOR3 v = plPos - transform.position;
	VECTOR3 vNorm = normalize(v); // 向きだけ
	MATRIX4X4 mat = XMMatrixRotationY(rotY);
	VECTOR3 forward = VECTOR3(0,0,1)*mat;
	if (dot(vNorm, forward) > cosf(RotSpeed)) {
		rotY = atan2f(v.x, v.z);
	} else {
		VECTOR3 right = VECTOR3(1, 0, 0) * mat;
		if (dot(right, v) > 0) {
			rotY += RotSpeed;
		} else {
			rotY -= RotSpeed;
		}
	}
	VECTOR3 move = VECTOR3(0,0,1) * XMMatrixRotationY(transform.rotation.y);
	transform.position += move * 0.05f;
	if ((plPos - transform.position).Length() < 2.0f) { //近づいた
		ChangeAction(ACT_PUNCH);
	}
}

void Golem::ActPunch()
{
	if (animator->Finished()) {
		ChangeAction(ACT_CHASE);
	}
}

void Golem::ActStand()
{
}

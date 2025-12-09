#include "Golem.h"
#include "Player.h"
#include "MyLibrary.h"
#include "EnemyManager.h"

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
	teritoriCenter = pos;

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
	// 他キャラとの当たり判定
	if (intent != INT_DEAD) {
		auto enemies = ObjectManager::FindGameObjects<Golem>();
		for (Golem* e : enemies) {
			// eと球の当たり判定
			// 自分の座標transform.position
			// 相手の座標e->GetTransform().position
			VECTOR3 v = transform.position - e->GetTransform().position;
			v.y = 0;
			float len = v.Length();
			if (len < 2.0f) {
				//当たった
				transform.position += normalize(v)*(2.0f-len);
			}
		}
	}

}

void Golem::Draw()
{
	Object3D::Draw();
	DrawSphere(transform.position, SonicRadius, RED); //shougekiha
	float f = animator->CurrentFrame();
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

bool Golem::CollideSword(VECTOR3 top, VECTOR3 btm)
{
	if (CollideSegmentToSphere(top, btm, 
				transform.position + VECTOR3(0, 1, 0), 1))
	{
		ChangeIntention(INT_DEAD);
	}
	return false;
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
	case INT_BACK:
		IntBack();
		break;
	case INT_DEAD:
		IntDead();
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
		break;
	case INT_WALK:
		ChangeAction(ACT_STAND);
		break;
	case INT_BACK:
		ChangeAction(ACT_STAND);
		break;
	case INT_DEAD:
		ChangeAction(ACT_DEAD);
		break;
	}
	intent = inte;

	// 順番待ちをキャンセル
	EnemyManager* man = ObjectManager::FindGameObject<EnemyManager>();
	man->CancelAttack(this);
}

bool Golem::InSight(VECTOR3 pos, float dist, float angle)
{
	VECTOR3 v = pos - transform.position;
	VECTOR3 vNorm = normalize(v);
	MATRIX4X4 mat = XMMatrixRotationY(transform.rotation.y);
	VECTOR3 forward = VECTOR3(0, 0, 1) * mat;

	if (magnitude(v) > dist)
		return false;
	return (dot(vNorm, forward) > cosf(angle));
}

void Golem::IntWalk()
{
	Player* pl = ObjectManager::FindGameObject<Player>();
	VECTOR3 plPos = pl->GetTransform().position;
	if (InSight(plPos, 5.0f, 30 * DegToRad)) {
		ChangeIntention(INT_ATTACK);
	}
}


void Golem::IntAttack()
{
	// 視野から外れたので、攻撃やめる
	Player* pl = ObjectManager::FindGameObject<Player>();
	VECTOR3 plPos = pl->GetTransform().position;
	if (not InSight(plPos, 6.0f, 40 * DegToRad)) {
		ChangeIntention(INT_BACK);
	}

	// テリトリーから外れたので、攻撃やめる
	VECTOR3 v = transform.position - teritoriCenter;
	if (magnitude(v) > 10.0f) {
		ChangeIntention(INT_BACK);
	}
}

void Golem::IntBack()
{
	animator->Play(A_WALK);
	animator->SetPlaySpeed(1.0f);
	//teritoriCenterに向かって移動
	const float RotSpeed = 20 * DegToRad; // 回転の速さ
	float& rotY = transform.rotation.y;

//	Player* pl = ObjectManager::FindGameObject<Player>();
//	VECTOR3 plPos = pl->GetTransform().position;
	VECTOR3 v = teritoriCenter - transform.position;
	VECTOR3 vNorm = normalize(v); // 向きだけ
	MATRIX4X4 mat = XMMatrixRotationY(rotY);
	VECTOR3 forward = VECTOR3(0, 0, 1) * mat;
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
	VECTOR3 move = VECTOR3(0, 0, 1) * XMMatrixRotationY(transform.rotation.y);
	transform.position += move * 0.02f;

	v = teritoriCenter - transform.position;
	if (magnitude(v) < 1.0f) {
		ChangeIntention(INT_WALK);
	}
}

void Golem::IntDead()
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
	case ACT_DEAD:
		ActDead();
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
	case ACT_DEAD:
		deadTimer = 0.0f;
		animator->Play(A_DIE);
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
	if ((plPos - transform.position).Length() < 2.0f) { //近づいた
		EnemyManager* man = 
			ObjectManager::FindGameObject<EnemyManager>();
		if (man->CanAttack(this)) {
			ChangeAction(ACT_PUNCH);
		}
	} else {
		transform.position += move * 0.05f;
	}
}

void Golem::ActPunch()
{
	if (animator->Finished()) {
		ChangeAction(ACT_CHASE);
	}
	float f = animator->CurrentFrame();
	if (f>30.0f) {
		EnemyManager* man = ObjectManager::FindGameObject<EnemyManager>();
		man->CancelAttack(this);
	}
	// 80～110フレームで衝撃波
	if (f >= 80.0f && f <= 110.0f) {
		Player* p = ObjectManager::FindGameObject<Player>();
		float rate = (f - 80.0f) / (110.f - 80.0f);
		SonicRadius = 4.0f * rate; //kokowo 0kara4.0he hirogeru
		p->CollideCircle(transform.position, SonicRadius);
	} else {
		SonicRadius = 0.0f;
	}
}

void Golem::ActStand()
{
}

void Golem::ActDead()
{
	float f = animator->CurrentFrame();
	if (f >= 50.0f) {
		animator->SetPlaySpeed(f / 50.0f);
	}
	if (animator->Finished()) {
		deadTimer += 1.0f;
		if (deadTimer > 30.0f) {
			transform.position.y -= 0.01f;
			if (transform.position.y < -1.0f) {
				DestroyMe();
			}
		}
	}
}

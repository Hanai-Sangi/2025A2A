#include "Coin.h"
#include "Player.h"

Coin::Coin()
{
	mesh = new CFbxMesh();
	mesh->Load("data/LowPoly/Coin.mesh");
	gotten = false;
}

Coin::Coin(VECTOR3 pos)
{
	transform.position = pos;

	mesh = new CFbxMesh();
	mesh->Load("data/LowPoly/Coin.mesh");
}

Coin::~Coin()
{
}

void Coin::Update()
{
	static const float JumpTime = 30.0f; // �t���[����
	static const float JumpHeight = 2.0f;
	if (gotten) {
		// �R�C�����v���C���[�ɋ߂Â�
		Player* pl = ObjectManager::FindGameObject<Player>();
		VECTOR3 plPos = pl->GetTransform().position;
		VECTOR3 diff = plPos - transform.position;
		diff.y = 0; // �������������ōl����̂�
		transform.position += diff / frameTime;
		frameTime -= 1;

		// �W�����v���̃v���O����
		velocityY -= 2.0f*JumpHeight/(JumpTime/2)/(JumpTime/2); // �d�͉����x
		transform.position.y += velocityY;
		// �W�����v���I�������DestroyMe();
		if (frameTime == 0) {
			DestroyMe();
		}
	} else {
		Player* pl = ObjectManager::FindGameObject<Player>();
		VECTOR3 plPos = pl->GetTransform().position;
		VECTOR3 diff = plPos - transform.position;
		if (diff.Length() < 0.4f + 0.4f) {
			gotten = true;
			// �W�����v�J�n
			velocityY = 2.0f * JumpHeight / (JumpTime / 2); // ��ɍs������
			frameTime = JumpTime; // int�ɂ��Ă���
		}
	}
}

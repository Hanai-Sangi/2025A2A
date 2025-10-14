#include "Player.h"
#include "stage.h"
#include "PlayScene.h"

Player::Player()
{
	mesh = new CFbxMesh();
	mesh->Load("data/Mousey/Mousey.mesh");
	animator = new Animator();
	animator->SetModel(mesh);
	mesh->LoadAnimation(0,"data/Mousey/Anim_Run.anmx", true);
	animator->Play(0);
}

Player::Player(VECTOR3 pos)
{	
	transform.position = pos;

	mesh = new CFbxMesh();
	mesh->Load("data/Mousey/Mousey.mesh");
	animator = new Animator();
	animator->SetModel(mesh);
	mesh->LoadAnimation(0, "data/Mousey/Anim_Run.anmx", true);
	animator->Play(0);

	MATRIX4X4 mat = XMMatrixRotationY(
		transform.rotation.y);

	VECTOR3 comPos = transform.position 
					+ VECTOR3(2, 4, -4) * mat;







	VECTOR3 camLook = transform.position + VECTOR3(0, 2, 0) * mat;  // Look�͂��Ƃ����O�������]�i��mat�j���Ă��ς��Ȃ� (1, 2, 0)�ɂ���Ǝ��_���΂ߌ��ɂȂ�

	GameDevice()->m_mView = XMMatrixLookAtLH(
		comPos, camLook, VECTOR3(0, 1, 0));
}

Player::~Player()
{
}

void Player::Update()
{
	animator->Update();

	PlayScene* scene =
				dynamic_cast<PlayScene*>(SceneManager::CurrentScene());

	if (!scene->CanMove()) { // �����Ȃ��̂�
		return;
	}

	CDirectInput* di = GameDevice()->m_pDI;
	if (di->CheckKey(KD_DAT, DIK_D))
	{
		transform.rotation.y += 3.0f * DegToRad;
	}
	if (di->CheckKey(KD_DAT, DIK_A))
	{
		transform.rotation.y -= 3.0f * DegToRad;
	}
	if (di->CheckKey(KD_DAT, DIK_W))
	{
		// �L�����N�^�[�̑O�ɐi��
		// float speed = 0.05f;
		VECTOR3 move = VECTOR3(0,0,0.05f);  // ����ĂȂ����̈ړ��x�N�g�� (0,0,1)*0.05f�ł�����
		//VECTOR3 move = VECTOR3(0,0,1)
		MATRIX4X4 mat = XMMatrixRotationY(
			transform.rotation.y);  // ��]�s��

		transform.position =      // �V�����ꏊ 
		transform.position/*���̏ꏊ*/ + move * mat/*�ړ���*/;
		//�ړ��ʂ͉���Ă��Ȃ����̈ړ��x�N�g�� �~ ��]�s��

		// �ǂƓ��Ă�
		Stage* stage = ObjectManager::FindGameObject<Stage>();
		if (stage != nullptr)
		{ 
			VECTOR3 push =
			stage->CollideSphere(transform.position + 
				VECTOR3(0, 0.5f, 0)/*���̒��S �� �v���C���[���W��0.5�� */, 0.4f/*���̔��a*/);
			transform.position += push;  //�����Ԃ��x�N�g����������
			push = stage->CollideSphere(transform.position +
				VECTOR3(0, 0.5f, 0), 0.4f);
			transform.position += push;
		}

	}

	MATRIX4X4 mat = XMMatrixRotationY(
		transform.rotation.y);

	VECTOR3 comPos = transform.position + VECTOR3(2, 4, -4) * mat;
	VECTOR3 camLook = transform.position + VECTOR3 (0, 2, 0) * mat;  // Look�͂��Ƃ����O�������]�i��mat�j���Ă��ς��Ȃ� (1, 2, 0)�ɂ���Ǝ��_���΂ߌ��ɂȂ�

	GameDevice()->m_mView = XMMatrixLookAtLH(
		comPos, camLook, VECTOR3(0, 1, 0));
}

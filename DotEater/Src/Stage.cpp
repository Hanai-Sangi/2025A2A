#include "Stage.h"
#include <vector>
#include "Player.h"
#include "Coin.h"
#include "CsvReader.h"

//std::vector<std::vector<int>> map = {  
//	{ 1, 1, 2, 1 },  //map[0].size()
//	{ 1, 3, 3, 1 },  //map[1]
//	{ 1, 1, 1, 1 },  //map[2]
//};
std::vector<std::vector<int>> map;

Stage::Stage() : Stage(0)
{
}

Stage::Stage(int stageNo)
{
	mesh = new CFbxMesh();
	mesh->Load("data/LowPoly/WallStone.mesh");	

	meshCol = new MeshCollider();
	meshCol->MakeFromMesh(mesh);// �����蔻��p�̃��f���f�[�^

	// csv����map�����
	char filename[30];
	sprintf_s<30>(filename, "data/Stage%02d.csv", stageNo);
	CsvReader* csv = new CsvReader(filename);
	map.resize(csv->GetLines());
	for (int z = 0; z < csv->GetLines(); z++) {
		map[z].resize(csv->GetColumns(z));
		for (int x = 0; x < csv->GetColumns(z); x++) {
			map[z][x] = csv->GetInt(z, x);
		}
	}
	delete csv;

	// map [][] ���Q�ɂȂ��Ă���΁A������new Player����
	for (int z = 0; z < map.size(); z++)  //sizeof(int)�ɂ����short�ɂ�����^�ς���ƍ���
	{
		for (int x = 0; x < map[z].size(); x++)
		{

			if (map[z][x] == 2)
			{
				new Player(VECTOR3(x, 0, -z));
			}
			else if (map[z][x] == 3)
			{
				new Coin(VECTOR3(x, 0, -z));
			}
		}
	}
}

Stage::~Stage()
{
}

void Stage::Update()
{
}

void Stage::Draw()
{
	for (int z = 0; z < map.size(); z++)  //sizeof(int)�ɂ����short�ɂ�����^�ς���ƍ���
	{
		for (int x = 0; x < map[z].size(); x++)
		{

			if (map[z][x] == 1)
			{
				transform.position = VECTOR3(x, 0, -z);
				Object3D::Draw();
			}
		}
	}
}

VECTOR3 Stage::CollideSphere(VECTOR3 center, float radius)
{
	VECTOR3 pushVec = VECTOR3(0,0,0); // �����Ԃ��x�N�g��
	float maxLen = 0; // ����Ԓ������
	for (int z = 0; z < map.size(); z++)
	{
		for (int x = 0; x < map[z].size(); x++)
		{
			if (map[z][x] == 1)
			{
				transform.position = VECTOR3(x, 0, -z);
				SphereCollider coll;
				coll.center = center;
				coll.radius = radius;
				MeshCollider::CollInfo info; // �����������
				if (HitSphereToMesh(coll, &info))
				{
					// �������Ă�B�����������info�ɂ���
					VECTOR3 v = center - info.hitPosition;
					VECTOR3 vNorm/*v�̌���*/ = v.Norm();
					float vLen/*v�̒���*/ = v.Length();
					float pushLen = radius - vLen;
					if (pushLen > maxLen) {
						maxLen = pushLen;
						pushVec = vNorm * pushLen;
					}
				}
			}
		}
	}
	return pushVec;
}

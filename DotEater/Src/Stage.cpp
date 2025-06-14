#include "Stage.h"
#include <vector>
#include "Player.h"
#include "Coin.h"

std::vector<std::vector<int>> map = {  
	{ 1, 1, 2, 1 },  //map[0].size()
	{ 1, 3, 3, 1 },  //map[1]
	{ 1, 1, 1, 1 },  //map[2]

	// std::vector は配列 
	// map の中に std::vector が入ってて その中に int が入ってる
};


Stage::Stage()
{
	mesh = new CFbxMesh();
	mesh->Load("data/LowPoly/WallStone.mesh");	

	meshCol = new MeshCollider();
	meshCol->MakeFromMesh(mesh);// 当たり判定用のモデルデータ

	// map [][] が２になっていれば、そこにnew Playerする

	for (int z = 0; z < map.size(); z++)  //sizeof(int)にするとshortにしたり型変えると困る
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
	for (int z = 0; z < map.size(); z++)  //sizeof(int)にするとshortにしたり型変えると困る
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
	VECTOR3 pushVec = VECTOR3(0,0,0); // 押し返すベクトル
	float maxLen = 0; // 今一番長いやつ
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
				MeshCollider::CollInfo info; // 当たった情報
				if (HitSphereToMesh(coll, &info))
				{
					// 当たってる。当たった情報がinfoにある
					VECTOR3 v = center - info.hitPosition;
					VECTOR3 vNorm/*vの向き*/ = v.Norm();
					float vLen/*vの長さ*/ = v.Length();
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

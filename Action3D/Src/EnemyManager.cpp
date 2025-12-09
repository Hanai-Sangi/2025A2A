#include "EnemyManager.h"

EnemyManager::EnemyManager()
{
	waiting.clear();
}

EnemyManager::~EnemyManager()
{
}

bool EnemyManager::CanAttack(Golem* golem)
{
	// ボードに入ってないなら
	// ①イテレーターで正しく回す
	//for (std::list<Golem*>::iterator itr = waiting.begin();
	//						itr != waiting.end(); itr++) {
	//	Golem* g = *itr;
	//}
	// ②イテレーターの宣言をautoにした
	//for (auto itr = waiting.begin(); itr != waiting.end(); itr++) {
	//	auto g = *itr;
	//}
	// ③要素抽出のforを使ったもの

	bool found = false;
	for (Golem* g : waiting) {
		if (g == golem) { // すでに登録済
			found = true;
			break;
		}
	}
	// Waitingボードに追加
	if (not found) {
		waiting.push_back(golem);
	}
	// Waitingボードの先頭ならばtrueを返す
	// begin()は先頭のデータのアドレス
	return *(waiting.begin()) == golem;
}

void EnemyManager::CancelAttack(Golem* golem)
{
	waiting.remove(golem); // リストから取り除く
}

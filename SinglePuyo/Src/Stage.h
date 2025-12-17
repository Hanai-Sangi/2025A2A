#pragma once
#include "GameObject.h"
#include <vector>
#include "Puyo.h"

class Stage : public GameObject
{
public:
	Stage();
	~Stage();
	void Update() override;
	void Draw() override;
	Puyo::Color Get(int x, int y) {
		return cells[x][y].color;
	}

	/// <summary>
	/// 移動してもいいかを調べる
	/// </summary>
	/// <param name="x">マスのＸ座標</param>
	/// <param name="y">マスのＹ座標</param>
	/// <returns>移動できるならtrue</returns>
	bool CanMove(int x, int y);

	void Set(int x, int y, Puyo::Color c);
private:
	bool EraseCheck(); // 消える判定
	int ConnectCheck(int x, int y);
	void EraseChecked();
	void EraseBegin();

	CSpriteImage* image;
	CSprite* spr;
	struct Cell { // 1つのマスの情報
		Puyo::Color color;
		bool checked; // 調べた
	};
	static const int WIDTH = 8;
	static const int HEIGHT = 15;

	// 盤面のデータを作る（Cellの二次元配列）
	Cell cells[WIDTH][HEIGHT];

	// 盤面を初期化（壁を配置、１つだけPuyoを置く
	// Stage::Stage()で初期化する

	// 盤面のデータ通りに画面に表示する

};
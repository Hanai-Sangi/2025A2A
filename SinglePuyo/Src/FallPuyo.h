#pragma once
//FallPuyo.h
#include "GameObject.h"
#include "Puyo.h"

class FallPuyo : public GameObject {
public:
	FallPuyo();
	~FallPuyo();
	void Update() override;
	void Draw() override;
private:
	CSpriteImage* image;
	CSprite* spr;
	int x, y; // マスの座標
	Puyo::Color color;

	float timer; // 落ちる時間を計測
};
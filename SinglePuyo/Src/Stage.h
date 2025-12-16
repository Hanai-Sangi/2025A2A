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
private:
	CSpriteImage* image;
	CSprite* spr;
	struct Cell {
		Puyo::Color color;
	};
	static const int WIDTH = 8;
	static const int HEIGHT = 15;
};
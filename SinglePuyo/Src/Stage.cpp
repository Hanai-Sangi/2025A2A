#include "Stage.h"

Stage::Stage()
{
	image = new CSpriteImage(GameDevice()->m_pShader, "Data/puyo_sozai.png");
	spr = new CSprite(image);
}

Stage::~Stage()
{
	delete spr;
	delete image;
}

void Stage::Update()
{
}

void Stage::Draw()
{
	int x = 200;
	int y = 100;
	int col = Puyo::C_GREEN;
	spr->Draw(image, x, y, col * 32, 0, 32, 32);
}
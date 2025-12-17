#include "Stage.h"

Stage::Stage()
{
	image = new CSpriteImage(GameDevice()->m_pShader, "Data/puyo_sozai.png");
	spr = new CSprite(image);

	for (int x = 0; x < WIDTH; x++) {
		for (int y = 0; y < HEIGHT; y++) {
			Puyo::Color c = Puyo::C_NONE;
			if (y == HEIGHT - 1 || x == 0 || x == WIDTH - 1) {
				c = Puyo::C_WALL;
			}
			cells[x][y].color = c;
		}
	}
	cells[3][4].color = Puyo::C_RED; //適当に１つ置く
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
	for (int x = 0; x < WIDTH; x++) {
		for (int y = 0; y < HEIGHT; y++) {
			int col = cells[x][y].color; // マスの色
			if (col >= Puyo::C_RED) {
				// 1つのマスの大きさは32x32
				spr->Draw(image, x * 32 + 100, y * 32 + 100,
					col * 32, 0, 32, 32);
			}
		}
	}
}

bool Stage::CanMove(int x, int y)
{
	switch (cells[x][y].color) {
	case Puyo::C_NONE:
		return true;
	}
	return false;
}

void Stage::Set(int x, int y, Puyo::Color c)
{
	cells[x][y].color = c;
}

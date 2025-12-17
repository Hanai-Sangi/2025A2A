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
	EraseCheck();
}

bool Stage::EraseCheck()
{
	for (int x = 0; x < WIDTH; x++) {
		for (int y = 0; y < HEIGHT; y++) {
			Puyo::Color c = cells[x][y].color;
			if (c == Puyo::C_NONE || c == Puyo::C_WALL)
				continue;
			if (ConnectCheck(x, y) >= 4) { // ここから４方向調べる
				//ぷよを消す（checkedがtrueのぷよのみ）
			}
		}
	}
	return false;
}

int Stage::ConnectCheck(int x, int y)
{
	if (cells[x][y].checked)
		return 0;

	char test[256];
	sprintf_s<256>(test, "Check %d %d\n", x, y);
	OutputDebugString(test);

	Puyo::Color c = cells[x][y].color;
	cells[x][y].checked = true;

	int count = 1; // 自分の分
	if (cells[x + 1][y].color == c) { // 右
		count += ConnectCheck(x + 1, y);
	}
	if (cells[x - 1][y].color == c) { // 左
		count += ConnectCheck(x - 1, y);
	}
	if (cells[x][y+1].color == c) { // 下
		count += ConnectCheck(x, y+1);
	}
	if (cells[x][y-1].color == c) { // 上
		count += ConnectCheck(x, y-1);
	}
	return count;
}

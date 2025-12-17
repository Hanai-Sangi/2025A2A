#include "FallPuyo.h"
#include "Stage.h"

FallPuyo::FallPuyo()
{
	image = new CSpriteImage(GameDevice()->m_pShader, "Data/puyo_sozai.png");
	spr = new CSprite(image);

	x = 4;
	y = 0;
	color = Puyo::C_BLUE; // とりあえず青
	timer = 1.0f;
}

FallPuyo::~FallPuyo()
{
}

void FallPuyo::Update()
{
	Stage* st = ObjectManager::FindGameObject<Stage>();
	CDirectInput* di = GameDevice()->m_pDI;
	if (di->CheckKey(KD_TRG, DIK_A)) {
		if (st->CanMove(x - 1, y)) { // １つ左に移動できるので
			x -= 1; // １つ左に移動する
		}
	}
	if (di->CheckKey(KD_TRG, DIK_D)) {
		if (st->CanMove(x + 1, y)) {
			x++;
		}
	}
	if (di->CheckKey(KD_DAT, DIK_S)) {
		timer = 0.0f;
	}

#ifdef _DEBUG
	if (di->CheckKey(KD_TRG, DIK_K)) { // 色を変える
		color = (Puyo::Color)((color+1)%5);
	}
#endif

	timer -= SceneManager::DeltaTime();
	if (timer <= 0.0f) {
		if (st->CanMove(x, y + 1)) {
			y++;
		} else {
			st->Set(x, y, color); // 確定
			x = 4; // 最初の位置に戻る
			y = 0;
			color = (Puyo::Color)(rand() % 5); // 色を乱数で
		}
		timer =	1.0f;
	}
}

void FallPuyo::Draw()
{
	spr->Draw(image, x * 32 + 100, y * 32 + 100, color * 32, 0, 32, 32);
}

#include "TitleScene.h"
#include "GameMain.h"

int calc(int d)
{
	if (d >= 10) {
		return 10;
	}
	return calc(d+1);
}

TitleScene::TitleScene()
{
	calc(0);
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	if (GameDevice()->m_pDI->
			CheckKey(KD_TRG, DIK_P)) {
		SceneManager::ChangeScene("PlayScene");
	}
}

void TitleScene::Draw()
{
	GameDevice()->m_pFont->Draw(
		20, 20, "TitleScene", 16, RGB(255, 0, 0));
}
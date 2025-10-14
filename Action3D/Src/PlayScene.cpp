#include "PlayScene.h"
#include <fstream>
#include "CsvReader.h"
#include <assert.h>
#include "Field.h"
#include "Player.h"
#include "Camera.h"

PlayScene::PlayScene()
{
	new Field();
	new Player();
	new Camera();
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	if (GameDevice()->m_pDI->CheckKey(KD_TRG, DIK_T)) {
		SceneManager::ChangeScene("TitleScene");
	}
}

void PlayScene::Draw()
{
	GameDevice()->m_pFont->Draw(
		20, 20, "PlayScene", 16, RGB(255, 255, 0));
}

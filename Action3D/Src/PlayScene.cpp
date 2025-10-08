#include "PlayScene.h"
#include <fstream>
#include "CsvReader.h"
#include <assert.h>
#include "Field.h"
#include "Player.h"

PlayScene::PlayScene()
{
	new Field();
	new Player();
	GameDevice()->m_vEyePt = VECTOR3(1, 2, -5); // カメラ座標
	GameDevice()->m_vLookatPt = VECTOR3(0, 0, 0); // 注視点
	GameDevice()->m_mView = XMMatrixLookAtLH(     // ビューマトリックス
		VECTOR3(1, 2, -5), VECTOR3(0, 1, 0), 
		VECTOR3(0, 1, 0));

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

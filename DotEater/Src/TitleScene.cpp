#include "TitleScene.h"
#include "GameMain.h"
#include <fstream>

TitleScene::TitleScene()
{
	// ファイルを読む実験
	std::ifstream ifs("data/Stage00.csv"); // ファイルを開く
	std::string str;
	std::getline(ifs, str); // 1行読む
	int n = str.find(','); // カンマの場所を探す
	std::string s = str.substr(0/*何文字目から*/, n/*何文字*/);
	int x = stoi(s); // String To Integer
	OutputDebugString(s.c_str());
	OutputDebugString("\n");
	ifs.close(); // ファイルを閉じる
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
#include "TitleScene.h"
#include "GameMain.h"
#include <fstream>

TitleScene::TitleScene()
{
	// �t�@�C����ǂގ���
	std::ifstream ifs("data/Stage00.csv"); // �t�@�C�����J��
	std::string str;
	std::getline(ifs, str); // 1�s�ǂ�
	int n = str.find(','); // �J���}�̏ꏊ��T��
	std::string s = str.substr(0/*�������ڂ���*/, n/*������*/);
	int x = stoi(s); // String To Integer
	OutputDebugString(s.c_str());
	OutputDebugString("\n");
	ifs.close(); // �t�@�C�������
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
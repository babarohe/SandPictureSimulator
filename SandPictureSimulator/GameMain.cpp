#include "GameMain.h"
#include <stdio.h>

GameMain::GameMain() {
}

GameMain::~GameMain() {
}

	
void GameMain::Load() {
}


int GameMain::Draw() {
	return 0;
}


int GameMain::Main() {
	char title_buf[MAX_STRING];

	while(true) {
		sprintf_s(title_buf, MAX_STRING, "%s  [%.02fFPS]", WINDOW_TITLE, GetFPS());
		SetMainWindowText(title_buf);

		// ��ʏ�����
		ClearDrawScreen();

		// �`��
		this->Draw();

		// ����ʕ`��
		ScreenFlip();

		// Windowm���b�Z�[�W���O����
		if (ProcessMessage() == -1) {
			return 0;
		}

	}
	return 0;
}

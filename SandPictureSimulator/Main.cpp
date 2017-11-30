#include "GameMain.h"


int end_flag = 0;
int FrameCount = 0;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
#ifdef _DEBUG
	//���O�o�͂���
	SetOutApplicationLogValidFlag(TRUE);
#else
	//���O�o�͂��Ȃ�
	SetOutApplicationLogValidFlag(FALSE);
#endif // _DEBUG

	// ��ʃ��[�h�̃Z�b�g
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);
	//�E�B���h�E���[�h�ŋN��
	ChangeWindowMode(TRUE);
	//�J�[�\��
	SetMouseDispFlag(TRUE);
	//�^�C�g��
	SetMainWindowText(WINDOW_TITLE);
	//�A�N�e�B�u�łȂ��Ă�������
	SetAlwaysRunFlag(TRUE);

	// VSync���܂�
	SetWaitVSyncFlag(TRUE);

	//�c�w���C�u��������������
	if (DxLib_Init() == -1) {
		return -1;
	}
	// �`����ʂ𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);
	//�`����o�C���j�A��
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	//	SetDrawMode(DX_DRAWMODE_NEAREST);

	
	GameMain *gm_p = new GameMain();
	
	gm_p->Main();

	delete gm_p;


	DxLib_End();

	printf("�I��\n");
	return 0;
}
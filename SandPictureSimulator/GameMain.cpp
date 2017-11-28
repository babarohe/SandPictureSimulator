#include "GameMain.h"
#include <stdio.h>

int px_table[SCREEN_WIDTH][SCREEN_HEIGHT];


double fluid_moov_n[SCREEN_WIDTH / FLUID_GRID][SCREEN_HEIGHT / FLUID_GRID];
double fluid_moov_x[SCREEN_WIDTH / FLUID_GRID][SCREEN_HEIGHT / FLUID_GRID];
double fluid_moov_y[SCREEN_WIDTH / FLUID_GRID][SCREEN_HEIGHT / FLUID_GRID];


GameMain::GameMain() {
}

GameMain::~GameMain() {
}


void GameMain::Load() {
	// ================================================================
	// �s�N�Z���e�[�u��������
	// ================================================================
	for (int i = 0; i < SCREEN_WIDTH; i++) {
		for (int j = 0; j < SCREEN_HEIGHT; j++) {
			px_table[i][j] = 0;
		}
	}

	// ================================================================
	// �v���Z�b�g������
	// ================================================================
	// [0] ���� 
	// [1] ����
	// [2] �F�� 1
	// [3] �F�� 2
	// [4] ����

	double init_hue = double(GetRand(36000)) / 100.0;
	double preset_s[MAX_PRESET] = { 0.0, 0.0, 0.9, 0.3, 0.8};
	double preset_v[MAX_PRESET] = { 0.8, 0.2, 1.0, 0.8, 0.2};
	int preset_s_rate[MAX_PRESET] = { 1000, 50, 200, 300, 25 };

	for (int i = 0; i < MAX_PRESET; i++) {
		this->preset[i].massa = (double(GetRand(280)) + 30.0) / 100.0;
		this->preset[i].h = init_hue;
		this->preset[i].s = preset_s[i];
		this->preset[i].v = preset_v[i];
		this->preset[i].shineing_rate = preset_s_rate[i];
	}

	// ================================================================
	// ��������
	// ================================================================
	for (int i = 0; i < MAX_SAND; i++) {
		int preset_id = GetRand(MAX_PRESET);
		double offset = pow(SCREEN_WIDTH / MAX_SAND, i);

		this->sand[i].y = 0.0 - GetRand(300);
		this->sand[i].x = SCREEN_WIDTH / 2 + (offset * SCREEN_WIDTH / MAX_SAND);
		

		this->sand[i].o_x = this->sand[i].x;
		this->sand[i].o_y = this->sand[i].y;

		this->sand[i].massa = this->preset[preset_id].massa * (1.25 - double(GetRand(500))/1000.0);
		this->sand[i].h = this->preset[preset_id].h;
		this->sand[i].s = this->preset[preset_id].s;
		this->sand[i].v = this->preset[preset_id].v;
		this->sand[i].shineing_rate = this->preset[preset_id].shineing_rate;
		this->sand[i].color = GetColorHSV(this->sand[i].h, this->sand[i].s, this->sand[i].v);
		this->sand[i].is_fix = false;
	}
}


int GameMain::Draw() {
	// ================================================================
	// �t�B�[���h��ԏ���
	// ================================================================
	for (int i = 0; i < SCREEN_WIDTH / FLUID_GRID; i++) {
		for (int j = 0; j < SCREEN_HEIGHT / FLUID_GRID; j++) {
			// DrawLine(i * FLUID_GRID, 0, i * FLUID_GRID, SCREEN_HEIGHT, 0x202020);
			// DrawLine(0, j * FLUID_GRID, SCREEN_WIDTH, j * FLUID_GRID, 0x202020);
			fluid_moov_n[i][j] = 0;
		}
	}

	// ================================================================
	// ��������
	// ================================================================
	for (int i = 0; i < MAX_SAND; i++) {
		// �ړ�����
		if(this->sand[i].is_fix == false) {
			this->sand[i].y += GRAVITY * this->sand[i].massa;
			this->sand[i].x += (4.9 - this->sand[i].massa) * (GetRand(2) - 1) * (this->sand[i].y / SCREEN_HEIGHT);

			// �t�B�[���h���f
			if (this->sand[i].x > 0 && this->sand[i].x < SCREEN_WIDTH && this->sand[i].y > 0 && this->sand[i].y < SCREEN_HEIGHT) {
				fluid_moov_n[int(this->sand[i].x / FLUID_GRID)][int(this->sand[i].y / FLUID_GRID)] += 1;
			}
		}

		// �s�N�Z�������蔻��
		if(this->sand[i].x > 0 && this->sand[i].x < SCREEN_WIDTH && this->sand[i].y > 0 && this->sand[i].y < SCREEN_HEIGHT) {
			if (px_table[int(this->sand[i].x)][int(this->sand[i].y) + 1] > FIX_BORDER) {
				if (px_table[int(this->sand[i].x) - 1][int(this->sand[i].y) + 1] < FIX_BORDER) {
					this->sand[i].x -= (2.8 - this->sand[i].massa) * (this->sand[i].y / SCREEN_HEIGHT);
				}
				else if (px_table[int(this->sand[i].x) + 1][int(this->sand[i].y) + 1] < FIX_BORDER) {
					this->sand[i].x += (2.8 - this->sand[i].massa) * (this->sand[i].y / SCREEN_HEIGHT);
				}
				else {
					this->sand[i].is_fix = true;
					px_table[int(this->sand[i].x)][int(this->sand[i].y)] += 1;
				}
			}
		}

		// �n�ʓ����蔻��
		if (this->sand[i].y >= SCREEN_HEIGHT-1) {
			this->sand[i].is_fix = true;
			this->sand[i].y = SCREEN_HEIGHT-1;
			if (this->sand[i].x > 0 && this->sand[i].x < SCREEN_WIDTH && this->sand[i].y > 0 && this->sand[i].y < SCREEN_HEIGHT) {
				px_table[int(this->sand[i].x)][int(this->sand[i].y)] += 1;
			}
		}


		// �ŏI����
		this->sand[i].acceleration = abs(this->sand[i].o_x - this->sand[i].x) + abs(this->sand[i].o_y - this->sand[i].y);
		this->sand[i].o_x = this->sand[i].x;
		this->sand[i].o_y = this->sand[i].y;
	}

	// ================================================================
	// �F�ʏ���
	// ================================================================
	for (int i = 0; i < MAX_SAND; i++) {
		// ��{�F
		this->sand[i].color = GetColorHSV(this->sand[i].h, this->sand[i].s, this->sand[i].v);

		// �����x�ω�����
		if (this->sand[i].acceleration > 0) {
			// �L���L������
			if ((GetRand(99)+1)%(this->sand[i].shineing_rate+1) == 1) {
				this->sand[i].color = GetColorHSV(this->sand[i].h, 0.0f, 1.0f);
			}
		}

	}

	// ================================================================
	// �`��
	// ================================================================
	for (int i = 0; i < SCREEN_WIDTH / FLUID_GRID; i++) {
		for (int j = 0; j < SCREEN_HEIGHT / FLUID_GRID; j++) {
			if (fluid_moov_n[i][j] > 0) {
				DrawBox(i * FLUID_GRID, j * FLUID_GRID, i * FLUID_GRID + FLUID_GRID, j * FLUID_GRID + FLUID_GRID, GetColorHSV(0.0f, 1.0f, fluid_moov_n[i][j] * 0.01f) , true);
			}
		}
	}

	for (int i = 0; i < MAX_SAND; i++) {
		DrawPixel(int(this->sand[i].x), int(this->sand[i].y), this->sand[i].color);
	}
	

	return 0;
}


int GameMain::Main() {
	char title_buf[MAX_STRING];

	this->Load();

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

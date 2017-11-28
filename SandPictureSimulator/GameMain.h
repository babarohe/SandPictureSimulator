#pragma once

#ifndef __GAME_MAIN_H__
#define __GAME_MAIN_H__
// #define __DOT_BY_DOT__


#include <stdio.h>
#include <iostream>
#include <string>

// ============================================================
// User Header
// ============================================================
#include "DataConst.h"
#include "CommonLib.h"
#include "DxLib.h"


// ============================================================
// ��ʉ𑜓x��`
// ============================================================
#ifdef __DOT_BY_DOT__
// �h�b�g�o�C�h�b�g
#define SCREEN_WIDTH	::GetSystemMetrics(SM_CXSCREEN)
#define SCREEN_HEIGHT	::GetSystemMetrics(SM_CYSCREEN)
#else __DOT_BY_DOT__
// �𑜓x��`
#define SCREEN_WIDTH	1024
#define SCREEN_HEIGHT	576
#endif __DOT_BY_DOT__

#define WINDOW_TITLE "SandPictureSimulator"

#define MAX_STRING 255

#define MAX_SAND 150000
#define MAX_PRESET 5

#define GRAVITY 0.25


typedef struct sand {
	double x = 0.0;
	double y = 0.0;
	double massa = 1.0;
	float h;
	float s;
	float v;
	int shineing_rate = 100;
	int color = 0xFFFFFF;
}sand_t;

class GameMain {

public:
	GameMain();
	~GameMain();
	int Main();

private:
	void Load();
	int Draw();
	sand_t sand[MAX_SAND];
	sand_t preset[MAX_PRESET];

};


#endif __GAME_MAIN_H__
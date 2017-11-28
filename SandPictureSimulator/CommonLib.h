#pragma once

#ifndef __COMMON_LIB_H__
#define __COMMON_LIB_H__

#include <stdio.h>
#include <iostream>
#include <string>

#include "DataConst.h"
#include "DxLib.h"


// FPS�擾�֐�
double GetFPS();

// �f�[�^�𕪊�
void GetData(char input[MAX_DATA_LENGTH], int *seed_id, int *entry_id, int *generation_id);

// �X�e�[�^�X�\��
void ShowStatusWithDirectX(int color, char *message);

#endif __COMMON_LIB_H__


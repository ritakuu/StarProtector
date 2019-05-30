//=============================================================================
//
// �Q�[����ʏ��� [game.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

#define DEFAULT_TIME_SPEED		(10.0f)
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void SetTimeStop(bool stop);
bool GetTimeStop(void);
float GetTimeSpeed(void);

#endif

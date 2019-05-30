//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_


#include "main.h"
#include "project3D.h"


#define PLAYER_MAX					(1)
//*****************************************************************************
// 構造体定義
//*****************************************************************************

typedef struct
{
	PROJECT3D						base;						// 3D基本構造体
	float							hp;							// Hp
	D3DXVECTOR3						diction;					// player移動方向(keyboard対応ため)		
	bool							snipermod;
	PART							gun;
	int								gunCount;
} PLAYER;


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetPlayer(int pno);

#endif

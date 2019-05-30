//=============================================================================
//
// �v���C���[���� [player.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_


#include "main.h"
#include "project3D.h"


#define PLAYER_MAX					(1)
//*****************************************************************************
// �\���̒�`
//*****************************************************************************

typedef struct
{
	PROJECT3D						base;						// 3D��{�\����
	float							hp;							// Hp
	D3DXVECTOR3						diction;					// player�ړ�����(keyboard�Ή�����)		
	bool							snipermod;
	PART							gun;
	int								gunCount;
} PLAYER;


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetPlayer(int pno);

#endif

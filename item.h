//=============================================================================
//
// �A�C�e������ [item.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_ITEM				(128)						// �A�C�e���ő吔

//**************************************
// ���
//**************************************
enum
{
	ITEMTYPE_COIN = 0,		// �R�C��
	ITEMTYPE_LIFE,			// ���C�t
	ITEMTYPE_TIMER,			// �^�C�}�[
	ITEMTYPE_MAX
};

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		// ���݂̈ʒu
	D3DXVECTOR3 rot;		// ���݂̌���
	float fRadius;			// ���a
	int nIdxShadow;			// �eID
	int nType;				// ���
	bool bUse;				// �g�p���Ă��邩�ǂ���
} ITEM;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType = ITEMTYPE_COIN);
void DeleteItem(int nIdxItem);
ITEM *GetItem(void);

#endif

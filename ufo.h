//=============================================================================
//
// �o���b�g���� [ufo.h]
// Author : lizeyu
//
//=============================================================================
#ifndef _UFO_H_
#define _UFO_H_

#include "main.h"
#include "project3D.h"

#define UFO_MAX						(1)							// �o���b�g����
#define UFO_SIZE					(3.0f)						// �o���b�g�傫���i�f�B�t�H���g�j
#define UFO_DAMAGE_PLAYER			(2)							// player�o���b�g�З�
#define UFO_DAMAGE_UFO				(1)							// �G�l�~�[�o���b�g�З�
#define UFO_HP_MAX					(10)

//�u���[�h�\����
typedef struct
{
	PROJECT3D		base;										// 3d
	int				hp;											// type ufo or player
	D3DXVECTOR3		rotshow;									// type ufo or player
	int				postarget;									// type ufo or player
} UFO;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
// �G�l�~�[������
HRESULT InitUfo(void);
// �G�l�~�[���
void UninitUfo(void);
// �G�l�~�[�X�V
void UpdateUfo(void);
// �G�l�~�[�`��idrawall���p�j
void DrawUfo();
// �G�l�~�[�擾
UFO* GetUfo(int pno);
// �G�l�~�[���ːݒu
void SetUfo(int eid, int type, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
// �G�l�~�[���ːݒu
void SetUfo(int type);

void UfoDamaged(int eid, int damage, int type);

#endif

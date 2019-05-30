//=============================================================================
//
// �o���b�g���� [bullet.h]
// Author : lizeyu
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include "project3D.h"

#define BULLET_MAX						(512)						// �o���b�g����
#define BULLET_SIZE						(3.0f)						// �o���b�g�傫���i�f�B�t�H���g�j
#define BULLET_DAMAGE_PLAYER			(2)							// player�o���b�g�З�
#define BULLET_DAMAGE_ENEMY				(1)							// �G�l�~�[�o���b�g�З�

//�u���[�h�\����
typedef struct
{
	PROJECT3D		base;											// 3d
	int				target;											// type enemy or player
	int				damage;											// �З�
} BULLET;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
// �o���b�g������
HRESULT InitBullet(void);
// �o���b�g���
void UninitBullet(void);
// �o���b�g�X�V
void UpdateBullet(void);
// �o���b�g�`��idrawall���p�j
void DrawBullet();
// �o���b�g�擾
BULLET* GetBullet(int pno);
// �o���b�g���ːݒu
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int target, int damage, float speed);
// �o���b�g���
void ResetBullet(int bno);


#endif

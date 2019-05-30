//=============================================================================
//
// �o���b�g���� [enemy.h]
// Author : lizeyu
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "project3D.h"

#define ENEMY_MAX						(12)						// �o���b�g����
#define ENEMY_SIZE						(100.0f)						// �o���b�g�傫���i�f�B�t�H���g�j
#define ENEMY_DAMAGE_PLAYER				(2)							// player�o���b�g�З�
#define ENEMY_DAMAGE_ENEMY				(1)							// �G�l�~�[�o���b�g�З�
#define ENEMY_HP_MAX					(10)

//�u���[�h�\����
typedef struct
{
	PROJECT3D		base;											// 3d
	int				hp;											// type enemy or player
} ENEMY;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
// �G�l�~�[������
HRESULT InitEnemy(void);
// �G�l�~�[���
void UninitEnemy(void);
// �G�l�~�[�X�V
void UpdateEnemy(void);
// �G�l�~�[�`��idrawall���p�j
void DrawEnemy();
// �G�l�~�[�擾
ENEMY* GetEnemy(int pno);
// �G�l�~�[���ːݒu
void SetEnemy(int eid, int type,D3DXVECTOR3 pos, D3DXVECTOR3 rot);
// �G�l�~�[���ːݒu
void SetEnemy(int type);
void SetEnemy(int uno, int type);

void EnemyDamaged(int eid,int damage,int type);

#endif

//=============================================================================
//
// �G�[������ [aim.h]
// Author :lizeyu 
//
//=============================================================================
#ifndef _AIM_H_
#define _AIM_H_

#include "main.h"
#include "project2D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_AIM_NORMAL		"data/TEXTURE/aim.png"						// �ǂݍ��ރe�N�X�`���t�@�C����
//�G�[������֌W
#define TIME_ANIMATION_AIM		(4)
#define TEXTURE_AIM_TYPE01_PATTERN_DIVIDE_X	(1)
#define TEXTURE_AIM_TYPE01_PATTERN_DIVIDE_Y	(1)
#define ANIM_PATTERN_AIM		(TEXTURE_AIM_TYPE01_PATTERN_DIVIDE_X*TEXTURE_AIM_TYPE01_PATTERN_DIVIDE_Y)

#define	AIM_POS_X				(SCREEN_CENTER_X)							// �G�[���̕\���ʒuX
#define	AIM_POS_Y				(SCREEN_CENTER_Y)							// �G�[���̕\���ʒuY
#define	AIM_SIZE_X				(30)										// �G�[���̕�
#define	AIM_SIZE_Y				(30)										// �G�[���̍���
#define AIM_MAX					(1)											// �G�[���̐�

typedef struct
{
	PROJECT2D	polygon;		//��{2D�\����
	bool		bUse;			//�G�[�������邩�ǂ���
	int			status;			//�G�[�����
}AIM;							//�G�[���\����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
//�G�[���̏�����
HRESULT InitAim(void);
//�G�[���̉��
void UninitAim(void);
//�G�[���̍X�V
void UpdateAim(void);
//�G�[���̏�Ԃ��l��
AIM* GetAim(int Ano);
//�G�[���̕`��
void DrawAim();

#endif

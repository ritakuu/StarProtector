
//=============================================================================
//
// �G�t�F�N�g���� [effect.h]
// Author : lizeyu
//
//=============================================================================


#ifndef EFFECT_H
#define EFFECT_H

#include "main.h"
#include "bullet.h"
#include "project3D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define	MAX_EFFECT_MOVE						(4096)							// �G�t�F�N�g�ő吔
#define	MAX_EFFECT_EXPLOSION				(BULLET_MAX)							// �G�t�F�N�g�ő吔
#define	MAX_EFFECT_LOCKON					(ENEMY_MAX)							// �G�t�F�N�g�ő吔
#define	MAX_EFFECT_SHIELD					(4096)							// �G�t�F�N�g�ő吔
#define	EFFECT_WIDTH_DEFAULT				(8.0f)							// �e�̔��a��
#define	EFFECT_HEIGHT_DEFAULT				(8.0f)							// �e�̔��a��
#define EFFECT_MOVE_SIZE_X					(5.0f)							// ���΃T�C�Y
#define EFFECT_MOVE_SIZE_Y					(5.0f)							// ���΃T�C�Y
#define EFFECT_MOVE_SIZE_MISSILE			(3.0f)							// �~�T�C�����΃T�C�Y
#define EFFECT_CHARGE_SIZE_X				(2.0f)							// �`���[�W�T�C�Y
#define EFFECT_CHARGE_SIZE_Y				(2.0f)							// �`���[�W�T�C�Y
#define EFFECT_SHOOT_SIZE					(60.0f)							// ���[�U�[�T�C�Y
#define EFFECT_MOVE_SPEED					(0.0f)							// ���Α��x
#define EFFECT_CHARGE_SPEED					(0.5f)							// �`���[�W�X�s�[�h
#define EFFECT_COUNT_DEFAULT				(-1)							// �J���^�[�g��Ȃ�
#define EFFECT_COUNT_CHARGE					(50)							// �`���[�W�J���^�[
#define EFFECT_SHOOT_DAMAGE					(1)								// ���[�U�[�_���[�W


//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXMATRIX		mtxWorld;						// ���[���h�}�g���b�N�X
	D3DXVECTOR3		pos;							// �ʒu
	D3DXVECTOR3		rot;							// ��]
	D3DXVECTOR3		scl;							// �X�P�[��
	XCOLOR			color;
	D3DXVECTOR2		size;
	int				CountAnim;						// �A�j���[�V�����J�E���g
	int				PatternAnim;					// �A�j���[�V�����p�^�[���i���o�[
	float			speed;
	bool			bUse;							// �g�p���Ă��邩�ǂ���
	int				count;
	int				type;
	PROJECT3D*		parent;

} EFFECT;


typedef struct
{
	float	sp;
	float	spmax;
	int		sid;
	int		count;

} SHIELD;



//HRESULT InitEffectMove(int type);
//void UninitEffectMove(void);
//void UpdateEffectMove(void);
//void DrawEffectMove(int id);
//int SetEffectMove(D3DXVECTOR3 pos, D3DXVECTOR3 rot, XCOLOR color, float sizeX, float sizeY, int count, float speed);
//void SetEffectCharge(D3DXVECTOR3 pos, int num, XCOLOR color, float sizeX, float sizeY, int count, float speed);
//void SetEffectShoot(D3DXVECTOR3 pos, D3DXVECTOR3 rot, XCOLOR color, float sizeX, float sizeY, int count, float speed);
//EFFECT *GetEffectMove(int eid);
//void PushEffectMove();
//


HRESULT InitEffectExplosion();
void UninitEffectExplosion(void);
void UpdateEffectExplosion(void);
void DrawEffectExplosion(void);
int SetEffectExplosion(D3DXVECTOR3 pos, float sizeX, float sizeY);
EFFECT *GetEffectExplosion(int eid);

//HRESULT InitEffectField(int type);
//void UninitEffectField(void);
//void UpdateEffectField(void);
//void DrawEffectField(int id);
//EFFECT *GetEffectField(int eid);
//void PushEffectField();
//
//HRESULT InitEffectLockon(int type);
//void UninitEffectLockon(void);
//void UpdateEffectLockon(void);
//void DrawEffectLockon(int id);
//int SetEffectLockon(D3DXVECTOR3 pos, float sizeX, float sizeY);
//EFFECT *GetEffectLockon(int eid);
//
//EFFECT *GetEffectShield(int eid);
//HRESULT InitEffectShield(int type);
//void UninitEffectShield(void);
//void UpdateEffectShield(void);
//void DrawEffectShield(int id);
//int SetEffectShield(D3DXVECTOR3 pos, float size, float color, PROJECT3D* parent);
//void PushEffectShield();
//
//void InitEffect(int type);
//void UpdateEffect(void);
//void UninitEffect(void);
//
#endif // !EFFECT_H

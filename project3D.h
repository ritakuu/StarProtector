//=============================================================================
//
// 3d��{�\���̏��� [Bproject.h]
// Author : lizeyu
// ���3d��{�f�[�^�Ǘ��ƌv�Z�֐�
//=============================================================================


#ifndef BPROJECT_H
#define BPROJECT_H

#include <windows.h>
#include "d3dx9.h"
#include "main.h"


#define DIRECTINPUT_VERSION (0x0800)	// �x���΍�
#include "dinput.h"

#define F2D3DV3(f)					(D3DXVECTOR3(f,f,f))

//*****************************************************************************
// �}�N����`
//*****************************************************************************
//�^�C�v�������X�g
enum PROJECT_TYPE
{
	TYPE_PLAYER,								//�v���[���^		
	TYPE_EFFECT_MOVE,							//���΃G�t�F�N�g�^
	TYPE_BULLET,								//�o���b�g�^
	TYPE_MISSILE,								//�~�T�C���^
	TYPE_ENEMY,									//�G�l�~�[�i�O��ށj�^
	TYPE_EFFECT_SHIELD,							//�V�[���h�G�t�F�N�g�^
	TYPE_EFFECT_EXPLOSION,						//�������o�^
	TYPE_EFFECT_CHARGE,							//�G�l�~�[���[�U�[�^�p���o
	TYPE_EFFECT_SHOOT,							//�G�l�~�[���[�U�[�^�p����
	TYPE_BLADE,									//�u���[�h�^
	TYPE_EFFECT_LOCKON,							//���[�N�I�����o�^
	TYPE_EFFECT_FIELD,							//���^
	TYPE_LASER,									//���[�U�[�^
	TYPE_BOSS,									//�{�X�^
	TYPE_MAX									
};

//�������X�g
enum DICTION
{
	DICTION_LEFT,
	DICTION_RIGHT,
	DICTION_UP,
	DICTION_DOWN,
	DICTION_FORWARD,
	DICTION_BACK,
	DICTION_MAX
};

//�F�p�\����
typedef struct
{
	float R;
	float G;
	float B;
	float A;
} XCOLOR;

//�v���[����p�@�������ړ��V�X�e���@���̃v���W�F�N�gnow�����g�p
typedef struct
{
	float		now;										//���̑��x
	float		target;										//�ڕW���x
	D3DXVECTOR3 v;											//���O�̎��ł̑��x�i�����j
	D3DXVECTOR3 a;											//�ڕW���x�i�����j
	D3DXVECTOR3 rotnow;										//���̉^������
	D3DXVECTOR3 rottarget;									//�ڕW�^������

} SPEED;

//��{3d�\����
typedef struct
{
	LPDIRECT3DTEXTURE9	texture;							// �e�N�X�`���ǂݍ��ݏꏊ
	LPD3DXMESH			mesh;								// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
	LPD3DXBUFFER		buffmat;							// ���b�V���̃}�e���A�������i�[
	DWORD				nummat;								// �������̑���

	D3DXMATRIX			mtxWorld;							// ���[���h�}�g���b�N�X
	D3DXVECTOR3			pos;								// ���݂̈ʒu
	D3DXVECTOR3			rot;								// ���݂̌���
	D3DXVECTOR3			scl;								// ���݂̊g�嗦
	XCOLOR				color;								// �F

	int					type;								// �^�C�v���X�g�Q��
	int					count;								// ���Ԋ֌W
	bool				bUse;								// �g�p���Ă��邩�ǂ���
	bool				bShow;								// �`�悷�邩�ǂ���
	bool				bUpdate;							// �X�V����邩�ǂ���

	SPEED				speed;								// �X�r�[�g�\����
	float				size;								// �o���f�B���O�T�[�N���p

} PROJECT3D;



//�p�[�g�\����
typedef struct
{
	D3DXVECTOR3	pos;										// �{�̂Ƃ̑��Έʒu
	D3DXVECTOR3	rot;										// �{�̂Ƃ̑��Ή�]
	PROJECT3D*		parent;									// �{�̂̃|�C���^�[
}PART;






//rot��-180����180�܂Ő��䂷��
float RotControl(float rot);
D3DXVECTOR3 RotControl(D3DXVECTOR3 rot);

//f1��f2��speed�̑��x�ŕς��
float Approach(float f1, float f2, float speed);
//f1��f2��speed�̑��x�ŕς��(rot�p)
float ApproachRot(float r1, float r2, float speed);
//�v���[����pspeed�v�Z
float ApproachSpeed(float vn, float vt, float au, float ad);
D3DXVECTOR3 ApproachSpeed(D3DXVECTOR3 vn, D3DXVECTOR3 vt, D3DXVECTOR3 au, D3DXVECTOR3 ad);
//countdown
int	CountDown(int now);

D3DXVECTOR3 Approach(D3DXVECTOR3 f1, D3DXVECTOR3 f2, D3DXVECTOR3 speed);
D3DXVECTOR3 Approach(D3DXVECTOR3 d1, D3DXVECTOR3 d2, float speed);
D3DXVECTOR3 ApproachRot(D3DXVECTOR3 r1, D3DXVECTOR3 r2, float speed);

//�����������ňړ����x����
D3DXVECTOR3 Move(D3DXVECTOR3 rot, float speed);
void Move(D3DXVECTOR3* pos, D3DXVECTOR3 rot, float speed);
void Move(PROJECT3D* project);

//directx�p�F�]��
D3DXCOLOR ColorX2D(XCOLOR color);
//�F�\���̐ݒu
XCOLOR SetXcolor(float R, float G, float B, float A);
//�J�����Ƌ������擾(�œK���p)
float GetDistance2Camera(D3DXVECTOR3 pos);
//���pos�̋���
float GetDistance(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2);
//�X�s�[�h�̍���
float GetDistance(D3DXVECTOR3 speed);
//��̈ʒu�̊p�x
D3DXVECTOR3 GetAngle(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2);
//�p�[�g�ʒu�v�Z
D3DXVECTOR3 GetPartPos(PART part);
//�p�[�g�ʒu�v�Z
D3DXVECTOR3 GetPartPos(D3DXVECTOR3 parentrot, D3DXVECTOR3 p);
//�p�x���t
D3DXVECTOR3 GetAniRot(D3DXVECTOR3 rot);

//�����蔻��@�o���f�B���O�T�[�N��
bool hitCheckCircle(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2);
//�����蔻��@�ː��ƃT�[�N��
bool hitCheckLC(D3DXVECTOR3 pos1, D3DXVECTOR3 rot1, D3DXVECTOR3 pos2, float size1, float size2,float distance);
// �����_��float�����܂��@min�ŏ��l�@max�ő�l�@digit�����@s������
float CreateRandf(int min,int max, int digit ,bool s);

#endif // !BPROJECT_H

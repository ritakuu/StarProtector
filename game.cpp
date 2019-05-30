//=============================================================================
//
// �Q�[����ʏ��� [game.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#include "game.h"
#include "light.h"
#include "camera.h"
#include "meshfield.h"
#include "meshwall.h"
#include "player.h"
#include "shadow.h"
#include "bullet.h"
#include "life.h"
#include "timer.h"
#include "score.h"
#include "item.h"
#include "sound.h"
#include "space.h"
#include "gun.h"
#include "aim.h"
#include "effect.h"
#include "enemy.h"
#include "ufo.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
bool			g_timestop;
float			g_timespeed;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitGame(void)
{
	// ���C�g�̏�����
	InitLight();

	// �J�����̏�����
	InitCamera();

	// �n�ʂ̏�����
	InitMeshField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 16, 16, 512.0f, 512.0f);



	//// �ǂ̏�����
	//InitMeshWall(D3DXVECTOR3(0.0f, 0.0f, 640.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	//								D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 2, 80.0f, 80.0f);
	//InitMeshWall(D3DXVECTOR3(-640.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.50f, 0.0f),
	//								D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 2, 80.0f, 80.0f);
	//InitMeshWall(D3DXVECTOR3(640.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.50f, 0.0f),
	//								D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 2, 80.0f, 80.0f);
	//InitMeshWall(D3DXVECTOR3(0.0f, 0.0f, -640.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
	//								D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 2, 80.0f, 80.0f);

	//// ��(�����p)
	//InitMeshWall(D3DXVECTOR3(0.0f, 0.0f, 640.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
	//								D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), 16, 2, 80.0f, 80.0f);
	//InitMeshWall(D3DXVECTOR3(-640.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.50f, 0.0f),
	//								D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), 16, 2, 80.0f, 80.0f);
	//InitMeshWall(D3DXVECTOR3(640.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.50f, 0.0f),
	//								D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), 16, 2, 80.0f, 80.0f);
	//InitMeshWall(D3DXVECTOR3(0.0f, 0.0f, -640.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	//								D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), 16, 2, 80.0f, 80.0f);

	// �e�̏�����
	InitShadow();

	// �v���C���[�̏�����
	InitPlayer();

	// �e�̏�����
	InitBullet();

	// ���C�t�̏�����
	InitLife();

	// �^�C�}�[�̏�����
	InitTimer();
	ResetTimer(300);

	// �X�R�A�̏�����
	InitScore();

	// �A�C�e���̏�����
	InitItem();

	//skybox�̏�����
	InitSpace();

	InitGun();

	InitAim();

	InitEffectExplosion();

	InitEnemy();

	for (int nCntCoin = 0; nCntCoin < 40; nCntCoin++)
	{
		float fPosX, fPosY, fPosZ;

		fPosX = (float)(rand() % 12000) / 10.0f - 600.0f;
		//		fPosY = (float)(rand() % 1400) / 10.0f + 10.0f;
		fPosY = 40.0f;
		fPosZ = (float)(rand() % 12000) / 10.0f - 600.0f;
		SetItem(D3DXVECTOR3(fPosX, fPosY, fPosZ), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE_COIN);
	}
	InitUfo();

	g_timespeed = DEFAULT_TIME_SPEED;
	// BGM�Đ�
	PlaySound(SOUND_LABEL_BGM000);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitGame(void)
{
	// ���C�g�̏I������
	UninitLight();

	// �J�����̏I������
	UninitCamera();

	// �n�ʂ̏I������
	UninitMeshField();

	// �ǂ̏I������
	UninitMeshWall();

	// �e�̏I������
	UninitShadow();

	// �v���C���[�̏I������
	UninitPlayer();

	// �e�̏I������
	UninitBullet();

	// ���C�t�̏I������
	UninitLife();

	// �^�C�}�[�̏I������
	UninitTimer();

	// �X�R�A�̏I������
	UninitScore();

	// �A�C�e���̏I������
	UninitItem();

	// skybox�I������
	UninitSpace();

	UninitGun();

	UninitAim();

	UninitEffectExplosion();

	UninitEnemy();

	UninitUfo();

	// BGM��~
	PlaySound(SOUND_LABEL_BGM000);
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGame(void)
{
	ShowCursor(false);
	SetCursorPos(SCREEN_CENTER_X, SCREEN_CENTER_Y);

	// �n�ʏ����̍X�V
	UpdateMeshField();

	// �Ǐ����̍X�V
	UpdateMeshWall();

	// �e�����̍X�V
	UpdateShadow();

	// �v���C���[�����̍X�V
	UpdatePlayer();

	// �J�����X�V
	UpdateCamera();

	if (GetTimeStop())
	{
		g_timespeed = Approach(g_timespeed, 0.0f, 0.1f);
	}
	else
	{
		g_timespeed = Approach(g_timespeed, 10.0f, 0.1f);
	}

	if (GetTimeSpeed() != 0.0f)
	{

		// ���C�t�����̍X�V
		UpdateLife();

		// �^�C�}�[�����̍X�V
		UpdateTimer();

		// �X�R�A�����̍X�V
		UpdateScore();

		// �A�C�e�������̍X�V
		UpdateItem();

		UpdateGun();


		UpdateEffectExplosion();

		// �e�����̍X�V
		UpdateBullet();

		UpdateAim();

		UpdateEnemy();

		UpdateUfo();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawGame(void)
{
	// �J�����̐ݒ�
	SetCamera();

	DrawSpace();

	// �n�ʏ����̕`��
	DrawMeshField();

	// �e�����̕`��
	DrawShadow();

	// �v���C���[�����̕`��
	DrawPlayer();

	DrawEnemy();


	// �A�C�e�������̕`��
	DrawItem();

	// �e�����̕`��
	DrawBullet();

	// �Ǐ����̕`��
	DrawMeshWall();

	// ���C�t�����̕`��
	DrawLife();

	// �^�C�}�[�����̕`��
	DrawTimer();

	// �X�R�A�����̕`��
	DrawScore();


	DrawGun();


	DrawUfo();

	DrawEffectExplosion();


	DrawAim();


}

void SetTimeStop(bool stop)
{
	g_timestop = stop;
}

bool GetTimeStop()
{
	return g_timestop;
}

float GetTimeSpeed()
{
	return g_timespeed / 10.0f;
}


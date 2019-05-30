//=============================================================================
//
// �^�C�}�[���� [timer.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#include "timer.h"
#include "fade.h"
#include "game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_TIMER		"data/TEXTURE/number000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TEXTURE_FRAME_TIMER	"data/TEXTURE/frame_timer.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	TIMER_SIZE_X		(35.0f)							// �^�C�}�[�̐����̕�
#define	TIMER_SIZE_Y		(50.0f)							// �^�C�}�[�̐����̍���
#define	TIMER_INTERVAL_X	(0.0f)							// �^�C�}�[�̐����̕\���Ԋu

#define	NUM_PLACE			(3)			// �^�C�}�[�̌���

#define	TIMER_POS_X			(SCREEN_WIDTH / 2 - ((TIMER_SIZE_X * NUM_PLACE + TIMER_INTERVAL_X * (NUM_PLACE - 1)) / 2) )	// �^�C�}�[�̕\����ʒu�w���W
#define	TIMER_POS_Y			(25.0f)																						// �^�C�}�[�̕\����ʒu�x���W

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexTimer(LPDIRECT3DDEVICE9 pDevice);
void SetTextureTimer(int idx, int number);

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureTimer[2] = {};		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffTimer = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

D3DXVECTOR3				g_posTimer;
D3DXVECTOR3				g_rotTimer;

int						g_nTimer;						// �^�C�}�[
bool					g_bEnableTimer;					// �^�C�}�[����ON/OFF

//=============================================================================
// ����������
//=============================================================================
HRESULT InitTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_posTimer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotTimer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �^�C�}�[�̏�����
	g_nTimer = 999 * 60;
	g_bEnableTimer = true;

	// ���_���̍쐬
	MakeVertexTimer(pDevice);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
		TEXTURE_TIMER,			// �t�@�C���̖��O
		&g_pD3DTextureTimer[0]);	// �ǂݍ��ރ������[
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
		TEXTURE_FRAME_TIMER,			// �t�@�C���̖��O
		&g_pD3DTextureTimer[1]);	// �ǂݍ��ރ������[

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTimer(void)
{
	if (g_pD3DTextureTimer[0] != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureTimer[0]->Release();
		g_pD3DTextureTimer[0] = NULL;
	}
	if (g_pD3DTextureTimer[1] != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureTimer[1]->Release();
		g_pD3DTextureTimer[1] = NULL;
	}

	if (g_pD3DVtxBuffTimer != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffTimer->Release();
		g_pD3DVtxBuffTimer = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTimer(void)
{
	if (g_bEnableTimer)
	{
		if (GetTimeSpeed() > 0.0f)
		{
			g_nTimer--;
		}
		if (g_nTimer < 0)
		{
			g_nTimer = 0;

			SetFade(FADE_OUT);
		}
		else if ((g_nTimer / 60) >= (int)(powf(10.0f, (float)(NUM_PLACE + 1))))
		{
			g_nTimer = (int)(powf(10.0f, (float)(NUM_PLACE + 1))) - 1;
		}
	}

	for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
	{
		int number;
		int timer;

		timer = g_nTimer + 59;
		number = ((timer / 60) % (int)(powf(10.0f, (float)(NUM_PLACE - nCntPlace)))) / (int)(powf(10.0f, (float)(NUM_PLACE - nCntPlace - 1)));
		SetTextureTimer(nCntPlace, number);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pD3DVtxBuffTimer, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureTimer[0]);

	// �|���S���̕`��
	for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (nCntPlace * 4), NUM_POLYGON);
	}

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureTimer[1]);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (NUM_PLACE * 4), NUM_POLYGON);
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexTimer(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * (NUM_VERTEX * NUM_PLACE + 4),	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,								// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,									// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,								// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffTimer,							// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))											// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_2D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntPlace = 0; nCntPlace < NUM_PLACE; nCntPlace++, pVtx += 4)
		{
			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(TIMER_POS_X + nCntPlace * TIMER_SIZE_X + TIMER_INTERVAL_X, TIMER_POS_Y, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(TIMER_POS_X + nCntPlace * (TIMER_INTERVAL_X + TIMER_SIZE_X) + TIMER_SIZE_X, TIMER_POS_Y, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(TIMER_POS_X + nCntPlace * TIMER_SIZE_X + TIMER_INTERVAL_X, TIMER_POS_Y + TIMER_SIZE_Y, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(TIMER_POS_X + nCntPlace * (TIMER_INTERVAL_X + TIMER_SIZE_X) + TIMER_SIZE_X, TIMER_POS_Y + TIMER_SIZE_Y, 0.0f);

			// rhw�̐ݒ�
			pVtx[0].rhw =
				pVtx[1].rhw =
				pVtx[2].rhw =
				pVtx[3].rhw = 1.0f;

			// ���ˌ��̐ݒ�
			pVtx[0].diffuse = D3DCOLOR_RGBA(0, 255, 255, 255);
			pVtx[1].diffuse = D3DCOLOR_RGBA(0, 255, 255, 255);
			pVtx[2].diffuse = D3DCOLOR_RGBA(0, 255, 255, 255);
			pVtx[3].diffuse = D3DCOLOR_RGBA(0, 255, 255, 255);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);
		}

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(TIMER_POS_X - 17.5f, TIMER_POS_Y - 25, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(TIMER_POS_X + (TIMER_INTERVAL_X + TIMER_SIZE_X) * NUM_PLACE + 17.5f, TIMER_POS_Y - 25, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(TIMER_POS_X - 17.5f, TIMER_POS_Y + 55, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(TIMER_POS_X + (TIMER_INTERVAL_X + TIMER_SIZE_X) * NUM_PLACE + 17.5f, TIMER_POS_Y + 55, 0.0f);

		// rhw�̐ݒ�
		pVtx[0].rhw =
			pVtx[1].rhw =
			pVtx[2].rhw =
			pVtx[3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DCOLOR_RGBA(0, 255, 255, 255);
		pVtx[1].diffuse = D3DCOLOR_RGBA(0, 255, 255, 255);
		pVtx[2].diffuse = D3DCOLOR_RGBA(0, 255, 255, 255);
		pVtx[3].diffuse = D3DCOLOR_RGBA(0, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffTimer->Unlock();
	}

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureTimer(int idx, int number)
{
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	g_pD3DVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (idx * 4);

	// ���_���W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(number * 0.1f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(number * 0.1f + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(number * 0.1f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(number * 0.1f + 0.1f, 1.0f);

	// ���_�f�[�^���A�����b�N����
	g_pD3DVtxBuffTimer->Unlock();
}

//=============================================================================
// �^�C�}�[�̊J�n
//=============================================================================
void EnableTimer(bool bEnable)
{
	g_bEnableTimer = bEnable;
}

//=============================================================================
// �^�C�}�[�̃��Z�b�g
//=============================================================================
void ResetTimer(int nTime)
{
	g_nTimer = nTime * 60;
}


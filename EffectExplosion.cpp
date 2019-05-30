//=============================================================================
//
// �������o���� [EffectExplosion.cpp]
// Author : lizeyu
//
//=============================================================================
#include "effect.h"
#include "camera.h"
#include "input.h"
#include "player.h"
#include "main.h"
#include "sound.h"
#include "gun.h"
#include "project3D.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_EFFECT_EXPLOSION		"data/TEXTURE/explosion2.png"	// �ǂݍ��ރe�N�X�`���t�@�C����


#define	EFFECT_WIDTH_EXPLOSION						(10.0f)							// �e�̔��a��
#define	EFFECT_HEIGHT_EXPLOSION						(10.0f)							// �e�̔��a��

#define TEXTURE_EXPLOSION_TYPE01_PATTERN_DIVIDE_X	(1)								// �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_EXPLOSION_TYPE01_PATTERN_DIVIDE_Y	(1)								// �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_EXPLOSION_TYPE01				(TEXTURE_EXPLOSION_TYPE01_PATTERN_DIVIDE_X*TEXTURE_EXPLOSION_TYPE01_PATTERN_DIVIDE_X)	// �A�j���[�V�����p�^�[����
#define TIME_ANIMATION_EXPLOSION_TYPE01				(4)								// �A�j���[�V�����̐؂�ւ��J�E���g




//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexEffectExplosion(LPDIRECT3DDEVICE9 pDevice);
void SetVertexEffectExplosion(int nIdxEffect, float fWidth, float fHeight);
void SetColorEffectExplosion(int nIdxEffect, D3DXCOLOR col);
void SetTextureExplosion(int eno, int cntPattern);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apD3DTextureEffectExplosion = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffEffectExplosion = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

EFFECT					effect_explosion[MAX_EFFECT_EXPLOSION];		// ���[�N
static bool				g_bAlpaTest;								// �A���t�@�e�X�gON/OFF
static int				g_nAlpha;									// �A���t�@�e�X�g��臒l
XCOLOR					color_explosion;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEffectExplosion()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_���̍쐬
	MakeVertexEffectExplosion(pDevice);

	// �e�N�X�`���̓ǂݍ���


	D3DXCreateTextureFromFile(pDevice,							// �f�o�C�X�ւ̃|�C���^
		TEXTURE_EFFECT_EXPLOSION,								// �t�@�C���̖��O
		&g_apD3DTextureEffectExplosion);						// �ǂݍ��ރ������[


	for (int i = 0; i < MAX_EFFECT_EXPLOSION; i++)
	{
		effect_explosion[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		effect_explosion[i].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		effect_explosion[i].CountAnim = 0;
		effect_explosion[i].PatternAnim = 0;
		effect_explosion[i].bUse = false;
	}

	color_explosion = SetXcolor(1.0f, 0.4f, 0.0f, 1.0f);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEffectExplosion(void)
{

	if (g_apD3DTextureEffectExplosion != NULL)
	{// �e�N�X�`���̊J��
		g_apD3DTextureEffectExplosion->Release();
		g_apD3DTextureEffectExplosion = NULL;
	}


	if (g_pD3DVtxBuffEffectExplosion != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pD3DVtxBuffEffectExplosion->Release();
		g_pD3DVtxBuffEffectExplosion = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEffectExplosion(void)
{
	GUN * gun = GetGun(0);
	EFFECT * explosion = GetEffectExplosion(0);
	for (int i = 0; i < MAX_EFFECT_EXPLOSION; i++)
	{
		explosion = GetEffectExplosion(i);
		if (effect_explosion[i].bUse)
		{

			// �A�j���[�V����
			explosion->CountAnim++;
			// �A�j���[�V����Wait�`�F�b�N
			if ((explosion->CountAnim % TIME_ANIMATION_EXPLOSION_TYPE01) == 0)
			{
				// �p�^�[���̐؂�ւ�
				explosion->PatternAnim = explosion->PatternAnim + 1;

				// �e�N�X�`�����W��ݒ�
				SetTextureExplosion(i, explosion->PatternAnim);

			}
			if (explosion->PatternAnim >= ANIM_PATTERN_EXPLOSION_TYPE01)
			{
				explosion->bUse = false;
				explosion->PatternAnim = 0;
			}
			explosion->pos = GetPartPos(gun->fire);

		}

	}

}


//=============================================================================
// �`�揈��
//=============================================================================
void DrawEffectExplosion()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxScale, mtxRot, mtxTranslate;


	// ���C���e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int i = 0; i < MAX_EFFECT_EXPLOSION; i++)
	{
		if (effect_explosion[i].bUse)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&effect_explosion[i].mtxWorld);

			// �r���[�}�g���b�N�X���擾
			mtxView = GetCamera(0)->CameraMtxView;

			// �|���S���𐳖ʂɌ�����
#if 0
		// �t�s������Ƃ߂�
			D3DXMatrixInverse(&effect_explosion02[nCntEffect02].mtxWorld, NULL, &mtxView);
			effect_explosion02[nCntEffect02].mtxWorld._41 = 0.0f;
			effect_explosion02[nCntEffect02].mtxWorld._42 = 0.0f;
			effect_explosion02[nCntEffect02].mtxWorld._43 = 0.0f;
#else
			effect_explosion[i].mtxWorld._11 = mtxView._11;
			effect_explosion[i].mtxWorld._12 = mtxView._21;
			effect_explosion[i].mtxWorld._13 = mtxView._31;
			effect_explosion[i].mtxWorld._21 = mtxView._12;
			effect_explosion[i].mtxWorld._22 = mtxView._22;
			effect_explosion[i].mtxWorld._23 = mtxView._32;
			effect_explosion[i].mtxWorld._31 = mtxView._13;
			effect_explosion[i].mtxWorld._32 = mtxView._23;
			effect_explosion[i].mtxWorld._33 = mtxView._33;
#endif

			// �X�P�[���𔽉f
			D3DXMatrixScaling(&mtxScale, effect_explosion[i].scl.x,
				effect_explosion[i].scl.y,
				effect_explosion[i].scl.z);
			D3DXMatrixMultiply(&effect_explosion[i].mtxWorld, &effect_explosion[i].mtxWorld, &mtxScale);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, effect_explosion[i].pos.x,
				effect_explosion[i].pos.y,
				effect_explosion[i].pos.z);
			D3DXMatrixMultiply(&effect_explosion[i].mtxWorld, &effect_explosion[i].mtxWorld, &mtxTranslate);



			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &effect_explosion[i].mtxWorld);

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pD3DVtxBuffEffectExplosion, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apD3DTextureEffectExplosion);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (i * 4), NUM_POLYGON);
		}

	}

	// ���C���e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);




}

//=============================================================================
// ���_���̍쐬
//=============================================================================
HRESULT MakeVertexEffectExplosion(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_EFFECT_EXPLOSION,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,						// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,							// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,						// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&g_pD3DVtxBuffEffectExplosion,						// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))									// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffEffectExplosion->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntEffect = 0; nCntEffect < MAX_EFFECT_EXPLOSION; nCntEffect++, pVtx += 4)
		{

			// ���_���W�̐ݒ�
			pVtx[0].vtx = D3DXVECTOR3(-EFFECT_WIDTH_DEFAULT / 2.0f, 0.0f, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(-EFFECT_WIDTH_DEFAULT / 2.0f, EFFECT_WIDTH_DEFAULT, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(EFFECT_WIDTH_DEFAULT / 2.0f, 0.0f, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(EFFECT_WIDTH_DEFAULT / 2.0f, EFFECT_WIDTH_DEFAULT, 0.0f);

			// ���ˌ��̐ݒ�
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
		}

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffEffectExplosion->Unlock();
	}
	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexEffectExplosion(int nIdxEffect, float fWidth, float fHeight)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffEffectExplosion->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxEffect * 4);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-fWidth, fHeight, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(fWidth, fHeight, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(-fWidth, -fHeight, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(fWidth, -fHeight, 0.0f);


		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffEffectExplosion->Unlock();
	}
}

//=============================================================================
// ���_�J���[�̐ݒ�
//=============================================================================
void SetColorEffectExplosion(int nIdxEffect, D3DXCOLOR col)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffEffectExplosion->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxEffect * 4);

		// ���_���W�̐ݒ�
		pVtx[0].diffuse =
			pVtx[1].diffuse =
			pVtx[2].diffuse =
			pVtx[3].diffuse = col;

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffEffectExplosion->Unlock();
	}
}



//=============================================================================
// ���_���̍쐬
//=============================================================================
int SetEffectExplosion(D3DXVECTOR3 pos, float sizeX, float sizeY)
{
	PLAYER* player = GetPlayer(0);
	int nIdxEffect = -1;

	for (int i = 0; i < MAX_EFFECT_EXPLOSION; i++)
	{
		if (!effect_explosion[i].bUse)
		{
			effect_explosion[i].pos = pos;
			effect_explosion[i].scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			effect_explosion[i].size.x = sizeX;
			effect_explosion[i].size.y = sizeY;
			effect_explosion[i].bUse = true;
			effect_explosion[i].type = TYPE_EFFECT_EXPLOSION;
			effect_explosion[i].color = SetXcolor(1.0f, 1.0f, 1.0f, 1.0f);

			// ���_���W�̐ݒ�
			SetVertexEffectExplosion(i, effect_explosion[i].size.x, effect_explosion[i].size.y);

			// ���_�J���[�̐ݒ�
			SetColorEffectExplosion(i, ColorX2D(effect_explosion[i].color));

			nIdxEffect = i;
			break;
		}
	}

	return nIdxEffect;

}


//=============================================================================
// �؂��擾
//=============================================================================
EFFECT *GetEffectExplosion(int eid)
{
	return &effect_explosion[eid];
}


//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureExplosion(int eno, int cntPattern)
{
	// �e�N�X�`�����W�̐ݒ�
	EFFECT *explosion = GetEffectExplosion(eno);

	int x = cntPattern % TEXTURE_EXPLOSION_TYPE01_PATTERN_DIVIDE_X;
	int y = cntPattern / TEXTURE_EXPLOSION_TYPE01_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / TEXTURE_EXPLOSION_TYPE01_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / TEXTURE_EXPLOSION_TYPE01_PATTERN_DIVIDE_Y;

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		g_pD3DVtxBuffEffectExplosion->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (eno * 4);

		// ���_���W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		pVtx[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		pVtx[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		pVtx[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);

		// ���_�f�[�^���A�����b�N����
		g_pD3DVtxBuffEffectExplosion->Unlock();
	}


}
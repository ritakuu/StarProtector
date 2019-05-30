//=============================================================================
//
// �v���C���[���� [gun.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#include "gun.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "bullet.h"
#include "item.h"
#include "score.h"
#include "sound.h"
#include "project3D.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MODEL_GUN		"data/MODEL/weapon.x"	// �ǂݍ��ރ��f����
#define	TEXTURE_GUN		"data/TEXTURE/UFO.bmp"	// �ǂݍ��ރ��f����
#define	GUN_RADIUS		(10.0f)						// ���a
#define	VALUE_MOVE_GUN	(10.0f)						// �ړ����x
#define	VALUE_ROTATE_GUN	(0.0025f)					// ��]���x
#define	VALUE_ROTATE_X_MAX	(D3DX_PI/2-0.01f)			// ��]���x
#define	VALUE_PLAYE_HEIGHT	(100.0f)			// ��]���x

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
GUN					gun[GUN_MAX];

LPDIRECT3DTEXTURE9	g_pD3DTextureGun;		// �e�N�X�`���ǂݍ��ݏꏊ
LPD3DXMESH			g_pMeshGun;				// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
LPD3DXBUFFER		g_pD3DXMatBuffGun;		// ���b�V���̃}�e���A�������i�[
DWORD				g_nNumMatGun;			// �������̑���

//=============================================================================
// ����������
//=============================================================================
HRESULT InitGun(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_pD3DTextureGun = NULL;
	g_pMeshGun = NULL;
	g_pD3DXMatBuffGun = NULL;

	// X�t�@�C���̓ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(MODEL_GUN,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pD3DXMatBuffGun,
		NULL,
		&g_nNumMatGun,
		&g_pMeshGun)))
	{
		return E_FAIL;
	}

	gun->base.pos = D3DXVECTOR3(0.0f, VALUE_PLAYE_HEIGHT, 0.0f);
	gun->base.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	gun->base.scl = D3DXVECTOR3(10.0f, 10.0f, 10.0f);
	gun->base.bUse = true;
	gun->base.nummat = g_nNumMatGun;
	gun->base.buffmat = g_pD3DXMatBuffGun;
	gun->base.mesh = g_pMeshGun;
	gun->fire.pos = D3DXVECTOR3(0.0f, 25.0f, -130.0f);
	gun->fire.parent = &gun->base;



	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
		TEXTURE_GUN,		// �t�@�C���̖��O
		&g_pD3DTextureGun);	// �ǂݍ��ރ������[

	gun->base.texture = g_pD3DTextureGun;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitGun(void)
{
	if (g_pD3DTextureGun != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTextureGun->Release();
		g_pD3DTextureGun = NULL;
	}

	if (g_pMeshGun != NULL)
	{// ���b�V���̊J��
		g_pMeshGun->Release();
		g_pMeshGun = NULL;
	}

	if (g_pD3DXMatBuffGun != NULL)
	{// �}�e���A���̊J��
		g_pD3DXMatBuffGun->Release();
		g_pD3DXMatBuffGun = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGun(void)
{
	GUN* gun = GetGun(0);
	PLAYER* player = GetPlayer(0);

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawGun(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate, mtxScl;
	D3DXMATERIAL *pD3DXMat;

	GUN* gun = GetGun(0);
	for (int i = 0; i < GUN_MAX; i++)
	{
		gun = GetGun(i);
		if (gun->base.bUse)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&gun->base.mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, -D3DX_PI / 158.0f, 0.0f, 0.0f);
			D3DXMatrixMultiply(&gun->base.mtxWorld, &gun->base.mtxWorld, &mtxRot);


			D3DXMatrixScaling(&mtxScl, gun->base.scl.x, gun->base.scl.y, gun->base.scl.z);
			D3DXMatrixMultiply(&gun->base.mtxWorld, &gun->base.mtxWorld, &mtxScl);



			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, gun->base.rot.y, gun->base.rot.x, gun->base.rot.z);
			D3DXMatrixMultiply(&gun->base.mtxWorld, &gun->base.mtxWorld, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, gun->base.pos.x, gun->base.pos.y, gun->base.pos.z);
			D3DXMatrixMultiply(&gun->base.mtxWorld, &gun->base.mtxWorld, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &gun->base.mtxWorld);

			// �}�e���A�����ɑ΂���|�C���^���擾
			pD3DXMat = (D3DXMATERIAL*)gun->base.buffmat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatGun; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, gun->base.texture);

				// �`��
				g_pMeshGun->DrawSubset(nCntMat);
			}

			{// �}�e���A�����f�t�H���g�ɖ߂�
				D3DXMATERIAL mat;

				mat.MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
				mat.MatD3D.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
				mat.MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

				pDevice->SetMaterial(&mat.MatD3D);
			}

		}
	}


}

//=============================================================================
// �v���C���[���擾
//=============================================================================
GUN *GetGun(int pno)
{
	return &gun[pno];
}


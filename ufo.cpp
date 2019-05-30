//=============================================================================
//
// �o���b�g���� [ufo.cpp]
// Author : lizeyu
//
//=============================================================================
#include "ufo.h"
#include "camera.h"
#include "input.h"
#include "sound.h"
#include "player.h"
#include "score.h"
#include "game.h"
#include "enemy.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	UFO_MODEL				"data/MODEL/UFO.x"			// �ǂݍ��ރ��f����
#define	UFO_TEXTURE				"data/TEXTURE/UFO.bmp"		// �ǂݍ��ރ��f����
#define	VALUE_MOVE_UFO			(0.50f)						// �ړ����x
#define	RATE_MOVE_UFO			(0.10f)						// �ړ������W��
#define	VALUE_ROTATE_UFO		(D3DX_PI * 0.05f)			// ��]���x
#define	RATE_ROTATE_UFO			(0.02f)						// ��]�����W��

#define UFO_SPEED_MAX			(4.0f)						// ufo�ő呬�x
#define UFO_SPEED_UP			(0.25f)						// ufo�����x
#define UFO_SPEED_ROT			(0.1f)						// ufo��]���x
#define UFO_SPEED_STOP			(2.0f)						// ufo��������̑��x

#define UFO_ROT_SPEED			(0.1f)						// ufo��]���x
#define UFO_POS_1				D3DXVECTOR3(4000.0f,2000.0f,5000.0f)
#define UFO_POS_2				D3DXVECTOR3(4000.0f,2000.0f,0.0f)
#define UFO_POS_3				D3DXVECTOR3(4000.0f,5000.0f,0.0f)
#define UFO_POS_4				D3DXVECTOR3(4000.0f,5000.0f,5000.0f)
#define UFO_COLD				(256)




//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

static LPD3DXMESH			mesh;						// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
static LPD3DXBUFFER			buffmat;					// ���b�V���̃}�e���A�������i�[
static DWORD				nummat;						// �������̑���
static LPDIRECT3DTEXTURE9	texture;					// �e�N�X�`���ǂݍ��ݏꏊ

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
UFO				ufo[UFO_MAX];
D3DXVECTOR3		ufopos[4] = { UFO_POS_1 ,UFO_POS_2 ,UFO_POS_3 ,UFO_POS_4 };
//=============================================================================
// ����������
//=============================================================================
HRESULT InitUfo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	UFO* ufo;

	// X�t�@�C���̓ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(UFO_MODEL,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&buffmat,
		NULL,
		&nummat,
		&mesh)))
	{
		return E_FAIL;
	}


	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
		UFO_TEXTURE,		// �t�@�C���̖��O
		&texture);	// �ǂݍ��ރ������[




	for (int i = 0; i < UFO_MAX; i++)
	{
		ufo = GetUfo(i);
		ufo->base.bUse = true;
		ufo->base.bUpdate = true;
		ufo->base.bShow = true;
		ufo->base.pos = UFO_POS_1;
		ufo->base.scl = F2D3DV3(10.0f);
		ufo->base.speed.now = 0.0f;
		ufo->base.type = TYPE_ENEMY;
		ufo->base.buffmat = buffmat;
		ufo->base.nummat = nummat;
		ufo->base.mesh = mesh;
		ufo->base.texture = texture;
		ufo->base.size = UFO_SIZE;
		ufo->hp = UFO_HP_MAX;
		ufo->rotshow = F2D3DV3(0.0f);
		ufo->postarget = 0;
		ufo->base.count = UFO_COLD;


	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitUfo(void)
{
	if (texture != NULL)
	{// �e�N�X�`���̊J��
		ufo->base.texture->Release();
		ufo->base.texture = NULL;
	}

	if (mesh != NULL)
	{// ���b�V���̊J��
		mesh->Release();
		mesh = NULL;
	}

	if (buffmat != NULL)
	{// �}�e���A���̊J��
		ufo->base.buffmat->Release();
		ufo->base.buffmat = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateUfo(void)
{
	UFO* ufo = GetUfo(0);
	PLAYER *player = GetPlayer(0);
	for (int i = 0; i < UFO_MAX; i++)
	{
		ufo = GetUfo(i);
		if (ufo->base.bUse&&ufo->base.bUpdate)
		{
			if (ufo->base.pos.y >= 4000.0f)
			{
				ufo->base.bShow = false;
			}
			else
			{
				ufo->base.bShow = true;
			}
			ufo->base.speed.now = 20.0f;
			ufo->base.speed.now *= GetTimeSpeed();
			ufo->rotshow.y += UFO_ROT_SPEED * GetTimeSpeed();
			ufo->base.pos = Approach(ufo->base.pos, ufopos[ufo->postarget],ufo->base.speed.now);
			if (ufo->base.pos.x == ufopos[ufo->postarget].x&&ufo->base.pos.z == ufopos[ufo->postarget].z&&ufo->base.pos.y == ufopos[ufo->postarget].y)
			{
				if (ufo->postarget == 1)
				{
					ufo->base.count--;
					if (ufo->base.count <= 0)
					{
						SetEnemy(i,TYPE_ENEMY);
						ufo->base.count = UFO_COLD;
						ufo->postarget = (ufo->postarget + 1) % 4;
					}
				}
				else
				{
					ufo->postarget = (ufo->postarget + 1) % 4;
				}
			}
		}
	}


}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawUfo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate, mtxScl;
	D3DXMATERIAL *pD3DXMat;

	UFO* ufo = GetUfo(0);
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);

	for (int i = 0; i < UFO_MAX; i++)
	{
		ufo = GetUfo(i);
		if (ufo->base.bShow)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&ufo->base.mtxWorld);

			D3DXMatrixScaling(&mtxScl, ufo->base.scl.x, ufo->base.scl.y, ufo->base.scl.z);
			D3DXMatrixMultiply(&ufo->base.mtxWorld, &ufo->base.mtxWorld, &mtxScl);


			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, ufo->rotshow.y, ufo->rotshow.x, ufo->rotshow.z);
			D3DXMatrixMultiply(&ufo->base.mtxWorld, &ufo->base.mtxWorld, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, ufo->base.pos.x, ufo->base.pos.y, ufo->base.pos.z);
			D3DXMatrixMultiply(&ufo->base.mtxWorld, &ufo->base.mtxWorld, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &ufo->base.mtxWorld);

			// �}�e���A�����ɑ΂���|�C���^���擾
			pD3DXMat = (D3DXMATERIAL*)ufo->base.buffmat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)ufo->base.nummat; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);


				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, ufo->base.texture);

				// �`��
				ufo->base.mesh->DrawSubset(nCntMat);
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



UFO* GetUfo(int bno)
{
	return &ufo[bno];
}


void SetUfo(int type)
{
	UFO *ufo = GetUfo(0);
	for (int i = 0; i < UFO_MAX; i++)
	{
		ufo = GetUfo(i);
		if (ufo->base.bUse == false)
		{
			D3DXVECTOR3 pos = D3DXVECTOR3(rand() % 5000 - 2500, rand() % 2000, rand() % 5000 - 2500);
			SetUfo(i, type, pos, F2D3DV3(0.0f));
		}
	}
}


void SetUfo(int eid, int type, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	UFO *ufo = GetUfo(eid);
	ufo->hp = UFO_HP_MAX;
	ufo->base.bUse = true;
	ufo->base.bShow = true;
	ufo->base.bUpdate = true;
	ufo->base.pos = pos;
	ufo->base.rot = rot;
	return;
}

void UfoDamaged(int eid, int damage, int type)
{
	UFO *ufo = GetUfo(eid);
	ufo->hp -= damage;
	if (ufo->hp <= 0)
	{
		ufo->base.bUse = false;
		ufo->base.bShow = false;
		ufo->base.bUpdate = false;
		ChangeScore(100);
	}
}
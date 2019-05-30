//=============================================================================
//
// �o���b�g���� [enemy.cpp]
// Author : lizeyu
//
//=============================================================================
#include "enemy.h"
#include "camera.h"
#include "input.h"
#include "sound.h"
#include "player.h"
#include "score.h"
#include "game.h"
#include "ufo.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	ENEMY_AIRPLANE			"data/MODEL/enemy_kari.x"	// �ǂݍ��ރ��f����
#define	VALUE_MOVE_ENEMY		(0.50f)						// �ړ����x
#define	RATE_MOVE_ENEMY			(0.10f)						// �ړ������W��
#define	VALUE_ROTATE_ENEMY		(D3DX_PI * 0.05f)			// ��]���x
#define	RATE_ROTATE_ENEMY		(0.02f)						// ��]�����W��

#define ENEMY_SPEED_MAX			(4.0f)						// enemy�ő呬�x
#define ENEMY_SPEED_UP			(0.25f)						// enemy�����x
#define ENEMY_SPEED_ROT			(0.1f)						// enemy��]���x
#define ENEMY_SPEED_STOP		(2.0f)						// enemy��������̑��x

#define ENEMY_ROT_MAX_Z		(D3DX_PI / 6.0f)			// enemyZ��]���E



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
ENEMY				enemy[ENEMY_MAX];


//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY* enemy;


	// X�t�@�C���̓ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(ENEMY_AIRPLANE,
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

#if 0
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
		TEXTURE_FILENAME,		// �t�@�C���̖��O
		&texture);	// �ǂݍ��ރ������[
#endif



	for (int i = 0; i < ENEMY_MAX; i++)
	{
		enemy = GetEnemy(i);
		enemy->base.bUse = false;
		enemy->base.bUpdate = false;
		enemy->base.bShow = false;
		enemy->base.speed.now = 0.0f;
		enemy->base.type = TYPE_ENEMY;

		enemy->base.pos = D3DXVECTOR3(rand() % 5000 - 2500, rand() % 2000, rand() % 5000 - 2500);
		enemy->base.scl =F2D3DV3(ENEMY_SIZE);


		enemy->base.buffmat = buffmat;
		enemy->base.nummat = nummat;
		enemy->base.mesh = mesh;
		enemy->base.texture = texture;
		enemy->base.size = ENEMY_SIZE;
		enemy->hp = ENEMY_HP_MAX;


	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy(void)
{
	if (texture != NULL)
	{// �e�N�X�`���̊J��
		enemy->base.texture->Release();
		enemy->base.texture = NULL;
	}

	if (mesh != NULL)
	{// ���b�V���̊J��
		mesh->Release();
		mesh = NULL;
	}

	if (buffmat != NULL)
	{// �}�e���A���̊J��
		enemy->base.buffmat->Release();
		enemy->base.buffmat = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy(void)
{
	ENEMY* enemy = GetEnemy(0);
	PLAYER *player = GetPlayer(0);
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		enemy = GetEnemy(i);
		if (enemy->base.bUse&&enemy->base.bUpdate)
		{
			//enemy->base.rot = GetAngle(enemy->base.pos,F2D3DV3(0.0f));
		//	enemy->base.speed.now = 15.0f;
			if (enemy->base.pos.y > ENEMY_SIZE/2)
			{
				enemy->base.speed.v.y -= GLAXY* GetTimeSpeed();
				enemy->base.pos.y += enemy->base.speed.v.y* GetTimeSpeed();
			}
			else
			{
				enemy->base.pos.y = ENEMY_SIZE/2;
				enemy->base.speed.v.y = 0.0f;
				enemy->base.speed.now *= GetTimeSpeed();
				Move(&enemy->base);

			}
			
		}
	}

	if (GetKeyboardTrigger(DIK_F))
	{
		SetEnemy(0,TYPE_ENEMY);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate, mtxScl;
	D3DXMATERIAL *pD3DXMat;

	ENEMY* enemy = GetEnemy(0);
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		enemy = GetEnemy(i);
		if (enemy->base.bShow)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&enemy->base.mtxWorld);

			D3DXMatrixScaling(&mtxScl, enemy->base.scl.x, enemy->base.scl.y, enemy->base.scl.z);
			D3DXMatrixMultiply(&enemy->base.mtxWorld, &enemy->base.mtxWorld, &mtxScl);


			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, enemy->base.rot.y, enemy->base.rot.x, enemy->base.rot.z);
			D3DXMatrixMultiply(&enemy->base.mtxWorld, &enemy->base.mtxWorld, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, enemy->base.pos.x, enemy->base.pos.y, enemy->base.pos.z);
			D3DXMatrixMultiply(&enemy->base.mtxWorld, &enemy->base.mtxWorld, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &enemy->base.mtxWorld);

			// �}�e���A�����ɑ΂���|�C���^���擾
			pD3DXMat = (D3DXMATERIAL*)enemy->base.buffmat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)enemy->base.nummat; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, enemy->base.texture);

				// �`��
				enemy->base.mesh->DrawSubset(nCntMat);
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



ENEMY* GetEnemy(int bno)
{
	return &enemy[bno];
}


void SetEnemy(int type)
{
	ENEMY *enemy = GetEnemy(0);
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		enemy = GetEnemy(i);
		if (enemy->base.bUse == false)
		{
			D3DXVECTOR3 pos = D3DXVECTOR3(rand() % 5000 - 2500, rand() % 2000, rand() % 5000 - 2500);
			SetEnemy(i, type, pos, F2D3DV3(0.0f));
		}
	}
}


void SetEnemy(int eid, int type, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	ENEMY *enemy = GetEnemy(eid);
	enemy->hp = ENEMY_HP_MAX;
	enemy->base.bUse = true;
	enemy->base.bShow = true;
	enemy->base.bUpdate = true;
	enemy->base.pos = pos;
	enemy->base.rot = rot;
	return;
}

void SetEnemy(int uno,int type)
{
	UFO* ufo = GetUfo(uno);
	ENEMY* enemy = GetEnemy(0);
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		enemy = GetEnemy(i);
		if (enemy->base.bUse == false)
		{
			SetEnemy(i,TYPE_ENEMY,ufo->base.pos,F2D3DV3(0.0f));
			break;
		}
	}
}

void EnemyDamaged(int eid, int damage, int type)
{
	ENEMY *enemy = GetEnemy(eid);
	enemy->hp -= damage;
	if (enemy->hp <= 0)
	{
		enemy->base.bUse = false;
		enemy->base.bShow = false;
		enemy->base.bUpdate = false;
		ChangeScore(100);
	}
}
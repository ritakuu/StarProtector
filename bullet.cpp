//=============================================================================
//
// �o���b�g���� [bullet.cpp]
// Author : lizeyu
//
//=============================================================================
#include "bullet.h"
#include "camera.h"
#include "input.h"
#include "sound.h"
#include "player.h"
#include "enemy.h"
#include "game.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	BULLET_AIRPLANE			"data/MODEL/bullet_enemy.x"	// �ǂݍ��ރ��f����
#define	BULLET_AIRPLANE2		"data/MODEL/bullet_player.x"	// �ǂݍ��ރ��f����
#define TEXTURE_FILENAME		"data/TEXTURE/airplane.jpg"
#define	VALUE_MOVE_BULLET		(0.50f)						// �ړ����x
#define	RATE_MOVE_BULLET		(0.10f)						// �ړ������W��
#define	VALUE_ROTATE_BULLET		(D3DX_PI * 0.05f)			// ��]���x
#define	RATE_ROTATE_BULLET		(0.02f)						// ��]�����W��

#define BULLET_SPEED_MAX		(4.0f)						// bullet�ő呬�x
#define BULLET_SPEED_UP			(0.25f)						// bullet�����x
#define BULLET_SPEED_ROT		(0.1f)						// bullet��]���x
#define BULLET_SPEED_STOP		(2.0f)						// bullet��������̑��x

#define BULLET_ROT_MAX_Z		(D3DX_PI / 6.0f)			// bulletZ��]���E



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

static LPD3DXMESH			mesh;						// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
static LPD3DXBUFFER			buffmat;					// ���b�V���̃}�e���A�������i�[
static DWORD				nummat;						// �������̑���
static LPDIRECT3DTEXTURE9	texture;					// �e�N�X�`���ǂݍ��ݏꏊ


static LPD3DXMESH			mesh2;						// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
static LPD3DXBUFFER			buffmat2;					// ���b�V���̃}�e���A�������i�[
static DWORD				nummat2;						// �������̑���
static LPDIRECT3DTEXTURE9	texture2;					// �e�N�X�`���ǂݍ��ݏꏊ

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
BULLET				bullet[BULLET_MAX];
int debug_enemy;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BULLET* bullet;
	debug_enemy = ENEMY_MAX;

	// X�t�@�C���̓ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(BULLET_AIRPLANE,
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

	// X�t�@�C���̓ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(BULLET_AIRPLANE2,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&buffmat2,
		NULL,
		&nummat2,
		&mesh2)))
	{
		return E_FAIL;
	}

#if 0
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
		TEXTURE_FILENAME,		// �t�@�C���̖��O
		&texture);	// �ǂݍ��ރ������[
#endif



	for (int i = 0; i < BULLET_MAX; i++)
	{
		bullet = GetBullet(i);
		bullet->base.bUse = false;
		bullet->base.speed.now = 0.0f;
		bullet->base.type = TYPE_BULLET;
		bullet->damage = BULLET_DAMAGE_ENEMY;

		bullet->base.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		bullet->base.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		bullet->base.scl = D3DXVECTOR3(2.5f, 2.5f, 25.0f);


		bullet->base.buffmat = buffmat;
		bullet->base.nummat = nummat;
		bullet->base.mesh = mesh;
		bullet->base.texture = texture;
		bullet->base.size = BULLET_SIZE;


	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBullet(void)
{
	if (texture != NULL)
	{// �e�N�X�`���̊J��
		bullet->base.texture->Release();
		bullet->base.texture = NULL;
	}

	if (mesh != NULL)
	{// ���b�V���̊J��
		mesh->Release();
		mesh = NULL;
	}

	if (buffmat != NULL)
	{// �}�e���A���̊J��
		bullet->base.buffmat->Release();
		bullet->base.buffmat = NULL;
	}

	if (texture2 != NULL)
	{// �e�N�X�`���̊J��
		texture2->Release();
		texture2 = NULL;
	}

	if (mesh2 != NULL)
	{// ���b�V���̊J��
		mesh2->Release();
		mesh2 = NULL;
	}

	if (buffmat2 != NULL)
	{// �}�e���A���̊J��
		buffmat2->Release();
		buffmat2 = NULL;
	}


}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBullet(void)
{
	BULLET* bullet = GetBullet(0);
	PLAYER *player = GetPlayer(0);
	ENEMY *enemy = GetEnemy(0);
	for (int i = 0; i < BULLET_MAX; i++)
	{
		bullet = GetBullet(i);
		if (bullet->base.bUse&&bullet->base.bUpdate)
		{
			D3DXVECTOR3 oldpos = bullet->base.pos;
			bullet->base.count--;
			if (bullet->base.count <= 0)
			{
				ResetBullet(i);
			}

			for (int j = 0; j < ENEMY_MAX; j++)
			{
				enemy = GetEnemy(j);
				if (enemy->base.bUse)
				{
					if (hitCheckLC(bullet->base.pos, bullet->base.rot, enemy->base.pos, 0.0f, 100.0f, bullet->base.speed.now)&&enemy->base.type == bullet->target)
					{
						EnemyDamaged(j,bullet->damage,TYPE_BULLET);
						ResetBullet(i);
						break;
					}

				}

			}

			bullet->base.pos += Move(bullet->base.rot, bullet->base.speed.now*GetTimeSpeed());

		}

		
	}
	
	/*if (debug_enemy <= 0)
	{
		SetMode(MODE_RESULT);
	}*/
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate, mtxScl;
	D3DXMATERIAL *pD3DXMat;

	BULLET* bullet = GetBullet(0);
	for (int i = 0; i < BULLET_MAX; i++)
	{
		bullet = GetBullet(i);
		if (bullet->base.bUse&&bullet->base.bShow)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&bullet->base.mtxWorld);

			D3DXMatrixScaling(&mtxScl, bullet->base.scl.x, bullet->base.scl.y, bullet->base.scl.z);
			D3DXMatrixMultiply(&bullet->base.mtxWorld, &bullet->base.mtxWorld, &mtxScl);


			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, bullet->base.rot.y, bullet->base.rot.x, bullet->base.rot.z);
			D3DXMatrixMultiply(&bullet->base.mtxWorld, &bullet->base.mtxWorld, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, bullet->base.pos.x, bullet->base.pos.y, bullet->base.pos.z);
			D3DXMatrixMultiply(&bullet->base.mtxWorld, &bullet->base.mtxWorld, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &bullet->base.mtxWorld);

			// �}�e���A�����ɑ΂���|�C���^���擾
			pD3DXMat = (D3DXMATERIAL*)bullet->base.buffmat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)bullet->base.nummat; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, bullet->base.texture);

				// �`��
				bullet->base.mesh->DrawSubset(nCntMat);
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



BULLET* GetBullet(int bno)
{
	return &bullet[bno];
}

void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int target, int damage, float speed)
{
	BULLET* bullet = GetBullet(0);
	for (int i = 0; i < BULLET_MAX; i++)
	{
		bullet = GetBullet(i);
		if (!bullet->base.bUse)
		{
			bullet->base.pos = pos;
			bullet->base.rot = rot;
			bullet->target = target;
			if (target == TYPE_ENEMY)
			{
				bullet->base.buffmat = buffmat2;
				bullet->base.nummat = nummat2;
				bullet->base.mesh = mesh2;
				bullet->damage = damage;
			}

			if (target == TYPE_PLAYER)
			{
				bullet->base.buffmat = buffmat;
				bullet->base.nummat = nummat;
				bullet->base.mesh = mesh;
				bullet->damage = damage;

			}
			bullet->base.speed.now = speed;
			bullet->base.bUse = true;
			bullet->base.bShow = true;
			bullet->base.bUpdate = true;
			bullet->base.count = 600;
			break;
		}
	}
}

void ResetBullet(int bno)
{
	BULLET *bullet = GetBullet(bno);

	bullet->base.bUse = false;
	bullet->base.bShow = false;
	bullet->base.bUpdate = false;
	bullet->base.speed.now = 0.0f;

	bullet->base.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bullet->base.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);


}

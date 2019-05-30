//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#include "player.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "bullet.h"
#include "item.h"
#include "score.h"
#include "sound.h"
#include "project3D.h"
#include "aim.h"
#include "effect.h"
#include "gun.h"
#include "game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MODEL_PLAYER		"data/MODEL/airplane000.x"	// �ǂݍ��ރ��f����
#define	PLAYER_RADIUS		(10.0f)						// ���a
#define	VALUE_MOVE_PLAYER	(10.0f)						// �ړ����x
#define	VALUE_ROTATE_PLAYER	(0.0025f)					// ��]���x
#define	VALUE_ROTATE_X_MAX	(D3DX_PI/2-0.01f)			// ��]���x
#define	VALUE_PLAYE_HEIGHT	(150.0f)			// ��]���x
#define VALUE_GUN_COLD		(5)
#define GUN_POS_NORMAL		(D3DXVECTOR3(-10.0f,-35.0f,-40.0f))
#define GUN_POS_SNIPE		(D3DXVECTOR3(-0.0f,-30.0f,-35.0f))
#define GUN_MODE_SPEED		(D3DXVECTOR3(2.0f,1.0f,1.0f))
#define VALUE_JUMP_SPEED	(15.0f)
#define VALUE_SHOOT_SHAKE	(5.0f)
#define VALUE_PLAYER_BULLET_DAMAGE	(4)
#define VALUE_PLAYER_BULLET_SPEED	(360.0f)



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
bool ControllByKeyboard(int pno);
//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
PLAYER				player[PLAYER_MAX];

LPDIRECT3DTEXTURE9	g_pD3DTexturePlayer;		// �e�N�X�`���ǂݍ��ݏꏊ
LPD3DXMESH			g_pMeshPlayer;				// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
LPD3DXBUFFER		g_pD3DXMatBuffPlayer;		// ���b�V���̃}�e���A�������i�[
DWORD				g_nNumMatPlayer;			// �������̑���
D3DXMATRIX			g_mtxWorldPlayer;			// ���[���h�}�g���b�N�X

//=============================================================================
// ����������
//=============================================================================
HRESULT InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER * player = GetPlayer(0);
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		player = GetPlayer(i);
		player->base.bUse = true;
		player->base.bUpdate = true;
		player->base.bShow = true;
		player->gun.parent = &player->base;
		player->gun.pos = D3DXVECTOR3(-0.0f,-30.0f,-40.0f);
		player->gunCount = 0;
	}
	g_pD3DTexturePlayer = NULL;
	g_pMeshPlayer = NULL;
	g_pD3DXMatBuffPlayer = NULL;

	player->base.pos = D3DXVECTOR3(0.0f, VALUE_PLAYE_HEIGHT, 0.0f);
	player->base.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// X�t�@�C���̓ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(MODEL_PLAYER,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pD3DXMatBuffPlayer,
		NULL,
		&g_nNumMatPlayer,
		&g_pMeshPlayer)))
	{
		return E_FAIL;
	}

#if 0
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
		TEXTURE_FILENAME,		// �t�@�C���̖��O
		&g_pD3DTexturePlayer);	// �ǂݍ��ރ������[
#endif


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	if (g_pD3DTexturePlayer != NULL)
	{// �e�N�X�`���̊J��
		g_pD3DTexturePlayer->Release();
		g_pD3DTexturePlayer = NULL;
	}

	if (g_pMeshPlayer != NULL)
	{// ���b�V���̊J��
		g_pMeshPlayer->Release();
		g_pMeshPlayer = NULL;
	}

	if (g_pD3DXMatBuffPlayer != NULL)
	{// �}�e���A���̊J��
		g_pD3DXMatBuffPlayer->Release();
		g_pD3DXMatBuffPlayer = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	PLAYER *player = GetPlayer(0);
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		player = GetPlayer(i);
		if (player->base.bUpdate)
		{
			player->gunCount = CountDown(player->gunCount);
		}
		ControllByKeyboard(i);

	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	PLAYER* player = GetPlayer(0);
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldPlayer);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, player->base.rot.y, player->base.rot.x, player->base.rot.z);
	D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, player->base.pos.x, player->base.pos.y, player->base.pos.z);
	D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPlayer);

	// �}�e���A�����ɑ΂���|�C���^���擾
	pD3DXMat = (D3DXMATERIAL*)g_pD3DXMatBuffPlayer->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatPlayer; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pD3DTexturePlayer);

		// �`��
		g_pMeshPlayer->DrawSubset(nCntMat);
	}

	{// �}�e���A�����f�t�H���g�ɖ߂�
		D3DXMATERIAL mat;

		mat.MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		mat.MatD3D.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		mat.MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

		pDevice->SetMaterial(&mat.MatD3D);
	}
}

//=============================================================================
// �v���C���[���擾
//=============================================================================
PLAYER *GetPlayer(int pno)
{
	return &player[pno];
}

bool ControllByKeyboard(int pno)
{
	PLAYER* player = GetPlayer(pno);
	CAMERA* camera = GetCamera(0);
	GUN* gun = GetGun(0);
	AIM *aim = GetAim(0);
	D3DXVECTOR3 diction = D3DXVECTOR3(0.0f, player->base.rot.y, 0.0f);

	player->base.rot.y += GetMouseX()*VALUE_ROTATE_PLAYER;
	player->base.rot.x -= GetMouseY()*VALUE_ROTATE_PLAYER;


	if (player->base.rot.x < -VALUE_ROTATE_X_MAX)
	{
		player->base.rot.x = -VALUE_ROTATE_X_MAX;
	}

	if (player->base.rot.x > VALUE_ROTATE_X_MAX)
	{
		player->base.rot.x = VALUE_ROTATE_X_MAX;
	}

	if (OPERATION_MOVE)
	{
		player->base.speed.now = VALUE_MOVE_PLAYER;
		if (OPERATION_MOVE_FRONT)
		{
			if (OPERATION_MOVE_LEFT)
			{
				diction.y -= D3DX_PI / 4;
			}
			else if (OPERATION_MOVE_RIGHT)
			{
				diction.y += D3DX_PI / 4;
			}

		}
		else if (OPERATION_MOVE_BACK)
		{
			diction.y -= D3DX_PI;
			if (OPERATION_MOVE_LEFT)
			{
				diction.y += D3DX_PI / 4;
			}
			else if (OPERATION_MOVE_RIGHT)
			{
				diction.y -= D3DX_PI / 4;
			}
		}
		else if (OPERATION_MOVE_LEFT)
		{
			diction.y -= D3DX_PI / 2;
		}
		else if (OPERATION_MOVE_RIGHT)
		{
			diction.y += D3DX_PI / 2;
		}
	}
	else
	{
		player->base.speed.now = 0.0f;
	}


	if (OPERATION_SNIPER_MODE)
	{
		player->gun.pos = Approach(player->gun.pos,GUN_POS_SNIPE, GUN_MODE_SPEED/**GetTimeSpeed()*/);
		aim->bUse = false;
	}
	else
	{
		player->gun.pos = Approach(player->gun.pos, GUN_POS_NORMAL, GUN_MODE_SPEED/**GetTimeSpeed()*/);
		aim->bUse = true;
	}

	if (player->base.pos.y > VALUE_PLAYE_HEIGHT)
	{
		player->base.speed.v.y -= GLAXY/**GetTimeSpeed()*/;
	}
	else
	{
		player->base.pos.y = VALUE_PLAYE_HEIGHT;
		player->base.speed.v.y = 0.0f;
	}

	if (OPERATION_JUMP && player->base.pos.y == VALUE_PLAYE_HEIGHT)
	{
		player->base.speed.v.y = VALUE_JUMP_SPEED;
	}

	if (OPERATION_SPEED_UP)
	{
		player->base.speed.now *= 2;
	}

	player->base.speed.v.x = -sinf(diction.y)*player->base.speed.now;
	player->base.speed.v.z = -cosf(diction.y)*player->base.speed.now;

	player->base.pos += player->base.speed.v/**GetTimeSpeed()*/;

	gun->base.pos = GetPartPos(player->gun);
	gun->base.rot = player->base.rot;


	if (OPERATION_SHOOT && player->gunCount == 0)
	{
		SetBullet(player->base.pos+Move(player->base.rot, VALUE_PLAYER_BULLET_SPEED/1.5f), player->base.rot, TYPE_ENEMY, VALUE_PLAYER_BULLET_DAMAGE, VALUE_PLAYER_BULLET_SPEED);
		if (GetTimeSpeed() > 0.0f)
		{
			player->gunCount = VALUE_GUN_COLD /*/ GetTimeSpeed()*/;
		}
		else
		{
			player->gunCount = VALUE_GUN_COLD ;
		}
		player->gun.pos.z += VALUE_SHOOT_SHAKE;
		SetEffectExplosion(GetPartPos(gun->fire),15.0f,15.0f);
		//player->base.rot.x += 0.01f;
	}

	if (GetKeyboardTrigger(DIK_G))
	{
		SetTimeStop(!GetTimeStop());
	}

	return false;
}

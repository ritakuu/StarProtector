//=============================================================================
//
// プレイヤー処理 [player.cpp]
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
// マクロ定義
//*****************************************************************************
#define	MODEL_PLAYER		"data/MODEL/airplane000.x"	// 読み込むモデル名
#define	PLAYER_RADIUS		(10.0f)						// 半径
#define	VALUE_MOVE_PLAYER	(10.0f)						// 移動速度
#define	VALUE_ROTATE_PLAYER	(0.0025f)					// 回転速度
#define	VALUE_ROTATE_X_MAX	(D3DX_PI/2-0.01f)			// 回転速度
#define	VALUE_PLAYE_HEIGHT	(150.0f)			// 回転速度
#define VALUE_GUN_COLD		(5)
#define GUN_POS_NORMAL		(D3DXVECTOR3(-10.0f,-35.0f,-40.0f))
#define GUN_POS_SNIPE		(D3DXVECTOR3(-0.0f,-30.0f,-35.0f))
#define GUN_MODE_SPEED		(D3DXVECTOR3(2.0f,1.0f,1.0f))
#define VALUE_JUMP_SPEED	(15.0f)
#define VALUE_SHOOT_SHAKE	(5.0f)
#define VALUE_PLAYER_BULLET_DAMAGE	(4)
#define VALUE_PLAYER_BULLET_SPEED	(360.0f)



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
bool ControllByKeyboard(int pno);
//*****************************************************************************
// グローバル変数
//*****************************************************************************
PLAYER				player[PLAYER_MAX];

LPDIRECT3DTEXTURE9	g_pD3DTexturePlayer;		// テクスチャ読み込み場所
LPD3DXMESH			g_pMeshPlayer;				// ID3DXMeshインターフェイスへのポインタ
LPD3DXBUFFER		g_pD3DXMatBuffPlayer;		// メッシュのマテリアル情報を格納
DWORD				g_nNumMatPlayer;			// 属性情報の総数
D3DXMATRIX			g_mtxWorldPlayer;			// ワールドマトリックス

//=============================================================================
// 初期化処理
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

	// Xファイルの読み込み
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
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
		TEXTURE_FILENAME,		// ファイルの名前
		&g_pD3DTexturePlayer);	// 読み込むメモリー
#endif


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	if (g_pD3DTexturePlayer != NULL)
	{// テクスチャの開放
		g_pD3DTexturePlayer->Release();
		g_pD3DTexturePlayer = NULL;
	}

	if (g_pMeshPlayer != NULL)
	{// メッシュの開放
		g_pMeshPlayer->Release();
		g_pMeshPlayer = NULL;
	}

	if (g_pD3DXMatBuffPlayer != NULL)
	{// マテリアルの開放
		g_pD3DXMatBuffPlayer->Release();
		g_pD3DXMatBuffPlayer = NULL;
	}
}

//=============================================================================
// 更新処理
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
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	PLAYER* player = GetPlayer(0);
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldPlayer);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, player->base.rot.y, player->base.rot.x, player->base.rot.z);
	D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, player->base.pos.x, player->base.pos.y, player->base.pos.z);
	D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxTranslate);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPlayer);

	// マテリアル情報に対するポインタを取得
	pD3DXMat = (D3DXMATERIAL*)g_pD3DXMatBuffPlayer->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_nNumMatPlayer; nCntMat++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

		// テクスチャの設定
		pDevice->SetTexture(0, g_pD3DTexturePlayer);

		// 描画
		g_pMeshPlayer->DrawSubset(nCntMat);
	}

	{// マテリアルをデフォルトに戻す
		D3DXMATERIAL mat;

		mat.MatD3D.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		mat.MatD3D.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		mat.MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

		pDevice->SetMaterial(&mat.MatD3D);
	}
}

//=============================================================================
// プレイヤーを取得
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

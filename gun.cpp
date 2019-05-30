//=============================================================================
//
// プレイヤー処理 [gun.cpp]
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
// マクロ定義
//*****************************************************************************
#define	MODEL_GUN		"data/MODEL/weapon.x"	// 読み込むモデル名
#define	TEXTURE_GUN		"data/TEXTURE/UFO.bmp"	// 読み込むモデル名
#define	GUN_RADIUS		(10.0f)						// 半径
#define	VALUE_MOVE_GUN	(10.0f)						// 移動速度
#define	VALUE_ROTATE_GUN	(0.0025f)					// 回転速度
#define	VALUE_ROTATE_X_MAX	(D3DX_PI/2-0.01f)			// 回転速度
#define	VALUE_PLAYE_HEIGHT	(100.0f)			// 回転速度

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
GUN					gun[GUN_MAX];

LPDIRECT3DTEXTURE9	g_pD3DTextureGun;		// テクスチャ読み込み場所
LPD3DXMESH			g_pMeshGun;				// ID3DXMeshインターフェイスへのポインタ
LPD3DXBUFFER		g_pD3DXMatBuffGun;		// メッシュのマテリアル情報を格納
DWORD				g_nNumMatGun;			// 属性情報の総数

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitGun(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_pD3DTextureGun = NULL;
	g_pMeshGun = NULL;
	g_pD3DXMatBuffGun = NULL;

	// Xファイルの読み込み
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



	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
		TEXTURE_GUN,		// ファイルの名前
		&g_pD3DTextureGun);	// 読み込むメモリー

	gun->base.texture = g_pD3DTextureGun;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGun(void)
{
	if (g_pD3DTextureGun != NULL)
	{// テクスチャの開放
		g_pD3DTextureGun->Release();
		g_pD3DTextureGun = NULL;
	}

	if (g_pMeshGun != NULL)
	{// メッシュの開放
		g_pMeshGun->Release();
		g_pMeshGun = NULL;
	}

	if (g_pD3DXMatBuffGun != NULL)
	{// マテリアルの開放
		g_pD3DXMatBuffGun->Release();
		g_pD3DXMatBuffGun = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGun(void)
{
	GUN* gun = GetGun(0);
	PLAYER* player = GetPlayer(0);

}

//=============================================================================
// 描画処理
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
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&gun->base.mtxWorld);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, -D3DX_PI / 158.0f, 0.0f, 0.0f);
			D3DXMatrixMultiply(&gun->base.mtxWorld, &gun->base.mtxWorld, &mtxRot);


			D3DXMatrixScaling(&mtxScl, gun->base.scl.x, gun->base.scl.y, gun->base.scl.z);
			D3DXMatrixMultiply(&gun->base.mtxWorld, &gun->base.mtxWorld, &mtxScl);



			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, gun->base.rot.y, gun->base.rot.x, gun->base.rot.z);
			D3DXMatrixMultiply(&gun->base.mtxWorld, &gun->base.mtxWorld, &mtxRot);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, gun->base.pos.x, gun->base.pos.y, gun->base.pos.z);
			D3DXMatrixMultiply(&gun->base.mtxWorld, &gun->base.mtxWorld, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &gun->base.mtxWorld);

			// マテリアル情報に対するポインタを取得
			pD3DXMat = (D3DXMATERIAL*)gun->base.buffmat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_nNumMatGun; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// テクスチャの設定
				pDevice->SetTexture(0, gun->base.texture);

				// 描画
				g_pMeshGun->DrawSubset(nCntMat);
			}

			{// マテリアルをデフォルトに戻す
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
// プレイヤーを取得
//=============================================================================
GUN *GetGun(int pno)
{
	return &gun[pno];
}


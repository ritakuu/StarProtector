//=============================================================================
//
// 爆発演出処理 [EffectExplosion.cpp]
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
// マクロ定義
//*****************************************************************************
#define	TEXTURE_EFFECT_EXPLOSION		"data/TEXTURE/explosion2.png"	// 読み込むテクスチャファイル名


#define	EFFECT_WIDTH_EXPLOSION						(10.0f)							// 弾の半径幅
#define	EFFECT_HEIGHT_EXPLOSION						(10.0f)							// 弾の半径幅

#define TEXTURE_EXPLOSION_TYPE01_PATTERN_DIVIDE_X	(1)								// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_EXPLOSION_TYPE01_PATTERN_DIVIDE_Y	(1)								// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_EXPLOSION_TYPE01				(TEXTURE_EXPLOSION_TYPE01_PATTERN_DIVIDE_X*TEXTURE_EXPLOSION_TYPE01_PATTERN_DIVIDE_X)	// アニメーションパターン数
#define TIME_ANIMATION_EXPLOSION_TYPE01				(4)								// アニメーションの切り替わるカウント




//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexEffectExplosion(LPDIRECT3DDEVICE9 pDevice);
void SetVertexEffectExplosion(int nIdxEffect, float fWidth, float fHeight);
void SetColorEffectExplosion(int nIdxEffect, D3DXCOLOR col);
void SetTextureExplosion(int eno, int cntPattern);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apD3DTextureEffectExplosion = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuffEffectExplosion = NULL;		// 頂点バッファインターフェースへのポインタ

EFFECT					effect_explosion[MAX_EFFECT_EXPLOSION];		// ワーク
static bool				g_bAlpaTest;								// アルファテストON/OFF
static int				g_nAlpha;									// アルファテストの閾値
XCOLOR					color_explosion;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEffectExplosion()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点情報の作成
	MakeVertexEffectExplosion(pDevice);

	// テクスチャの読み込み


	D3DXCreateTextureFromFile(pDevice,							// デバイスへのポインタ
		TEXTURE_EFFECT_EXPLOSION,								// ファイルの名前
		&g_apD3DTextureEffectExplosion);						// 読み込むメモリー


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
// 終了処理
//=============================================================================
void UninitEffectExplosion(void)
{

	if (g_apD3DTextureEffectExplosion != NULL)
	{// テクスチャの開放
		g_apD3DTextureEffectExplosion->Release();
		g_apD3DTextureEffectExplosion = NULL;
	}


	if (g_pD3DVtxBuffEffectExplosion != NULL)
	{// 頂点バッファの開放
		g_pD3DVtxBuffEffectExplosion->Release();
		g_pD3DVtxBuffEffectExplosion = NULL;
	}
}

//=============================================================================
// 更新処理
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

			// アニメーション
			explosion->CountAnim++;
			// アニメーションWaitチェック
			if ((explosion->CountAnim % TIME_ANIMATION_EXPLOSION_TYPE01) == 0)
			{
				// パターンの切り替え
				explosion->PatternAnim = explosion->PatternAnim + 1;

				// テクスチャ座標を設定
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
// 描画処理
//=============================================================================
void DrawEffectExplosion()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxScale, mtxRot, mtxTranslate;


	// ラインティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	for (int i = 0; i < MAX_EFFECT_EXPLOSION; i++)
	{
		if (effect_explosion[i].bUse)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&effect_explosion[i].mtxWorld);

			// ビューマトリックスを取得
			mtxView = GetCamera(0)->CameraMtxView;

			// ポリゴンを正面に向ける
#if 0
		// 逆行列をもとめる
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

			// スケールを反映
			D3DXMatrixScaling(&mtxScale, effect_explosion[i].scl.x,
				effect_explosion[i].scl.y,
				effect_explosion[i].scl.z);
			D3DXMatrixMultiply(&effect_explosion[i].mtxWorld, &effect_explosion[i].mtxWorld, &mtxScale);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, effect_explosion[i].pos.x,
				effect_explosion[i].pos.y,
				effect_explosion[i].pos.z);
			D3DXMatrixMultiply(&effect_explosion[i].mtxWorld, &effect_explosion[i].mtxWorld, &mtxTranslate);



			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &effect_explosion[i].mtxWorld);

			// 頂点バッファをデバイスのデータストリームにバインド
			pDevice->SetStreamSource(0, g_pD3DVtxBuffEffectExplosion, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_apD3DTextureEffectExplosion);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, (i * 4), NUM_POLYGON);
		}

	}

	// ラインティングを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);




}

//=============================================================================
// 頂点情報の作成
//=============================================================================
HRESULT MakeVertexEffectExplosion(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_EFFECT_EXPLOSION,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,						// 頂点バッファの使用法　
		FVF_VERTEX_3D,							// 使用する頂点フォーマット
		D3DPOOL_MANAGED,						// リソースのバッファを保持するメモリクラスを指定
		&g_pD3DVtxBuffEffectExplosion,						// 頂点バッファインターフェースへのポインタ
		NULL)))									// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffEffectExplosion->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntEffect = 0; nCntEffect < MAX_EFFECT_EXPLOSION; nCntEffect++, pVtx += 4)
		{

			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3(-EFFECT_WIDTH_DEFAULT / 2.0f, 0.0f, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3(-EFFECT_WIDTH_DEFAULT / 2.0f, EFFECT_WIDTH_DEFAULT, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(EFFECT_WIDTH_DEFAULT / 2.0f, 0.0f, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(EFFECT_WIDTH_DEFAULT / 2.0f, EFFECT_WIDTH_DEFAULT, 0.0f);

			// 反射光の設定
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
		}

		// 頂点データをアンロックする
		g_pD3DVtxBuffEffectExplosion->Unlock();
	}
	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexEffectExplosion(int nIdxEffect, float fWidth, float fHeight)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffEffectExplosion->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxEffect * 4);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-fWidth, fHeight, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(fWidth, fHeight, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(-fWidth, -fHeight, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(fWidth, -fHeight, 0.0f);


		// 頂点データをアンロックする
		g_pD3DVtxBuffEffectExplosion->Unlock();
	}
}

//=============================================================================
// 頂点カラーの設定
//=============================================================================
void SetColorEffectExplosion(int nIdxEffect, D3DXCOLOR col)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffEffectExplosion->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nIdxEffect * 4);

		// 頂点座標の設定
		pVtx[0].diffuse =
			pVtx[1].diffuse =
			pVtx[2].diffuse =
			pVtx[3].diffuse = col;

		// 頂点データをアンロックする
		g_pD3DVtxBuffEffectExplosion->Unlock();
	}
}



//=============================================================================
// 頂点情報の作成
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

			// 頂点座標の設定
			SetVertexEffectExplosion(i, effect_explosion[i].size.x, effect_explosion[i].size.y);

			// 頂点カラーの設定
			SetColorEffectExplosion(i, ColorX2D(effect_explosion[i].color));

			nIdxEffect = i;
			break;
		}
	}

	return nIdxEffect;

}


//=============================================================================
// 木を取得
//=============================================================================
EFFECT *GetEffectExplosion(int eid)
{
	return &effect_explosion[eid];
}


//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureExplosion(int eno, int cntPattern)
{
	// テクスチャ座標の設定
	EFFECT *explosion = GetEffectExplosion(eno);

	int x = cntPattern % TEXTURE_EXPLOSION_TYPE01_PATTERN_DIVIDE_X;
	int y = cntPattern / TEXTURE_EXPLOSION_TYPE01_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / TEXTURE_EXPLOSION_TYPE01_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / TEXTURE_EXPLOSION_TYPE01_PATTERN_DIVIDE_Y;

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		g_pD3DVtxBuffEffectExplosion->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (eno * 4);

		// 頂点座標の設定
		pVtx[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
		pVtx[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
		pVtx[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
		pVtx[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);

		// 頂点データをアンロックする
		g_pD3DVtxBuffEffectExplosion->Unlock();
	}


}
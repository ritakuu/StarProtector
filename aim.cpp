//=============================================================================
//
// エーム処理 [Aim.cpp]
// Author : lizeyu
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "aim.h"
#include "player.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexAim(void);
void SetTextureAim(int pno, int cntPattern);					// 
void SetVertexAim(int pno);										// 頂点の計算処理



//*****************************************************************************
// グローバル変数
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTextureAim = NULL;		// テクスチャへのポインタ

AIM								aim[AIM_MAX];

float							g_fRadiusAim;					// ポリゴンの半径
float							g_fBaseAngleAim;				// ポリゴンの角度

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitAim()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	AIM *aim = NULL;
	for (int i = 0; i < AIM_MAX; i++)
	{
		aim = GetAim(i);
		aim->polygon.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		aim->polygon.pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);
		aim->polygon.CountAnim = 0;
		aim->polygon.PatternAnim = 0;
		aim->bUse = true;

		aim->polygon.texSize[0] = AIM_SIZE_X;
		aim->polygon.texSize[1] = AIM_SIZE_Y;

		aim->polygon.hitSize[0] = AIM_SIZE_X;
		aim->polygon.hitSize[1] = AIM_SIZE_Y;

		D3DXVECTOR2 temp = D3DXVECTOR2(AIM_SIZE_X, AIM_SIZE_Y);
		aim->polygon.Radius = D3DXVec2Length(&temp);					// エームの半径を初期化
		aim->polygon.Angle = atan2f(AIM_SIZE_Y, AIM_SIZE_X);			// エームの角度を初期化

		aim->polygon.Texture = g_pD3DTextureAim;						// テクスチャ情報
	}

	// 頂点情報の作成
	MakeVertexAim();


	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,		// デバイスのポインタ
		TEXTURE_AIM_NORMAL,				// ファイルの名前
		&g_pD3DTextureAim);					// 読み込むメモリのポインタ



	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitAim(void)
{
	if (g_pD3DTextureAim != NULL)
	{	// テクスチャの開放
		g_pD3DTextureAim->Release();
		g_pD3DTextureAim = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateAim(void)
{
	AIM *aim = GetAim(0);
	PLAYER* player = GetPlayer(0);
	for (int i = 0; i < AIM_MAX; i++)
	{

		aim->polygon.rot.z = player->base.rot.z;
		// アニメーション
		aim->polygon.CountAnim++;
		// アニメーションWaitチェック
		if ((aim->polygon.CountAnim % TIME_ANIMATION_AIM) == 0)
		{
			// パターンの切り替え
			aim->polygon.PatternAnim = (aim->polygon.PatternAnim + 1) % ANIM_PATTERN_AIM;

			// テクスチャ座標を設定
			SetTextureAim(i, aim->polygon.PatternAnim);
		}
		SetVertexAim(i);	// 頂点の計算処理

	}





}

//=============================================================================
// 描画処理
//=============================================================================
void DrawAim(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	AIM *aim = NULL;

	for (int i = 0; i < AIM_MAX; i++)
	{
		aim = GetAim(i);
		if (aim->bUse)
		{

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_2D);

			// テクスチャの設定
			pDevice->SetTexture(0, g_pD3DTextureAim);

			// ポリゴンの描画


			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, aim->polygon.vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexAim(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	AIM *aim = NULL;
	for (int i = 0; i < AIM_MAX; i++)
	{
		aim = GetAim(i);
		// 頂点の計算処理

		// 頂点座標の設定	
		SetVertexAim(i);

		// rhwの設定
		aim->polygon.vertexWk[0].rhw =
			aim->polygon.vertexWk[1].rhw =
			aim->polygon.vertexWk[2].rhw =
			aim->polygon.vertexWk[3].rhw = 1.0f;

		// 反射光の設定
		aim->polygon.vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		aim->polygon.vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		aim->polygon.vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		aim->polygon.vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		SetTextureAim(i, aim->polygon.PatternAnim);
	}

	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定
//=============================================================================
void SetTextureAim(int pno, int cntPattern)
{
	// テクスチャ座標の設定
	AIM *aim = GetAim(pno);

	int x = cntPattern % TEXTURE_AIM_TYPE01_PATTERN_DIVIDE_X;
	int y = cntPattern / TEXTURE_AIM_TYPE01_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / TEXTURE_AIM_TYPE01_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / TEXTURE_AIM_TYPE01_PATTERN_DIVIDE_Y;

	aim->polygon.vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	aim->polygon.vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	aim->polygon.vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	aim->polygon.vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}


//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexAim(int pno)
{
	AIM *aim = GetAim(pno);

	// 頂点座標の設定
	aim->polygon.vertexWk[0].vtx.x = aim->polygon.pos.x - cosf(aim->polygon.Angle + aim->polygon.rot.z) * aim->polygon.Radius;
	aim->polygon.vertexWk[0].vtx.y = aim->polygon.pos.y - sinf(aim->polygon.Angle + aim->polygon.rot.z) * aim->polygon.Radius;
	aim->polygon.vertexWk[0].vtx.z = 0.0f;

	aim->polygon.vertexWk[1].vtx.x = aim->polygon.pos.x + cosf(aim->polygon.Angle - aim->polygon.rot.z) * aim->polygon.Radius;
	aim->polygon.vertexWk[1].vtx.y = aim->polygon.pos.y - sinf(aim->polygon.Angle - aim->polygon.rot.z) * aim->polygon.Radius;
	aim->polygon.vertexWk[1].vtx.z = 0.0f;

	aim->polygon.vertexWk[2].vtx.x = aim->polygon.pos.x - cosf(aim->polygon.Angle - aim->polygon.rot.z) * aim->polygon.Radius;
	aim->polygon.vertexWk[2].vtx.y = aim->polygon.pos.y + sinf(aim->polygon.Angle - aim->polygon.rot.z) * aim->polygon.Radius;
	aim->polygon.vertexWk[2].vtx.z = 0.0f;

	aim->polygon.vertexWk[3].vtx.x = aim->polygon.pos.x + cosf(aim->polygon.Angle + aim->polygon.rot.z) * aim->polygon.Radius;
	aim->polygon.vertexWk[3].vtx.y = aim->polygon.pos.y + sinf(aim->polygon.Angle + aim->polygon.rot.z) * aim->polygon.Radius;
	aim->polygon.vertexWk[3].vtx.z = 0.0f;
}

AIM* GetAim(int pno)
{
	return &aim[pno];
}






//=============================================================================
//
// バレット処理 [ufo.cpp]
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
// マクロ定義
//*****************************************************************************
#define	UFO_MODEL				"data/MODEL/UFO.x"			// 読み込むモデル名
#define	UFO_TEXTURE				"data/TEXTURE/UFO.bmp"		// 読み込むモデル名
#define	VALUE_MOVE_UFO			(0.50f)						// 移動速度
#define	RATE_MOVE_UFO			(0.10f)						// 移動慣性係数
#define	VALUE_ROTATE_UFO		(D3DX_PI * 0.05f)			// 回転速度
#define	RATE_ROTATE_UFO			(0.02f)						// 回転慣性係数

#define UFO_SPEED_MAX			(4.0f)						// ufo最大速度
#define UFO_SPEED_UP			(0.25f)						// ufo加速度
#define UFO_SPEED_ROT			(0.1f)						// ufo回転速度
#define UFO_SPEED_STOP			(2.0f)						// ufo非加速時の速度

#define UFO_ROT_SPEED			(0.1f)						// ufo回転速度
#define UFO_POS_1				D3DXVECTOR3(4000.0f,2000.0f,5000.0f)
#define UFO_POS_2				D3DXVECTOR3(4000.0f,2000.0f,0.0f)
#define UFO_POS_3				D3DXVECTOR3(4000.0f,5000.0f,0.0f)
#define UFO_POS_4				D3DXVECTOR3(4000.0f,5000.0f,5000.0f)
#define UFO_COLD				(256)




//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

static LPD3DXMESH			mesh;						// ID3DXMeshインターフェイスへのポインタ
static LPD3DXBUFFER			buffmat;					// メッシュのマテリアル情報を格納
static DWORD				nummat;						// 属性情報の総数
static LPDIRECT3DTEXTURE9	texture;					// テクスチャ読み込み場所

//*****************************************************************************
// グローバル変数
//*****************************************************************************
UFO				ufo[UFO_MAX];
D3DXVECTOR3		ufopos[4] = { UFO_POS_1 ,UFO_POS_2 ,UFO_POS_3 ,UFO_POS_4 };
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitUfo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	UFO* ufo;

	// Xファイルの読み込み
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


	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
		UFO_TEXTURE,		// ファイルの名前
		&texture);	// 読み込むメモリー




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
// 終了処理
//=============================================================================
void UninitUfo(void)
{
	if (texture != NULL)
	{// テクスチャの開放
		ufo->base.texture->Release();
		ufo->base.texture = NULL;
	}

	if (mesh != NULL)
	{// メッシュの開放
		mesh->Release();
		mesh = NULL;
	}

	if (buffmat != NULL)
	{// マテリアルの開放
		ufo->base.buffmat->Release();
		ufo->base.buffmat = NULL;
	}

}

//=============================================================================
// 更新処理
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
// 描画処理
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
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&ufo->base.mtxWorld);

			D3DXMatrixScaling(&mtxScl, ufo->base.scl.x, ufo->base.scl.y, ufo->base.scl.z);
			D3DXMatrixMultiply(&ufo->base.mtxWorld, &ufo->base.mtxWorld, &mtxScl);


			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, ufo->rotshow.y, ufo->rotshow.x, ufo->rotshow.z);
			D3DXMatrixMultiply(&ufo->base.mtxWorld, &ufo->base.mtxWorld, &mtxRot);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, ufo->base.pos.x, ufo->base.pos.y, ufo->base.pos.z);
			D3DXMatrixMultiply(&ufo->base.mtxWorld, &ufo->base.mtxWorld, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &ufo->base.mtxWorld);

			// マテリアル情報に対するポインタを取得
			pD3DXMat = (D3DXMATERIAL*)ufo->base.buffmat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)ufo->base.nummat; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);


				// テクスチャの設定
				pDevice->SetTexture(0, ufo->base.texture);

				// 描画
				ufo->base.mesh->DrawSubset(nCntMat);
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
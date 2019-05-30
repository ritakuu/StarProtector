//=============================================================================
//
// バレット処理 [enemy.cpp]
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
// マクロ定義
//*****************************************************************************
#define	ENEMY_AIRPLANE			"data/MODEL/enemy_kari.x"	// 読み込むモデル名
#define	VALUE_MOVE_ENEMY		(0.50f)						// 移動速度
#define	RATE_MOVE_ENEMY			(0.10f)						// 移動慣性係数
#define	VALUE_ROTATE_ENEMY		(D3DX_PI * 0.05f)			// 回転速度
#define	RATE_ROTATE_ENEMY		(0.02f)						// 回転慣性係数

#define ENEMY_SPEED_MAX			(4.0f)						// enemy最大速度
#define ENEMY_SPEED_UP			(0.25f)						// enemy加速度
#define ENEMY_SPEED_ROT			(0.1f)						// enemy回転速度
#define ENEMY_SPEED_STOP		(2.0f)						// enemy非加速時の速度

#define ENEMY_ROT_MAX_Z		(D3DX_PI / 6.0f)			// enemyZ回転限界



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
ENEMY				enemy[ENEMY_MAX];


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY* enemy;


	// Xファイルの読み込み
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
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
		TEXTURE_FILENAME,		// ファイルの名前
		&texture);	// 読み込むメモリー
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
// 終了処理
//=============================================================================
void UninitEnemy(void)
{
	if (texture != NULL)
	{// テクスチャの開放
		enemy->base.texture->Release();
		enemy->base.texture = NULL;
	}

	if (mesh != NULL)
	{// メッシュの開放
		mesh->Release();
		mesh = NULL;
	}

	if (buffmat != NULL)
	{// マテリアルの開放
		enemy->base.buffmat->Release();
		enemy->base.buffmat = NULL;
	}

}

//=============================================================================
// 更新処理
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
// 描画処理
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
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&enemy->base.mtxWorld);

			D3DXMatrixScaling(&mtxScl, enemy->base.scl.x, enemy->base.scl.y, enemy->base.scl.z);
			D3DXMatrixMultiply(&enemy->base.mtxWorld, &enemy->base.mtxWorld, &mtxScl);


			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, enemy->base.rot.y, enemy->base.rot.x, enemy->base.rot.z);
			D3DXMatrixMultiply(&enemy->base.mtxWorld, &enemy->base.mtxWorld, &mtxRot);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, enemy->base.pos.x, enemy->base.pos.y, enemy->base.pos.z);
			D3DXMatrixMultiply(&enemy->base.mtxWorld, &enemy->base.mtxWorld, &mtxTranslate);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &enemy->base.mtxWorld);

			// マテリアル情報に対するポインタを取得
			pD3DXMat = (D3DXMATERIAL*)enemy->base.buffmat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)enemy->base.nummat; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

				// テクスチャの設定
				pDevice->SetTexture(0, enemy->base.texture);

				// 描画
				enemy->base.mesh->DrawSubset(nCntMat);
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
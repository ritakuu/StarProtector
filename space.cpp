//=============================================================================
//
// skyboxの処理 [space.cpp]
// Author : lizeyu
//
//=============================================================================
#include "input.h"
#include "player.h"
#include "camera.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define			MAX_SPACE					(6)								// 壁の総数
#define			SPACE_TEXTURE_FILENAME		"data/TEXTURE/9233f460aa6b43e937a46dff3857c812 (1).png"		// 読み込むテクスチャファイル名

#define			SPACE_MAX					(6)
#define			SPACE_NUM_VERTEX			(4)
#define			SPACE_NUM_INDEX				(4)
#define			SPACE_NUM_POLYGIN			(2)
#define			SPACE_SIZE					(VIEW_FAR_Z/2.8f)				// skyboxの大きさ


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 spaceTexture = NULL;										// テクスチャ読み込み場所
LPDIRECT3DVERTEXBUFFER9 pD3DVtxBuff;										// 頂点バッファインターフェースへのポインタ
D3DXMATRIX mtxWorld;														// ワールドマトリックス


D3DXVECTOR3	vertexinfo[8] = {
	D3DXVECTOR3(-SPACE_SIZE, SPACE_SIZE, SPACE_SIZE),
	D3DXVECTOR3(SPACE_SIZE, SPACE_SIZE, SPACE_SIZE),
	D3DXVECTOR3(-SPACE_SIZE,-SPACE_SIZE, SPACE_SIZE),
	D3DXVECTOR3(SPACE_SIZE,-SPACE_SIZE, SPACE_SIZE),
	D3DXVECTOR3(-SPACE_SIZE, SPACE_SIZE,-SPACE_SIZE),
	D3DXVECTOR3(SPACE_SIZE, SPACE_SIZE,-SPACE_SIZE),
	D3DXVECTOR3(-SPACE_SIZE,-SPACE_SIZE,-SPACE_SIZE),
	D3DXVECTOR3(SPACE_SIZE,-SPACE_SIZE,-SPACE_SIZE),
};


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitSpace()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	// テクスチャの読み込み
	if (!spaceTexture)
	{
		D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
			SPACE_TEXTURE_FILENAME,							// ファイルの名前
			&spaceTexture);									// 読み込むメモリー
	}


	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * SPACE_NUM_VERTEX*MAX_SPACE,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,					// 頂点バッファの使用法　
		FVF_VERTEX_3D,						// 使用する頂点フォーマット
		D3DPOOL_MANAGED,					// リソースのバッファを保持するメモリクラスを指定
		&pD3DVtxBuff,						// 頂点バッファインターフェースへのポインタ
		NULL)))								
	{
		return E_FAIL;
	}


	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;


		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
		
		// 頂点座標の設定
		pVtx[0].vtx = vertexinfo[0];
		pVtx[1].vtx = vertexinfo[1];
		pVtx[2].vtx = vertexinfo[2];
		pVtx[3].vtx = vertexinfo[3];

		// 法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(1.0f / 4.0f, 1.0f / 3.0f);
		pVtx[1].tex = D3DXVECTOR2(2.0f / 4.0f, 1.0f / 3.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f / 4.0f, 2.0f / 3.0f);
		pVtx[3].tex = D3DXVECTOR2(2.0f / 4.0f, 2.0f / 3.0f);


		// 頂点座標の設定
		pVtx[4].vtx = vertexinfo[5];
		pVtx[5].vtx = vertexinfo[4];
		pVtx[6].vtx = vertexinfo[7];
		pVtx[7].vtx = vertexinfo[6];

		// 法線ベクトルの設定
		pVtx[4].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[5].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[6].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[7].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

		// 反射光の設定
		pVtx[4].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[5].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[6].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[7].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[4].tex = D3DXVECTOR2(3.0f / 4.0f, 1.0f / 3.0f);
		pVtx[5].tex = D3DXVECTOR2(1.0f, 1.0f / 3.0f);
		pVtx[6].tex = D3DXVECTOR2(3.0f / 4.0f, 2.0f / 3.0f);
		pVtx[7].tex = D3DXVECTOR2(1.0f, 2.0f / 3.0f);


		// 頂点座標の設定
		pVtx[8].vtx = vertexinfo[4];
		pVtx[9].vtx = vertexinfo[0];
		pVtx[10].vtx = vertexinfo[6];
		pVtx[11].vtx = vertexinfo[2];

		// 法線ベクトルの設定
		pVtx[8].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[9].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[10].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[11].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

		// 反射光の設定
		pVtx[8].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[9].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[10].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[11].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[8].tex = D3DXVECTOR2(0.0f, 1.0f / 3.0f);
		pVtx[9].tex = D3DXVECTOR2(1.0f / 4.0f, 1.0f / 3.0f);
		pVtx[10].tex = D3DXVECTOR2(0.0f, 2.0f / 3.0f);
		pVtx[11].tex = D3DXVECTOR2(1.0f / 4.0f, 2.0f / 3.0f);


		// 頂点座標の設定
		pVtx[12].vtx = vertexinfo[1];
		pVtx[13].vtx = vertexinfo[5];
		pVtx[14].vtx = vertexinfo[3];
		pVtx[15].vtx = vertexinfo[7];

		// 法線ベクトルの設定
		pVtx[12].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[13].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[14].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[15].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

		// 反射光の設定
		pVtx[12].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[13].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[14].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[15].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[12].tex = D3DXVECTOR2(2.0f / 4.0f, 1.0f / 3.0f);
		pVtx[13].tex = D3DXVECTOR2(3.0f / 4.0f, 1.0f / 3.0f);
		pVtx[14].tex = D3DXVECTOR2(2.0f / 4.0f, 2.0f / 3.0f);
		pVtx[15].tex = D3DXVECTOR2(3.0f / 4.0f, 2.0f / 3.0f);


		// 頂点座標の設定
		pVtx[16].vtx = vertexinfo[4];
		pVtx[17].vtx = vertexinfo[5];
		pVtx[18].vtx = vertexinfo[0];
		pVtx[19].vtx = vertexinfo[1];

		// 法線ベクトルの設定
		pVtx[16].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[17].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[18].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[19].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

		// 反射光の設定
		pVtx[16].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[17].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[18].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[19].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[16].tex = D3DXVECTOR2(1.0f / 4.0f, 0.0f);
		pVtx[17].tex = D3DXVECTOR2(2.0f / 4.0f, 0.0f);
		pVtx[18].tex = D3DXVECTOR2(1.0f / 4.0f, 1.0f / 3.0f);
		pVtx[19].tex = D3DXVECTOR2(2.0f / 4.0f, 1.0f / 3.0f);


		// 頂点座標の設定
		pVtx[20].vtx = vertexinfo[2];
		pVtx[21].vtx = vertexinfo[3];
		pVtx[22].vtx = vertexinfo[6];
		pVtx[23].vtx = vertexinfo[7];

		// 法線ベクトルの設定
		pVtx[20].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[21].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[22].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[23].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

		// 反射光の設定
		pVtx[20].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[21].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[22].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[23].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[20].tex = D3DXVECTOR2(1.0f / 4.0f, 2.0f / 3.0f);
		pVtx[21].tex = D3DXVECTOR2(2.0f / 4.0f, 2.0f / 3.0f);
		pVtx[22].tex = D3DXVECTOR2(1.0f / 4.0f, 1.0f);
		pVtx[23].tex = D3DXVECTOR2(2.0f / 4.0f, 1.0f);
		// 頂点データをアンロックする
		pD3DVtxBuff->Unlock();
	}
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitSpace(void)
{
	if (pD3DVtxBuff)
	{// 頂点バッファの開放
		pD3DVtxBuff->Release();
		pD3DVtxBuff = NULL;
	}


	if (spaceTexture)
	{// テクスチャの開放
		spaceTexture->Release();
		spaceTexture = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateSpace(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawSpace(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *player = GetPlayer(0);
	D3DXMATRIX mtxRot, mtxTranslate;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, 0.0f, 0.0f, 0.0f);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// 移動を反映　常にプレーヤと同じ位置
	D3DXMatrixTranslation(&mtxTranslate, player->base.pos.x, player->base.pos.y, player->base.pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// 頂点バッファをレンダリングパイプラインに設定
	pDevice->SetStreamSource(0, pD3DVtxBuff, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, spaceTexture);


	for (int i = 0; i < 6; i++)
	{
		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, 2);
	}
}


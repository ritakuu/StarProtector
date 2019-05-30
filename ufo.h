//=============================================================================
//
// バレット処理 [ufo.h]
// Author : lizeyu
//
//=============================================================================
#ifndef _UFO_H_
#define _UFO_H_

#include "main.h"
#include "project3D.h"

#define UFO_MAX						(1)							// バレット総数
#define UFO_SIZE					(3.0f)						// バレット大きさ（ディフォルト）
#define UFO_DAMAGE_PLAYER			(2)							// playerバレット威力
#define UFO_DAMAGE_UFO				(1)							// エネミーバレット威力
#define UFO_HP_MAX					(10)

//ブレード構造体
typedef struct
{
	PROJECT3D		base;										// 3d
	int				hp;											// type ufo or player
	D3DXVECTOR3		rotshow;									// type ufo or player
	int				postarget;									// type ufo or player
} UFO;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
// エネミー初期化
HRESULT InitUfo(void);
// エネミー解放
void UninitUfo(void);
// エネミー更新
void UpdateUfo(void);
// エネミー描画（drawall利用）
void DrawUfo();
// エネミー取得
UFO* GetUfo(int pno);
// エネミー発射設置
void SetUfo(int eid, int type, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
// エネミー発射設置
void SetUfo(int type);

void UfoDamaged(int eid, int damage, int type);

#endif

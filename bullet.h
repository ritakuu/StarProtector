//=============================================================================
//
// バレット処理 [bullet.h]
// Author : lizeyu
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"
#include "project3D.h"

#define BULLET_MAX						(512)						// バレット総数
#define BULLET_SIZE						(3.0f)						// バレット大きさ（ディフォルト）
#define BULLET_DAMAGE_PLAYER			(2)							// playerバレット威力
#define BULLET_DAMAGE_ENEMY				(1)							// エネミーバレット威力

//ブレード構造体
typedef struct
{
	PROJECT3D		base;											// 3d
	int				target;											// type enemy or player
	int				damage;											// 威力
} BULLET;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
// バレット初期化
HRESULT InitBullet(void);
// バレット解放
void UninitBullet(void);
// バレット更新
void UpdateBullet(void);
// バレット描画（drawall利用）
void DrawBullet();
// バレット取得
BULLET* GetBullet(int pno);
// バレット発射設置
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int target, int damage, float speed);
// バレット回収
void ResetBullet(int bno);


#endif

//=============================================================================
//
// バレット処理 [enemy.h]
// Author : lizeyu
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "project3D.h"

#define ENEMY_MAX						(12)						// バレット総数
#define ENEMY_SIZE						(100.0f)						// バレット大きさ（ディフォルト）
#define ENEMY_DAMAGE_PLAYER				(2)							// playerバレット威力
#define ENEMY_DAMAGE_ENEMY				(1)							// エネミーバレット威力
#define ENEMY_HP_MAX					(10)

//ブレード構造体
typedef struct
{
	PROJECT3D		base;											// 3d
	int				hp;											// type enemy or player
} ENEMY;



//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
// エネミー初期化
HRESULT InitEnemy(void);
// エネミー解放
void UninitEnemy(void);
// エネミー更新
void UpdateEnemy(void);
// エネミー描画（drawall利用）
void DrawEnemy();
// エネミー取得
ENEMY* GetEnemy(int pno);
// エネミー発射設置
void SetEnemy(int eid, int type,D3DXVECTOR3 pos, D3DXVECTOR3 rot);
// エネミー発射設置
void SetEnemy(int type);
void SetEnemy(int uno, int type);

void EnemyDamaged(int eid,int damage,int type);

#endif

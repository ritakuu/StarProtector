//=============================================================================
//
// エーム処理 [aim.h]
// Author :lizeyu 
//
//=============================================================================
#ifndef _AIM_H_
#define _AIM_H_

#include "main.h"
#include "project2D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_AIM_NORMAL		"data/TEXTURE/aim.png"						// 読み込むテクスチャファイル名
//エーム動画関係
#define TIME_ANIMATION_AIM		(4)
#define TEXTURE_AIM_TYPE01_PATTERN_DIVIDE_X	(1)
#define TEXTURE_AIM_TYPE01_PATTERN_DIVIDE_Y	(1)
#define ANIM_PATTERN_AIM		(TEXTURE_AIM_TYPE01_PATTERN_DIVIDE_X*TEXTURE_AIM_TYPE01_PATTERN_DIVIDE_Y)

#define	AIM_POS_X				(SCREEN_CENTER_X)							// エームの表示位置X
#define	AIM_POS_Y				(SCREEN_CENTER_Y)							// エームの表示位置Y
#define	AIM_SIZE_X				(30)										// エームの幅
#define	AIM_SIZE_Y				(30)										// エームの高さ
#define AIM_MAX					(1)											// エームの数

typedef struct
{
	PROJECT2D	polygon;		//基本2D構造体
	bool		bUse;			//エーム見えるかどうか
	int			status;			//エーム状態
}AIM;							//エーム構造体

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
//エームの初期化
HRESULT InitAim(void);
//エームの解放
void UninitAim(void);
//エームの更新
void UpdateAim(void);
//エームの状態を獲得
AIM* GetAim(int Ano);
//エームの描画
void DrawAim();

#endif

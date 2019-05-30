//=============================================================================
//
// ゲーム画面処理 [game.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#include "game.h"
#include "light.h"
#include "camera.h"
#include "meshfield.h"
#include "meshwall.h"
#include "player.h"
#include "shadow.h"
#include "bullet.h"
#include "life.h"
#include "timer.h"
#include "score.h"
#include "item.h"
#include "sound.h"
#include "space.h"
#include "gun.h"
#include "aim.h"
#include "effect.h"
#include "enemy.h"
#include "ufo.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
bool			g_timestop;
float			g_timespeed;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitGame(void)
{
	// ライトの初期化
	InitLight();

	// カメラの初期化
	InitCamera();

	// 地面の初期化
	InitMeshField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 16, 16, 512.0f, 512.0f);



	//// 壁の初期化
	//InitMeshWall(D3DXVECTOR3(0.0f, 0.0f, 640.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	//								D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 2, 80.0f, 80.0f);
	//InitMeshWall(D3DXVECTOR3(-640.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.50f, 0.0f),
	//								D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 2, 80.0f, 80.0f);
	//InitMeshWall(D3DXVECTOR3(640.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.50f, 0.0f),
	//								D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 2, 80.0f, 80.0f);
	//InitMeshWall(D3DXVECTOR3(0.0f, 0.0f, -640.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
	//								D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 16, 2, 80.0f, 80.0f);

	//// 壁(裏側用)
	//InitMeshWall(D3DXVECTOR3(0.0f, 0.0f, 640.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f),
	//								D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), 16, 2, 80.0f, 80.0f);
	//InitMeshWall(D3DXVECTOR3(-640.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.50f, 0.0f),
	//								D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), 16, 2, 80.0f, 80.0f);
	//InitMeshWall(D3DXVECTOR3(640.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.50f, 0.0f),
	//								D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), 16, 2, 80.0f, 80.0f);
	//InitMeshWall(D3DXVECTOR3(0.0f, 0.0f, -640.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	//								D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f), 16, 2, 80.0f, 80.0f);

	// 影の初期化
	InitShadow();

	// プレイヤーの初期化
	InitPlayer();

	// 弾の初期化
	InitBullet();

	// ライフの初期化
	InitLife();

	// タイマーの初期化
	InitTimer();
	ResetTimer(300);

	// スコアの初期化
	InitScore();

	// アイテムの初期化
	InitItem();

	//skyboxの初期化
	InitSpace();

	InitGun();

	InitAim();

	InitEffectExplosion();

	InitEnemy();

	for (int nCntCoin = 0; nCntCoin < 40; nCntCoin++)
	{
		float fPosX, fPosY, fPosZ;

		fPosX = (float)(rand() % 12000) / 10.0f - 600.0f;
		//		fPosY = (float)(rand() % 1400) / 10.0f + 10.0f;
		fPosY = 40.0f;
		fPosZ = (float)(rand() % 12000) / 10.0f - 600.0f;
		SetItem(D3DXVECTOR3(fPosX, fPosY, fPosZ), D3DXVECTOR3(0.0f, 0.0f, 0.0f), ITEMTYPE_COIN);
	}
	InitUfo();

	g_timespeed = DEFAULT_TIME_SPEED;
	// BGM再生
	PlaySound(SOUND_LABEL_BGM000);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGame(void)
{
	// ライトの終了処理
	UninitLight();

	// カメラの終了処理
	UninitCamera();

	// 地面の終了処理
	UninitMeshField();

	// 壁の終了処理
	UninitMeshWall();

	// 影の終了処理
	UninitShadow();

	// プレイヤーの終了処理
	UninitPlayer();

	// 弾の終了処理
	UninitBullet();

	// ライフの終了処理
	UninitLife();

	// タイマーの終了処理
	UninitTimer();

	// スコアの終了処理
	UninitScore();

	// アイテムの終了処理
	UninitItem();

	// skybox終了処理
	UninitSpace();

	UninitGun();

	UninitAim();

	UninitEffectExplosion();

	UninitEnemy();

	UninitUfo();

	// BGM停止
	PlaySound(SOUND_LABEL_BGM000);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGame(void)
{
	ShowCursor(false);
	SetCursorPos(SCREEN_CENTER_X, SCREEN_CENTER_Y);

	// 地面処理の更新
	UpdateMeshField();

	// 壁処理の更新
	UpdateMeshWall();

	// 影処理の更新
	UpdateShadow();

	// プレイヤー処理の更新
	UpdatePlayer();

	// カメラ更新
	UpdateCamera();

	if (GetTimeStop())
	{
		g_timespeed = Approach(g_timespeed, 0.0f, 0.1f);
	}
	else
	{
		g_timespeed = Approach(g_timespeed, 10.0f, 0.1f);
	}

	if (GetTimeSpeed() != 0.0f)
	{

		// ライフ処理の更新
		UpdateLife();

		// タイマー処理の更新
		UpdateTimer();

		// スコア処理の更新
		UpdateScore();

		// アイテム処理の更新
		UpdateItem();

		UpdateGun();


		UpdateEffectExplosion();

		// 弾処理の更新
		UpdateBullet();

		UpdateAim();

		UpdateEnemy();

		UpdateUfo();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawGame(void)
{
	// カメラの設定
	SetCamera();

	DrawSpace();

	// 地面処理の描画
	DrawMeshField();

	// 影処理の描画
	DrawShadow();

	// プレイヤー処理の描画
	DrawPlayer();

	DrawEnemy();


	// アイテム処理の描画
	DrawItem();

	// 弾処理の描画
	DrawBullet();

	// 壁処理の描画
	DrawMeshWall();

	// ライフ処理の描画
	DrawLife();

	// タイマー処理の描画
	DrawTimer();

	// スコア処理の描画
	DrawScore();


	DrawGun();


	DrawUfo();

	DrawEffectExplosion();


	DrawAim();


}

void SetTimeStop(bool stop)
{
	g_timestop = stop;
}

bool GetTimeStop()
{
	return g_timestop;
}

float GetTimeSpeed()
{
	return g_timespeed / 10.0f;
}


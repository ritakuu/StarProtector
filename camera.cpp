//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#include "camera.h"
#include "player.h"
#include "input.h"
#include "project3D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	VIEW_ANGLE			(D3DXToRadian(45.0f))	// 視野角
#define	VALUE_MOVE_CAMERA	(2.0f)					// カメラの移動量
#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.01f)		// カメラの回転量
#define	VALUE_DISTANCE_CAMERA	(60.0f)				// カメラの距離

#define	INTERVAL_CAMERA_R	(12.5f)					// モデルの視線の先までの距離
#define	RATE_CHASE_CAMERA_P	(0.35f)					// カメラの視点への補正係数
#define	RATE_CHASE_CAMERA_R	(0.20f)					// カメラの注視点への補正係数

#define	CHASE_HEIGHT_P		(100.0f)				// 追跡時の視点の高さ
#define	CHASE_HEIGHT_R		(10.0f)					// 追跡時の注視点の高さ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
CAMERA			camera[CAMERA_MAX];


//=============================================================================
// カメラの初期化
//=============================================================================
HRESULT InitCamera(void)
{
	CAMERA* camera = GetCamera(0);
	for (int i = 0; i < CAMERA_MAX; i++)
	{
		camera = GetCamera(i);
		camera->CameraAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		camera->CameraDis = VALUE_DISTANCE_CAMERA;
		camera->CameraRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		camera->CameraType = CAMERA_TYPE_1;
		camera->CameraUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		camera->ViewAngle = VIEW_ANGLE;

	}

	return S_OK;
}

//=============================================================================
// カメラの終了処理
//=============================================================================
void UninitCamera(void)
{
}

//=============================================================================
// カメラの更新処理
//=============================================================================
void UpdateCamera(void)
{
	CAMERA* camera = GetCamera(0);
	PLAYER* player = GetPlayer(0);
	for (int i = 0; i < CAMERA_MAX; i++)
	{
		camera = GetCamera(i);
		camera->CameraPos = player->base.pos;
		camera->CameraAt = player->base.pos+ Move(player->base.rot,1.0f);
	}
}

//=============================================================================
// カメラの設定処理
//=============================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CAMERA * camera = GetCamera(0);
	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&camera->CameraMtxView);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&camera->CameraMtxView,
						&camera->CameraPos,		// カメラの視点
						&camera->CameraAt,		// カメラの注視点
						&camera->CameraUp);		// カメラの上方向

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &camera->CameraMtxView);


	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&camera->CameraMtxProjection);

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&camera->CameraMtxProjection,
								camera->ViewAngle,										// 視野角
								((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT),	// アスペクト比
								VIEW_NEAR_Z,									// ビュー平面のNearZ値
								VIEW_FAR_Z);									// ビュー平面のFarZ値

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &camera->CameraMtxProjection);
}


CAMERA* GetCamera(int cno)
{
	return &camera[cno];
}

D3DXVECTOR3 GetCameraPos(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float distance)
{
	D3DXVECTOR3 partpos;

	partpos.x = pos.x + cosf(rot.x)*sinf(rot.y)*distance;
	partpos.y = pos.y - sinf(rot.x)*distance;
	partpos.z = pos.z + cosf(rot.x)*cosf(rot.y)*distance;

	return partpos;
}

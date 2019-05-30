//=============================================================================
//
// カメラ処理 [camera.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"
#define CAMERA_MAX						(1)
#define CAMERA_TYPE_1					(0)										//第一視角
#define	CAMERA_TYPE_3					(1)										//第三視角
#define	VIEW_FAR_Z						(22000.0f)								// ビュー平面のFarZ値
#define	VIEW_NEAR_Z						(10.0f)									// ビュー平面のNearZ値


typedef struct
{
	D3DXVECTOR3								CameraPos;										// カメラの視点
	D3DXVECTOR3								CameraAt;										// カメラの注視点
	D3DXVECTOR3								CameraUp;										// カメラの上方向
	D3DXVECTOR3								CameraRot;										// カメラの回転
	float									CameraDis;										// カメラの視点と注視点の距離
	float									ViewAngle;										// カメラの視点と注視点の距離
	D3DXMATRIX								CameraMtxView;									// ビューマトリックス
	D3DXMATRIX								CameraMtxProjection;							// プロジェクションマトリックス
	bool									CameraType;										// 第三視角(1)又は第一視角(0)

}CAMERA;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);

void SetCamera(void);
CAMERA* GetCamera(int cno);
// カメラ位置計算
D3DXVECTOR3 GetCameraPos(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float distance);


#endif

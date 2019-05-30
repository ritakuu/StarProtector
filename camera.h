//=============================================================================
//
// �J�������� [camera.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"
#define CAMERA_MAX						(1)
#define CAMERA_TYPE_1					(0)										//��ꎋ�p
#define	CAMERA_TYPE_3					(1)										//��O���p
#define	VIEW_FAR_Z						(22000.0f)								// �r���[���ʂ�FarZ�l
#define	VIEW_NEAR_Z						(10.0f)									// �r���[���ʂ�NearZ�l


typedef struct
{
	D3DXVECTOR3								CameraPos;										// �J�����̎��_
	D3DXVECTOR3								CameraAt;										// �J�����̒����_
	D3DXVECTOR3								CameraUp;										// �J�����̏����
	D3DXVECTOR3								CameraRot;										// �J�����̉�]
	float									CameraDis;										// �J�����̎��_�ƒ����_�̋���
	float									ViewAngle;										// �J�����̎��_�ƒ����_�̋���
	D3DXMATRIX								CameraMtxView;									// �r���[�}�g���b�N�X
	D3DXMATRIX								CameraMtxProjection;							// �v���W�F�N�V�����}�g���b�N�X
	bool									CameraType;										// ��O���p(1)���͑�ꎋ�p(0)

}CAMERA;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);

void SetCamera(void);
CAMERA* GetCamera(int cno);
// �J�����ʒu�v�Z
D3DXVECTOR3 GetCameraPos(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float distance);


#endif

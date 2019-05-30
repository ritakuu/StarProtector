//=============================================================================
//
// �J�������� [camera.cpp]
// Author : AKIRA TANAKA
//
//=============================================================================
#include "camera.h"
#include "player.h"
#include "input.h"
#include "project3D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	VIEW_ANGLE			(D3DXToRadian(45.0f))	// ����p
#define	VALUE_MOVE_CAMERA	(2.0f)					// �J�����̈ړ���
#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.01f)		// �J�����̉�]��
#define	VALUE_DISTANCE_CAMERA	(60.0f)				// �J�����̋���

#define	INTERVAL_CAMERA_R	(12.5f)					// ���f���̎����̐�܂ł̋���
#define	RATE_CHASE_CAMERA_P	(0.35f)					// �J�����̎��_�ւ̕␳�W��
#define	RATE_CHASE_CAMERA_R	(0.20f)					// �J�����̒����_�ւ̕␳�W��

#define	CHASE_HEIGHT_P		(100.0f)				// �ǐՎ��̎��_�̍���
#define	CHASE_HEIGHT_R		(10.0f)					// �ǐՎ��̒����_�̍���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
CAMERA			camera[CAMERA_MAX];


//=============================================================================
// �J�����̏�����
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
// �J�����̏I������
//=============================================================================
void UninitCamera(void)
{
}

//=============================================================================
// �J�����̍X�V����
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
// �J�����̐ݒ菈��
//=============================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CAMERA * camera = GetCamera(0);
	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&camera->CameraMtxView);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&camera->CameraMtxView,
						&camera->CameraPos,		// �J�����̎��_
						&camera->CameraAt,		// �J�����̒����_
						&camera->CameraUp);		// �J�����̏����

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &camera->CameraMtxView);


	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&camera->CameraMtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&camera->CameraMtxProjection,
								camera->ViewAngle,										// ����p
								((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT),	// �A�X�y�N�g��
								VIEW_NEAR_Z,									// �r���[���ʂ�NearZ�l
								VIEW_FAR_Z);									// �r���[���ʂ�FarZ�l

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
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

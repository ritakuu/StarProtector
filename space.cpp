//=============================================================================
//
// skybox�̏��� [space.cpp]
// Author : lizeyu
//
//=============================================================================
#include "input.h"
#include "player.h"
#include "camera.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define			MAX_SPACE					(6)								// �ǂ̑���
#define			SPACE_TEXTURE_FILENAME		"data/TEXTURE/9233f460aa6b43e937a46dff3857c812 (1).png"		// �ǂݍ��ރe�N�X�`���t�@�C����

#define			SPACE_MAX					(6)
#define			SPACE_NUM_VERTEX			(4)
#define			SPACE_NUM_INDEX				(4)
#define			SPACE_NUM_POLYGIN			(2)
#define			SPACE_SIZE					(VIEW_FAR_Z/2.8f)				// skybox�̑傫��


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 spaceTexture = NULL;										// �e�N�X�`���ǂݍ��ݏꏊ
LPDIRECT3DVERTEXBUFFER9 pD3DVtxBuff;										// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
D3DXMATRIX mtxWorld;														// ���[���h�}�g���b�N�X


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
// ����������
//=============================================================================
HRESULT InitSpace()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	// �e�N�X�`���̓ǂݍ���
	if (!spaceTexture)
	{
		D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
			SPACE_TEXTURE_FILENAME,							// �t�@�C���̖��O
			&spaceTexture);									// �ǂݍ��ރ������[
	}


	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * SPACE_NUM_VERTEX*MAX_SPACE,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,					// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,						// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,					// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&pD3DVtxBuff,						// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))								
	{
		return E_FAIL;
	}


	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;


		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
		
		// ���_���W�̐ݒ�
		pVtx[0].vtx = vertexinfo[0];
		pVtx[1].vtx = vertexinfo[1];
		pVtx[2].vtx = vertexinfo[2];
		pVtx[3].vtx = vertexinfo[3];

		// �@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(1.0f / 4.0f, 1.0f / 3.0f);
		pVtx[1].tex = D3DXVECTOR2(2.0f / 4.0f, 1.0f / 3.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f / 4.0f, 2.0f / 3.0f);
		pVtx[3].tex = D3DXVECTOR2(2.0f / 4.0f, 2.0f / 3.0f);


		// ���_���W�̐ݒ�
		pVtx[4].vtx = vertexinfo[5];
		pVtx[5].vtx = vertexinfo[4];
		pVtx[6].vtx = vertexinfo[7];
		pVtx[7].vtx = vertexinfo[6];

		// �@���x�N�g���̐ݒ�
		pVtx[4].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[5].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[6].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[7].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

		// ���ˌ��̐ݒ�
		pVtx[4].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[5].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[6].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[7].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[4].tex = D3DXVECTOR2(3.0f / 4.0f, 1.0f / 3.0f);
		pVtx[5].tex = D3DXVECTOR2(1.0f, 1.0f / 3.0f);
		pVtx[6].tex = D3DXVECTOR2(3.0f / 4.0f, 2.0f / 3.0f);
		pVtx[7].tex = D3DXVECTOR2(1.0f, 2.0f / 3.0f);


		// ���_���W�̐ݒ�
		pVtx[8].vtx = vertexinfo[4];
		pVtx[9].vtx = vertexinfo[0];
		pVtx[10].vtx = vertexinfo[6];
		pVtx[11].vtx = vertexinfo[2];

		// �@���x�N�g���̐ݒ�
		pVtx[8].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[9].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[10].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[11].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

		// ���ˌ��̐ݒ�
		pVtx[8].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[9].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[10].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[11].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[8].tex = D3DXVECTOR2(0.0f, 1.0f / 3.0f);
		pVtx[9].tex = D3DXVECTOR2(1.0f / 4.0f, 1.0f / 3.0f);
		pVtx[10].tex = D3DXVECTOR2(0.0f, 2.0f / 3.0f);
		pVtx[11].tex = D3DXVECTOR2(1.0f / 4.0f, 2.0f / 3.0f);


		// ���_���W�̐ݒ�
		pVtx[12].vtx = vertexinfo[1];
		pVtx[13].vtx = vertexinfo[5];
		pVtx[14].vtx = vertexinfo[3];
		pVtx[15].vtx = vertexinfo[7];

		// �@���x�N�g���̐ݒ�
		pVtx[12].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[13].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[14].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[15].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

		// ���ˌ��̐ݒ�
		pVtx[12].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[13].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[14].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[15].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[12].tex = D3DXVECTOR2(2.0f / 4.0f, 1.0f / 3.0f);
		pVtx[13].tex = D3DXVECTOR2(3.0f / 4.0f, 1.0f / 3.0f);
		pVtx[14].tex = D3DXVECTOR2(2.0f / 4.0f, 2.0f / 3.0f);
		pVtx[15].tex = D3DXVECTOR2(3.0f / 4.0f, 2.0f / 3.0f);


		// ���_���W�̐ݒ�
		pVtx[16].vtx = vertexinfo[4];
		pVtx[17].vtx = vertexinfo[5];
		pVtx[18].vtx = vertexinfo[0];
		pVtx[19].vtx = vertexinfo[1];

		// �@���x�N�g���̐ݒ�
		pVtx[16].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[17].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[18].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[19].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

		// ���ˌ��̐ݒ�
		pVtx[16].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[17].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[18].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[19].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[16].tex = D3DXVECTOR2(1.0f / 4.0f, 0.0f);
		pVtx[17].tex = D3DXVECTOR2(2.0f / 4.0f, 0.0f);
		pVtx[18].tex = D3DXVECTOR2(1.0f / 4.0f, 1.0f / 3.0f);
		pVtx[19].tex = D3DXVECTOR2(2.0f / 4.0f, 1.0f / 3.0f);


		// ���_���W�̐ݒ�
		pVtx[20].vtx = vertexinfo[2];
		pVtx[21].vtx = vertexinfo[3];
		pVtx[22].vtx = vertexinfo[6];
		pVtx[23].vtx = vertexinfo[7];

		// �@���x�N�g���̐ݒ�
		pVtx[20].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[21].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[22].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		pVtx[23].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

		// ���ˌ��̐ݒ�
		pVtx[20].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[21].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[22].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[23].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[20].tex = D3DXVECTOR2(1.0f / 4.0f, 2.0f / 3.0f);
		pVtx[21].tex = D3DXVECTOR2(2.0f / 4.0f, 2.0f / 3.0f);
		pVtx[22].tex = D3DXVECTOR2(1.0f / 4.0f, 1.0f);
		pVtx[23].tex = D3DXVECTOR2(2.0f / 4.0f, 1.0f);
		// ���_�f�[�^���A�����b�N����
		pD3DVtxBuff->Unlock();
	}
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitSpace(void)
{
	if (pD3DVtxBuff)
	{// ���_�o�b�t�@�̊J��
		pD3DVtxBuff->Release();
		pD3DVtxBuff = NULL;
	}


	if (spaceTexture)
	{// �e�N�X�`���̊J��
		spaceTexture->Release();
		spaceTexture = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateSpace(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawSpace(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PLAYER *player = GetPlayer(0);
	D3DXMATRIX mtxRot, mtxTranslate;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, 0.0f, 0.0f, 0.0f);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// �ړ��𔽉f�@��Ƀv���[���Ɠ����ʒu
	D3DXMatrixTranslation(&mtxTranslate, player->base.pos.x, player->base.pos.y, player->base.pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// ���_�o�b�t�@�������_�����O�p�C�v���C���ɐݒ�
	pDevice->SetStreamSource(0, pD3DVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, spaceTexture);


	for (int i = 0; i < 6; i++)
	{
		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, 2);
	}
}


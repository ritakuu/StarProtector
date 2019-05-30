//=============================================================================
//
// �G�[������ [Aim.cpp]
// Author : lizeyu
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "aim.h"
#include "player.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexAim(void);
void SetTextureAim(int pno, int cntPattern);					// 
void SetVertexAim(int pno);										// ���_�̌v�Z����



//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static LPDIRECT3DTEXTURE9		g_pD3DTextureAim = NULL;		// �e�N�X�`���ւ̃|�C���^

AIM								aim[AIM_MAX];

float							g_fRadiusAim;					// �|���S���̔��a
float							g_fBaseAngleAim;				// �|���S���̊p�x

//=============================================================================
// ����������
//=============================================================================
HRESULT InitAim()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	AIM *aim = NULL;
	for (int i = 0; i < AIM_MAX; i++)
	{
		aim = GetAim(i);
		aim->polygon.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		aim->polygon.pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);
		aim->polygon.CountAnim = 0;
		aim->polygon.PatternAnim = 0;
		aim->bUse = true;

		aim->polygon.texSize[0] = AIM_SIZE_X;
		aim->polygon.texSize[1] = AIM_SIZE_Y;

		aim->polygon.hitSize[0] = AIM_SIZE_X;
		aim->polygon.hitSize[1] = AIM_SIZE_Y;

		D3DXVECTOR2 temp = D3DXVECTOR2(AIM_SIZE_X, AIM_SIZE_Y);
		aim->polygon.Radius = D3DXVec2Length(&temp);					// �G�[���̔��a��������
		aim->polygon.Angle = atan2f(AIM_SIZE_Y, AIM_SIZE_X);			// �G�[���̊p�x��������

		aim->polygon.Texture = g_pD3DTextureAim;						// �e�N�X�`�����
	}

	// ���_���̍쐬
	MakeVertexAim();


	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
		TEXTURE_AIM_NORMAL,				// �t�@�C���̖��O
		&g_pD3DTextureAim);					// �ǂݍ��ރ������̃|�C���^



	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitAim(void)
{
	if (g_pD3DTextureAim != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureAim->Release();
		g_pD3DTextureAim = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateAim(void)
{
	AIM *aim = GetAim(0);
	PLAYER* player = GetPlayer(0);
	for (int i = 0; i < AIM_MAX; i++)
	{

		aim->polygon.rot.z = player->base.rot.z;
		// �A�j���[�V����
		aim->polygon.CountAnim++;
		// �A�j���[�V����Wait�`�F�b�N
		if ((aim->polygon.CountAnim % TIME_ANIMATION_AIM) == 0)
		{
			// �p�^�[���̐؂�ւ�
			aim->polygon.PatternAnim = (aim->polygon.PatternAnim + 1) % ANIM_PATTERN_AIM;

			// �e�N�X�`�����W��ݒ�
			SetTextureAim(i, aim->polygon.PatternAnim);
		}
		SetVertexAim(i);	// ���_�̌v�Z����

	}





}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawAim(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	AIM *aim = NULL;

	for (int i = 0; i < AIM_MAX; i++)
	{
		aim = GetAim(i);
		if (aim->bUse)
		{

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_2D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pD3DTextureAim);

			// �|���S���̕`��


			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, aim->polygon.vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexAim(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	AIM *aim = NULL;
	for (int i = 0; i < AIM_MAX; i++)
	{
		aim = GetAim(i);
		// ���_�̌v�Z����

		// ���_���W�̐ݒ�	
		SetVertexAim(i);

		// rhw�̐ݒ�
		aim->polygon.vertexWk[0].rhw =
			aim->polygon.vertexWk[1].rhw =
			aim->polygon.vertexWk[2].rhw =
			aim->polygon.vertexWk[3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		aim->polygon.vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		aim->polygon.vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		aim->polygon.vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		aim->polygon.vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		SetTextureAim(i, aim->polygon.PatternAnim);
	}

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureAim(int pno, int cntPattern)
{
	// �e�N�X�`�����W�̐ݒ�
	AIM *aim = GetAim(pno);

	int x = cntPattern % TEXTURE_AIM_TYPE01_PATTERN_DIVIDE_X;
	int y = cntPattern / TEXTURE_AIM_TYPE01_PATTERN_DIVIDE_X;
	float sizeX = 1.0f / TEXTURE_AIM_TYPE01_PATTERN_DIVIDE_X;
	float sizeY = 1.0f / TEXTURE_AIM_TYPE01_PATTERN_DIVIDE_Y;

	aim->polygon.vertexWk[0].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY);
	aim->polygon.vertexWk[1].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY);
	aim->polygon.vertexWk[2].tex = D3DXVECTOR2((float)(x)* sizeX, (float)(y)* sizeY + sizeY);
	aim->polygon.vertexWk[3].tex = D3DXVECTOR2((float)(x)* sizeX + sizeX, (float)(y)* sizeY + sizeY);
}


//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexAim(int pno)
{
	AIM *aim = GetAim(pno);

	// ���_���W�̐ݒ�
	aim->polygon.vertexWk[0].vtx.x = aim->polygon.pos.x - cosf(aim->polygon.Angle + aim->polygon.rot.z) * aim->polygon.Radius;
	aim->polygon.vertexWk[0].vtx.y = aim->polygon.pos.y - sinf(aim->polygon.Angle + aim->polygon.rot.z) * aim->polygon.Radius;
	aim->polygon.vertexWk[0].vtx.z = 0.0f;

	aim->polygon.vertexWk[1].vtx.x = aim->polygon.pos.x + cosf(aim->polygon.Angle - aim->polygon.rot.z) * aim->polygon.Radius;
	aim->polygon.vertexWk[1].vtx.y = aim->polygon.pos.y - sinf(aim->polygon.Angle - aim->polygon.rot.z) * aim->polygon.Radius;
	aim->polygon.vertexWk[1].vtx.z = 0.0f;

	aim->polygon.vertexWk[2].vtx.x = aim->polygon.pos.x - cosf(aim->polygon.Angle - aim->polygon.rot.z) * aim->polygon.Radius;
	aim->polygon.vertexWk[2].vtx.y = aim->polygon.pos.y + sinf(aim->polygon.Angle - aim->polygon.rot.z) * aim->polygon.Radius;
	aim->polygon.vertexWk[2].vtx.z = 0.0f;

	aim->polygon.vertexWk[3].vtx.x = aim->polygon.pos.x + cosf(aim->polygon.Angle + aim->polygon.rot.z) * aim->polygon.Radius;
	aim->polygon.vertexWk[3].vtx.y = aim->polygon.pos.y + sinf(aim->polygon.Angle + aim->polygon.rot.z) * aim->polygon.Radius;
	aim->polygon.vertexWk[3].vtx.z = 0.0f;
}

AIM* GetAim(int pno)
{
	return &aim[pno];
}






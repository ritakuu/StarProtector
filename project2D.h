//=============================================================================
//
// �v���C���[���� [polygon.h]
// Author : taku
//
//=============================================================================
#ifndef POLYGON_H
#define POLYGON_H
#include "main.h"


//=============================================================================


typedef struct
{
	VERTEX_2D				vertexWk[NUM_VERTEX];			// ���_���i�[���[�N
	D3DXVECTOR3				pos;							// �|���S���̍��W
	D3DXVECTOR3				rot;							// �|���S���̉�]��
	int						CountAnim;						// �A�j���[�V�����J�E���g
	int						PatternAnim;					// �A�j���[�V�����p�^�[���i���o�[
	D3DXVECTOR3				texSize;						// �����ڂ̑傫��
	D3DXVECTOR3				hitSize;						// hit�̑傫��
	float					Radius;							// �|���S���̔��a
	float					Angle;							// �|���S���̊p�x


	LPDIRECT3DTEXTURE9		Texture;						// �e�N�X�`�����

}PROJECT2D;



#endif // !POLYGON_H

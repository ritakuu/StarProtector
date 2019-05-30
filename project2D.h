//=============================================================================
//
// プレイヤー処理 [polygon.h]
// Author : taku
//
//=============================================================================
#ifndef POLYGON_H
#define POLYGON_H
#include "main.h"


//=============================================================================


typedef struct
{
	VERTEX_2D				vertexWk[NUM_VERTEX];			// 頂点情報格納ワーク
	D3DXVECTOR3				pos;							// ポリゴンの座標
	D3DXVECTOR3				rot;							// ポリゴンの回転量
	int						CountAnim;						// アニメーションカウント
	int						PatternAnim;					// アニメーションパターンナンバー
	D3DXVECTOR3				texSize;						// 見た目の大きさ
	D3DXVECTOR3				hitSize;						// hitの大きさ
	float					Radius;							// ポリゴンの半径
	float					Angle;							// ポリゴンの角度


	LPDIRECT3DTEXTURE9		Texture;						// テクスチャ情報

}PROJECT2D;



#endif // !POLYGON_H

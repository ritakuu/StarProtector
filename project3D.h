//=============================================================================
//
// 3d基本構造体処理 [Bproject.h]
// Author : lizeyu
// 主に3d基本データ管理と計算関数
//=============================================================================


#ifndef BPROJECT_H
#define BPROJECT_H

#include <windows.h>
#include "d3dx9.h"
#include "main.h"


#define DIRECTINPUT_VERSION (0x0800)	// 警告対策
#include "dinput.h"

#define F2D3DV3(f)					(D3DXVECTOR3(f,f,f))

//*****************************************************************************
// マクロ定義
//*****************************************************************************
//タイプ属性リスト
enum PROJECT_TYPE
{
	TYPE_PLAYER,								//プレーヤ型		
	TYPE_EFFECT_MOVE,							//噴火エフェクト型
	TYPE_BULLET,								//バレット型
	TYPE_MISSILE,								//ミサイル型
	TYPE_ENEMY,									//エネミー（三種類）型
	TYPE_EFFECT_SHIELD,							//シールドエフェクト型
	TYPE_EFFECT_EXPLOSION,						//爆発演出型
	TYPE_EFFECT_CHARGE,							//エネミーレーザー型用演出
	TYPE_EFFECT_SHOOT,							//エネミーレーザー型用発射
	TYPE_BLADE,									//ブレード型
	TYPE_EFFECT_LOCKON,							//ロークオン演出型
	TYPE_EFFECT_FIELD,							//星型
	TYPE_LASER,									//レーザー型
	TYPE_BOSS,									//ボス型
	TYPE_MAX									
};

//方向リスト
enum DICTION
{
	DICTION_LEFT,
	DICTION_RIGHT,
	DICTION_UP,
	DICTION_DOWN,
	DICTION_FORWARD,
	DICTION_BACK,
	DICTION_MAX
};

//色用構造体
typedef struct
{
	float R;
	float G;
	float B;
	float A;
} XCOLOR;

//プレーヤ専用　慣性つく移動システム　他のプロジェクトnowだけ使用
typedef struct
{
	float		now;										//今の速度
	float		target;										//目標速度
	D3DXVECTOR3 v;											//今三つの軸での速度（分解）
	D3DXVECTOR3 a;											//目標速度（分解）
	D3DXVECTOR3 rotnow;										//今の運動方向
	D3DXVECTOR3 rottarget;									//目標運動方向

} SPEED;

//基本3d構造体
typedef struct
{
	LPDIRECT3DTEXTURE9	texture;							// テクスチャ読み込み場所
	LPD3DXMESH			mesh;								// ID3DXMeshインターフェイスへのポインタ
	LPD3DXBUFFER		buffmat;							// メッシュのマテリアル情報を格納
	DWORD				nummat;								// 属性情報の総数

	D3DXMATRIX			mtxWorld;							// ワールドマトリックス
	D3DXVECTOR3			pos;								// 現在の位置
	D3DXVECTOR3			rot;								// 現在の向き
	D3DXVECTOR3			scl;								// 現在の拡大率
	XCOLOR				color;								// 色

	int					type;								// タイプリスト参照
	int					count;								// 時間関係
	bool				bUse;								// 使用しているかどうか
	bool				bShow;								// 描画するかどうか
	bool				bUpdate;							// 更新されるかどうか

	SPEED				speed;								// スビート構造体
	float				size;								// バンディングサークル用

} PROJECT3D;



//パート構造体
typedef struct
{
	D3DXVECTOR3	pos;										// 本体との相対位置
	D3DXVECTOR3	rot;										// 本体との相対回転
	PROJECT3D*		parent;									// 本体のポインター
}PART;






//rotを-180から180まで制御する
float RotControl(float rot);
D3DXVECTOR3 RotControl(D3DXVECTOR3 rot);

//f1がf2にspeedの速度で変わる
float Approach(float f1, float f2, float speed);
//f1がf2にspeedの速度で変わる(rot用)
float ApproachRot(float r1, float r2, float speed);
//プレーヤ専用speed計算
float ApproachSpeed(float vn, float vt, float au, float ad);
D3DXVECTOR3 ApproachSpeed(D3DXVECTOR3 vn, D3DXVECTOR3 vt, D3DXVECTOR3 au, D3DXVECTOR3 ad);
//countdown
int	CountDown(int now);

D3DXVECTOR3 Approach(D3DXVECTOR3 f1, D3DXVECTOR3 f2, D3DXVECTOR3 speed);
D3DXVECTOR3 Approach(D3DXVECTOR3 d1, D3DXVECTOR3 d2, float speed);
D3DXVECTOR3 ApproachRot(D3DXVECTOR3 r1, D3DXVECTOR3 r2, float speed);

//向かい方向で移動速度分析
D3DXVECTOR3 Move(D3DXVECTOR3 rot, float speed);
void Move(D3DXVECTOR3* pos, D3DXVECTOR3 rot, float speed);
void Move(PROJECT3D* project);

//directx用色転換
D3DXCOLOR ColorX2D(XCOLOR color);
//色構造体設置
XCOLOR SetXcolor(float R, float G, float B, float A);
//カメラと距離を取得(最適化用)
float GetDistance2Camera(D3DXVECTOR3 pos);
//二つのposの距離
float GetDistance(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2);
//スピードの合成
float GetDistance(D3DXVECTOR3 speed);
//二つの位置の角度
D3DXVECTOR3 GetAngle(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2);
//パート位置計算
D3DXVECTOR3 GetPartPos(PART part);
//パート位置計算
D3DXVECTOR3 GetPartPos(D3DXVECTOR3 parentrot, D3DXVECTOR3 p);
//角度反逆
D3DXVECTOR3 GetAniRot(D3DXVECTOR3 rot);

//当たり判定　バンディングサークル
bool hitCheckCircle(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2);
//当たり判定　射線とサークル
bool hitCheckLC(D3DXVECTOR3 pos1, D3DXVECTOR3 rot1, D3DXVECTOR3 pos2, float size1, float size2,float distance);
// ランダムfloatを作ります　min最小値　max最大値　digit小数　s符号つく
float CreateRandf(int min,int max, int digit ,bool s);

#endif // !BPROJECT_H

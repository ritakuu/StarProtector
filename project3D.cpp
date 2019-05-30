//=============================================================================
//
// 基本計算処理 [project3D.cpp]
// Author : lizeyu
//
//=============================================================================

#include "project3D.h"
#include "camera.h"

//=============================================================================
// rotを-180から180まで制御する
// rot:対象rot
//=============================================================================
float RotControl(float rot)
{
	float r = rot;

	if (rot > D3DX_PI)
	{
		r = rot - 2 * D3DX_PI;
	}

	if (rot <= -D3DX_PI)
	{
		r = rot + 2 * D3DX_PI;
	}

	return r;
}


//=============================================================================
// rotを-180から180まで制御する
// rot:対象rot
//=============================================================================
D3DXVECTOR3 RotControl(D3DXVECTOR3 rot)
{
	D3DXVECTOR3 r;
	r.x = RotControl(rot.x);
	r.y = RotControl(rot.y);
	r.z = RotControl(rot.z);
	return r;
}


//=============================================================================
// フレームごとで変わる
// now: 現在値　target:目標値　speed:変化速度
// now = Approach(now,target,speed);
//=============================================================================
float Approach(float now, float target, float speed)
{
	float dis = target - now;
	if (dis <= speed && dis >= -speed)
	{
		dis = target;
	}
	else if (dis > speed)
	{
		dis = now + speed;
	}
	else
	{
		dis = now - speed;
	}

	return dis;
}

//=============================================================================
// count down フレームごとに1減らしつづ
// now: 現在値
// now = CountDown(now);
//=============================================================================
int	CountDown(int now)
{
	if (now >= 1)
	{
		return now - 1;
	}
	else
	{
		return now;
	}

}

//=============================================================================
// フレームごとで変わる
// now: 現在値　target:目標値　speed:変化速度
// now = Approach(now,target,speed);
//=============================================================================
D3DXVECTOR3 Approach(D3DXVECTOR3 now, D3DXVECTOR3 target, D3DXVECTOR3 speed)
{
	D3DXVECTOR3 dis;
	dis.x = Approach(now.x, target.x, speed.x);
	dis.y = Approach(now.y, target.y, speed.y);
	dis.z = Approach(now.z, target.z, speed.z);
	return dis;
}

//=============================================================================
// フレームごとで変わるrot用
// now: 現在値　target:目標値　speed:変化速度
// now = Approach(now,target,speed);
//=============================================================================
float ApproachRot(float now, float target, float speed)
{
	float dis;
	if (target - now > D3DX_PI || target - now < -D3DX_PI)
	{
		if (now < 0)
		{
			now += D3DX_PI * 2;
		}
		else
		{
			now -= D3DX_PI * 2;
		}
	}
	dis = Approach(now, target, speed);
	return dis;
}


//=============================================================================
// フレームごとで変わる
// now: 現在値　target:目標値　speed:変化速度
// now = Approach(now,target,speed);
//=============================================================================
D3DXVECTOR3 Approach(D3DXVECTOR3 now, D3DXVECTOR3 target, float speed)
{
	D3DXVECTOR3 dis;
	float dx = now.x - target.x;
	if (dx < 0)
	{
		dx = -dx;
	}

	float dy = now.y - target.y;
	if (dy < 0)
	{
		dy = -dy;
	}

	float dz = now.z - target.z;
	if (dz < 0)
	{
		dz = -dz;
	}

	if (dx == 0.0f&&dy == 0.0f&&dz == 0.0f)
	{
		return target;
	}

	dis.x = Approach(now.x, target.x, speed / (dx + dy + dz)*dx);
	dis.y = Approach(now.y, target.y, speed / (dx + dy + dz)*dy);
	dis.z = Approach(now.z, target.z, speed / (dx + dy + dz)*dz);

	return dis;
}


//=============================================================================
// フレームごとで変わるrot用
// now: 現在値　target:目標値　speed:変化速度
// now = Approach(now,target,speed);
//=============================================================================
D3DXVECTOR3 ApproachRot(D3DXVECTOR3 r1, D3DXVECTOR3 r2, float speed)
{
	D3DXVECTOR3 dis;
	float dx = r1.x - r2.x;
	if (dx < 0)
	{
		dx = -dx;
	}

	float dy = r1.y - r2.y;
	if (dy < 0)
	{
		dy = -dy;
	}

	float dz = r1.z - r2.z;
	if (dz < 0)
	{
		dz = -dz;
	}

	if (dx == 0.0f&&dy == 0.0f&&dz == 0.0f)
	{
		return r2;
	}

	dis.x = ApproachRot(r1.x, r2.x, speed / (dx + dy + dz)*dx);
	dis.y = ApproachRot(r1.y, r2.y, speed / (dx + dy + dz)*dy);
	dis.z = ApproachRot(r1.z, r2.z, speed / (dx + dy + dz)*dz);

	return dis;
}

//=============================================================================
// 慣性用approach
// vn: 今の速度　vt:目標速度 au:自体提供する加速度　ad:慣性加速度
// now = Approach(vn,vt,au,ad);
//=============================================================================
float ApproachSpeed(float vn, float vt, float au, float ad)
{
	float dis = vt - vn;
	if (dis == 0)
	{
		return vn;
	}
	float a;
	if (vn*vt < 0)
	{
		a = au + ad;
	}
	else if ((vn > 0 && vn > vt) || (vn < 0 && vn < vt))
	{
		a = ad;
	}
	else
	{
		a = au;
	}

	if (dis <= a && dis >= -a)
	{
		dis = vt;
	}
	else if (dis > a)
	{
		dis = vn + a;
	}
	else
	{
		dis = vn - a;
	}

	return dis;
}

//=============================================================================
// 慣性用approach
// vn: 今の速度　vt:目標速度 au:自体提供する加速度　ad:慣性加速度
// now = Approach(vn,vt,au,ad);
//=============================================================================
D3DXVECTOR3 ApproachSpeed(D3DXVECTOR3 vn, D3DXVECTOR3 vt, D3DXVECTOR3 au, D3DXVECTOR3 ad)
{
	D3DXVECTOR3 dis;

	dis.x = ApproachSpeed(vn.x, vt.x, au.x, ad.x);
	dis.y = ApproachSpeed(vn.y, vt.y, au.y, ad.y);
	dis.z = ApproachSpeed(vn.z, vt.z, au.z, ad.z);

	return dis;
}

//=============================================================================
// 向かい方向で移動速度分析
// rot: 移動方向	speed:移動速度
// pos += Move(rot,speed);
//=============================================================================
D3DXVECTOR3 Move(D3DXVECTOR3 rot, float speed)
{
	D3DXVECTOR3 t_speed;
	t_speed.x = -cosf(rot.x)*sinf(rot.y)*speed;
	t_speed.y = sinf(rot.x)*speed;
	t_speed.z = -cosf(-rot.x)*cosf(rot.y)*speed;
	return t_speed;
}

//=============================================================================
// 向かい方向で移動速度分析
// rot: 移動方向	speed:移動速度
//  Move(pos,rot,speed);
//=============================================================================
void Move(D3DXVECTOR3* pos, D3DXVECTOR3 rot, float speed)
{
	pos->x += -cosf(rot.x)*sinf(rot.y)*speed;
	pos->y += sinf(rot.x)*speed;
	pos->z += -cosf(-rot.x)*cosf(rot.y)*speed;
}

//=============================================================================
// 向かい方向で移動速度分析
// rot: 移動方向	speed:移動速度
//  Move(project);
//=============================================================================
void Move(PROJECT3D* project)
{
	project->pos.x += -cosf(project->rot.x)*sinf(project->rot.y)*project->speed.now;
	project->pos.y += sinf(project->rot.x)*project->speed.now;
	project->pos.z += -cosf(-project->rot.x)*cosf(project->rot.y)*project->speed.now;
}

//=============================================================================
// XCOLOR から D3DXCOLORへ変化
//=============================================================================
D3DXCOLOR ColorX2D(XCOLOR color)
{
	return D3DXCOLOR(color.R, color.G, color.B, color.A);
}

//=============================================================================
// XCOLORセット
//=============================================================================
XCOLOR SetXcolor(float R, float G, float B, float A)
{
	XCOLOR color;
	color.R = R;
	color.G = G;
	color.B = B;
	color.A = A;
	return color;
}


//=============================================================================
// カメラとの距離を取得
// pos: 目標位置
//=============================================================================
float GetDistance2Camera(D3DXVECTOR3 pos)
{
	D3DXVECTOR3 cpos = GetCamera(0)->CameraPos;
	D3DXVECTOR3 temp = D3DXVECTOR3(cpos.x - pos.x, cpos.y - pos.y, cpos.z - pos.z);
	return D3DXVec3Length(&temp);
}

//=============================================================================
// 二つの位置の距離を取得
// pos1: 目標位置1 pos2: 目標位置2
//=============================================================================
float GetDistance(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2)
{
	D3DXVECTOR3 temp = D3DXVECTOR3(pos1.x - pos2.x, pos1.y - pos2.y, pos1.z - pos2.z);
	return D3DXVec3Length(&temp);
}


//=============================================================================
// 距離を取得
// speed: 三つの軸の距離
//=============================================================================
float GetDistance(D3DXVECTOR3 speed)
{
	D3DXVECTOR3 temp = D3DXVECTOR3(speed.x, speed.y, speed.z);
	return D3DXVec3Length(&temp);
}

//=============================================================================
// 向いてる方向を取得
// pos1: 目標位置1 pos2: 目標位置2
//=============================================================================
D3DXVECTOR3 GetAngle(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2)
{
	D3DXVECTOR2 temp = D3DXVECTOR2(pos1.x - pos2.x, pos1.z - pos2.z);
	float dis = D3DXVec2Length(&temp);
	float x = -atan2f(pos1.y - pos2.y, dis);
	float y = atan2f(pos1.x - pos2.x, pos1.z - pos2.z);
	return D3DXVECTOR3(x, y, 0.0f);
}


//=============================================================================
// パーツの座標を計算すると現座標系の移動
// part 目標パーツ
// pos = GetPartPos(part);
//=============================================================================
D3DXVECTOR3 GetPartPos(PART part)
{

	D3DXVECTOR3 ppos = part.parent->pos;
	D3DXVECTOR3 prot = part.parent->rot;

	D3DXVECTOR3 pos = part.pos;

	D3DXVECTOR3 x = D3DXVECTOR3(pos.x, 0.0f, 0.0f);
	D3DXVECTOR3 y = D3DXVECTOR3(0.0f, pos.y, 0.0f);
	D3DXVECTOR3 z = D3DXVECTOR3(0.0f, 0.0f, pos.z);

	x.x = pos.x*cosf(prot.z)*cosf(prot.y);
	x.y = pos.x*sinf(prot.z)*cosf(prot.x);
	x.z = -pos.x*cosf(prot.z)*sinf(prot.y);

	y.x = pos.y*cosf(prot.z)*sinf(prot.x)*sinf(prot.y);
	y.y = pos.y*cosf(prot.z)*cosf(prot.x);
	y.z = pos.y*cosf(prot.z)*sinf(prot.x)*cosf(prot.y);

	z.x = pos.z*cosf(prot.x)*sinf(prot.y);
	z.y = -pos.z*sinf(prot.x);
	z.z = pos.z * cosf(prot.x)*cosf(prot.y);

	pos = x + y + z + ppos;


	return  pos;

}


//=============================================================================
// パーツの座標を計算すると現座標系の移動
// part 目標パーツ rot: 親の回転角度
// pos = GetPartPos(rot,part);
//=============================================================================
D3DXVECTOR3 GetPartPos(D3DXVECTOR3 parentrot, D3DXVECTOR3 p)
{

	D3DXVECTOR3 prot = parentrot;

	D3DXVECTOR3 pos = p;

	D3DXVECTOR3 x = D3DXVECTOR3(pos.x, 0.0f, 0.0f);
	D3DXVECTOR3 y = D3DXVECTOR3(0.0f, pos.y, 0.0f);
	D3DXVECTOR3 z = D3DXVECTOR3(0.0f, 0.0f, pos.z);

	x.x = pos.x*cosf(prot.z)*cosf(prot.y);
	x.y = pos.x*sinf(prot.z)*cosf(prot.x);
	x.z = -pos.x*cosf(prot.z)*sinf(prot.y);

	y.x = pos.y*cosf(prot.z)*sinf(prot.x)*sinf(prot.y);
	y.y = pos.y*cosf(prot.z)*cosf(prot.x);
	y.z = pos.y*cosf(prot.z)*sinf(prot.x)*cosf(prot.y);

	z.x = pos.z*cosf(prot.x)*sinf(prot.y);
	z.y = -pos.z*sinf(prot.x);
	z.z = pos.z * cosf(prot.x)*cosf(prot.y);

	pos = x + y + z;


	return  pos;

}

//=============================================================================
// バンディングサークル当たり判定
// pos1: 対象1の位置　pos2: 対象2の位置 size1:対象1の半径　size2:対象2の半径
// 戻り値: true 当たってる　false: 当たってない
//=============================================================================
bool hitCheckCircle(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float size1, float size2)
{
	float dis = GetDistance(pos1, pos2);
	if (dis > size1 + size2)
	{
		return false;
	}
	else
	{
		return true;
	}
}

//=============================================================================
// バンディングサークルと射線の当たり判定
// pos1: 射線の始点位置　rot1: 射線の方向　pos2: 対象2の位置 size1:射線1の半径　size2:対象2の半径　distance:線の長さ
// 戻り値: true 当たってる　false: 当たってない
//=============================================================================
bool hitCheckLC(D3DXVECTOR3 pos1, D3DXVECTOR3 rot1, D3DXVECTOR3 pos2, float size1, float size2, float distance)
{
	D3DXVECTOR3 v1 = Move(rot1, 1.0f);
	D3DXVECTOR3 v2 = pos2 - pos1;
	float dis = GetDistance(pos1, pos2);
	float a = D3DXVec3Dot(&v1, &v2);
	if (a < 0)
	{
		return false;
	}
	else
	{
		float angle;
		if ((int)dis == (int)a)
		{
			angle = 0.0f;
		}
		else
		{
			angle = acosf(a / D3DXVec3Length(&v1) / D3DXVec3Length(&v2));
		}
		if (sinf(angle)*dis > size1 + size2)
		{
			return false;
		}
		else
		{
			float angle2 = asinf(sinf(angle)*dis / (size1 + size2));
			if ((size1 + size2)*cosf(angle2) + distance >= dis * cosf(angle))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
}

//=============================================================================
//反対方向を求めます
// rot: 目標方向
// 戻り値: 入力値の反対
//=============================================================================
D3DXVECTOR3 GetAniRot(D3DXVECTOR3 rot) {
	D3DXVECTOR3 anirot = rot;
	anirot.x = -anirot.x;
	anirot.y += D3DX_PI;
	return RotControl(anirot);
}

//=============================================================================
//ランダムのfloat値を取得する
//min:ランダムちの下限　max:ランダムの上限 digit:小数をつけたい場合　bool:ゼロ以下つけるかどうか
//例： -0.003f~0.003fのランダムの場合　f=CreateRandf(0,3,1000,true);
//=============================================================================
float CreateRandf(int min, int max, int digit, bool s) {
	bool sign = rand() % 2;
	float r = (float)(rand() % (max - min) + min) / (float)digit;
	if (s&&sign)
	{
		r = -r;
	}
	return r;
}


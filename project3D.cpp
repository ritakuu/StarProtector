//=============================================================================
//
// ��{�v�Z���� [project3D.cpp]
// Author : lizeyu
//
//=============================================================================

#include "project3D.h"
#include "camera.h"

//=============================================================================
// rot��-180����180�܂Ő��䂷��
// rot:�Ώ�rot
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
// rot��-180����180�܂Ő��䂷��
// rot:�Ώ�rot
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
// �t���[�����Ƃŕς��
// now: ���ݒl�@target:�ڕW�l�@speed:�ω����x
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
// count down �t���[�����Ƃ�1���炵��
// now: ���ݒl
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
// �t���[�����Ƃŕς��
// now: ���ݒl�@target:�ڕW�l�@speed:�ω����x
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
// �t���[�����Ƃŕς��rot�p
// now: ���ݒl�@target:�ڕW�l�@speed:�ω����x
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
// �t���[�����Ƃŕς��
// now: ���ݒl�@target:�ڕW�l�@speed:�ω����x
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
// �t���[�����Ƃŕς��rot�p
// now: ���ݒl�@target:�ڕW�l�@speed:�ω����x
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
// �����papproach
// vn: ���̑��x�@vt:�ڕW���x au:���̒񋟂�������x�@ad:���������x
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
// �����papproach
// vn: ���̑��x�@vt:�ڕW���x au:���̒񋟂�������x�@ad:���������x
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
// �����������ňړ����x����
// rot: �ړ�����	speed:�ړ����x
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
// �����������ňړ����x����
// rot: �ړ�����	speed:�ړ����x
//  Move(pos,rot,speed);
//=============================================================================
void Move(D3DXVECTOR3* pos, D3DXVECTOR3 rot, float speed)
{
	pos->x += -cosf(rot.x)*sinf(rot.y)*speed;
	pos->y += sinf(rot.x)*speed;
	pos->z += -cosf(-rot.x)*cosf(rot.y)*speed;
}

//=============================================================================
// �����������ňړ����x����
// rot: �ړ�����	speed:�ړ����x
//  Move(project);
//=============================================================================
void Move(PROJECT3D* project)
{
	project->pos.x += -cosf(project->rot.x)*sinf(project->rot.y)*project->speed.now;
	project->pos.y += sinf(project->rot.x)*project->speed.now;
	project->pos.z += -cosf(-project->rot.x)*cosf(project->rot.y)*project->speed.now;
}

//=============================================================================
// XCOLOR ���� D3DXCOLOR�֕ω�
//=============================================================================
D3DXCOLOR ColorX2D(XCOLOR color)
{
	return D3DXCOLOR(color.R, color.G, color.B, color.A);
}

//=============================================================================
// XCOLOR�Z�b�g
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
// �J�����Ƃ̋������擾
// pos: �ڕW�ʒu
//=============================================================================
float GetDistance2Camera(D3DXVECTOR3 pos)
{
	D3DXVECTOR3 cpos = GetCamera(0)->CameraPos;
	D3DXVECTOR3 temp = D3DXVECTOR3(cpos.x - pos.x, cpos.y - pos.y, cpos.z - pos.z);
	return D3DXVec3Length(&temp);
}

//=============================================================================
// ��̈ʒu�̋������擾
// pos1: �ڕW�ʒu1 pos2: �ڕW�ʒu2
//=============================================================================
float GetDistance(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2)
{
	D3DXVECTOR3 temp = D3DXVECTOR3(pos1.x - pos2.x, pos1.y - pos2.y, pos1.z - pos2.z);
	return D3DXVec3Length(&temp);
}


//=============================================================================
// �������擾
// speed: �O�̎��̋���
//=============================================================================
float GetDistance(D3DXVECTOR3 speed)
{
	D3DXVECTOR3 temp = D3DXVECTOR3(speed.x, speed.y, speed.z);
	return D3DXVec3Length(&temp);
}

//=============================================================================
// �����Ă�������擾
// pos1: �ڕW�ʒu1 pos2: �ڕW�ʒu2
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
// �p�[�c�̍��W���v�Z����ƌ����W�n�̈ړ�
// part �ڕW�p�[�c
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
// �p�[�c�̍��W���v�Z����ƌ����W�n�̈ړ�
// part �ڕW�p�[�c rot: �e�̉�]�p�x
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
// �o���f�B���O�T�[�N�������蔻��
// pos1: �Ώ�1�̈ʒu�@pos2: �Ώ�2�̈ʒu size1:�Ώ�1�̔��a�@size2:�Ώ�2�̔��a
// �߂�l: true �������Ă�@false: �������ĂȂ�
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
// �o���f�B���O�T�[�N���Ǝː��̓����蔻��
// pos1: �ː��̎n�_�ʒu�@rot1: �ː��̕����@pos2: �Ώ�2�̈ʒu size1:�ː�1�̔��a�@size2:�Ώ�2�̔��a�@distance:���̒���
// �߂�l: true �������Ă�@false: �������ĂȂ�
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
//���Ε��������߂܂�
// rot: �ڕW����
// �߂�l: ���͒l�̔���
//=============================================================================
D3DXVECTOR3 GetAniRot(D3DXVECTOR3 rot) {
	D3DXVECTOR3 anirot = rot;
	anirot.x = -anirot.x;
	anirot.y += D3DX_PI;
	return RotControl(anirot);
}

//=============================================================================
//�����_����float�l���擾����
//min:�����_�����̉����@max:�����_���̏�� digit:�������������ꍇ�@bool:�[���ȉ����邩�ǂ���
//��F -0.003f~0.003f�̃����_���̏ꍇ�@f=CreateRandf(0,3,1000,true);
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


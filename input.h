//=============================================================================
//
// ���͏��� [input.h]
// Author : lizeyu
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_
#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

// �v���O������������Ƃ��Ɏg��
#define	USE_KEYBOARD										// �錾����ƃL�[�{�[�h�ő���\�ɂȂ�
#define	USE_MOUSE											// �錾����ƃ}�E�X�ő���\�ɂȂ�
#define	USE_PAD												// �錾����ƃp�b�h�ő���\�ɂȂ�


/* game pad��� */
#define BUTTON_UP			0x00000001l						// �����L�[��(.IY<0)
#define BUTTON_DOWN			0x00000002l						// �����L�[��(.IY>0)
#define BUTTON_LEFT			0x00000004l						// �����L�[��(.IX<0)
#define BUTTON_RIGHT		0x00000008l						// �����L�[�E(.IX>0)
#define BUTTON_RL			0x00000010l						// �`�{�^��(.rgbButtons[0]&0x80)
#define BUTTON_RD			0x00000020l						// �a�{�^��(.rgbButtons[1]&0x80)
#define BUTTON_RR			0x00000040l						// �b�{�^��(.rgbButtons[2]&0x80)
#define BUTTON_RU			0x00000080l						// �w�{�^��(.rgbButtons[3]&0x80)
#define BUTTON_L1			0x00000100l						// �x�{�^��(.rgbButtons[4]&0x80)
#define BUTTON_R1			0x00000200l						// �y�{�^��(.rgbButtons[5]&0x80)
#define BUTTON_L2			0x00000400l						// �k�{�^��(.rgbButtons[6]&0x80)
#define BUTTON_R2			0x00000800l						// �q�{�^��(.rgbButtons[7]&0x80)
#define BUTTON_SHARE		0x00001000l						// �r�s�`�q�s�{�^��(.rgbButtons[8]&0x80)
#define BUTTON_OPTIONS		0x00002000l						// �l�{�^��(.rgbButtons[9]&0x80)
#define BUTTON_L3			0x00004000l						// �l�{�^��(.rgbButtons[10]&0x80)
#define BUTTON_R3			0x00008000l						// �l�{�^��(.rgbButtons[11]&0x80)
#define BUTTON_TOUCH		0x00010000l						// touch�{�^��(.rgbButtons[12]&0x80)
#define BUTTON_LL			0x00020000l						// touch�{�^��(.rgbButtons[12]&0x80)
#define BUTTON_LD			0x00040000l						// touch�{�^��(.rgbButtons[12]&0x80)
#define BUTTON_LR			0x00080000l						// touch�{�^��(.rgbButtons[12]&0x80)
#define BUTTON_LU			0x00100000l						// touch�{�^��(.rgbButtons[12]&0x80)
#define GAMEPADMAX			4								// �����ɐڑ�����W���C�p�b�h�̍ő吔���Z�b�g

#define DEADZONE			2500							// �e����25%�𖳌��]�[���Ƃ���
#define RANGE_MAX			1000							// �L���͈͂̍ő�l
#define RANGE_MIN			-1000							// �L���͈͂̍ŏ��l

#define OPERATION_MENUE_UP				(GetKeyboardTrigger(DIK_LEFT)||GetKeyboardTrigger(DIK_A)||GetKeyboardTrigger(DIK_W)||IsButtonTriggered(0,BUTTON_LL)||IsButtonTriggered(0,BUTTON_LU)||IsButtonTriggered(0,BUTTON_UP)||IsButtonTriggered(0,BUTTON_LEFT))
#define OPERATION_MENUE_DOWN			(GetKeyboardTrigger(DIK_RIGHT)||GetKeyboardTrigger(DIK_D)||GetKeyboardTrigger(DIK_S)||IsButtonTriggered(0,BUTTON_LR)||IsButtonTriggered(0,BUTTON_LD)||IsButtonTriggered(0,BUTTON_DOWN)||IsButtonTriggered(0,BUTTON_RIGHT))
#define OPERATION_FIND_NEXT_ENEMY		(GetKeyboardPress(DIK_E)||IsButtonPressed(0,BUTTON_R3))
#define OPERATION_CHANGE_VIEW			(GetKeyboardTrigger(DIK_TAB)||IsButtonTriggered(0,BUTTON_L3))
#define OPERATION_JUMP					(GetKeyboardTrigger(DIK_SPACE)||IsButtonTriggered(0,BUTTON_RD))
#define OPERATION_SELECT				(GetKeyboardTrigger(DIK_RETURN)||IsButtonTriggered(0,BUTTON_RR))
#define OPERATION_PAUSE					(GetKeyboardTrigger(DIK_BACK)||IsButtonTriggered(0,BUTTON_OPTIONS))
#define OPERATION_SHOOT					(IsMouseLeftPressed()||IsButtonPressed(0,BUTTON_R2))
#define OPERATION_MISSILE				(IsMouseCenterPressed()||IsButtonPressed(0,BUTTON_L2))
#define OPERATION_SPEED_UP				(GetKeyboardPress(DIK_LSHIFT)||IsButtonPressed(0,BUTTON_R1))
#define OPERATION_SNIPER_MODE			(IsMouseRightPressed()||IsButtonPressed(0,BUTTON_L1))
#define OPERATION_SNIPER_MODE			(IsMouseRightPressed()||IsButtonPressed(0,BUTTON_L1))

#define OPERATION_DICTION				(GetKeyboardTrigger(DIK_UP)||GetKeyboardTrigger(DIK_DOWN)||GetKeyboardTrigger(DIK_RIGHT)||GetKeyboardTrigger(DIK_LEFT))
#define OPERATION_MOVE					(GetKeyboardPress(DIK_W)||GetKeyboardPress(DIK_A)||GetKeyboardPress(DIK_S)||GetKeyboardPress(DIK_D))
#define OPERATION_MOVE_FRONT			(GetKeyboardPress(DIK_W))
#define OPERATION_MOVE_LEFT				(GetKeyboardPress(DIK_A))
#define OPERATION_MOVE_RIGHT			(GetKeyboardPress(DIK_D))
#define OPERATION_MOVE_BACK				(GetKeyboardPress(DIK_S))


#define CHEAT_KILL_ALL					(GetKeyboardTrigger(DIK_F4)||IsButtonTriggered(0,BUTTON_TOUCH))
#define CHEAT_ENEMY1_ADD				(GetKeyboardTrigger(DIK_F1)||(IsButtonPressed(0,BUTTON_RU)&&IsButtonTriggered(0,BUTTON_LL)))
#define CHEAT_ENEMY2_ADD				(GetKeyboardTrigger(DIK_F2)||(IsButtonPressed(0,BUTTON_RU)&&IsButtonTriggered(0,BUTTON_LU)))
#define CHEAT_ENEMY3_ADD				(GetKeyboardTrigger(DIK_F3)||(IsButtonPressed(0,BUTTON_RU)&&IsButtonTriggered(0,BUTTON_LR)))


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitInput(HINSTANCE hInst, HWND hWnd);
void UninitInput(void);
void UpdateInput(void);

//---------------------------- keyboard
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);
bool GetKeyboardRepeat(int nKey);
bool GetKeyboardRelease(int nKey);

//---------------------------- mouse
BOOL IsMouseLeftPressed(void);								// ���N���b�N�������
BOOL IsMouseLeftTriggered(void);							// ���N���b�N�����u��
BOOL IsMouseRightPressed(void);								// �E�N���b�N�������
BOOL IsMouseRightTriggered(void);							// �E�N���b�N�����u��
BOOL IsMouseCenterPressed(void);							// ���N���b�N�������
BOOL IsMouseCenterTriggered(void);							// ���N���b�N�����u��
long GetMouseX(void);										// �}�E�X��X�����ɓ��������Βl
long GetMouseY(void);										// �}�E�X��Y�����ɓ��������Βl
long GetMouseZ(void);										// �}�E�X�z�C�[�������������Βl

//---------------------------- game pad
BOOL IsButtonPressed(int padNo, DWORD button);
BOOL IsButtonTriggered(int padNo, DWORD button);
D3DXVECTOR3 GetButtonDictionL(int padNo);
D3DXVECTOR3 GetButtonDictionR(int padNo);
BOOL IsButtonReleased(int padNo, DWORD button);


#endif
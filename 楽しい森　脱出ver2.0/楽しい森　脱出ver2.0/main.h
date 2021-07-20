//=============================================================================
//
// ���C������ [main.h]
// Author : ����@�r�H
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#define _CRT_SECURE_NO_WARNINGS
#define DIRECTINPUT_VERSION 0x0800

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include <Windows.h>
#include "d3dx9.h"
#include "dinput.h"
#include <stdlib.h>
#include <xaudio2.h>
#include <stdio.h>

//*****************************************************************************
//�O������
//*****************************************************************************
//class CRenderer;
//class CScene;

//*****************************************************************************
// ���C�u�����t�@�C���̃����N
//*****************************************************************************
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dinput8.lib")

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define SCREEN_WIDTH (1280)//�E�B���h�E�̕�
#define SCREEN_HEIGHT (720)//�E�B���h�E�̍���
#define NUM_VERTEX (4) //���_��
#define NUM_POLYGON (2) //�|���S����
#define MAX_POLYGON (256)


//*****************************************************************************
// �\���̒�`
//*****************************************************************************
// 2D�ݒ�
typedef struct
{
	D3DXVECTOR3 pos; //���_���W
	float rhw; //���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col; //���_�J���[
	D3DXVECTOR2 tex; //�e�N�X�`�����W
}VERTEX_2D;

// 3D�ݒ�
typedef struct
{
	D3DXVECTOR3 pos;	//�I�����_���W
	D3DXVECTOR3 nor;	//�I���@���x�N�g��
	D3DCOLOR col;		//�I�����_�J���[
	D3DXVECTOR2 tex;
}VERTEX_3D;


int GetFPS(void);

#endif
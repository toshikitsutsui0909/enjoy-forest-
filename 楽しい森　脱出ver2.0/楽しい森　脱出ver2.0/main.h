//=============================================================================
//
// メイン処理 [main.h]
// Author : 筒井　俊稀
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#define _CRT_SECURE_NO_WARNINGS
#define DIRECTINPUT_VERSION 0x0800

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include <Windows.h>
#include "d3dx9.h"
#include "dinput.h"
#include <stdlib.h>
#include <xaudio2.h>
#include <stdio.h>

//*****************************************************************************
//前方処理
//*****************************************************************************
//class CRenderer;
//class CScene;

//*****************************************************************************
// ライブラリファイルのリンク
//*****************************************************************************
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dinput8.lib")

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define SCREEN_WIDTH (1280)//ウィンドウの幅
#define SCREEN_HEIGHT (720)//ウィンドウの高さ
#define NUM_VERTEX (4) //頂点数
#define NUM_POLYGON (2) //ポリゴン数
#define MAX_POLYGON (256)


//*****************************************************************************
// 構造体定義
//*****************************************************************************
// 2D設定
typedef struct
{
	D3DXVECTOR3 pos; //頂点座標
	float rhw; //座標変換用係数(1.0fで固定)
	D3DCOLOR col; //頂点カラー
	D3DXVECTOR2 tex; //テクスチャ座標
}VERTEX_2D;

// 3D設定
typedef struct
{
	D3DXVECTOR3 pos;	//！＜頂点座標
	D3DXVECTOR3 nor;	//！＜法線ベクトル
	D3DCOLOR col;		//！＜頂点カラー
	D3DXVECTOR2 tex;
}VERTEX_3D;


int GetFPS(void);

#endif
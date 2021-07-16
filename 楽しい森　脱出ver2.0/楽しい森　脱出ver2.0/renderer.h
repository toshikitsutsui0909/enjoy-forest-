//=============================================================================
//
// レンダラー処理 [renderer.h]
// Author : 
//
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"

//-----------------------------------------------------------------------------
//レンダリングクラス
//-----------------------------------------------------------------------------
class CRenderer
{
public:
	CRenderer();
	~CRenderer();
	HRESULT Init(HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }
private:
	void DrawFPS(void);

	LPDIRECT3D9				m_pD3D;			// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9		m_pD3DDevice;	// Deviceオブジェクト(描画に必要)
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffPolygon; //頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9		m_pTexturePolygon; //テクスチャへのポインタ
	D3DXVECTOR3				m_PosPolygon;
	LPD3DXFONT				m_pFont;			// フォントへのポインタ

};

#endif
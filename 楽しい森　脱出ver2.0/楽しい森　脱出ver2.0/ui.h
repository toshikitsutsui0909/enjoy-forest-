//=============================================================================
//
// UI処理 [ui.h]
// Author : 筒井　俊稀
//
//=============================================================================

#ifndef _UI_H_
#define _UI_H_

#include "main.h"
#include "scene.h"

class CUi : public CScene
{
public:
	typedef enum
	{
		UI_NONE = 0,
		UI_MAX
	}UI;

	CUi();
	~CUi();

	static CUi *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);
	HRESULT Load(void);
	void Unload(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPos(const D3DXVECTOR3 pos);		// pos座標の設定
	D3DXVECTOR3 GetPos(void) { return m_pos; }		// pos座標の取得
	void SetSize(const D3DXVECTOR3 size);	// size情報の設定
	D3DXVECTOR3 GetSize(void) { return m_size; }	// size情報の取得

private:
	void Vertex(void);

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; //頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9		m_apTexture[UI_MAX]; //テクスチャへのポインタ
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;

};




#endif
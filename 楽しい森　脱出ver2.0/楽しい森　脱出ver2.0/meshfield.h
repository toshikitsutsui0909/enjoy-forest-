//=============================================================================
//
// UI処理 [ui.h]
// Author : 筒井　俊稀
//
//=============================================================================

#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

//=============================================================================
// インクルード定義
//=============================================================================
#include "main.h"
#include "scene3d.h"

//=============================================================================
// クラス定義
//=============================================================================
class CMeshfield : public CScene
{
public:
	CMeshfield();
	~CMeshfield();

	static HRESULT Load(void);
	static void Unload(void);
	static CMeshfield *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	//インデックスバッファへのポインタ
	D3DXVECTOR3 m_pos;			//メッシュフィールドの位置
	D3DXVECTOR3 m_rot;			//メッシュフィールドの向き
	D3DXCOLOR m_col;
	D3DXMATRIX m_mtxWorld;		//メッシュフィールドのワールドマトリックス

};

#endif // !__MESHFIELD_H_

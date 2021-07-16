//=============================================================================
//
// プレイヤー処理[player.h]
// Author : 筒井 俊稀
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene3d.h"

//=============================================================================
// クラス定義
//=============================================================================
class CPlayer : public CScene3d
{
public:
	CPlayer();
	~CPlayer();

	static CPlayer *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture; //テクスチャへのポインタ
	D3DXVECTOR3				m_pos;		//座標変数
	D3DXVECTOR3				m_size;		//サイズ変数
	D3DXVECTOR3				m_rot;		//rot変数
	D3DXCOLOR				m_col;		//カラー変数
};












#endif //! _PLAYER_H_
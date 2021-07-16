//------------------------------------------
//
//	クラスポリゴン描画[scene2d.h]
//	筒井
//
//------------------------------------------

#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//------------------------------------------
//	インクルードファイル
//------------------------------------------
#include"main.h"
#include"scene.h"

//------------------------------------------
//	scene2dクラス
//------------------------------------------
class CScene2d : public CScene
{
public:
	// フラッシュ設定
	typedef enum
	{
		FLASH_STATE_NONE = 0,
		FLASH_STATE_IN,
		FLASH_STATE_OUT,
		FLASH_STATE_MAX
	}FLASH_STATE;

	CScene2d(int nPriority = OBJTYPE_NONE);
	~CScene2d();

	static CScene2d *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPos(D3DXVECTOR3 pos);	// pos座標の設定
	void SetSize(D3DXVECTOR3 size);	// size情報の設定
	void SetColor(D3DXCOLOR col);	// color情報の設定

	D3DXVECTOR3 GetSize(void) { return m_size; }	// size情報の取得
	D3DXVECTOR3 GetPos(void) { return m_pos; }		// pos座標の取得

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);	//Bind　割り当てる
	void Flashing(void);							//フラッシュ処理関数
private:
	void Vertex(void);

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; //頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9		m_pTexture; //テクスチャへのポインタ
	D3DXVECTOR3				m_pos;		//座標変数
	D3DXVECTOR3				m_size;		//サイズ変数
	D3DXVECTOR2				m_Texture;	//テクスチャ変数
	D3DXCOLOR				m_col;		//カラー変数
	bool					m_bFlash;	//フラッシュするかしないかの判別
	FLASH_STATE				m_FlashState;
};


#endif //_SCENE2D_H_
//------------------------------------------
//
//	クラスポリゴン描画[scene3d.h]
//	Author : 筒井　俊稀
//
//------------------------------------------

#ifndef _SCENE3D_H_
#define _SCENE3D_H_

//------------------------------------------
//	インクルードファイル
//------------------------------------------
#include"main.h"
#include"scene.h"

//------------------------------------------
//	scene2dクラス
//------------------------------------------
class CScene3d : public CScene
{
public:

	CScene3d(int nPriority = OBJTYPE_NONE);
	~CScene3d();

	static CScene3d *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPos(const D3DXVECTOR3 pos);		// pos座標の設定
	void SetSize(const D3DXVECTOR3 size);	// size情報の設定
	void SetColor(const D3DXCOLOR col);		// color情報の設定
	void SetRot(const D3DXVECTOR3 rot);		// rot情報の設定

	D3DXVECTOR3 GetSize(void) { return m_size; }	// size情報の取得
	D3DXVECTOR3 GetPos(void) { return m_pos; }		// pos座標の取得
	D3DXVECTOR3 GetRot(void) { return m_rot; }		// rot情報の取得

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);	//Bind　割り当てる
private:
	void Vertex(void);

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; //頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9		m_pTexture; //テクスチャへのポインタ
	D3DXVECTOR3				m_pos;		//座標変数
	D3DXVECTOR3				m_size;		//サイズ変数
	D3DXVECTOR3				m_rot;		//rot変数
	D3DXCOLOR				m_col;		//カラー変数
	D3DXMATRIX				m_mtxWorld;
};


#endif //_SCENE3D_H_
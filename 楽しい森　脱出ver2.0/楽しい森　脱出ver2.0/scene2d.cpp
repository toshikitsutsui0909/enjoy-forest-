//=============================================================================
//
// scene2d処理 [scene2d.cpp]
// Author : 筒井 俊稀
//
//=============================================================================
#include "scene2d.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
//	マクロ定義
//=============================================================================
#define FLASH_RATE 0.05f	// フラッシュの速さ

//=============================================================================
//	コンストラクタ
//=============================================================================
CScene2d::CScene2d(int nPriority) : CScene(nPriority)
{
	//初期化
	m_pVtxBuff = NULL;
	m_pTexture = NULL;
	m_pos = D3DXVECTOR3();
	m_size = D3DXVECTOR3();
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_bFlash = true;
	m_FlashState = FLASH_STATE_IN;
}

//=============================================================================
//	デストラクタ
//=============================================================================
CScene2d::~CScene2d()
{
}

//=============================================================================
//	生成処理
//=============================================================================
CScene2d * CScene2d::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	CScene2d *pScene2D;
	pScene2D = new CScene2d;
	if (pScene2D != NULL)
	{
		pScene2D->SetPos(pos);
		pScene2D->SetSize(size);
		pScene2D->Init();
	}
	return pScene2D;
}
//=============================================================================
//	初期化処理
//=============================================================================
HRESULT CScene2d::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3((m_pos.x - (m_size.x / 2)), (m_pos.y - (m_size.y / 2)), 0.0f);//左上
	pVtx[1].pos = D3DXVECTOR3((m_pos.x + (m_size.x / 2)), (m_pos.y - (m_size.y / 2)), 0.0f);//右上
	pVtx[2].pos = D3DXVECTOR3((m_pos.x - (m_size.x / 2)), (m_pos.y + (m_size.y / 2)), 0.0f);//左下
	pVtx[3].pos = D3DXVECTOR3((m_pos.x + (m_size.x / 2)), (m_pos.y + (m_size.y / 2)), 0.0f);//右下

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//rhwの設定(値は1.0で固定)
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定(0～255の範囲で設定)
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);


	//頂点データをアンロックする
	m_pVtxBuff->Unlock();
	return S_OK;
}

//=============================================================================
//	終了処理
//=============================================================================
void CScene2d::Uninit(void)
{
	//バッファの開放
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	SetDeathFlag();
}

//=============================================================================
//	更新処理
//=============================================================================
void CScene2d::Update(void)
{
	Vertex();
}

//=============================================================================
//	描画処理
//=============================================================================
void CScene2d::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	//テクスチャの設定を元に戻す
	pDevice->SetTexture(0, NULL);
}

//=============================================================================
//	描画したい場所の座標を求める処理
//=============================================================================
void CScene2d::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
//	描画したい場所の大きさを求める処理
//=============================================================================
void CScene2d::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//=============================================================================
//	描画したい場所のテクスチャを求める処理
//=============================================================================
void CScene2d::SetColor(D3DXCOLOR col)
{
	m_col = col;
}

//=============================================================================
//	テクスチャを分ける処理
//=============================================================================
void CScene2d::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//=============================================================================
//	テクスチャフラッシュ処理
//=============================================================================
void CScene2d::Flashing(void)
{
	if (m_FlashState == FLASH_STATE_IN)
	{
		m_col.a -= FLASH_RATE;
		if (m_col.a <= 0.0f)
		{
			m_col.a = 0.0f;
			m_FlashState = FLASH_STATE_OUT;
		}
	}
	else if (m_FlashState == FLASH_STATE_OUT)
	{
		m_col.a += FLASH_RATE;
		if (m_col.a >= 1.0f)
		{
			m_col.a = 1.0f;
			m_FlashState = FLASH_STATE_IN;
		}
	}
}

//=============================================================================
//	セット更新処理
//=============================================================================
void CScene2d::Vertex(void)
{
	VERTEX_2D *pVtx; //頂点情報へのポインタ

					 //頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3((m_pos.x - m_size.x / 2), (m_pos.y - m_size.y / 2), 0.0f);//左上
	pVtx[1].pos = D3DXVECTOR3((m_pos.x + m_size.x / 2), (m_pos.y - m_size.y / 2), 0.0f);//右上
	pVtx[2].pos = D3DXVECTOR3((m_pos.x - m_size.x / 2), (m_pos.y + m_size.y / 2), 0.0f);//左下
	pVtx[3].pos = D3DXVECTOR3((m_pos.x + m_size.x / 2), (m_pos.y + m_size.y / 2), 0.0f);//右下

	//頂点カラーの設定(0～255の範囲で設定)
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//頂点データをアンロックする
	m_pVtxBuff->Unlock();
}
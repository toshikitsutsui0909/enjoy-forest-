//=============================================================================
//
// scene2d処理 [scene2d.cpp]
// Author : 筒井 俊稀
//
//=============================================================================
#include "scene3d.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
//	マクロ定義
//=============================================================================

//=============================================================================
//	コンストラクタ
//=============================================================================
CScene3d::CScene3d(int nPriority)
{
	//初期化
	m_pVtxBuff = NULL;
	m_pTexture = NULL;
	m_pos = D3DXVECTOR3();
	m_size = D3DXVECTOR3();
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
//	デストラクタ
//=============================================================================
CScene3d::~CScene3d()
{
}

//=============================================================================
//	生成処理
//=============================================================================
CScene3d * CScene3d::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	CScene3d *pScene3d = new CScene3d;

	if (pScene3d != NULL)
	{
		pScene3d->SetPos(pos);
		pScene3d->SetSize(size);
		pScene3d->Init();
	}
	return pScene3d;
}

//=============================================================================
//	初期化処理
//=============================================================================
HRESULT CScene3d::Init(void)
{
	VERTEX_3D *pVtx;

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	// メンバ変数の初期化
	m_col = { 0.0f,1.0f,1.0f,1.0f };

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3((m_pos.x - (m_size.x / 2)), (m_pos.y + (m_size.y / 2)), (m_pos.z + (m_size.z / 2)));
	pVtx[1].pos = D3DXVECTOR3((m_pos.x + (m_size.x / 2)), (m_pos.y + (m_size.y / 2)), (m_pos.z + (m_size.z / 2)));
	pVtx[2].pos = D3DXVECTOR3((m_pos.x - (m_size.x / 2)), (m_pos.y - (m_size.y / 2)), (m_pos.z - (m_size.z / 2)));
	pVtx[3].pos = D3DXVECTOR3((m_pos.x + (m_size.x / 2)), (m_pos.y - (m_size.y / 2)), (m_pos.z - (m_size.z / 2)));

	//各頂点の法線の設定（※ベクトルの大きさは１にする必要がある）
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// 色の設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//各頂点の法線の設定（※ベクトルの大きさは１にする必要がある）
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	// アンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
//	終了処理
//=============================================================================
void CScene3d::Uninit(void)
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
void CScene3d::Update(void)
{
	Vertex();
}

//=============================================================================
//	描画処理
//=============================================================================
void CScene3d::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans, mtxScail;//行列計算用マトリクス

										  // マトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixIdentity(&mtxRot);
	D3DXMatrixIdentity(&mtxTrans);
	D3DXMatrixIdentity(&mtxScail);

	// サイズ
	//D3DXMatrixScaling(&mtxScail, 1.0f, 1.0f, 1.0f);
	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScail);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	pDevice->SetTexture(0, 0);
}

//=============================================================================
//	POS座標の設定
//=============================================================================
void CScene3d::SetPos(const D3DXVECTOR3 pos)
{
	//posの代入
	m_pos = pos;
}

//=============================================================================
//	SIZE情報の設定
//=============================================================================
void CScene3d::SetSize(const D3DXVECTOR3 size)
{
	m_size = size;
	// 頂点座標の再設定
	SetPos(m_pos);
}

//=============================================================================
//	color情報の設定
//=============================================================================
void CScene3d::SetColor(const D3DXCOLOR col)
{
	m_col = col;
}

//=============================================================================
//	rotの設定
//=============================================================================
void CScene3d::SetRot(const D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
//	テクスチャを分ける処理
//=============================================================================
void CScene3d::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//=============================================================================
//	セット更新処理
//=============================================================================
void CScene3d::Vertex(void)
{
	VERTEX_3D *pVtx; //頂点情報へのポインタ

					 //頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3((m_pos.x - (m_size.x / 2)), (m_pos.y + (m_size.y / 2)), (m_pos.z + (m_size.z / 2)));
	pVtx[1].pos = D3DXVECTOR3((m_pos.x + (m_size.x / 2)), (m_pos.y + (m_size.y / 2)), (m_pos.z + (m_size.z / 2)));
	pVtx[2].pos = D3DXVECTOR3((m_pos.x - (m_size.x / 2)), (m_pos.y - (m_size.y / 2)), (m_pos.z - (m_size.z / 2)));
	pVtx[3].pos = D3DXVECTOR3((m_pos.x + (m_size.x / 2)), (m_pos.y - (m_size.y / 2)), (m_pos.z - (m_size.z / 2)));

	//頂点カラーの設定(0～255の範囲で設定)
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//頂点データをアンロックする
	m_pVtxBuff->Unlock();
}

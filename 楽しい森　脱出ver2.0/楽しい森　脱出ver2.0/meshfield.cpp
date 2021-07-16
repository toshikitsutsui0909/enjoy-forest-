//=============================================================================
//
// メッシュフィールド処理 [meshfield.cpp]
// Author : 筒井 俊稀
//
//=============================================================================
//=============================================================================
//	インクルードファイル
//=============================================================================
#include "meshfield.h"
#include "manager.h"
#include "renderer.h"

#define MESHFIELD_X_BLOCK 50//X方向のブロック数
#define MESHFIELD_Z_BLOCK 50//Y方向のブロック数
#define MESH_LENGTH 20	//一片の長さ
#define MESHFIELD_VERTEX_NUM ((MESHFIELD_X_BLOCK+1)*(MESHFIELD_Z_BLOCK+1))	//頂点数
#define MESHFIELD_INDEX_NUM (((MESHFIELD_X_BLOCK+1)*2)*MESHFIELD_Z_BLOCK+(MESHFIELD_Z_BLOCK-1)*2)	//インデックス数
#define MESHFIELD_PRIMITIVE_NUM	((MESHFIELD_X_BLOCK*2)*MESHFIELD_Z_BLOCK+(MESHFIELD_Z_BLOCK-1)*4)	//ポリゴン数

//=============================================================================
//	静的メンバ変数宣言初期化
//=============================================================================
LPDIRECT3DTEXTURE9 CMeshfield::m_pTexture = NULL;

//=============================================================================
//	コンストラクタ
//=============================================================================
CMeshfield::CMeshfield()
{
	m_pVtxBuff = NULL;
	m_pIdxBuff = NULL;
	m_pos = D3DXVECTOR3();
	m_rot = D3DXVECTOR3();
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_mtxWorld;
}

//=============================================================================
//	デストラクタ
//=============================================================================
CMeshfield::~CMeshfield()
{
}

//=============================================================================
//	テクスチャロード処理
//=============================================================================
HRESULT CMeshfield::Load(void)
{
	return S_OK;
}

//=============================================================================
//	テクスチャ破棄
//=============================================================================
void CMeshfield::Unload(void)
{
}

//=============================================================================
//	生成処理
//=============================================================================
CMeshfield * CMeshfield::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	CMeshfield *pMeshfield = new CMeshfield;

	if (pMeshfield != NULL)
	{
		pMeshfield->m_pos = pos;
		pMeshfield->m_rot = rot;
		pMeshfield->Init();
	}

	return pMeshfield;
}

//=============================================================================
//	初期化処理
//=============================================================================
HRESULT CMeshfield::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	int nCntX;
	int nCntZ;
	int nCount = 0;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * MESHFIELD_VERTEX_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);
	//インデックスバッファ（ポリゴンバッファ）の生成
	pDevice->CreateIndexBuffer(
		sizeof(WORD) * (MESHFIELD_INDEX_NUM),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	VERTEX_3D*pVtx = NULL;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標設定
	for (nCntZ = 0; nCntZ < (MESHFIELD_Z_BLOCK + 1); nCntZ++)
	{
		for (nCntX = 0; nCntX < (MESHFIELD_X_BLOCK + 1); nCntX++)
		{
			pVtx[nCount].pos = D3DXVECTOR3(
				(float)nCntX * MESH_LENGTH - (MESHFIELD_X_BLOCK * (MESH_LENGTH / 2)),
				0.5f,
				(float)nCntZ*-MESH_LENGTH + (MESHFIELD_Z_BLOCK * (MESH_LENGTH / 2)));

			nCount += 1;
		}
	}

	//頂点の法線・カラー設定
	for (int nCnt = 0; nCnt < MESHFIELD_VERTEX_NUM; nCnt++)
	{
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[nCnt].col = m_col;

	}


	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();


	WORD*pIdx;

	//インデックスバッファをロック
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//インデックス座標の設定
	nCount = 0;

	for (int nIdZ = 0; nIdZ < MESHFIELD_Z_BLOCK; nIdZ++)
	{
		if (nIdZ != 0)
		{
			pIdx[nCount] = (MESHFIELD_X_BLOCK + 1 + (nIdZ*(MESHFIELD_X_BLOCK + 1)));
			nCount += 1;
		}
		for (int nIdxX = 0; nIdxX < (MESHFIELD_X_BLOCK + 1); nIdxX++)
		{

			pIdx[nCount] = (MESHFIELD_X_BLOCK + 1 + nIdxX + (nIdZ*(MESHFIELD_X_BLOCK + 1)));
			nCount += 1;

			pIdx[nCount] = (pIdx[nCount - 1] - (MESHFIELD_X_BLOCK + 1));
			nCount += 1;
		}
		if (nIdZ != (MESHFIELD_Z_BLOCK - 1))
		{
			pIdx[nCount] = pIdx[nCount - 1];
			nCount += 1;
		}
	}

	//インデックスバッファのアンロック
	m_pIdxBuff->Unlock();
	return S_OK;
}

//=============================================================================
//	終了処理
//=============================================================================
void CMeshfield::Uninit(void)
{
	//バッファの開放
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	// インデックスの開放
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	SetDeathFlag();
}

//=============================================================================
//	更新処理
//=============================================================================
void CMeshfield::Update(void)
{

}

//=============================================================================
//	描画処理
//=============================================================================
void CMeshfield::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans, mtxScail;//行列計算用マトリクス

										  // マトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixIdentity(&mtxRot);
	D3DXMatrixIdentity(&mtxTrans);
	D3DXMatrixIdentity(&mtxScail);

	// サイズ
	D3DXMatrixScaling(&mtxScail, 1.0f, 1.0f, 1.0f);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScail);

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
	pDevice->SetTexture(0, NULL);
}

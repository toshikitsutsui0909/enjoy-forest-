//=============================================================================
//
// camera処理 [camera.cpp]
// Author : トシキ
//
//=============================================================================
#include "camera.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"

//=============================================================================
//コンストラクタ
//=============================================================================
CCamera::CCamera()
{
	m_fCamera = 0.9f;

	m_posV = D3DXVECTOR3(0.0f, 100.0f, -100.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
}

//=============================================================================
//デストラクタ
//=============================================================================
CCamera::~CCamera()
{
}

//=============================================================================
//生成処理
//=============================================================================
CCamera * CCamera::Create(void)
{
	CCamera * pCamera = new CCamera;

	if (pCamera != NULL)
	{
		pCamera->Init();
	}
	return pCamera;
}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CCamera::Init(void)
{
	//m_fDistance = m_posR.z - m_posV.z;
	m_fDistance = -50.0f;
	m_posV = D3DXVECTOR3(0.0f, 300.0f, -m_fDistance);	//位置zはm_fDistance分-方向へ設定する
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//注視点は全て0座標を見る
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void CCamera::Uninit(void)
{
}

//=============================================================================
//更新処理
//=============================================================================
void CCamera::Update(void)
{
	CInputKeyBoard *pInput
		= CManager::GetInput();
	m_posVOld = m_posV;

	//前
	if (pInput->GetKeyPress(DIK_W))
	{
		m_posV.z += 5.0f;
		m_posR.z += 5.0f;
	}

	//後
	if (pInput->GetKeyPress(DIK_S))
	{
		m_posV.z -= 5.0f;
		m_posR.z -= 5.0f;
	}

	//右
	if (pInput->GetKeyPress(DIK_D))
	{
		m_posV.x += 5.0f;
		m_posR.x += 5.0f;
	}
	//左
	if (pInput->GetKeyPress(DIK_A))
	{
		m_posV.x -= 5.0f;
		m_posR.x -= 5.0f;
	}
}

void CCamera::Draw(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxProjection);

	//プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		10000.0f);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION,
		&m_mtxProjection);
}

//=============================================================================
//
// camera処理 [camera.cpp]
// Author : 筒井俊稀
//
//=============================================================================
#include "light.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
//コンストラクタ
//=============================================================================
CLight::CLight()
{
	SecureZeroMemory(&m_light, sizeof(D3DLIGHT9));
}

//=============================================================================
//デストラクタ
//=============================================================================
CLight::~CLight()
{
}

//=============================================================================
//生成処理
//=============================================================================
CLight * CLight::Create(void)
{
	CLight * pLight = new CLight;

	if (pLight != NULL)
	{
		pLight->Init();
	}
	return pLight;
}

//=============================================================================
//初期化処理
//=============================================================================
HRESULT CLight::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();//デバイスへのポインタ
	D3DXVECTOR3 vecDir;//ライトの方向ベクトル
	//ライトをクリアする
	ZeroMemory(&m_light, sizeof(D3DLIGHT9));
	//ライトの種類を設定
	m_light.Type = D3DLIGHT_DIRECTIONAL;
	//ライトの拡散光を設定
	m_light.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	//ライトの光の色を設定
	m_light.Diffuse = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);

	//ライトの方向を設定
	vecDir = D3DXVECTOR3(0.0f, -2.0f, 1.0f);
	//pCamera->posR - pCamera->posV;
	D3DXVec3Normalize(&vecDir, &vecDir);//正規化する（大きさ１のベクトルにする必要がある）

	m_light.Direction = vecDir;

	//ライトを設定する
	pDevice->SetLight(0, &m_light);

	//ライトを有効にする
	pDevice->LightEnable(0, TRUE);

	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void CLight::Uninit(void)
{
}

//=============================================================================
//更新処理
//=============================================================================
void CLight::Update(void)
{
}

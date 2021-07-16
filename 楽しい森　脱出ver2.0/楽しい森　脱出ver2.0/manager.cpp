//=============================================================================
//
// マネージャー処理 [manager.cpp]
// Author : 筒井 俊稀
//
//=============================================================================
//=============================================================================
//	インクルードファイル
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "scene3d.h"
#include <Windows.h>
#include "manager.h"
#include "scene.h"
#include "meshfield.h"
#include "camera.h"
#include "light.h"
#include "input.h"

//-----------------------------------------------------------------------------
//		静的メンバ変数の初期化
//-----------------------------------------------------------------------------
CRenderer*CManager::m_pRenderer = NULL;
CGame*CManager::m_pGame = NULL;
CManager::MODE CManager::m_mode = CManager::MODE_NONE;
CScene * CManager::m_pScene = NULL;
CInputKeyBoard * CManager::m_pInput = NULL;
CMeshfield * CManager::m_pMeshfield = NULL;
CCamera * CManager::m_pCamera = NULL;
CLight * CManager::m_pLight = NULL;

//-----------------------------------------------------------------------------
//		コンストラクタ
//-----------------------------------------------------------------------------
CManager::CManager()
{
}

//-----------------------------------------------------------------------------
//		デストラクタ
//-----------------------------------------------------------------------------
CManager::~CManager()
{
}

//-----------------------------------------------------------------------------
//		初期化処理
//-----------------------------------------------------------------------------
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	//レンダリングクラスを生成
	m_pRenderer = new CRenderer;
	// 初期化処理
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Init(hWnd, bWindow);
	}
	//インプットクラスを生成
	m_pInput = new CInputKeyBoard;
	// 初期化処理
	if (m_pInput != NULL)
	{
		m_pInput->Init(hInstance, hWnd);
	}

	m_pCamera = CCamera::Create();
	m_pLight = CLight::Create();
	
	CScene2d::Create(D3DXVECTOR3(400.0f, 500.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f));
	
	CScene3d::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 100.0f));
	//各テクスチャロード処理

	return S_OK;
}

//-----------------------------------------------------------------------------
//		終了処理
//-----------------------------------------------------------------------------
void CManager::Uninit(void)
{
	//各テクスチャ破棄処理

	CScene::ReleaseAll();

	if (m_pRenderer != NULL)
	{
		// 終了処理
		m_pRenderer->Uninit();
		//メモリを解放
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
	if (m_pInput != NULL)
	{
		// 終了処理
		m_pInput->Uninit();
		//メモリを解放
		delete m_pInput;
		m_pInput = NULL;
	}
	if (m_pCamera != NULL)
	{
		// 終了処理
		m_pCamera->Uninit();
		//メモリを解放
		delete m_pCamera;
		m_pCamera = NULL;
	}
	if (m_pLight != NULL)
	{
		// 終了処理
		m_pLight->Uninit();
		//メモリを解放
		delete m_pLight;
		m_pLight = NULL;
	}
}

//-----------------------------------------------------------------------------
//		更新処理
//-----------------------------------------------------------------------------
void CManager::Updata(void)
{
	if (m_pRenderer != NULL)
	{
		// 更新処理
		m_pRenderer->Update();
	}

	if (m_pCamera != NULL)
	{
		// 更新処理
		m_pCamera->Update();
	}
	if (m_pInput != NULL)
	{
		// 終了処理
		m_pInput->Update();
	}

	//更新モード
	switch (m_mode)
	{
		//タイトルの時
	case MODE_TITLE:
		break;
		//チュートリアルの時
	case MODE_TUTORIAL:
		break;
		//ゲームの時
	case MODE_GAME:
		break;
		//ゲームオーバーの時
	case MODE_GAMEOVER:
		break;
		//リザルトの時
	case MODE_RESULT:
		break;
	}
}

//-----------------------------------------------------------------------------
//		描画処理
//-----------------------------------------------------------------------------
void CManager::Draw(void)
{
	if (m_pRenderer != NULL)
	{
		// 描画処理
		m_pRenderer->Draw();
	}
	if (m_pCamera != NULL)
	{
		// 描画処理
		m_pCamera->Draw();
	}
	//描画モード
	switch (m_mode)
	{
	case MODE_TITLE:
		break;
	case MODE_TUTORIAL:
		break;
	case MODE_GAME:
		break;
	case MODE_RESULT:
		break;
	}

}

//-----------------------------------------------------------------------------
//		モードを設定
//-----------------------------------------------------------------------------
void CManager::SetMode(MODE mode)
{
	//初期化と終了のモード分け
	switch (m_mode)
	{
		//タイトルの時
	case MODE_TITLE:

		break;
		//チュートリアルの時
	case MODE_TUTORIAL:

		break;
		//ゲームの時
	case MODE_GAME:

		break;
		//ゲームオーバーの時
	case MODE_GAMEOVER:

		break;
		//リザルトの時
	case MODE_RESULT:

		break;
	}
	//mode変数に現在のモードを入れる
	m_mode = mode;

	switch (mode)
	{
		//タイトルの時
	case MODE_TITLE:

		break;
		//チュートリアルの時
	case MODE_TUTORIAL:

		break;
		//ゲームの時
	case MODE_GAME:

		break;
		//ゲームの時
	case MODE_GAMEOVER:

		break;
		//リザルトの時
	case MODE_RESULT:

		break;
	}
}
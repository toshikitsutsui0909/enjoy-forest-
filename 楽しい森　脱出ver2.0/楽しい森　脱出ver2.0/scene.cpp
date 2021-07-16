//=============================================================================
//
// オブジェクト処理 [scene.cpp]
// Author : 
//
//=============================================================================
#include "scene.h"
#include "main.h"

//=============================================================================
//	静的メンバ変数の初期化
//=============================================================================
bool CScene::m_bPause = true;
CScene *CScene::m_pTop[PRIORITY] = {};
CScene *CScene::m_pCur[PRIORITY] = {};

//=============================================================================
//	コンストラクタ
//=============================================================================
CScene::CScene(int nPriority)
{
	// priorityを代入
	m_nPriority = nPriority;
	// 削除フラグの初期化
	m_bDeathFlag = false;

	// 先頭のポインタが存在しなかった場合
	if (m_pTop[m_nPriority] == NULL)
	{
		// 自身を先頭にする
		m_pTop[m_nPriority] = this;
		// 先頭なので後ろはなし
		m_pPrev = NULL;
	}

	// 最後尾のポインタが存在しなかった場合
	if (m_pCur[m_nPriority] == NULL)
	{
		// 自身を最後尾にする
		m_pCur[m_nPriority] = this;
		// 最後尾なので次のポインタはなし
		m_pNext = NULL;
	}
	// わざと最後尾のポインタに自身を入れる
	m_pCur[m_nPriority]->m_pNext = this;

	// 最後尾のポインタが自身の場合
	if (m_pCur[m_nPriority] == this)
	{
		// 後ろのポインタをNULLにする
		m_pPrev = NULL;
	}
	else
	{
		// それ以外の場合は前のポインタに最後尾のポインタを入れる
		m_pPrev = m_pCur[m_nPriority];
	}

	// 最後に最後尾のポインタに自身を入れる
	m_pCur[m_nPriority] = this;

	//自身の次情報をクリアする
	m_pNext = NULL;

	// オブジェクトの設定
	m_objType = OBJTYPE_NONE;
}

//=============================================================================
//	デストラクタ
//=============================================================================
CScene::~CScene()
{

}

//=============================================================================
//	オブジェクトの種類の設定
//=============================================================================
void CScene::SetObjType(OBJTYPE objtype)
{
	m_objType = objtype;
}

//=============================================================================
//	オブジェクトの種類の取得
//=============================================================================
CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_objType;
}

//=============================================================================
//	全体の更新処理
//=============================================================================
void CScene::UpdateAll(void)
{
	// priority分回す
	for (int nCntPriority = 0; nCntPriority < PRIORITY; nCntPriority++)
	{
		CScene *pScene = m_pTop[nCntPriority];

		// pSceneポインタがNULLになるまで回す
		while (pScene != NULL)
		{
			//次情報の一時保存
			CScene *pNext = pScene->m_pNext;

			if (pScene->m_bDeathFlag == false)
			{
				// アップデート処理
				pScene->Update();
			}
			// 先頭に次のポインタを入れる
			pScene = pScene->m_pNext;
		}
	}

	// priority分回す
	for (int nCntPriority = 0; nCntPriority < PRIORITY; nCntPriority++)
	{
		CScene *pScene = m_pTop[nCntPriority];

		// pSceneポインタがNULLになるまで回す
		while (pScene != NULL)
		{
			//次情報の一時保存
			CScene *pNext = pScene->m_pNext;

			if (pScene->m_bDeathFlag == true)
			{
				// 接続しなおし
				pScene->connect();
			}
			// 先頭に次のポインタを入れる
			pScene = pScene->m_pNext;
		}
	}
}

//=============================================================================
//	全体の描画処理
//=============================================================================
void CScene::DrawAll(void)
{
	// priority分回す
	for (int nCntPriority = 0; nCntPriority < PRIORITY; nCntPriority++)
	{
		CScene *pScene = m_pTop[nCntPriority];

		// pSceneポインタがNULLになるまで回す
		while (pScene != NULL)
		{
			if (pScene->m_bDeathFlag == false)
			{
				// 描画処理
				pScene->Draw();
			}
			// 先頭に次のポインタを入れる
			pScene = pScene->m_pNext;
		}
	}
}

//=============================================================================
//	全体の解放処理
//=============================================================================
void CScene::ReleaseAll(void)
{
	// priority分回す
	for (int nCntPriority = 0; nCntPriority < PRIORITY; nCntPriority++)
	{
		CScene *pScene = m_pTop[nCntPriority];

		// pSceneポインタがNULLになるまで回す
		while (pScene != NULL)
		{
			// 次のポインタの情報を一時的に保存する
			CScene *pNext = pScene->m_pNext;
			//終了処理呼び出し
			pScene->Uninit();
			// 接続しなおし
			pScene->connect();
			// 自身のポインタに次のポインタ入れる
			pScene = pNext;
		}
	}
}

//=============================================================================
//	ポーズ情報の取得
//=============================================================================
void CScene::Pause(bool bPause)
{
	m_bPause = bPause;
}

//=============================================================================
//	再接続
//=============================================================================
void CScene::connect(void)
{
	// 自身のポインタが先頭のポインタだった場合
	if (this == m_pTop[m_nPriority])
	{
		// 先頭のポインタに次のポインタを入れる
		m_pTop[m_nPriority] = m_pNext;
	}
	// 自身のポインタが最後尾のポインタだった場合
	if (this == m_pCur[m_nPriority])
	{
		// 最後尾のポインタに前のポインタを入れる
		m_pCur[m_nPriority] = m_pPrev;
	}
	// 前のポインタがNULLじゃない場合
	if (m_pPrev != NULL)
	{
		// 前のオブジェクトの次情報に自身の次情報のポインタを入れる
		m_pPrev->m_pNext = m_pNext;
	}
	// 次のポインタがNULLじゃなかった場合
	if (m_pNext != NULL)
	{
		// 次のオブジェクトの前情報に自身の前情報のポインタを入れる
		m_pNext->m_pPrev = m_pPrev;
	}

	// メモリ削除
	delete this;
}

//=============================================================================
//	解放処理
//=============================================================================
void CScene::SetDeathFlag(void)
{
	m_bDeathFlag = true;
}
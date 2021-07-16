//------------------------------------------
//
//	マネージャー処理[manager.h]
//	筒井
//
//------------------------------------------

#ifndef _MANAGER_H_
#define _MANAGER_H_

//------------------------------------------
//	インクルードファイル
//------------------------------------------
#include "main.h"

//------------------------------------------
//	前方宣言
//------------------------------------------
class CRenderer;
class CGame;
class CScene;
class CInputKeyBoard;
class CMeshfield;
class CCamera;
class CLight;

//------------------------------------------
//	マネージャークラス
//------------------------------------------
class CManager
{
public:
	//ゲームの移行
	typedef enum
	{
		MODE_NONE = 0,
		MODE_TITLE,
		MODE_GAME,
		MODE_RESULT,
		MODE_TUTORIAL,
		MODE_GAMEOVER,
		MODE_END,
		MODE_MAX
	}MODE;
	//メンバ関数宣言
	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);
	void Uninit(void);
	void Updata(void);
	void Draw(void);
	static void SetMode(MODE mode);
	static MODE GetMode(void) { return m_mode; }
	static CRenderer *GetRenderer(void) { return m_pRenderer; }
	static CGame *GetGame(void) { return m_pGame; }
	static CScene *GetScene(void) { return m_pScene; }
	static CInputKeyBoard *GetInput(void) { return m_pInput; }
	static CMeshfield *GetMeshfield(void) { return m_pMeshfield; }
	static CCamera *GetCamera(void) { return m_pCamera; }
	static CLight *GetLight(void) { return m_pLight; }
private:
	//メンバ変数宣言
	static CRenderer *m_pRenderer;
	static CGame *m_pGame;
	static MODE m_mode;
	static CScene *m_pScene;
	static CInputKeyBoard *m_pInput;
	static CMeshfield *m_pMeshfield;
	static CCamera*m_pCamera;
	static CLight *m_pLight;
};



#endif
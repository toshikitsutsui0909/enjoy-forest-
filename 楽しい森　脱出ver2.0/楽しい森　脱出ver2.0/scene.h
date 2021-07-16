//------------------------------------------
//
//	クラスポリゴン描画[scene.h]
//	筒井
//
//------------------------------------------

#ifndef _SCENE_H_
#define _SCENE_H_

//------------------------------------------
//	インクルードファイル
//------------------------------------------
#include "main.h"

#define PRIORITY 15
//------------------------------------------
//	オブジェクトクラス
//------------------------------------------
class CScene
{
public:
	//各種類の当たり判定の設定
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_MAX
	}OBJTYPE;

	CScene(int nPriority = OBJTYPE_NONE);
	virtual ~CScene();
	void SetObjType(OBJTYPE objtype);
	OBJTYPE GetObjType(void);
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	static CScene *GetTop(int nNum) { return m_pTop[nNum]; }
	CScene *GetNext(void) { return m_pNext; }

	static void UpdateAll(void);
	static void DrawAll(void);
	static void ReleaseAll(void);
	static void Pause(bool bPause);
private:
	void connect(void);

	static CScene *m_pTop[PRIORITY];	//先頭のオブジェクトポインタ
	static CScene *m_pCur[PRIORITY];	//現在のオブジェクトポインタ

	CScene *m_pPrev;					//前のオブジェクトポインタ
	CScene *m_pNext;					//次のオブジェクトポインタ

	bool m_bDeathFlag;//死亡フラグ
	OBJTYPE m_objType;	//オブジェクトの種類
	int m_nPriority;
	static bool m_bPause;

protected:
	void SetDeathFlag(void);
};
//virtualがないと派生クラスのデストラクタが呼び出されないためもし
//派生クラスのデストラクタにdelete処理が入っていたら呼び出されず
//メモリの開放ができないので大変なことになる。


#endif // !_SCENE_H_

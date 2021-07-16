//=============================================================================
//
// カメラ処理 [camera.h]
// Author : 筒井　俊稀
//
//=============================================================================

#ifndef _CAMERA_H_
#define _CAMERA_H_

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// クラス定義
//=============================================================================
class CCamera
{
public:
	CCamera();
	~CCamera();

	static CCamera *Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	D3DXVECTOR3 m_posV;	//！＜カメラの座標
	D3DXVECTOR3 m_posR;	//！＜注視点
	D3DXVECTOR3 m_vecU;	//！＜上方向ベクトル
	D3DXVECTOR3 m_rot;	//！＜向き取得用
	D3DXMATRIX m_mtxProjection;//！＜プロジェクションマトリックス
	D3DXMATRIX m_mtxView;	//！＜ビューマトリックス
	D3DXVECTOR3 m_posVDest;//カメラの座標（目的値）
	D3DXVECTOR3 m_posRDest;//注意点（目的値）
	D3DXVECTOR3 m_rotDest;
	D3DXVECTOR3 m_posVOld;
	float m_fDistance;	//！＜視点ー注視点の距離
	float m_fCamera;
	bool m_use;
};



#endif // !_CAMERA_H_
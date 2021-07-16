//=============================================================================
//
// �J�������� [camera.h]
// Author : ����@�r�H
//
//=============================================================================

#ifndef _CAMERA_H_
#define _CAMERA_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �N���X��`
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
	D3DXVECTOR3 m_posV;	//�I���J�����̍��W
	D3DXVECTOR3 m_posR;	//�I�������_
	D3DXVECTOR3 m_vecU;	//�I��������x�N�g��
	D3DXVECTOR3 m_rot;	//�I�������擾�p
	D3DXMATRIX m_mtxProjection;//�I���v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;	//�I���r���[�}�g���b�N�X
	D3DXVECTOR3 m_posVDest;//�J�����̍��W�i�ړI�l�j
	D3DXVECTOR3 m_posRDest;//���ӓ_�i�ړI�l�j
	D3DXVECTOR3 m_rotDest;
	D3DXVECTOR3 m_posVOld;
	float m_fDistance;	//�I�����_�[�����_�̋���
	float m_fCamera;
	bool m_use;
};



#endif // !_CAMERA_H_
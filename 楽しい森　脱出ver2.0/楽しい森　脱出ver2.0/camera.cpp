//=============================================================================
//
// camera���� [camera.cpp]
// Author : �g�V�L
//
//=============================================================================
#include "camera.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CCamera::CCamera()
{
	m_fCamera = 0.9f;

	m_posV = D3DXVECTOR3(0.0f, 100.0f, -100.0f);
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CCamera::~CCamera()
{
}

//=============================================================================
//��������
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
//����������
//=============================================================================
HRESULT CCamera::Init(void)
{
	//m_fDistance = m_posR.z - m_posV.z;
	m_fDistance = -50.0f;
	m_posV = D3DXVECTOR3(0.0f, 300.0f, -m_fDistance);	//�ʒuz��m_fDistance��-�����֐ݒ肷��
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�����_�͑S��0���W������
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	return S_OK;
}

//=============================================================================
//�I������
//=============================================================================
void CCamera::Uninit(void)
{
}

//=============================================================================
//�X�V����
//=============================================================================
void CCamera::Update(void)
{
	CInputKeyBoard *pInput
		= CManager::GetInput();
	m_posVOld = m_posV;

	//�O
	if (pInput->GetKeyPress(DIK_W))
	{
		m_posV.z += 5.0f;
		m_posR.z += 5.0f;
	}

	//��
	if (pInput->GetKeyPress(DIK_S))
	{
		m_posV.z -= 5.0f;
		m_posR.z -= 5.0f;
	}

	//�E
	if (pInput->GetKeyPress(DIK_D))
	{
		m_posV.x += 5.0f;
		m_posR.x += 5.0f;
	}
	//��
	if (pInput->GetKeyPress(DIK_A))
	{
		m_posV.x -= 5.0f;
		m_posR.x -= 5.0f;
	}
}

void CCamera::Draw(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		10000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION,
		&m_mtxProjection);
}

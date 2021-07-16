//=============================================================================
//
// �}�l�[�W���[���� [manager.cpp]
// Author : ���� �r�H
//
//=============================================================================
//=============================================================================
//	�C���N���[�h�t�@�C��
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
//		�ÓI�����o�ϐ��̏�����
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
//		�R���X�g���N�^
//-----------------------------------------------------------------------------
CManager::CManager()
{
}

//-----------------------------------------------------------------------------
//		�f�X�g���N�^
//-----------------------------------------------------------------------------
CManager::~CManager()
{
}

//-----------------------------------------------------------------------------
//		����������
//-----------------------------------------------------------------------------
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	//�����_�����O�N���X�𐶐�
	m_pRenderer = new CRenderer;
	// ����������
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Init(hWnd, bWindow);
	}
	//�C���v�b�g�N���X�𐶐�
	m_pInput = new CInputKeyBoard;
	// ����������
	if (m_pInput != NULL)
	{
		m_pInput->Init(hInstance, hWnd);
	}

	m_pCamera = CCamera::Create();
	m_pLight = CLight::Create();
	
	CScene2d::Create(D3DXVECTOR3(400.0f, 500.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f));
	
	CScene3d::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 100.0f));
	//�e�e�N�X�`�����[�h����

	return S_OK;
}

//-----------------------------------------------------------------------------
//		�I������
//-----------------------------------------------------------------------------
void CManager::Uninit(void)
{
	//�e�e�N�X�`���j������

	CScene::ReleaseAll();

	if (m_pRenderer != NULL)
	{
		// �I������
		m_pRenderer->Uninit();
		//�����������
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
	if (m_pInput != NULL)
	{
		// �I������
		m_pInput->Uninit();
		//�����������
		delete m_pInput;
		m_pInput = NULL;
	}
	if (m_pCamera != NULL)
	{
		// �I������
		m_pCamera->Uninit();
		//�����������
		delete m_pCamera;
		m_pCamera = NULL;
	}
	if (m_pLight != NULL)
	{
		// �I������
		m_pLight->Uninit();
		//�����������
		delete m_pLight;
		m_pLight = NULL;
	}
}

//-----------------------------------------------------------------------------
//		�X�V����
//-----------------------------------------------------------------------------
void CManager::Updata(void)
{
	if (m_pRenderer != NULL)
	{
		// �X�V����
		m_pRenderer->Update();
	}

	if (m_pCamera != NULL)
	{
		// �X�V����
		m_pCamera->Update();
	}
	if (m_pInput != NULL)
	{
		// �I������
		m_pInput->Update();
	}

	//�X�V���[�h
	switch (m_mode)
	{
		//�^�C�g���̎�
	case MODE_TITLE:
		break;
		//�`���[�g���A���̎�
	case MODE_TUTORIAL:
		break;
		//�Q�[���̎�
	case MODE_GAME:
		break;
		//�Q�[���I�[�o�[�̎�
	case MODE_GAMEOVER:
		break;
		//���U���g�̎�
	case MODE_RESULT:
		break;
	}
}

//-----------------------------------------------------------------------------
//		�`�揈��
//-----------------------------------------------------------------------------
void CManager::Draw(void)
{
	if (m_pRenderer != NULL)
	{
		// �`�揈��
		m_pRenderer->Draw();
	}
	if (m_pCamera != NULL)
	{
		// �`�揈��
		m_pCamera->Draw();
	}
	//�`�惂�[�h
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
//		���[�h��ݒ�
//-----------------------------------------------------------------------------
void CManager::SetMode(MODE mode)
{
	//�������ƏI���̃��[�h����
	switch (m_mode)
	{
		//�^�C�g���̎�
	case MODE_TITLE:

		break;
		//�`���[�g���A���̎�
	case MODE_TUTORIAL:

		break;
		//�Q�[���̎�
	case MODE_GAME:

		break;
		//�Q�[���I�[�o�[�̎�
	case MODE_GAMEOVER:

		break;
		//���U���g�̎�
	case MODE_RESULT:

		break;
	}
	//mode�ϐ��Ɍ��݂̃��[�h������
	m_mode = mode;

	switch (mode)
	{
		//�^�C�g���̎�
	case MODE_TITLE:

		break;
		//�`���[�g���A���̎�
	case MODE_TUTORIAL:

		break;
		//�Q�[���̎�
	case MODE_GAME:

		break;
		//�Q�[���̎�
	case MODE_GAMEOVER:

		break;
		//���U���g�̎�
	case MODE_RESULT:

		break;
	}
}
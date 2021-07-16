//=============================================================================
//
// �I�u�W�F�N�g���� [scene.cpp]
// Author : 
//
//=============================================================================
#include "scene.h"
#include "main.h"

//=============================================================================
//	�ÓI�����o�ϐ��̏�����
//=============================================================================
bool CScene::m_bPause = true;
CScene *CScene::m_pTop[PRIORITY] = {};
CScene *CScene::m_pCur[PRIORITY] = {};

//=============================================================================
//	�R���X�g���N�^
//=============================================================================
CScene::CScene(int nPriority)
{
	// priority����
	m_nPriority = nPriority;
	// �폜�t���O�̏�����
	m_bDeathFlag = false;

	// �擪�̃|�C���^�����݂��Ȃ������ꍇ
	if (m_pTop[m_nPriority] == NULL)
	{
		// ���g��擪�ɂ���
		m_pTop[m_nPriority] = this;
		// �擪�Ȃ̂Ō��͂Ȃ�
		m_pPrev = NULL;
	}

	// �Ō���̃|�C���^�����݂��Ȃ������ꍇ
	if (m_pCur[m_nPriority] == NULL)
	{
		// ���g���Ō���ɂ���
		m_pCur[m_nPriority] = this;
		// �Ō���Ȃ̂Ŏ��̃|�C���^�͂Ȃ�
		m_pNext = NULL;
	}
	// �킴�ƍŌ���̃|�C���^�Ɏ��g������
	m_pCur[m_nPriority]->m_pNext = this;

	// �Ō���̃|�C���^�����g�̏ꍇ
	if (m_pCur[m_nPriority] == this)
	{
		// ���̃|�C���^��NULL�ɂ���
		m_pPrev = NULL;
	}
	else
	{
		// ����ȊO�̏ꍇ�͑O�̃|�C���^�ɍŌ���̃|�C���^������
		m_pPrev = m_pCur[m_nPriority];
	}

	// �Ō�ɍŌ���̃|�C���^�Ɏ��g������
	m_pCur[m_nPriority] = this;

	//���g�̎������N���A����
	m_pNext = NULL;

	// �I�u�W�F�N�g�̐ݒ�
	m_objType = OBJTYPE_NONE;
}

//=============================================================================
//	�f�X�g���N�^
//=============================================================================
CScene::~CScene()
{

}

//=============================================================================
//	�I�u�W�F�N�g�̎�ނ̐ݒ�
//=============================================================================
void CScene::SetObjType(OBJTYPE objtype)
{
	m_objType = objtype;
}

//=============================================================================
//	�I�u�W�F�N�g�̎�ނ̎擾
//=============================================================================
CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_objType;
}

//=============================================================================
//	�S�̂̍X�V����
//=============================================================================
void CScene::UpdateAll(void)
{
	// priority����
	for (int nCntPriority = 0; nCntPriority < PRIORITY; nCntPriority++)
	{
		CScene *pScene = m_pTop[nCntPriority];

		// pScene�|�C���^��NULL�ɂȂ�܂ŉ�
		while (pScene != NULL)
		{
			//�����̈ꎞ�ۑ�
			CScene *pNext = pScene->m_pNext;

			if (pScene->m_bDeathFlag == false)
			{
				// �A�b�v�f�[�g����
				pScene->Update();
			}
			// �擪�Ɏ��̃|�C���^������
			pScene = pScene->m_pNext;
		}
	}

	// priority����
	for (int nCntPriority = 0; nCntPriority < PRIORITY; nCntPriority++)
	{
		CScene *pScene = m_pTop[nCntPriority];

		// pScene�|�C���^��NULL�ɂȂ�܂ŉ�
		while (pScene != NULL)
		{
			//�����̈ꎞ�ۑ�
			CScene *pNext = pScene->m_pNext;

			if (pScene->m_bDeathFlag == true)
			{
				// �ڑ����Ȃ���
				pScene->connect();
			}
			// �擪�Ɏ��̃|�C���^������
			pScene = pScene->m_pNext;
		}
	}
}

//=============================================================================
//	�S�̂̕`�揈��
//=============================================================================
void CScene::DrawAll(void)
{
	// priority����
	for (int nCntPriority = 0; nCntPriority < PRIORITY; nCntPriority++)
	{
		CScene *pScene = m_pTop[nCntPriority];

		// pScene�|�C���^��NULL�ɂȂ�܂ŉ�
		while (pScene != NULL)
		{
			if (pScene->m_bDeathFlag == false)
			{
				// �`�揈��
				pScene->Draw();
			}
			// �擪�Ɏ��̃|�C���^������
			pScene = pScene->m_pNext;
		}
	}
}

//=============================================================================
//	�S�̂̉������
//=============================================================================
void CScene::ReleaseAll(void)
{
	// priority����
	for (int nCntPriority = 0; nCntPriority < PRIORITY; nCntPriority++)
	{
		CScene *pScene = m_pTop[nCntPriority];

		// pScene�|�C���^��NULL�ɂȂ�܂ŉ�
		while (pScene != NULL)
		{
			// ���̃|�C���^�̏����ꎞ�I�ɕۑ�����
			CScene *pNext = pScene->m_pNext;
			//�I�������Ăяo��
			pScene->Uninit();
			// �ڑ����Ȃ���
			pScene->connect();
			// ���g�̃|�C���^�Ɏ��̃|�C���^�����
			pScene = pNext;
		}
	}
}

//=============================================================================
//	�|�[�Y���̎擾
//=============================================================================
void CScene::Pause(bool bPause)
{
	m_bPause = bPause;
}

//=============================================================================
//	�Đڑ�
//=============================================================================
void CScene::connect(void)
{
	// ���g�̃|�C���^���擪�̃|�C���^�������ꍇ
	if (this == m_pTop[m_nPriority])
	{
		// �擪�̃|�C���^�Ɏ��̃|�C���^������
		m_pTop[m_nPriority] = m_pNext;
	}
	// ���g�̃|�C���^���Ō���̃|�C���^�������ꍇ
	if (this == m_pCur[m_nPriority])
	{
		// �Ō���̃|�C���^�ɑO�̃|�C���^������
		m_pCur[m_nPriority] = m_pPrev;
	}
	// �O�̃|�C���^��NULL����Ȃ��ꍇ
	if (m_pPrev != NULL)
	{
		// �O�̃I�u�W�F�N�g�̎����Ɏ��g�̎����̃|�C���^������
		m_pPrev->m_pNext = m_pNext;
	}
	// ���̃|�C���^��NULL����Ȃ������ꍇ
	if (m_pNext != NULL)
	{
		// ���̃I�u�W�F�N�g�̑O���Ɏ��g�̑O���̃|�C���^������
		m_pNext->m_pPrev = m_pPrev;
	}

	// �������폜
	delete this;
}

//=============================================================================
//	�������
//=============================================================================
void CScene::SetDeathFlag(void)
{
	m_bDeathFlag = true;
}
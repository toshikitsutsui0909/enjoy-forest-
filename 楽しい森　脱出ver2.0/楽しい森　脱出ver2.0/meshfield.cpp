//=============================================================================
//
// ���b�V���t�B�[���h���� [meshfield.cpp]
// Author : ���� �r�H
//
//=============================================================================
//=============================================================================
//	�C���N���[�h�t�@�C��
//=============================================================================
#include "meshfield.h"
#include "manager.h"
#include "renderer.h"

#define MESHFIELD_X_BLOCK 50//X�����̃u���b�N��
#define MESHFIELD_Z_BLOCK 50//Y�����̃u���b�N��
#define MESH_LENGTH 20	//��Ђ̒���
#define MESHFIELD_VERTEX_NUM ((MESHFIELD_X_BLOCK+1)*(MESHFIELD_Z_BLOCK+1))	//���_��
#define MESHFIELD_INDEX_NUM (((MESHFIELD_X_BLOCK+1)*2)*MESHFIELD_Z_BLOCK+(MESHFIELD_Z_BLOCK-1)*2)	//�C���f�b�N�X��
#define MESHFIELD_PRIMITIVE_NUM	((MESHFIELD_X_BLOCK*2)*MESHFIELD_Z_BLOCK+(MESHFIELD_Z_BLOCK-1)*4)	//�|���S����

//=============================================================================
//	�ÓI�����o�ϐ��錾������
//=============================================================================
LPDIRECT3DTEXTURE9 CMeshfield::m_pTexture = NULL;

//=============================================================================
//	�R���X�g���N�^
//=============================================================================
CMeshfield::CMeshfield()
{
	m_pVtxBuff = NULL;
	m_pIdxBuff = NULL;
	m_pos = D3DXVECTOR3();
	m_rot = D3DXVECTOR3();
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_mtxWorld;
}

//=============================================================================
//	�f�X�g���N�^
//=============================================================================
CMeshfield::~CMeshfield()
{
}

//=============================================================================
//	�e�N�X�`�����[�h����
//=============================================================================
HRESULT CMeshfield::Load(void)
{
	return S_OK;
}

//=============================================================================
//	�e�N�X�`���j��
//=============================================================================
void CMeshfield::Unload(void)
{
}

//=============================================================================
//	��������
//=============================================================================
CMeshfield * CMeshfield::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	CMeshfield *pMeshfield = new CMeshfield;

	if (pMeshfield != NULL)
	{
		pMeshfield->m_pos = pos;
		pMeshfield->m_rot = rot;
		pMeshfield->Init();
	}

	return pMeshfield;
}

//=============================================================================
//	����������
//=============================================================================
HRESULT CMeshfield::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	int nCntX;
	int nCntZ;
	int nCount = 0;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * MESHFIELD_VERTEX_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);
	//�C���f�b�N�X�o�b�t�@�i�|���S���o�b�t�@�j�̐���
	pDevice->CreateIndexBuffer(
		sizeof(WORD) * (MESHFIELD_INDEX_NUM),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	VERTEX_3D*pVtx = NULL;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�ݒ�
	for (nCntZ = 0; nCntZ < (MESHFIELD_Z_BLOCK + 1); nCntZ++)
	{
		for (nCntX = 0; nCntX < (MESHFIELD_X_BLOCK + 1); nCntX++)
		{
			pVtx[nCount].pos = D3DXVECTOR3(
				(float)nCntX * MESH_LENGTH - (MESHFIELD_X_BLOCK * (MESH_LENGTH / 2)),
				0.5f,
				(float)nCntZ*-MESH_LENGTH + (MESHFIELD_Z_BLOCK * (MESH_LENGTH / 2)));

			nCount += 1;
		}
	}

	//���_�̖@���E�J���[�ݒ�
	for (int nCnt = 0; nCnt < MESHFIELD_VERTEX_NUM; nCnt++)
	{
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[nCnt].col = m_col;

	}


	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();


	WORD*pIdx;

	//�C���f�b�N�X�o�b�t�@�����b�N
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//�C���f�b�N�X���W�̐ݒ�
	nCount = 0;

	for (int nIdZ = 0; nIdZ < MESHFIELD_Z_BLOCK; nIdZ++)
	{
		if (nIdZ != 0)
		{
			pIdx[nCount] = (MESHFIELD_X_BLOCK + 1 + (nIdZ*(MESHFIELD_X_BLOCK + 1)));
			nCount += 1;
		}
		for (int nIdxX = 0; nIdxX < (MESHFIELD_X_BLOCK + 1); nIdxX++)
		{

			pIdx[nCount] = (MESHFIELD_X_BLOCK + 1 + nIdxX + (nIdZ*(MESHFIELD_X_BLOCK + 1)));
			nCount += 1;

			pIdx[nCount] = (pIdx[nCount - 1] - (MESHFIELD_X_BLOCK + 1));
			nCount += 1;
		}
		if (nIdZ != (MESHFIELD_Z_BLOCK - 1))
		{
			pIdx[nCount] = pIdx[nCount - 1];
			nCount += 1;
		}
	}

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_pIdxBuff->Unlock();
	return S_OK;
}

//=============================================================================
//	�I������
//=============================================================================
void CMeshfield::Uninit(void)
{
	//�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	// �C���f�b�N�X�̊J��
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	SetDeathFlag();
}

//=============================================================================
//	�X�V����
//=============================================================================
void CMeshfield::Update(void)
{

}

//=============================================================================
//	�`�揈��
//=============================================================================
void CMeshfield::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans, mtxScail;//�s��v�Z�p�}�g���N�X

										  // �}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixIdentity(&mtxRot);
	D3DXMatrixIdentity(&mtxTrans);
	D3DXMatrixIdentity(&mtxScail);

	// �T�C�Y
	D3DXMatrixScaling(&mtxScail, 1.0f, 1.0f, 1.0f);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScail);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	pDevice->SetTexture(0, NULL);
}

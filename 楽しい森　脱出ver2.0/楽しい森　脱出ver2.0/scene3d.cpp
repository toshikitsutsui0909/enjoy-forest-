//=============================================================================
//
// scene2d���� [scene2d.cpp]
// Author : ���� �r�H
//
//=============================================================================
#include "scene3d.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
//	�}�N����`
//=============================================================================

//=============================================================================
//	�R���X�g���N�^
//=============================================================================
CScene3d::CScene3d(int nPriority)
{
	//������
	m_pVtxBuff = NULL;
	m_pTexture = NULL;
	m_pos = D3DXVECTOR3();
	m_size = D3DXVECTOR3();
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
//	�f�X�g���N�^
//=============================================================================
CScene3d::~CScene3d()
{
}

//=============================================================================
//	��������
//=============================================================================
CScene3d * CScene3d::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	CScene3d *pScene3d = new CScene3d;

	if (pScene3d != NULL)
	{
		pScene3d->SetPos(pos);
		pScene3d->SetSize(size);
		pScene3d->Init();
	}
	return pScene3d;
}

//=============================================================================
//	����������
//=============================================================================
HRESULT CScene3d::Init(void)
{
	VERTEX_3D *pVtx;

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	// �����o�ϐ��̏�����
	m_col = { 0.0f,1.0f,1.0f,1.0f };

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3((m_pos.x - (m_size.x / 2)), (m_pos.y + (m_size.y / 2)), (m_pos.z + (m_size.z / 2)));
	pVtx[1].pos = D3DXVECTOR3((m_pos.x + (m_size.x / 2)), (m_pos.y + (m_size.y / 2)), (m_pos.z + (m_size.z / 2)));
	pVtx[2].pos = D3DXVECTOR3((m_pos.x - (m_size.x / 2)), (m_pos.y - (m_size.y / 2)), (m_pos.z - (m_size.z / 2)));
	pVtx[3].pos = D3DXVECTOR3((m_pos.x + (m_size.x / 2)), (m_pos.y - (m_size.y / 2)), (m_pos.z - (m_size.z / 2)));

	//�e���_�̖@���̐ݒ�i���x�N�g���̑傫���͂P�ɂ���K�v������j
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// �F�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//�e���_�̖@���̐ݒ�i���x�N�g���̑傫���͂P�ɂ���K�v������j
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	// �A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
//	�I������
//=============================================================================
void CScene3d::Uninit(void)
{
	//�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	SetDeathFlag();
}

//=============================================================================
//	�X�V����
//=============================================================================
void CScene3d::Update(void)
{
	Vertex();
}

//=============================================================================
//	�`�揈��
//=============================================================================
void CScene3d::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans, mtxScail;//�s��v�Z�p�}�g���N�X

										  // �}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixIdentity(&mtxRot);
	D3DXMatrixIdentity(&mtxTrans);
	D3DXMatrixIdentity(&mtxScail);

	// �T�C�Y
	//D3DXMatrixScaling(&mtxScail, 1.0f, 1.0f, 1.0f);
	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScail);

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
	pDevice->SetTexture(0, 0);
}

//=============================================================================
//	POS���W�̐ݒ�
//=============================================================================
void CScene3d::SetPos(const D3DXVECTOR3 pos)
{
	//pos�̑��
	m_pos = pos;
}

//=============================================================================
//	SIZE���̐ݒ�
//=============================================================================
void CScene3d::SetSize(const D3DXVECTOR3 size)
{
	m_size = size;
	// ���_���W�̍Đݒ�
	SetPos(m_pos);
}

//=============================================================================
//	color���̐ݒ�
//=============================================================================
void CScene3d::SetColor(const D3DXCOLOR col)
{
	m_col = col;
}

//=============================================================================
//	rot�̐ݒ�
//=============================================================================
void CScene3d::SetRot(const D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
//	�e�N�X�`���𕪂��鏈��
//=============================================================================
void CScene3d::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//=============================================================================
//	�Z�b�g�X�V����
//=============================================================================
void CScene3d::Vertex(void)
{
	VERTEX_3D *pVtx; //���_���ւ̃|�C���^

					 //���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3((m_pos.x - (m_size.x / 2)), (m_pos.y + (m_size.y / 2)), (m_pos.z + (m_size.z / 2)));
	pVtx[1].pos = D3DXVECTOR3((m_pos.x + (m_size.x / 2)), (m_pos.y + (m_size.y / 2)), (m_pos.z + (m_size.z / 2)));
	pVtx[2].pos = D3DXVECTOR3((m_pos.x - (m_size.x / 2)), (m_pos.y - (m_size.y / 2)), (m_pos.z - (m_size.z / 2)));
	pVtx[3].pos = D3DXVECTOR3((m_pos.x + (m_size.x / 2)), (m_pos.y - (m_size.y / 2)), (m_pos.z - (m_size.z / 2)));

	//���_�J���[�̐ݒ�(0�`255�͈̔͂Őݒ�)
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();
}

//------------------------------------------
//
//	�N���X�|���S���`��[scene3d.h]
//	Author : ����@�r�H
//
//------------------------------------------

#ifndef _SCENE3D_H_
#define _SCENE3D_H_

//------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------
#include"main.h"
#include"scene.h"

//------------------------------------------
//	scene2d�N���X
//------------------------------------------
class CScene3d : public CScene
{
public:

	CScene3d(int nPriority = OBJTYPE_NONE);
	~CScene3d();

	static CScene3d *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPos(const D3DXVECTOR3 pos);		// pos���W�̐ݒ�
	void SetSize(const D3DXVECTOR3 size);	// size���̐ݒ�
	void SetColor(const D3DXCOLOR col);		// color���̐ݒ�
	void SetRot(const D3DXVECTOR3 rot);		// rot���̐ݒ�

	D3DXVECTOR3 GetSize(void) { return m_size; }	// size���̎擾
	D3DXVECTOR3 GetPos(void) { return m_pos; }		// pos���W�̎擾
	D3DXVECTOR3 GetRot(void) { return m_rot; }		// rot���̎擾

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);	//Bind�@���蓖�Ă�
private:
	void Vertex(void);

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; //���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9		m_pTexture; //�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3				m_pos;		//���W�ϐ�
	D3DXVECTOR3				m_size;		//�T�C�Y�ϐ�
	D3DXVECTOR3				m_rot;		//rot�ϐ�
	D3DXCOLOR				m_col;		//�J���[�ϐ�
	D3DXMATRIX				m_mtxWorld;
};


#endif //_SCENE3D_H_
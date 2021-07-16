//=============================================================================
//
// UI���� [ui.h]
// Author : ����@�r�H
//
//=============================================================================

#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

//=============================================================================
// �C���N���[�h��`
//=============================================================================
#include "main.h"
#include "scene3d.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CMeshfield : public CScene
{
public:
	CMeshfield();
	~CMeshfield();

	static HRESULT Load(void);
	static void Unload(void);
	static CMeshfield *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;			//���b�V���t�B�[���h�̈ʒu
	D3DXVECTOR3 m_rot;			//���b�V���t�B�[���h�̌���
	D3DXCOLOR m_col;
	D3DXMATRIX m_mtxWorld;		//���b�V���t�B�[���h�̃��[���h�}�g���b�N�X

};

#endif // !__MESHFIELD_H_

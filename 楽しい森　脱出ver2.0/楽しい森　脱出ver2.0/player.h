//=============================================================================
//
// �v���C���[����[player.h]
// Author : ���� �r�H
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene3d.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CPlayer : public CScene3d
{
public:
	CPlayer();
	~CPlayer();

	static CPlayer *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);
	static HRESULT Load(void);
	static void Unload(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture; //�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3				m_pos;		//���W�ϐ�
	D3DXVECTOR3				m_size;		//�T�C�Y�ϐ�
	D3DXVECTOR3				m_rot;		//rot�ϐ�
	D3DXCOLOR				m_col;		//�J���[�ϐ�
};












#endif //! _PLAYER_H_
//------------------------------------------
//
//	�N���X�|���S���`��[scene2d.h]
//	����
//
//------------------------------------------

#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------
#include"main.h"
#include"scene.h"

//------------------------------------------
//	scene2d�N���X
//------------------------------------------
class CScene2d : public CScene
{
public:
	// �t���b�V���ݒ�
	typedef enum
	{
		FLASH_STATE_NONE = 0,
		FLASH_STATE_IN,
		FLASH_STATE_OUT,
		FLASH_STATE_MAX
	}FLASH_STATE;

	CScene2d(int nPriority = OBJTYPE_NONE);
	~CScene2d();

	static CScene2d *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPos(D3DXVECTOR3 pos);	// pos���W�̐ݒ�
	void SetSize(D3DXVECTOR3 size);	// size���̐ݒ�
	void SetColor(D3DXCOLOR col);	// color���̐ݒ�

	D3DXVECTOR3 GetSize(void) { return m_size; }	// size���̎擾
	D3DXVECTOR3 GetPos(void) { return m_pos; }		// pos���W�̎擾

	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);	//Bind�@���蓖�Ă�
	void Flashing(void);							//�t���b�V�������֐�
private:
	void Vertex(void);

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; //���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9		m_pTexture; //�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3				m_pos;		//���W�ϐ�
	D3DXVECTOR3				m_size;		//�T�C�Y�ϐ�
	D3DXVECTOR2				m_Texture;	//�e�N�X�`���ϐ�
	D3DXCOLOR				m_col;		//�J���[�ϐ�
	bool					m_bFlash;	//�t���b�V�����邩���Ȃ����̔���
	FLASH_STATE				m_FlashState;
};


#endif //_SCENE2D_H_
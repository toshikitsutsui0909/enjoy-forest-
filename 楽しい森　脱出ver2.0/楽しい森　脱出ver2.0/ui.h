//=============================================================================
//
// UI���� [ui.h]
// Author : ����@�r�H
//
//=============================================================================

#ifndef _UI_H_
#define _UI_H_

#include "main.h"
#include "scene.h"

class CUi : public CScene
{
public:
	typedef enum
	{
		UI_NONE = 0,
		UI_MAX
	}UI;

	CUi();
	~CUi();

	static CUi *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);
	HRESULT Load(void);
	void Unload(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPos(const D3DXVECTOR3 pos);		// pos���W�̐ݒ�
	D3DXVECTOR3 GetPos(void) { return m_pos; }		// pos���W�̎擾
	void SetSize(const D3DXVECTOR3 size);	// size���̐ݒ�
	D3DXVECTOR3 GetSize(void) { return m_size; }	// size���̎擾

private:
	void Vertex(void);

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; //���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9		m_apTexture[UI_MAX]; //�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_size;

};




#endif
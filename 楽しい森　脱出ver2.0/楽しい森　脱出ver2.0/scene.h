//------------------------------------------
//
//	�N���X�|���S���`��[scene.h]
//	����
//
//------------------------------------------

#ifndef _SCENE_H_
#define _SCENE_H_

//------------------------------------------
//	�C���N���[�h�t�@�C��
//------------------------------------------
#include "main.h"

#define PRIORITY 15
//------------------------------------------
//	�I�u�W�F�N�g�N���X
//------------------------------------------
class CScene
{
public:
	//�e��ނ̓����蔻��̐ݒ�
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_MAX
	}OBJTYPE;

	CScene(int nPriority = OBJTYPE_NONE);
	virtual ~CScene();
	void SetObjType(OBJTYPE objtype);
	OBJTYPE GetObjType(void);
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	static CScene *GetTop(int nNum) { return m_pTop[nNum]; }
	CScene *GetNext(void) { return m_pNext; }

	static void UpdateAll(void);
	static void DrawAll(void);
	static void ReleaseAll(void);
	static void Pause(bool bPause);
private:
	void connect(void);

	static CScene *m_pTop[PRIORITY];	//�擪�̃I�u�W�F�N�g�|�C���^
	static CScene *m_pCur[PRIORITY];	//���݂̃I�u�W�F�N�g�|�C���^

	CScene *m_pPrev;					//�O�̃I�u�W�F�N�g�|�C���^
	CScene *m_pNext;					//���̃I�u�W�F�N�g�|�C���^

	bool m_bDeathFlag;//���S�t���O
	OBJTYPE m_objType;	//�I�u�W�F�N�g�̎��
	int m_nPriority;
	static bool m_bPause;

protected:
	void SetDeathFlag(void);
};
//virtual���Ȃ��Ɣh���N���X�̃f�X�g���N�^���Ăяo����Ȃ����߂���
//�h���N���X�̃f�X�g���N�^��delete�����������Ă�����Ăяo���ꂸ
//�������̊J�����ł��Ȃ��̂ő�ςȂ��ƂɂȂ�B


#endif // !_SCENE_H_

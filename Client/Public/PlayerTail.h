#pragma once

#include "GameObject.h"

BEGIN(Engine)

class CCollider;

END

class CPlayerTail final : public CGameObject
{
private:
	CPlayerTail();
	virtual ~CPlayerTail() = default; 


public:
	virtual HRESULT Initialize(GAME_OBJECT_DESC* _desc) override;

	virtual void Priority_Update(float _fTimeDelta) override;
	virtual void Update(float _fTimeDelta) override;
	virtual void Late_Update(float _fTimeDelta) override;
	virtual HRESULT Render() override;


public:
	HRESULT Ready_Components();



	void Set_Color(int _Color) { m_Color = _Color; }
	void Set_Parent(CGameObject* _pParent) {m_pParent = _pParent;}
	CGameObject* Get_Parent() { return m_pParent; }

private:
	Vector2 m_vParentPos = { 0,0 };
	Vector2 m_vParentDir = { 0,0 };
	Vector2 m_vCurPos = { 0,0 };
	CGameObject* m_pParent = nullptr;

	CCollider* m_pCollider = nullptr;
	
	unsigned short m_Color = FOREGROUND_BLUE;

public:
	static CPlayerTail* Create(GAME_OBJECT_DESC* _desc = nullptr);
	virtual void Free() override; 

};


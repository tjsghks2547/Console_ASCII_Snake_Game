#pragma once

#include "GameObject.h"	

BEGIN(Engine)

class CCollider;
END

class CAttack_item final : public CGameObject
{
private:
	CAttack_item();
	virtual ~CAttack_item();


public:

	virtual HRESULT Initialize(GAME_OBJECT_DESC* _desc) override;


	virtual void Priority_Update(float _fTimeDelta) override;
	virtual void Update(float _fTimeDelta) override;
	virtual void Late_Update(float _fTimeDelta) override;
	virtual HRESULT Render() override;

public:
	HRESULT Ready_Components();

	virtual void OnCollisionEnter(CGameObject* _pOther) override;
	virtual void OnCollision(CGameObject* _pOther) override;
	virtual void OnCollisionExit(CGameObject* _pOther) override;


private:
	CCollider* m_pCollider;
	bool m_bMove = false; 
	bool m_bDead = false; 



public:
	static CAttack_item* Create(GAME_OBJECT_DESC* _desc = nullptr);
	virtual void Free() override;


};




#pragma once

#include "GameObject.h"	

BEGIN(Engine)

class CCollider;
END

class CTailPlus_Item final : public CGameObject
{
private:
	CTailPlus_Item();
	virtual ~CTailPlus_Item();



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



public:
	static CTailPlus_Item* Create(GAME_OBJECT_DESC* _desc = nullptr);	
	virtual void Free() override;


};




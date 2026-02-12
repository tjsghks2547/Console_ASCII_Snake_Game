#pragma once

#include "GameObject.h"	

BEGIN(Engine)
class CCollider;
END

class CTower_projectile final : public CGameObject
{
private:
	CTower_projectile();
	virtual ~CTower_projectile() = default;



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

private:
	Vector2 m_vDir;
	bool  m_bSetGreen = false;
	int   m_iImage_Size = 2;
	

	float m_fAccumulatedTimeDelta =0.f;
	bool  m_bDead = false; 

public:
	static CTower_projectile* Create(GAME_OBJECT_DESC* _desc = nullptr);
	virtual void Free() override;



};




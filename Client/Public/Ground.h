#pragma once

#include "GameObject.h"	

class CGround final : public CGameObject
{
private:
	CGround();
	virtual ~CGround() = default;


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



public:
	static CGround* Create(GAME_OBJECT_DESC* _desc = nullptr);
	virtual void Free() override;


};




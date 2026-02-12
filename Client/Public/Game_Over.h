#pragma once

#include "GameObject.h"	


class CGame_Over final : public CGameObject
{
private:
	CGame_Over();
	virtual ~CGame_Over() = default;



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

	void Set_Color_Green(bool _bOnOff) { m_bSetGreen = _bOnOff; }


private:
	bool m_bSetGreen = false;
	int m_iImage_Size = 6;
	char* Letter_image[6];

	float m_fAccumulatedDeletatime = 0.f; 


public:
	static CGame_Over* Create(GAME_OBJECT_DESC* _desc = nullptr);
	virtual void Free() override;



};




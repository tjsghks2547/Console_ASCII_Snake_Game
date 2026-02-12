#pragma once

#include "GameObject.h"	


class CSpeed_Up final : public CGameObject
{
private:
	CSpeed_Up();
	virtual ~CSpeed_Up() = default;



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
	int m_iImage_Size =13;
	char* Letter_image[13];

	float m_fAccumulatedDeletatime = 0.f;


public:
	static CSpeed_Up* Create(GAME_OBJECT_DESC* _desc = nullptr);
	virtual void Free() override;



};




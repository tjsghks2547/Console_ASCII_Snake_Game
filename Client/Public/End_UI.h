#pragma once

#include "GameObject.h"	


class CEnd_UI final : public CGameObject
{
private:
	CEnd_UI();
	virtual ~CEnd_UI() = default;



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
	int m_iImage_Size = 4;
	char* Letter_image[4];



public:
	static CEnd_UI* Create(GAME_OBJECT_DESC* _desc = nullptr);
	virtual void Free() override;



};




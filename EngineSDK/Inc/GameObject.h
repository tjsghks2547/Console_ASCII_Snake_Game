#pragma once

#include "Engine_Macro.h"
#include "Engine_Defines.h"
#include "Vector2.h"
#include "Transform.h"

BEGIN(Engine)


struct GAME_OBJECT_DESC
{
	int dir_x = 0; 
	int dir_y = 0; 
	int x = 0;
	int y = 0;
};


class ENGINE_DLL CGameObject
{


protected:
	CGameObject(const char* _name = nullptr);	
	virtual ~CGameObject();

public:
	virtual HRESULT Initialize(GAME_OBJECT_DESC* _desc);

#pragma region 기본적인 게임 루프
	virtual void Priority_Update(float _fTimeDelta);
	virtual void Update(float _fTimeDelta);
	virtual void Late_Update(float _fTimeDelta);
	virtual HRESULT Render();
#pragma endregion
	const char* Get_Name() { return name; }
	CComponent* Find_Component(const wstring& _CommponentName);
	

protected:
	class CDevice* m_pDevice;
	class CGameInstance* m_pGameInstance;



protected:
	const char* name = " ";
	map<const wstring, class CComponent*> m_mapComponents;

	const char* image = " ";


protected: 
	class CTransform* m_pTransform = nullptr; 


public:
	virtual void OnCollisionEnter(CGameObject* _pOther) {};
	virtual void OnCollision(CGameObject* _pOther) {};
	virtual void OnCollisionExit(CGameObject* _pOther) {};



public:
	static CGameObject* Create(GAME_OBJECT_DESC* _desc = nullptr, const char* _name = nullptr);
	virtual void Free();

	
};

END
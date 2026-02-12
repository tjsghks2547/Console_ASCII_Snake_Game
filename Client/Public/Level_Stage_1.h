#pragma once

#include "Level.h"
#include "Vector2.h"

BEGIN(Client)

class CLevel_Stage_1 final : public CLevel
{
private:
	CLevel_Stage_1();
	virtual ~CLevel_Stage_1();


public:
	virtual HRESULT Initialize() override;
	virtual void Update(float _fTimeDelta) override;
	virtual void Late_Update() override;

	void Load_Map(const char* filename);

public:

	HRESULT Ready_Layer_UI(const wchar_t* pLayerTag);
	HRESULT Ready_Layer_Structure(const wchar_t* pLayerTag);
	HRESULT Ready_Layer_Player(const wchar_t* pLayerTag);
	HRESULT Ready_Layer_Item(const wchar_t* pLayerTag);
	//HRESULT Ready_Layer_Camera(const _tchar* pLayerTag);
	HRESULT Ready_Layer_Monster(const wchar_t* pLayerTag);
	//HRESULT Ready_Layer_Effect(const _tchar* pLayerTag);


public:
	Vector2 GetRandomPos(int minX, int maxX, int minY, int maxY);

private:
	int m_iCurrentTailItemCount = 0; 
	int m_iCurrentAttack_ItemCount = 0;
	int m_iCurrentTowerCount = 0;

	int m_iCurrentMenuIndex = 1;


	float m_fItemAccDeltaTime = 0.f; 
	float m_fAttack_ItemAccDeltaTime = 0.f;
	float m_fTowerAccDeltaTime = 0.f;
	

public:
	static CLevel_Stage_1* Create();
	virtual void Free() override;
};

END

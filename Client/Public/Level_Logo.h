#pragma once
#include "Level.h"

BEGIN(Client)

class CLevel_Logo final : public CLevel
{
private: 
	CLevel_Logo();
	~CLevel_Logo(); 


public:
	virtual HRESULT Initialize() override; 
	virtual void Update(float _fTimeDelta) override;
	virtual void Late_Update() override; 

	void Load_Map(const char* filename);
	
public:
	HRESULT Ready_Layer_BackGround(const wchar_t* pLayerTag);
	HRESULT Ready_Layer_UI(const wchar_t* pLayerTag);	

	//HRESULT Ready_Layer_Structure(const _tchar* pLayerTag);
	//HRESULT Ready_Layer_Player(const _tchar* pLayerTag);
	//HRESULT Ready_Layer_Camera(const _tchar* pLayerTag);
	//HRESULT Ready_Layer_Monster(const _tchar* pLayerTag);
	//HRESULT Ready_Layer_Effect(const _tchar* pLayerTag);



private:
	int m_iCurrentMenuIndex = 1; 

public:
	static CLevel_Logo* Create(); 
	virtual void Free() override;
};

END

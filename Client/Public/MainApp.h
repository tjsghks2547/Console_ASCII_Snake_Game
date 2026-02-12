#pragma once
#include "Engine.h"
#include "Client_Defines.h"

BEGIN(Engine)
// 엔진 애들 전방선언해서 가져올것들 
class CGameInstance;
END

BEGIN(Client)
class CMainApp
{
private: 
	CMainApp();
	~CMainApp(); 

public: 
	HRESULT Init(); 
	void Update();
	void Late_Update();
	void Render(); 

private:
	CGameInstance* m_pGameInstance = nullptr; 
	float* m_pfDT = nullptr; 


public:
	static CMainApp* Create(); 
	void Free(); 


};

END
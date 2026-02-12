#pragma once

#include "Engine_Defines.h"	
#include "Engine_Macro.h"


BEGIN(Engine)
class ENGINE_DLL CEngine
{
	
private:
	CEngine();
	~CEngine() = default; 

public:
	HRESULT Initalize(); 
	void Update(); 
	void Late_Update(); 
	void Render(); 


public: 
	static CEngine* Create(); 
	void Free();

};
END

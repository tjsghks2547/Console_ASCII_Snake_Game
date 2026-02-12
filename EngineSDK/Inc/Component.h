#pragma once 

#include "Engine_Macro.h"
#include "Engine_Defines.h"
#include "Vector2.h"

BEGIN(Engine)

class ENGINE_DLL CComponent
{
protected:
	CComponent();
	virtual ~CComponent(); 


public:
	virtual HRESULT Initialize();

public:
	virtual void Free(); 
};

END
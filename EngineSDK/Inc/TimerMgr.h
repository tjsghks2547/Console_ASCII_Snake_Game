#pragma once
#include "Engine_Defines.h"
#include "Engine_Macro.h"

BEGIN(Engine)
class ENGINE_DLL CTimerMgr
{
private:
	CTimerMgr();
	~CTimerMgr() = default;


public:
	HRESULT Init();
	bool Update();
	float* Get_DeltaTime_ptr() { return &m_dDT; }	
	
private:
	long long		m_llCurCount;
	long long		m_llPrevCount;
	LARGE_INTEGER	m_llFrequency;

	float			m_dDT;		  // 프레임 사이의 시간값  ( 델타 타임)

public:
	static CTimerMgr* Create();
	void Free(); 
	



};

END
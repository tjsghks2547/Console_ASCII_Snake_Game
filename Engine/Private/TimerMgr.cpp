#include "TimerMgr.h"

CTimerMgr::CTimerMgr()
{

}

HRESULT CTimerMgr::Init()
{
	QueryPerformanceFrequency(&m_llFrequency); // <- 초당 카운트 횟수(m_llFrequency.QuadPart에 저장됨)
	//빈번도,얼마나 자주 즉 1초당 얼마나 카운트가 발생하는지에 대한 수를 얻음

	// 하드웨어 타이머로 시간 구하기
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);

	//엔진 시작 직전에는 두 시간 값을 같게 맞춤.	
	m_llCurCount = time.QuadPart;	
	m_llPrevCount = m_llCurCount;	


	

	return S_OK;
}


bool CTimerMgr::Update()
{
	

	//기준 프레임 ( 단위: 초 )
	float targetFrameRate = 120.0f;  // 1초에 240번 실행
	float oneFrameTime = 1.0f / targetFrameRate;

	LARGE_INTEGER time;	
	// 현재 시간 구하기
	QueryPerformanceCounter(&time);
	m_llCurCount = time.QuadPart;	

	// 프레임 시간 계산. 
	m_dDT = static_cast<float>(m_llCurCount - m_llPrevCount);

	// 초단위 변환
	m_dDT = m_dDT / static_cast<float>(m_llFrequency.QuadPart);  //  ex) 1ms 은 1/1000초를 의미 
	// 따라서 여기서도 진동수가 곧 1초의 max 진동이니깐 그걸 현재 차이를 나누면 현재 지난 시간을 알 수있다. 이 방법임


	// 고정 프레임 기법. 
	if (m_dDT >= oneFrameTime)
	{

		//cout << "DeltaTime : " << m_dDT
		//	<< ", FPS : " << (1.0f / m_dDT) << "\n";

		// 이전 시간 값 갱신. 
		m_llPrevCount = m_llCurCount;

		return true; 
	}

	return false; 
}



CTimerMgr* CTimerMgr::Create()
{
	CTimerMgr* pInstance = new CTimerMgr(); 

	if(FAILED(pInstance->Init()))
	{
		MSG_BOX("Failed to Created : TimerMgr");
		__debugbreak(); 
	}

	return pInstance; 
}


void CTimerMgr::Free()
{
	delete this; 
}
#pragma once

#include "Vector2.h"
#include <Windows.h>

BEGIN(Engine)

class ENGINE_DLL CScreenBuffer
{
private:
	CScreenBuffer(Vector2 _ScreenSize);
	~CScreenBuffer(); 


public:
	
	HRESULT Initialize(Vector2 _ScreenSize);

	// 콘솔 버퍼 지우는 함수 
	void Clear(); 
	
	// 콘솔에 2차원 글자 배열을 그릴 때 사용하는 함수.
	void Draw(CHAR_INFO* charInfo);

	// 버퍼 반환 Getter 
	inline HANDLE GetBuffer() const { return m_buffer; }

private:
	
	// 콘솔 출력 핸들
	HANDLE m_buffer = nullptr;

	// 화면 크기 
	Vector2 m_screenSize; 


public:
	static CScreenBuffer* Create(Vector2 _ScreenSize);
	void Free(); 

};

END
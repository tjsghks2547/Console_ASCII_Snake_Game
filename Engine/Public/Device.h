#pragma once

#include "Engine_Defines.h"
#include "Engine_Macro.h"
#include "Vector2.h"
#include "Color.h"
#include "Renderer.h"

BEGIN(Engine)

class ENGINE_DLL CDevice
{
	// 프레임 구조체 - 2차원 글자 배열의 항목이 될 구조체
	struct Frame
	{
		Frame(int bufferCount);
		~Frame();

		// 지우기 함수.
		void Clear(const Vector2& screenSize);

		// 글자 값과 글자의 색상을 갖는 타입.
		CHAR_INFO* charInfoArray = nullptr;
	};

	// 렌더링할 데이터
	struct RenderCommand
	{
		// 화면에 보여줄 문자열
		const char* text = nullptr;	

		// 좌표
		Vector2 position;

		// 색상값
		Color color = Color::White;	
			
		// 그리기 우선순위
		int sortingOrder = 0;

	};


public:
	CDevice();
	~CDevice();

public: 


	// 그리는데 필요한 데이터를 제출(적재)하는 함수
	/*void Submit(const char* text,
		const Vector2& position,
		Color color = Color::White,
		CRenderer::RENDER_GROUP _eRenderGroup = CRenderer::RENDER_GROUP::RG_NONE);*/

	// 그리기 함수 
	//void Draw(); 

	HRESULT Initialize(const Vector2& screenSize);

	
	// 화면 지우는 함수
	void Clear();

	// 더블 버퍼링을 활용해 활성화 버퍼를 교환하는 함수. 
	void Present(); 
	

	// 현재 사용할 버퍼를 반환하는 함수(Getter) 
	class CScreenBuffer* GetCurrentBuffer(); 


	// 현재 사용할 프레임 들고오는 함수 
	Frame* Get_Frame() { return m_frame; }
	Vector2 Get_ScreenSize() { return m_screenSize; }

private:

	// 화면 크기 
	Vector2 m_screenSize; 

	// 관리할 프레임 객체.
	Frame* m_frame = nullptr; 

	// 이중 버퍼 배열 
	class CScreenBuffer* screenBuffers[2] = {}; 

	// 현재 활성화된 버퍼 인덱스
	int currentBufferIndex = 0;


public:
	static CDevice* Create(const Vector2& screenSize);
	void Free(); 



};

END
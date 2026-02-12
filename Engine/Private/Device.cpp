#include "Device.h"
#include "ScreenBuffer.h"

CDevice::Frame::Frame(int bufferCount)
{
	// 배열 생성 및 초기화
	charInfoArray = new CHAR_INFO[bufferCount];
	memset(charInfoArray, 0, sizeof(CHAR_INFO) * bufferCount);
	


}

CDevice::Frame::~Frame()
{
	SafeDeleteArray(charInfoArray);
}

HRESULT CDevice::Initialize(const Vector2& screenSize)
{
	m_screenSize = screenSize; 

	// 프레임 객체 생성
	const int bufferCount = screenSize.x * screenSize.y; 
	m_frame = new Frame(bufferCount);

	// 프레임 초기화
	m_frame->Clear(screenSize);


	screenBuffers[0] = CScreenBuffer::Create(screenSize);
	screenBuffers[0]->Clear();

	screenBuffers[1] = CScreenBuffer::Create(screenSize);
	screenBuffers[1]->Clear();


	// 활성화 버퍼 설정
	Present();

	

	return S_OK;
}


void CDevice::Frame::Clear(const Vector2& screenSize)
{
	// 2차원 배열로 다루는 1차원 배열을 순회하면서 
	// 빈 문자(' ')를 설정.
	const int width = screenSize.x;
	const int height = screenSize.y;

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			// 배열 인덱스 구하기
			const int index = (y * width) + x;

			// 글자 값 및 속성 설정.
			CHAR_INFO& info = charInfoArray[index];
			info.Char.AsciiChar =' ';
			info.Attributes = 0;
		}
	}

	// ----------- Frame ----------- //
	



}


CDevice::CDevice()	
{

}

CDevice::~CDevice()
{

}

//
//void CDevice::Submit(const char* text, const Vector2& position, Color color, CRenderer::RENDER_GROUP _eRenderGroup)
//{
//	
//
//
//
//}

void CDevice::Clear()
{
	// 화면 지우기
	// 1. 프레임 (2차원 배열 데이터) 지우기.
	m_frame->Clear(m_screenSize);	

	// 2. 콘솔 버퍼 지우기.	
	GetCurrentBuffer()->Clear();	


}


CScreenBuffer* CDevice::GetCurrentBuffer()
{
	return screenBuffers[currentBufferIndex];	
}


void CDevice::Present()
{
	// 버퍼 교환 
	SetConsoleActiveScreenBuffer(GetCurrentBuffer()->GetBuffer());


	// 인덱스 교체
	currentBufferIndex = 1 - currentBufferIndex; 

}


CDevice* CDevice::Create(const Vector2& screenSize)
{
	CDevice* pInstance = new CDevice(); 
	
	if(FAILED(pInstance->Initialize(screenSize)))
	{
		MSG_BOX("Failed to Created : Device");
		__debugbreak();
		delete pInstance;
	}

	return pInstance;
}

void CDevice::Free()
{
	
	screenBuffers[0]->Free();
	screenBuffers[1]->Free();

	delete m_frame;

	delete this;
}
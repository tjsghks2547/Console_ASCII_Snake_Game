#include "ScreenBuffer.h"
#include "Device.h"

CScreenBuffer::CScreenBuffer(Vector2 _ScreenSize)
	:m_screenSize(_ScreenSize)
{

}

CScreenBuffer::~CScreenBuffer()
{
}

HRESULT CScreenBuffer::Initialize(Vector2 _ScreenSize)
{


	COORD ScreenSize;
	ScreenSize.X = (SHORT)_ScreenSize.x;
	ScreenSize.Y = (SHORT)_ScreenSize.y;


	// Console Output 생성
	m_buffer = CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		nullptr,
		CONSOLE_TEXTMODE_BUFFER,
		nullptr
	);


	// 예외 처리 
	if (m_buffer == INVALID_HANDLE_VALUE)
	{
		MSG_BOX("Failed to Initialize ScreenBuffer");
		__debugbreak();
		return E_FAIL;
	}


	
	// 콘솔의 전체 버퍼 크기 설정
	if (!SetConsoleScreenBufferSize(m_buffer, ScreenSize))
	{
		MSG_BOX("Failed to set console buffer size.");
		__debugbreak();
	}


	// 버퍼 중 어디를 얼마나 보여줄지 크기 지정 (뷰포트 영역 ) 
	SMALL_RECT rect;
	rect.Left = 0;
	rect.Top = 0;
	rect.Right = ScreenSize.X - 1;
	rect.Bottom = ScreenSize.Y - 1;

	if (!SetConsoleWindowInfo(
		m_buffer,
		true,
		&rect))
	{
		MSG_BOX("Failed to console window info.");
		__debugbreak();
	}


	
	// 커서 끄기 
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(m_buffer, &info);

	// 끄도록 설정.
	info.bVisible = false;
	SetConsoleCursorInfo(m_buffer, &info);



	return S_OK;
}



void CScreenBuffer::Clear()
{
	// 실제로 화면을 지우고 난 뒤에
	// 몇 글자를 썼는지 반환 받는데 사용
	DWORD writtenCount = 0; 


	// 콘솔 버퍼에 있는 화면 지우기
	// 그래픽스 -> 지우기 -> 한 색상(또는 값)으로 덮어쓰기.

	FillConsoleOutputCharacterA(
		m_buffer, // 현재 버퍼 
		L' ',    // ' ' 로 채우기
		m_screenSize.x * m_screenSize.y, // 전체 지울 영역
		Vector2(0, 0),  // 지우기 시작할 좌표 
		&writtenCount   // 몇 글자가 채워졌는지
	);


	FillConsoleOutputAttribute(
		m_buffer, // 현재 버퍼 
		0,    // ' ' 로 채우기
		m_screenSize.x * m_screenSize.y, // 전체 지울 영역
		Vector2(0, 0),  // 지우기 시작할 좌표 
		&writtenCount   // 몇 글자가 채워졌는지
	);


}




void CScreenBuffer::Draw(CHAR_INFO* charInfo)
{
	
	// 설정할 버퍼의 크기 
	SMALL_RECT writeRegion = {}; 
	writeRegion.Left = 0;
	writeRegion.Top = 0; 
	writeRegion.Right = static_cast<short>(m_screenSize.x - 1);
	writeRegion.Bottom = static_cast<short>(m_screenSize.y - 1);


	// 버퍼에 전달 받은 글자 배열 설정
	WriteConsoleOutputA(
		m_buffer,
		charInfo,  // 모든 글자가 들어있는 곳 
		m_screenSize,
		Vector2(0, 0),
		&writeRegion
	);


}


CScreenBuffer* CScreenBuffer::Create(Vector2 _ScreenSize)
{
	CScreenBuffer* pInstance = new CScreenBuffer(_ScreenSize);

	if(FAILED(pInstance->Initialize(_ScreenSize)))
	{
		MSG_BOX("Failed to Created : ScreenBuffer");
		__debugbreak(); 
		delete pInstance;
	}

	return pInstance;
}

void CScreenBuffer::Free()
{
	// 버퍼 해제.
	if (m_buffer)
	{
		CloseHandle(m_buffer);
	}

	delete this;
}
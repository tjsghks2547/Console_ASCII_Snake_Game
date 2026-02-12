#pragma once

#include "Engine_Defines.h"
#include "Engine_Macro.h"
#include <Windows.h>


BEGIN(Engine)

// 콘솔에 텍스트 색상 등을 지정할 때 사용할 
// 색상 열거형
enum class ENGINE_DLL Color : unsigned short
{
	Black = 0,
	Blue = FOREGROUND_BLUE,
	Green = FOREGROUND_GREEN,
	Red = FOREGROUND_RED,  // MS만 BGR 형태를 사용 보통 RGB인데
	White = Blue | Green | Red,

};


END


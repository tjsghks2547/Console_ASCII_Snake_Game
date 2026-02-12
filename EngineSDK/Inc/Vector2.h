#pragma once

#include "Engine_Macro.h"
#include "Engine_Defines.h"

BEGIN(Engine)

class ENGINE_DLL Vector2
{
public: 
	Vector2(); 
	Vector2(int x, int y);

	~Vector2(); 

  // 연산자 오버로딩
	Vector2 operator+(const Vector2& other) const; 
	Vector2 operator-(const Vector2& other) const; 
		
	
	bool operator==(const Vector2& other) const; 
	bool operator!=(const Vector2& other) const;





	// 형변환 연산자 오버로딩.
	operator COORD() const;


	int x = 0; 
	int y = 0; 

};

END
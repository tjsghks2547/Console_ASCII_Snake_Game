#pragma once

#pragma warning (disable : 4251)


#include <Windows.h>
#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <map>
#include <wchar.h>
#include <cstring> 
#include <string>



using namespace std; 


namespace Engine
{

}
using namespace Engine;


// 메모리 정리 함수.
template<typename T>
void SafeDelete(T*& t)
{
	if (t)
	{
		delete t;
		t = nullptr;

	}
}


template<typename T>
void SafeDeleteArray(T*& t)
{
	if (t)
	{
		delete[] t;
		t = nullptr;

	}
}


enum class GROUP_TYPE {	
	PLAYER,
	PLAYER_WEAPON,
	MONSTER,
	TAIL,
	BULLET,
	ENEMY,
	OBJECT,
	UI,
	GROUP_END,
};
#pragma once


#ifdef	ENGINE_EXPORTS		
#define ENGINE_DLL		_declspec(dllexport)
#else
#define ENGINE_DLL		_declspec(dllimport)	
#endif

#define			BEGIN(NAMESPACE)		namespace NAMESPACE {
#define			END						}


#define			MSG_BOX(_message)			MessageBox(nullptr, TEXT(_message), L"System Message", MB_OK)


#define  SINGLETON(type) public:\
								static type* GetInstance()\
								{\
									static type instance;\
									return &instance;\
								};


#define TEXT(quote) __TEXT(quote)	
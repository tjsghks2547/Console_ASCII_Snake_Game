#include "Transform.h"

CTransform::CTransform()
{

}

CTransform::~CTransform()
{

}


HRESULT CTransform::Initialize()
{
	
	return S_OK;
}


void CTransform::Go_Right(float _fTimedelta)
{
	m_vDir.x = 1; 
	m_vDir.y = 0;

	m_fPosition_x += _fTimedelta * m_fSpeedPerSec;

	m_vPosition.x = (int)(m_fPosition_x);
}

void CTransform::Go_Right_Up_Diagonal(float _fTimedelta)
{
	m_vDir.x =  1;
	m_vDir.y = -1;

	m_fPosition_x += _fTimedelta * m_fSpeedPerSec;
	m_fPosition_y -= _fTimedelta * m_fSpeedPerSec;

	m_vPosition.x = (int)(m_fPosition_x);
	m_vPosition.y = (int)(m_fPosition_y);
}

void CTransform::Go_Right_Down_Diagonal(float _fTimedelta)
{
	m_vDir.x = 1;
	m_vDir.y = 1;

	m_fPosition_x += _fTimedelta * m_fSpeedPerSec;
	m_fPosition_y += _fTimedelta * m_fSpeedPerSec;

	m_vPosition.x = (int)(m_fPosition_x);
	m_vPosition.y = (int)(m_fPosition_y);
}

void CTransform::Go_Left(float _fTimedelta)
{
	m_vDir.x = -1;
	m_vDir.y =  0;


	m_fPosition_x -= _fTimedelta * m_fSpeedPerSec;

	m_vPosition.x = (int)(m_fPosition_x);
}

void CTransform::Go_Left_Up_Diagonal(float _fTimedelta)
{
	m_vDir.x = -1;
	m_vDir.y = -1;

	m_fPosition_x -= _fTimedelta * m_fSpeedPerSec;
	m_fPosition_y -= _fTimedelta * m_fSpeedPerSec;

	m_vPosition.x = (int)(m_fPosition_x);
	m_vPosition.y = (int)(m_fPosition_y);
}

void CTransform::Go_Left_Down_Diagonal(float _fTimedelta)
{
	m_vDir.x = -1;
	m_vDir.y =  1;

	m_fPosition_x -= _fTimedelta * m_fSpeedPerSec;
	m_fPosition_y += _fTimedelta * m_fSpeedPerSec;

	m_vPosition.x = (int)(m_fPosition_x);
	m_vPosition.y = (int)(m_fPosition_y);
}



void CTransform::Go_Up(float _fTimedelta)
{
	m_vDir.x =  0;
	m_vDir.y = -1;

	m_fPosition_y -= _fTimedelta * m_fSpeedPerSec;
	m_vPosition.y = (int)(m_fPosition_y);
}

void CTransform::Go_Down(float _fTimedelta)
{
	m_vDir.x = 0;
	m_vDir.y = 1;

	m_fPosition_y += _fTimedelta * m_fSpeedPerSec;
	m_vPosition.y = (int)(m_fPosition_y);	
}

void CTransform::Set_Position(float _x, float _y)
{

	m_fPosition_x = _x;
	m_fPosition_y = _y; 

	m_vPosition.x = (int)_x; 
	m_vPosition.y = (int)_y;

}

void CTransform::Set_Position(int _x, int _y)
{

	m_fPosition_x = (int)_x;
	m_fPosition_y = (int)_y;

	m_vPosition.x = _x;
	m_vPosition.y = _y;

}

CTransform* CTransform::Create()
{
	CTransform* pInstance = new CTransform(); 
	
	if (FAILED(pInstance->Initialize()))
	{
		MSG_BOX("Failed to Created : Transform");
	}

	return pInstance; 
}

void CTransform::Free()
{
	delete this;
}
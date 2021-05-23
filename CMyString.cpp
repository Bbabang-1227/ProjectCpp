#include <iostream>
#include "CMyString.h"

using namespace std;

//생성자

CMyString::CMyString()
	: m_pszData(NULL)
	, m_nLength(0)	
{
}

CMyString::CMyString(const CMyString& rhs)
	: m_pszData(NULL)
	, m_nLength(0)
{
	cout << "CMyString 복사 생성자 호출" << endl;
	this->SetString(rhs.GetString());
}

//변환생성자 호출
CMyString::CMyString(const char* pszParam)
	: m_pszData(NULL)
	, m_nLength(0)
{
	cout << "CMyString 변환 생성자 호출" << endl;
	SetString(pszParam);
}
//소멸자
CMyString::~CMyString()
{
	Release();
}

//getter & setter
int CMyString::SetString(const char* pszParam)
{
	Release();
	this->m_pszData = new char[strlen(pszParam) + 1];
	m_nLength = strlen(pszParam);
	strcpy_s(m_pszData,sizeof(char) * (strlen(pszParam) + 1), pszParam);
	return m_nLength;
}

const char* CMyString::GetString() const
{
	return m_pszData;
}

//릴리즈
void CMyString::Release()
{
	//delete[] m_pszData;
	free(m_pszData);
	m_pszData = NULL;
	m_nLength = 0;
}

//연산자
//=
CMyString& CMyString::operator=(const CMyString& rhs) 
{
	this->SetString(rhs.GetString());
	return *this;
}

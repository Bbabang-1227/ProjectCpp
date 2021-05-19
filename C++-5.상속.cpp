#include <iostream>
using namespace std;
//#define ON_MAIN
#ifdef ON_MAIN
class CMyDataA
{
public:
	CMyDataA() {
		cout << "CMyDataA()" << endl;
		m_pData = new char[32];
	}
	~CMyDataA() {
		cout << "~CMyDataA()" << endl;
		if (m_pData != NULL)
			delete[] m_pData;
	}

private:
protected:
	char* m_pData;
};

class CMyDataB : public CMyDataA
{
public:
	CMyDataB() {
		cout << "CMyDataB()" << endl;
	}
	~CMyDataB() {
		cout << "~CMyDataB()" << endl;
	}

private:

};

class CMyDataC : public CMyDataB
{
public:
	CMyDataC() {
		cout << "CMyDataC()" << endl;
	}
	~CMyDataC() {
		cout << "~CMyDataC()" << endl;
		delete[] m_pData;
		m_pData = NULL;
	}

private:

};
//////////////////////////////////////////
class CParent
{
public:
	CParent()
	{
		cout << "CParent()" << endl;
	}
	CParent(int a)
	{
		cout << "CParent(int)" << endl;
	}
	CParent(double a)
	{
		cout << "CParent(double)" << endl;
	}

	~CParent() {}
	int GetData() { return m_nData; };
	void SetData(int nParam) { m_nData = nParam; };

private:
	int m_nData = 0;

protected: // 상속받은 클래스 내부에서만 사용가능
	void PrintData() { cout << "CParent::PrintData() : " << m_nData << endl; };
};

class CChild : public CParent
{
public:
	CChild() : CParent() //부모쿨래스의 생성자 선택가능
	{
		cout << "CChild()" << endl;
	}
	CChild(int a) : CParent(a) //부모쿨래스의 생성자 선택가능
	{
		cout << "CChild(int)" << endl;
	}
	CChild(double a) : CParent(a) //부모쿨래스의 생성자 선택가능
	{
		cout << "CChild(double)" << endl;
	}
	void TextFunc()
	{
		SetData(5);
		PrintData();
	}
	//overriding
	void SetData(int nParam)
	{
		if (nParam < 0)
		{
			CParent::SetData(0);
		}
		else if (nParam > 10 && nParam < 15)
		{
			CParent::SetData(10);
		}
		else
			CParent::SetData(nParam);
	}
	~CChild() {}

private:

};
//////////////////////////////////////////////

int main()
{
	//생성자 선택
	{
		CChild a;
		CChild b(4);
		CChild c(3.3);
		return 0;
	}
	{
		CParent p;
		p.SetData(13);
		cout << p.GetData() << endl;

		CChild a;
		a.SetData(13);
		cout << a.GetData() << endl;

		CParent& cp = a;
		cp.SetData(13);
		cout << cp.GetData() << endl;

		a.TextFunc(); // protected의 접근
		return 0;
	}

	{
		cout << "Main begin" << endl;
		CMyDataC a;
		cout << "Main end" << endl;
		return 0;
	}
}
#endif
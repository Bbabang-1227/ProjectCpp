#include <iostream>
using namespace std;
//#define ON_MAIN

#ifdef ON_MAIN
class CAnimal // 가상함수를 하나라도 포함하면 가상 클래스
{
public:
	CAnimal() {}
	~CAnimal() {}
	
	virtual void Cry() = 0; // 순수가상함수 pure virtual function PVF + 필요에따라 재정의
	//virtual void Cry() {} // 가상함수 VF + 재정의 필수
	void TestFunc() 
	{ 
		cout << "=====TestFunc()=====" << endl;
		Cry();
		cout << "====================" << endl;
	}
private:

};

class CDog : public CAnimal
{
public:
	void Cry() override
	{ cout << "집가고싶다" << endl; }

private:

};

class CCat : public CAnimal
{
public:
	void Cry() override
	{ cout << "나도가고싶다" << endl; }

private:

};

int main() 
{
	//Ref + virtual
	{
		CCat a;
		a.Cry();

		CAnimal& ref = a;
		ref.Cry();
		return 0;
	}
	{
		//CAnimal* p0 = new CAnimal; //가상클래스는 객체를 생성할수없다.
		
		CAnimal* p1 = new CCat;
		p1->Cry();
		delete p1;

		CAnimal* p2 = new CDog;
		p2->Cry();
		delete p2;

		return 0;
	}
	{
		CCat* a = new CCat;
		a->Cry();
		a->TestFunc();

		CDog* b = new CDog;
		b->Cry();
		b->TestFunc();
		delete a, b;
	}
	return 0;
}
#endif
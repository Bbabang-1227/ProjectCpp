#include <iostream>
using namespace std;
//#define ON_MAIN

#ifdef ON_MAIN
class CAnimal // �����Լ��� �ϳ��� �����ϸ� ���� Ŭ����
{
public:
	CAnimal() {}
	~CAnimal() {}
	
	virtual void Cry() = 0; // ���������Լ� pure virtual function PVF + �ʿ信���� ������
	//virtual void Cry() {} // �����Լ� VF + ������ �ʼ�
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
	{ cout << "������ʹ�" << endl; }

private:

};

class CCat : public CAnimal
{
public:
	void Cry() override
	{ cout << "��������ʹ�" << endl; }

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
		//CAnimal* p0 = new CAnimal; //����Ŭ������ ��ü�� �����Ҽ�����.
		
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
#include <iostream>
using namespace std;
#pragma once // �ߺ� ����� ������� �����Ѵ�
//#define ON_MAIN

#ifdef ON_MAIN
#define DEFAULT_FARE 45000

class CPerson
{
public:
	virtual void CalcFare() { m_nFare = DEFAULT_FARE; };
	unsigned int GetFare() { return m_nFare; }

protected:
	unsigned int m_nFare = 0;
};

// ������(0~7��) ��� ��� --> // 0%
class CBaby : public CPerson 
{
public:
	void CalcFare() override {
		m_nFare = 0;
	}
};
// ���(8~13��) ��� ��� --> // 50%
class CChild : public CPerson 
{
public:
	void CalcFare() override {
		m_nFare = DEFAULT_FARE*0.5;
	}
};
// û�ҳ�(14~19��) ��� ���--> // 75%
class CTeen : public CPerson 
{
public:
	void CalcFare() override {
		m_nFare = DEFAULT_FARE*0.75;
	}
};
// ����(20�� �̻�) ��� ���--> // 100%
class CAdult : public CPerson 
{
public:
	
};


int main()
{
	while (1)
	{
	cout << "=======================================" << endl;
	cout << "\t �������� ��� ����" << endl;
	cout << "=======================================" << endl;

	int nCount = 0;
	cout << "�� �� ���� �����Ͻó���? ";
	cin >> nCount;
	cout << "------------------------------" << endl;

	CPerson* arListTemp[3]; //�������ιۿ� ������ ����
	CPerson** arList = new CPerson * [nCount]; //CPerson�� ����Ű�� pointer �� nCount��ŭ ��´�
	// ���ÿ� ����          ���� ����

	// 1. �ڷ� �Է�: ����� �Է¿� ���� ������ ��ü ����
	int nAge = 0;
	for (int i = 0; i < nCount; i++)
	{
		cout << i + 1 << "���� ���̸� �Է��ϼ���: ";
		cin >> nAge;
		
		// ����ڰ� �Է��� ���̿� ���� ��ü�� ���� �����Ѵ�.
		if (nAge <= 7)
			arList[i] = new CBaby;
		else if (nAge <= 13)
			arList[i] = new CChild;
		else if (nAge <= 19)
			arList[i] = new CTeen;
		else if (nAge >= 20)
			arList[i] = new CAdult;
		else
			cout << "�߸��Է��ϼ˽��ϴ�" << endl;

		// ������ ��ü�� �´� ����� �ڵ����� ���ȴ�.
		arList[i]->CalcFare();
	}

	// 2. �ڷ� ���: ����� ����� Ȱ���ϴ� �κ�
	int nFare = 0;
	int nTotal = 0;
	cout << "------------------------------" << endl;
	for (int i = 0; i < nCount; i++)
	{
		nFare = arList[i]->GetFare();
		nTotal += nFare;
		cout << i + 1 << "���� ����� " << nFare << "��" << endl;
	}
	cout << "------------------------------" << endl;
	cout << "�� ��� : " << nTotal << endl;
	cout << "------------------------------" << endl;

	// 3. �ڷ� ���� �� ����
	for (int i = 0; i < nCount; i++)
	{
		delete[] arList[i];
	}
	delete[] arList;

	cout << "=======================================" << endl;
	cout << "����Ͻðڽ��ϱ�? (0.yes , 1.no) : " ;
	cin >> nCount;
	if (nCount == 0)
		system("cls");
	else
		break;
	}
	return 0;
}
#endif
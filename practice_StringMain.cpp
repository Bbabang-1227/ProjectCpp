#include <iostream>
#include "CMyStringEx.h"

using namespace std;
#pragma once // �ߺ� ����� ������� �����Ѵ�
#define ON_MAIN
#ifdef ON_MAIN

int main() {
	{
		//��ȯ������ ȣ��
		CMyStringEx aaa("I Love you");
		cout << aaa.GetString() << endl;

		aaa.Append(". Do you?");
		cout << aaa.GetString() << endl;

		int a = aaa.Find("you");
		cout << a << endl;
		return 0;
	}

	{
	CMyString strData;
	int a = strData.SetString("Hello");
	cout << strData.GetString() << endl;

	cout << a << endl;
	strData.SetString("�ȳ�ȳ�");
	cout << strData.GetString() << endl;
		
	CMyString strData2(strData);	
	cout << strData2.GetString() << endl;

	CMyString strData3 = strData;
	cout << strData3.GetString() << endl;

	//���Կ����� �����ε�
	strData2 = strData3;
	//���տ����� �����ε�
	//strData3 = strData + strData2;
	cout << "���Կ����� : " << strData3.GetString() << endl;
	cout << "���Կ����� : " << strData2.GetString() << endl;
	cout << strData3.GetString() << endl;

	//��ȯ������ ()
	//CMyString strData4("");
	
	return 0;
	}
}
#endif // ON_MAIN
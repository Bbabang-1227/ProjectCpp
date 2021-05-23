#include <iostream>
#include "CMyStringEx.h"

using namespace std;
#pragma once // 중복 헤더가 있을경우 배제한다
#define ON_MAIN
#ifdef ON_MAIN

int main() {
	{
		//변환생성자 호출
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
	strData.SetString("안녕안녕");
	cout << strData.GetString() << endl;
		
	CMyString strData2(strData);	
	cout << strData2.GetString() << endl;

	CMyString strData3 = strData;
	cout << strData3.GetString() << endl;

	//대입연산자 오버로딩
	strData2 = strData3;
	//병합연산자 오버로딩
	//strData3 = strData + strData2;
	cout << "대입연산자 : " << strData3.GetString() << endl;
	cout << "대입연산자 : " << strData2.GetString() << endl;
	cout << strData3.GetString() << endl;

	//변환생성자 ()
	//CMyString strData4("");
	
	return 0;
	}
}
#endif // ON_MAIN
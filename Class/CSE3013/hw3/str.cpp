#include "str.h"	// str.h 헤더파일을 포함한다.
#include <iostream>	// iostream 헤더파일을 포함한다.
#include <cstdlib>	// 동적할당을 위해 cstdlib헤더파일을 포함한다.

using std::cout;	// cout이 std::cout으로 사용된다는 것을 알려준다. 

Str::Str(int leng)	//Str클래스의 int leng을 매개변수로 하는 Str 객체 생성자
{
	len = leng;		//int leng을 Str 객체의 데이터 len에 대입한다.
	str = new char [len];	// len 만큼의 길이를 가진 char 배열의 포인터를 str에 동적할당한다.
}

Str::Str(const char *neyong)	// Str클래스의 char * neyong을 매개변수로 하는 Str객체 생성자
{
	len = strlen(neyong);	// string.h의 함수인 strlen을 사용해 neyong이 가리키는 문자열의 길이를 구해 이를 길이를 나타내는 데이터 len에 대입한다.
	str = new char [len];	// 문자열의 길이 len 만큼의 길이를 가진 char 배열의 포인터를 str에 동적할당한다.	
	strcpy(str, neyong);	// string.h의 함수인 strcpy를 str과 neyong에 사용해 neyong이 가리키는 문자열을 str이 가리키는 문자열로 복사한다.
}

Str::~Str()	// Str 클래스의 소멸자 ~Str
{
	delete [] str;	// 동적할당됐던 str 포인터를 해제한다.
}

int Str::length(void)	// Str 클래스의 문자열의 길이를 리턴하는 함수
{
	return len;	// 길이를 저장하는 변수 len의 값을 리턴한다.
}

char* Str::contents(void)	// Str 클래스의 문자열의 내용을 리턴하는 함수
{
	return str; // 문자열을 지시하는 포인터 str을 리턴한다.
}

int Str::compare(class Str & a) // Str 클래스의 문자열과 다른 Str 객체의 문자열을 비교하는 함수
{
	int comp, result;
	comp = strcmp(str, a.contents());	// strcmp 의 결과를 int comparison에 대입
	if( comp > 0 )	// comparison이 0보다 크면
		result = 1;		// 리턴할 result = 1
	else if ( comp == 0)	// comparison이 0이면 
		result = 0;	// 리턴할 result = 0
	else 
		result = -1;	// comparison이 음수면 -1 리턴
	return result; // result 리턴
	// str 포인터와 다른 Str 객체 a의 문자열을 지시하는 포인터에 strcmp를 사용해 두 문자열을 비교한다.
	// 이때 두 문자열이 같으면 0, str이 아스키 코드에서 더 크면 1, a가 지시하는 문자열 아스키 코드에서 더 크면 -1을 리턴한다.
	//strcmp 바로 리턴시 1, 0, -1 외의 다른 수들도 리턴돼 result를 따로 생성했다.
}

int Str::compare(const char *a) // Str 클래스의 문자열과 다른 문자열을 비교하는 함수
{
	int result;
	int comp = strcmp(str,a); 	// strcmp의 결과를 int comp에 저장
	if (comp > 0) 	// comp가 0보다 크면
		result = 1;	// result 는 1
	else if (comp == 0) // comp 가 0이면
		result = 0;	// result 는 0
	else 
		result = -1;	// comp가 음수면 -1리턴
	return result; // result 리턴
	// strcmp를 사용해 str 포인터와 a 포인터가 지시하는 문자열을 비교한다.
	// 이때 두 문자열이 같으면 0, str이 아스키 코드에서 더 크면 1, a가 지시하는 문자열 아스키 코드에서 더 크면 -1을 리턴한다.
	//strcmp 바로 리턴시 1, 0, -1 외의 다른 수들도 리턴돼 result를 따로 생성했다.
} 

void Str::operator=(const char *a)	// Str 클래스의 = 연산자 오버로딩이다. char *a가 지시하는 문자열을 기존 Str 객체의 문자열에 대입한다. (매개변수가 char* 형일때)
{
	int newlen = strlen(a);	// a가 지시하는 문자열의 길이를 strlen을 이용해 구하고, 이를 newlen 변수에 대입한다.
	if ( newlen != len)	// newlen과 Str 객체의 len이 다르면
	{
		delete [] str;	// 기존 str을 해제한다.
		str = new char [newlen];	//newlen 길이의 char 배열 포인터를 str에 동적할당한다.
		len = newlen;	// newlen으로 len을 재설정한다. 
	}
	// newlen과 len이 같은 경우 위 작업없이 strcpy만 진행한다.
	strcpy(str,a);	// strcpy(str,a)를 통해 a가 지시하는 문자열을 str이 지시하는 문자열로 복사한다.
}

void Str::operator=(class Str& a)	// Str 클래스의 = 연산자 오버로딩이디. 다른 Str 객체의 문자열을 기존 Str 객체의 문자열에 대입한다. (매개변수가 Str& 형일때)
{
 	int newlen = a.length();	// Str 객체 a의 길이는 private 데이터이므로 a.length() 메서드를 통해 길이를 얻고 이를 newlen에 대입한다.
    if ( newlen != len)	// newlen과 Str 객체의 len이 다르면
    {
    	delete [] str;	// 기존 str을 해제한다.
    	str = new char [newlen];	// newlen 길이의 char 배열 포인터를 str에 동적할당한다.
    	len = newlen;	// newlen으로 len을 재설정한다.
	}
    strcpy(str, a.contents());		// strcpy(str,a.contents())를 통해 Str 객체 a의 문자열을 str이 지시하는 문자열로 복사한다. a의 str 포인터는 private 데이터이므로 a.contents() 메서드를 통해 str 포인터를 얻어 이를 사용한다. 
}

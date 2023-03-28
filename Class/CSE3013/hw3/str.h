#ifndef __Str__ // str.h를 1회만 포함하기 위해 __Str__이 정의되지 않았을때 __Str__을 정의
#define __Str__	// __Str__을 정의하면

#include <string.h> // string.h 헤더파일을 include 한다.

class Str	// Str 클래스를 선언
{
	private:
		char *str;	// 문자열의 첫번째 포인터가 될 char 포인터 str, string의 내용을 저장한다.
		int len;	//	string의 길이를 저장할 int len
	public:
		Str(int leng);	// leng 은 string의 길이다
		Str(char *neyong); // neyong은 초기화할 내용이 들어간다.
		~Str(); // Str 객체의 소멸자 
		int length(void); // string의 길이를 리턴하는 함수
		char *contents(void); // string의 내용을 리턴하는 함수
		int compare(class Str & a);  // a의 내용과 string에 strcmp함수를 사용한 결과를 리턴하는 함수
		int compare(char *a);  // a의 내용과 string에 strcmp 함수를 사용한 결과를 리턴한다.
		void operator=(char *a); // a 포인터가 지시하는 문자열을 string에 대입한다
		void operator=(class Str & a); //Str 객체의 str 포인터가 지시하는 문자열의 내용을 객체에 대입한다.
};
#endif //매크로 종료 

#include "str.h"
#include <iostream>


int main()
{
	using std::cout;
	using std::endl;
	Str a(11);
	a = "I'm a girl";
	cout << a.contents();
	a = "I'm a boy\n";
	cout << a.contents();
	cout << a.compare("I'm a a") << endl;
	return 0;
}


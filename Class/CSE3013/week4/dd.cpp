#include <iostream>
using namespace std;

class One
{
public:
	int one;
	One (int input = 6) {
		one = input * 2;
	}
	virtual void print()
	{
		one++;
		cout << one << endl;
	}
};

class Two : public One
{
public:
	int one;
	Two(int input) { one = input; }
	void print()
	{
		cout << one << endl;
		cout << this-> one << endl;
		cout << One::one << endl;
	}
};
int main()
{
	One o(1);
	One* op = new One;
	Two two(10);
	op = &two;
	op->print();
}

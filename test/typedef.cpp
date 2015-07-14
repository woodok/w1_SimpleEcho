#include <iostream>

using namespace std;

typedef int Key;

void op(int i)
{
	cout << "op(int)" << endl;
}

void op(char c)
{
	cout << "op(char)" << endl;
}

//void op(Key key)
//{
//	cout << "op(Key)" << endl;
//}

int main(void)
{
	cout << "main() start" << endl;

	int i = 0;
	Key key = 11;
	char c = 'a';

	op(key);
	op(i);
	op(c);

	cout << "main() end" << endl;

	return 0;
}
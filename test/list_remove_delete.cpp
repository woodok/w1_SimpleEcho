#include <iostream>
#include <list>

using std::cin;
using std::cout;
using std::endl;

class Test
{
private:
	static int count;
public:
	int objCount;
	int key;
public:
	Test()
	{
		objCount = ++count;
		cout << "Test()" << endl;
	}
	Test(int _key) : key(_key)
	{
		objCount = ++count;
		cout << "Test(" << _key << ")" << endl;
	}
	~Test()
	{
		cout << "~Test()" << endl;
	}
};
int Test::count = 0;

int main(void)
{
	cout << "main() start" << endl;

	/*
	std::list<Test*> tlist;

	tlist.push_back(new Test);
	tlist.remove(0);
	*/
	


	cout << "main() end" << endl;
	return 0;
}
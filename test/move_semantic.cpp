#include <iostream>
#include <string>
#include <utility>

using std::cin;
using std::cout;
using std::endl;

class TestSmall
{
public:
	int id;
	char data;
	static int idCount;
public:
	TestSmall()
	{
		id = idCount++;
		data = ' ';
		cout << "TestSmall() called. id:" << id << " /address:" << &id << endl;
	}
	TestSmall(char c)
	{
		id = idCount++;
		data = c;
		cout << "TestSmall(char) called. id:" << id << " /address:" << &id << endl;
	}
	TestSmall(const TestSmall& _obj) 
	{
		id = idCount++;
		data = _obj.data;
		cout << "TestSmall(const TestSmall&) called. id:" << id << " /address:" << &id << endl;
	}
	TestSmall(TestSmall&& _obj)
	{
		id = _obj.id;
		cout << "TestSmall(TestSmall&&) called. id:" << id << " /address:" << &id << endl;
	}
	~TestSmall()
	{
		cout << "~TestSmall() called. id:" << id << " /address:" << &id << endl;
	}
};
int TestSmall::idCount = 0;
//std::ostream& operator<<(std::ostream& obj, TestSmall& _testSmall)
//{
//	cout << "TestSmall object id:" << _testSmall.id << endl;
//}

class TestBig
{
public:
	int id;
	static int idCount;
	TestSmall data;
public:
	TestBig()
	{
		id = idCount++;
		data = TestSmall();
		cout << "TestBig() called. id:" << id << " /address:" << &id << endl;
	}
	//TestBig(const TestSmall& _obj) : data(_obj)		
	TestBig(const TestSmall& _obj) : data(_obj)
	//TestBig(const TestSmall& _obj) : data(_obj)
	{
		id = idCount++;
		//data(_obj);
		cout << "TestBig(TestSmall&) called. id:" << id << " /address:" << &id << endl;
	}
	TestBig(TestSmall&& _obj) : data(std::move(_obj))		//? 이렇게 하면 move semantic으로 작동하나?
	//TestBig(TestSmall&& _obj) : data(std::move(_obj))
	{
		id = idCount++;
		//data(_obj);
		cout << "TestBig(TestSmall&&) called. id:" << id << " /address:" << &id << endl;
	}
	~TestBig()
	{
		cout << "~TestBig() called. id:" << id << " /address:" << &id << endl;
	}
};
int TestBig::idCount = 0;

int main()
{
	cout << "main() start" << endl;

	TestSmall a;
	cout << "----------------------------------" << endl;
	TestSmall b;
	cout << "----------------------------------" << endl;

	TestBig A(a);
	cout << "----------------------------------" << endl;
	//TestBig B(b);
	TestBig B(std::move(b));
	cout << "----------------------------------" << endl;

	cout << "main() end" << endl;
	return 0;
}
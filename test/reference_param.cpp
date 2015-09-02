// object�� reference�� �ǳ��� �� constructor �۵� ��� �׽�Ʈ

#include <iostream>
#include <vector>

using namespace std;

class Test
{
public:
	Test()
	{
		cout << "Test() calling" << endl;
	}
	/*Test(Test& _test)
	{
		cout << "Test(Test&) calling" << endl;
	}*/
	Test(const Test& _test)
	{
		cout << "Test(const Test&) calling" << endl;
	}
	Test(Test&& _test)
	{
		cout << "Test(Test&&) calling" << endl;
	}
	Test& operator=(const Test& _test)
	{
		cout << "operator=() calling" << endl;
	}
	~Test()
	{
		cout << "~Test() calling" << endl;
	}
	void use()
	{
		cout << "do whatever" << endl;
	}
};

//void function(Test _test)		// �Լ� ȣ�� �� ��ȣ�� �����ε�
//{
//	cout << "function(Test) calling" << endl;
//}
void fuction(Test& _test)
{
	cout << "fuction(Test&) calling" << endl;
}
void function(const Test& calling)
{
	cout << "function(const Test&) calling" << endl;
}
void function(Test&& _test)
{
	cout << "fuction(Test&&) calling" << endl;
}
void function(vector<Test>& _v)
{
	cout << "function(vector<Test>&) calling" << endl;
}

int main()
{
	cout << "main() start" << endl;
	cout << "------------------------" << endl;
	
	//Test a();		// �۵� �ȵ�
	Test a;

	cout << "------------------------" << endl;

	function(a);

	cout << "------------------------" << endl;

	function(std::move(a));
	
	a.use();

	cout << "------------------------" << endl;
	cout << "passing vector for parameter" << endl;
	cout << "------------------------" << endl;
	Test v1;
	Test v2;
	Test v3;
	//Test v4;
	//Test v5;
	//Test v6;
	//Test v7;
	//Test v8;
	//Test v9;
	//Test v10;
	
	vector<Test> vec;
	//cout << "capacity of vec: " << vec.capacity() << endl;
	//vector<Test&> rvec;		//? ����..?
	//vector<const Test&> vec;	//? ����..?

	cout << "------------------------" << endl;

	cout << "------------------------" << endl;
	cout << "case 1" << endl;
	cout << "push back vector without using move semantic" << endl;
	//cout << "vector reserve: 3" << endl;
	//vec.reserve(3);
	//vec.push_back(v1);
	vec.push_back(std::move(v1));
	cout << "capacity of vec: " << vec.capacity() << endl;
	//vec.push_back(v2);
	vec.push_back(std::move(v2));
	cout << "capacity of vec: " << vec.capacity() << endl;
	//vec.push_back(v3);
	vec.push_back(std::move(v3));
	cout << "capacity of vec: " << vec.capacity() << endl;
	cout << "------------------------" << endl;
	function(vec);


	cout << "main() end" << endl;

	return 0;
}
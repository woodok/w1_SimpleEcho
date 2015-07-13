#include <iostream>
#include <list>
#include <vector>
#include <functional>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;

class Test
{
public:
	int key;
public:
	Test() : key(0)
	{
		cout << "Test()" << endl;
	}
	Test(int _key) : key(_key)
	{
		cout << "Test(" << _key << ")" << endl;
	}
	~Test()
	{
		cout << "~Test(" << key << ")" << endl;
	}
	bool operator==(int _key) { return key == _key; }
};
class TestVec
{
public:
	std::vector<Test *> head;
	int objCreated;
public:
	TestVec()
	{
		objCreated = 0;
	}
	void add(int _key);
	void del(int _key);
	//~TestVec();			//rev
};
class TestList
{
private:
	int objCreated;
public:
	std::list<Test *> head;
public:
	TestList() :objCreated(0) {}
	void add(int _key);
	void del(int _key);
};

int main(void)
{
	cout << "main() start" << endl;

	// list - remove test
	/*std::list<Test*> tlist;

	tlist.push_back(new Test);
	tlist.remove(0);
	*/
	// TestVec test using vector - functor
	/*TestVec tvec;
	tvec.add(1);
	tvec.add(10);
	tvec.add(100);

	tvec.del(1);
	tvec.del(10);
	tvec.del(100);
*/

	// TestList test


	cout << "main() end" << endl;
	return 0;
}

void TestVec::add(int _key)
{
	++objCreated;
	head.push_back(new Test(_key));
}
void TestVec::del(int _key)
{
	struct TestVec_deletor {
		int targetKey;
		void operator()(Test *& e) {
			if (e->key == targetKey) {
				delete e;
				e = NULL;
			}
		}
		TestVec_deletor(int _targetKey) :targetKey(_targetKey) { }
	};
	for_each(head.begin(), head.end(), TestVec_deletor(_key));
	std::vector<Test *>::iterator newEnd = remove(head.begin(), head.end(), static_cast<Test*>(NULL));
	head.erase(newEnd, head.end());
}

void TestList::add(int _key)
{
	++objCreated;
	head.push_back(new Test(_key));
}
void TestList::del(int _key)
{
	//rev
	head.remove(head.begin(), head.end(), find(head.begin(), head.end(), _key));

}
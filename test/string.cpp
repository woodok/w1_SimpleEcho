#include <iostream>
#include <string>
#include <sstream>

using std::cin;
using std::cout;
using std::endl;

class Test
{
private:
	int iData;
	char cData;
public:
	Test(int _newInt = 0, char _newChar = '/0') : iData(_newInt), cData(_newChar) {}
	friend void operator<<(std::string&, const Test&);
};

void operator<<(std::string& _originStr, const Test& _test)
{
	_originStr += '|';
	_originStr += std::to_string(_test.iData);
	_originStr += '|';
	_originStr += _test.cData;
}

int main(void)
{
	std::string str1("012345");

	const char * cstr;
	
	cstr = str1.c_str();

	cout << "main start" << endl;
	cout << "cstr: " << cstr << endl;
	cout << "sizeof(cstr): " << sizeof(cstr) << endl;
	cout << "strlen(cstr): " << strlen(cstr) << endl;
	cout << "cstr[4]: " << cstr[4] << endl;

	str1 += "6789";

	cout << "str1: " << str1 << endl;

	// std::string operator<< overloading test
	//--------------------------------------------------------------
	std::string str2;
	cout << "str2 input: ";
	cin >> str2;
	cout << "str2: " << str2 << endl;

	Test tst(1004, 'a');
	str2 << tst;

	cout << "str2 << operation: " << str2 << endl;

	//int i0 = str2.find('|');
	//cout << "i0: " << i0 << endl;
	//i0 = str2.find('|', i0 + 1);
	//cout << "i0: " << i0 << endl;
	//i0 = str2.find('|', i0 + 1);
	//cout << "i0: " << i0 << endl;

	std::string temp;
	std::stringstream ss;
	ss.str(str2);

	while (getline(ss, temp, '|'))
		cout << temp << endl;

	return 0;	
}
#include <iostream>
#include <string>
#include <sstream>
#include <ostream>
#include <istream>

using std::cin;
using std::cout;
using std::endl;

int main()
{
	std::stringstream ss("1234|asdf|4321 asdf 1423");
	std::string s;
	char c[100];

	//while (getline(ss, s, '|')) {
	//	cout << s << endl;
	//}
	//cout << ss.str() << endl;


	//ss.clear();
	//getline(ss, s, '|');
	//cout << s << endl;
	//cout << ss.str() << endl;

	//ss << endl;

	ss.getline(c, 100, '|');
	cout << c << endl;
	ss.getline(c, 100, '|');
	cout << c << endl;
	//ss.clear(std::ios_base::goodbit);	// 이 함수로는 추출할 위치 초기화 안됨. 
	ss.seekg(std::ios_base::beg);		// 다음으로 추출할 위치를 지정하는 함수..
	ss.getline(c, 100, '|');
	cout << c << endl;

	return 0;
}
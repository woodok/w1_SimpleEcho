
#include <iostream>
#include <algorithm>
#include <unordered_map>

using std::cout;
using std::endl;

typedef std::unordered_map<int, double> umid;

int main()
{
	cout << "main() start" << endl << endl;
	std::unordered_map<int, double> um;

	um.insert(std::unordered_map<int, double>::value_type(1, 1.2342));
	um.insert(std::unordered_map<int, double>::value_type(2, 0.8273));
	um.insert(std::unordered_map<int, double>::value_type(3, 12.0281));
	um.insert(umid::value_type(10, 10.2341));

	// case1 => error
	/*std::for_each(um.begin(), um.end(), [](std::unordered_map<int, double>::iterator & e) {
		cout << e->first;
	});*/

	// case2 => error
	/*std::for_each(um.begin(), um.end(), [](std::pair<int, double> & e) {
		cout << e.first;
	});*/

	// case3 => no error
	cout << "case3" << endl;
	std::for_each(um.begin(), um.end(), [](std::pair<int, double> e) {
		cout << e.first << " ";
	});
	cout << endl;

	// case4 => no error
	cout << "case4" << endl;
	for_each(um.begin(), um.end(), [](std::pair<const int, double> &e) {		// for_each ³ª std::for_each³ª no matter
		cout << e.first << " ";
	});
	cout << endl;

	// case5 => no error
	cout << "case5" << endl;
	std::for_each(um.begin(), um.end(), [](std::unordered_map<int, double>::value_type & e) {
		cout << e.first << " ";
	});
	cout << endl;

	// case6 => no error
	cout << "case6" << endl;
	std::for_each(um.begin(), um.end(), [](const std::unordered_map<int, double>::value_type & e){
		cout << e.first << " ";
	});
	cout << endl;

	cout << endl << "main() end" << endl;
}
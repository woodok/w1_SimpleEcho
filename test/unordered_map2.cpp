

#include <iostream>
#include <WinSock2.h>
#include <algorithm>
#include <map>
#include <vector>
#include <unordered_map>

using std::cout;
using std::cin;
using std::endl;

int main()
{
	cout << "main() start" << endl;

	std::unordered_map<int, std::vector<HANDLE>> um;
	std::vector<HANDLE> vec{ INVALID_HANDLE_VALUE };

	um.insert(std::unordered_map<int, std::vector<HANDLE>>::value_type(1, vec));
	um.insert(std::unordered_map<int, std::vector<HANDLE>>::value_type(2, vec));

	um.find(2)->second.push_back(INVALID_HANDLE_VALUE);

	//for_each(um.begin(), um.end(), [](std::unordered_map<int, std::vector<HANDLE>> & e) {
	for_each(um.begin(), um.end(), [](const std::unordered_map<int, std::vector<HANDLE>>::value_type &e) {
		cout << "key:" << e.first << "\t|";
		int idx = 0;
		//std::for_each(e.second.begin(), e.second.end(), [&idx](HANDLE e) {			// no error
		std::for_each(e.second.begin(), e.second.end(), [&idx](const HANDLE &e) {
		//for_each(e.second.begin(), e.second.end(), [&idx](const HANDLE * & e) {	// error
			cout << "vec[" << idx++ << "]:" << e << " >> ";
		});
		cout << " (end)" << endl;

	});
}
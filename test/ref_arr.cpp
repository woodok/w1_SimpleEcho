#include <iostream>

using namespace std;

void main()
{
	int arr[] = { 0, 1, 2, 3, 4 };
	int i = 4;
	int i2 = 24;
	int& ri = i;

	cout << "ri = i = " << ri << endl;

	ri = i2;
	cout << "ri = i2 = " << ri << endl;

	ri = *(arr + 1);
	cout << "ri = *(arr + 1) = " << ri << endl;

	ri = (*arr) + 1;
	cout << "ri = (*arr)+1 = " << ri << endl;

	ri = (*arr + 3);
	cout << "ri = (*arr)+3 = " << ri << endl;		// reference ri�� i�� �ѹ� �ʱ�ȭ �� �ٸ� variable�� �ٲٴ� ���� �Ұ���!!

	return;
}
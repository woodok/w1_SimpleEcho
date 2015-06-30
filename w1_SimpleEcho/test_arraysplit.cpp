#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#pragma warning(disable: 4996)

int main(void)
{
	char arr[100];
	int a = 14;
	int b = 10;

	*((int*) arr) = a;
	*((int *) (arr + sizeof(int)) ) = b;
	*((int *)(arr + sizeof(int) + sizeof(int))) = 20;

	//printf("%d\n", *((int *) arr));
	//printf("%d\n", *((int *) (arr + sizeof(int)) ));
	//printf("%d\n", *((int *)(arr + sizeof(int) + sizeof(int))));

	std::cout << static_cast<int>(*arr) << std::endl;
	std::cout << static_cast<int>(*(arr + sizeof(int))) << std::endl;
	std::cout << static_cast<int>(*(arr + sizeof(int) * 2)) << std::endl;

	return 0;
}
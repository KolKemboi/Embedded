#include <stdio.h>

int min(int, int, int);

int main() {
	int num = 10;
	int numb = 100;
	 
	{
		int a = 10;
		printf("%d\n", a);
		printf("%d\n", num);
	}
	int maximum = min(10, 18, 50);
	printf("The lesser is %d\n", maximum);
	printf("Code Has Run\n");
	return 0;
}

int min(int a, int b, int c) {
	int less =  ((a) > (b) ? (a) : (b));
	int lesser =  ((less) > (c) ? (less) : (c));
	return lesser;
}

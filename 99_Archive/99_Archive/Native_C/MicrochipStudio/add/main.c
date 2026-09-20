/*
 * add.c
 *
 * Created: 2024-05-24 오후 11:55:54
 * Author : Soochan Kim
 */ 

#include <avr/io.h>

int sub(int a)
{
	a = a - 1;	

	return a;
}

int add(int a, int b)
{
	a = a + 1;
	a = a + b;
	
	a = sub(a);
	return a;
}

int main(void)
{
	char str[100] = "0123456789";
	
	int a = 8;
	int b = 4;
	
	str[2] = str[3];
	
	b = add(a, b);
	
	return b;
}


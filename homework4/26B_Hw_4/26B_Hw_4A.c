/*******************************************************
Homework 4: Part A
NAME: Dat Nguyen
IDE:  Visual Studio 2015
Biwise Operators

There are three requirements:
1. Define and use a macro to turn on a range of bits
2. Define and use a macro to turn off a range of bits
3. Define and use a macro to toggle a range of bits
4. Write a function that takes an unsigned short parameter and returns an unsigned short
with the bits in the parameter turned backwards.
*******************************************************/

#include <stdio.h>
// 1)
#define TURN_ON_BITS(startbit,  numbits)		(unsigned short)((~(((unsigned short)~0) << (numbits))) << (startbit))     // turn on a range of bits
// 2)
#define TURN_OFF_BITS(startbit,numbits)			(unsigned short)(~((~(((unsigned short) ~0) << (numbits))) << (startbit))) //turn off a range of bits
// 3)
#define TOGGLE_BITS(bits, startbit, numbits)    (unsigned short)( (bits)^TURN_ON_BITS((startbit), (numbits)) )			   // toggle a range of bit
// 4)
unsigned short reverse(unsigned short a) {
	// The Idea is to swap bit by pair instead of iterating through 
	// Big-O : O(log(n))
	// Reference: http://articles.leetcode.com/reverse-bits/ (This is 32 bit, I modified to 16 bit version)
	const unsigned short mask0 = 21845; // 0x5555
	const unsigned short mask1 = 13107; // 0x3333
	const unsigned short mask2 = 3855; // 0x0F0F
	const unsigned short mask3 = 255; // 0x00FF
	a = (((~mask0) & a) >> 1) | ((mask0 & a) << 1);
	a = (((~mask1) & a) >> 2) | ((mask1 & a) << 2);
	a = (((~mask2) & a) >> 4) | ((mask2 & a) << 4);
	a = (((~mask3) & a) >> 8) | ((mask3 & a) << 8);
	return a;
}

int  testbit(unsigned short wrd, int bit_to_test);
void printbits(unsigned short wrd);

int main(void) {
	unsigned short wrd = 65, a = 32, b, mask;
	int numbits = 3;
	int startbit = 2;

	printbits(wrd);
	mask = TURN_ON_BITS(startbit, numbits); // replace this by a macro with arguments
	b = a | mask;
	printf("Turn ON %d bits starting at bit#%d\n", numbits, startbit);
	printf("%d\n", a);
	printbits(a);
	printbits(b);
	printf("%d\n", b);

	a = 31;
	mask = TURN_OFF_BITS(startbit, numbits); // replace this by a macro with arguments
	b = a & mask;
	printf("Turn OFF %d bits starting at bit#%d\n", numbits, startbit);
	printf("%d\n", a);
	printbits(a);
	printbits(b);
	printf("%d\n", b);

	a = 85;
	int c = TOGGLE_BITS(a, startbit, numbits);
	printf("Toggle %d bits starting at bit#%d\n", numbits, startbit);
	printf("%d\n", a);
	printbits(a);
	printbits(c);
	printf("%d\n", c);

	a = 85;
	c = reverse(a);
	printf("Reversing bit :", numbits, startbit);
	printf("%d\n", a);
	printbits(a);
	printbits(c);
	printf("%d\n", c);

	return 0;
}

int revserse(unsigned short wrd) {
	unsigned short masked = 0;
	for (int i = 0; i < sizeof(wrd); i++) {
		if (testbit(wrd, i) == 1)
			masked |= 1;
		masked <<= 1;
	}
}
/**************************************************************
Return 1 if bit_to_test is set and 0 if it is unset
*/
int  testbit(unsigned short wrd, int bit_to_test)
{
	wrd >>= bit_to_test;
	wrd &= 1;
	return wrd;
}

/**************************************************************
This uses a trick to print an unsigned short as a string of
16 bits
*/
void printbits(unsigned short wrd)
{
	int  testbit(unsigned short wrd, int bit_to_test);
	int i;

	for (i = 15; i >= 0; i--)
	{
		printf("%1d", testbit(wrd, i));
		if (!(i % 4))
			printf(" ");
	}
	printf("\n");
	return;
}

/*
SAMPLE OUTPUT

0000 0000 0100 0001
Turn ON 3 bits starting at bit#2
32
0000 0000 0010 0000
0000 0000 0011 1100
60
Turn OFF 3 bits starting at bit#2
31
0000 0000 0001 1111
0000 0000 0000 0011
3
Toggle 3 bits starting at bit#2
85
0000 0000 0101 0101
0000 0000 0100 1001
73
Reversing bit :85
0000 0000 0101 0101
1010 1010 0000 0000
43520
Press any key to continue . . .*/
#include <stdio.h>

void show_bytes(short* start, size_t len);
int main()
{
	unsigned char num[5] = "abcde";
	show_bytes( (short *) &num, sizeof(num));

	return 0;
}

void show_bytes(short * start, size_t len)
{
	size_t i;
	for ( i=0; i < len; i++)
	{
		printf("%p: 0x%02x\n", start+i, start[i]);
	}
}

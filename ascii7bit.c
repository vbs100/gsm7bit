#include <stdio.h>
#include <string.h>


int get_bit(char *in, int bit_per_byte, int bit_pos)
{
	int byte_pos=bit_pos/bit_per_byte;
	int bit_in_byte=bit_per_byte-bit_pos%bit_per_byte-1;
	return (in[byte_pos] & (1<<bit_in_byte)) == (1<<bit_in_byte);
}

int set_bit(char *out, int bit_per_byte, int bit_pos, int val)
{
	int byte_pos=bit_pos/bit_per_byte;
	int bit_in_byte=bit_per_byte-bit_pos%bit_per_byte-1;
	return out[byte_pos] |= (val<<bit_in_byte);
}

void ascii_to_ascii7bit(char *in, int bitlen, char *out)
{
	int i, b;
	for(i=0;i<bitlen;i++)
	{
		b = get_bit(in, 7, i);
		set_bit(out, 8, i, b);
	}
}

void ascii7bit_to_ascii(char *in, int bitlen, char *out)
{
	int i, b;
	for(i=0;i<bitlen;i++)
	{
		b = get_bit(in, 8, i);
		set_bit(out, 7, i, b);
	}
}

int main()
{
	unsigned char num1[] = { 0x62, 0xc9, 0x9b, 0x60 };
	unsigned char num2[] = { 0x31, 0x32, 0x33, 0x36 };
	unsigned char result[128];
	int i,len1,len2,ret,outlen=0;

	len1 = sizeof(num1);
	len2 = sizeof(num2);

	printf("ascii7bit 1:");
	for(i=0;i<len1;i++)
		printf(" %02x", num1[i]);
	printf("\n");

	memset(result,0,sizeof(result));
	ascii_to_ascii7bit(num2, 28, result);
	printf("7bit 2:");
	for(i=0;i<28/8+1;i++)
		printf(" %02x", result[i]);
	printf("\n");

	printf("ascii 1:");
	for(i=0;i<len2;i++)
		printf(" %02x", num2[i]);
	printf("\n");

	memset(result,0,sizeof(result));
	ascii7bit_to_ascii(num1, 28, result);
	printf("ascii 2:");
	for(i=0;i<28/7;i++)
		printf(" %02x", result[i]);
	printf("\n");
}

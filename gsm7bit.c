#include <stdio.h>
#include <string.h>


int get_bit(char *in, int bit_per_byte, int bit_pos)
{
	int byte_pos=bit_pos/bit_per_byte;
	int bit_in_byte=bit_pos%bit_per_byte;
	return (in[byte_pos] & (1<<bit_in_byte)) == (1<<bit_in_byte);
}

int set_bit(char *out, int bit_per_byte, int bit_pos, int val)
{
	int byte_pos=bit_pos/bit_per_byte;
	int bit_in_byte=bit_pos%bit_per_byte;
	return out[byte_pos] |= (val<<bit_in_byte);
}

void ascii_to_gsm7bit(char *in, int bitlen, char *out)
{
	int i, b;
	for(i=0;i<bitlen;i++)
	{
		b = get_bit(in, 7, i);
		set_bit(out, 8, i, b);
	}
}

void gsm7bit_to_ascii(char *in, int bitlen, char *out)
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
	unsigned char char7bit[] = { 0xE8, 0x32, 0x9B, 0xFD, 0x46, 0x97, 0xD9, 0xEC, 0x37 };
	unsigned char char8bit[] = { 0x68, 0x65, 0x6C, 0x6C, 0x6F, 0x68, 0x65, 0x6C, 0x6C, 0x6F };
	unsigned char helloworld[] = { 0xe8, 0x32, 0x9b, 0xfd, 0xbe, 0xbf, 0xe5, 0x6c, 0x32 };
	unsigned char result[128];
	int i,len1,len2,ret,outlen=0;

	len1 = sizeof(char7bit);
	len2 = sizeof(char8bit);

	printf("7bit 1:");
	for(i=0;i<len1;i++)
		printf(" %02x", char7bit[i]);
	printf("\n");

	memset(result,0,sizeof(result));
	ascii_to_gsm7bit(char8bit, 70, result);
	printf("7bit 2:");
	for(i=0;i<70/8+1;i++)
		printf(" %02x", result[i]);
	printf("\n");
		
	printf("ascii 1:");
	for(i=0;i<len2;i++)
		printf(" %02x", char8bit[i]);
	printf("\n");

	memset(result,0,sizeof(result));
	gsm7bit_to_ascii(char7bit, 70, result);
	printf("ascii 2:");
	for(i=0;i<70/7;i++)
		printf(" %02x", result[i]);
	printf("\n");

	memset(result,0,sizeof(result));
	gsm7bit_to_ascii(helloworld, sizeof(helloworld)*8, result);
	printf("result=(%s)\n", result);

}

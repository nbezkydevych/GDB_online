#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <errno.h>

#define PRINT_EX_BITS(TYPE,VALUE) do { TYPE x = VALUE; print_bits(#TYPE, #VALUE, (unsigned char*) &x, sizeof(x)); } while(0)

#define BITSET(byte,nbit)   ((byte) |=  (1<<(nbit)))
#define BITCLEAR(byte,nbit) ((byte) &= ~(1<<(nbit)))
#define BITFLIP(byte,nbit)  ((byte) ^=  (1<<(nbit)))
#define BITCHECK(byte,nbit) ((byte) &   (1<<(nbit)))

void print_byte(char val)
{
    for (int i = 7; 0 <= i; i--)
        printf("%c", (val & (1 << i)) ? '1' : '0');
}

void print_bits(char* type, char* value, unsigned char* bytes, size_t num_bytes)
{
    printf("(%s) %s = [ ", type, value);
    for (size_t i = num_bytes; i != 0; i--)
    {
        print_byte(bytes[i-1]);
        printf(" ");
    }
    printf("]\n");
}

void printBits(void* ptr, size_t num_bytes)
{
    unsigned char* bytes = (unsigned char*)ptr;
    
    printf("[ ");
    for (size_t i = num_bytes; i != 0; i--)
    {
        print_byte(bytes[i-1]);
        if (i-1)
            printf(" ");
    }
    printf(" ]\n");
}

void RGB_to_GRB(uint32_t* ptr)
{
    uint32_t tmp = *ptr;
    
    *ptr = ((tmp >> 24) << 24);
    *ptr |= (((tmp >> 8) << 24) >> 8);
    *ptr |= (((tmp >> 16) << 24) >> 16);
    *ptr |= ((tmp << 24) >> 24);
}

int main()
{
    PRINT_EX_BITS(int, 0);
    PRINT_EX_BITS(int, 1);
    PRINT_EX_BITS(int, 17);
    PRINT_EX_BITS(int, -17);
    PRINT_EX_BITS(int, 256);
    PRINT_EX_BITS(int, INT_MAX);
    PRINT_EX_BITS(int, ~INT_MAX);
    PRINT_EX_BITS(unsigned int, 17);
    PRINT_EX_BITS(unsigned int, -17);
    PRINT_EX_BITS(unsigned int, UINT_MAX);
    PRINT_EX_BITS(unsigned int, UINT_MAX+1);
    PRINT_EX_BITS(unsigned char, 255);
    PRINT_EX_BITS(long, 17);
    PRINT_EX_BITS(short, 17);
    PRINT_EX_BITS(uint32_t, 17);
    PRINT_EX_BITS(uint16_t, 17*256+18);
    PRINT_EX_BITS(void*, &errno);
    PRINT_EX_BITS(unsigned int, 1 << 1);
    PRINT_EX_BITS(unsigned int, 1 << 2);
    PRINT_EX_BITS(unsigned int, 1 << 4);
    PRINT_EX_BITS(unsigned int, 1 << 8);
    PRINT_EX_BITS(unsigned int, 1 << 16);

    uint8_t i1 = 0b10101010, r1 = 0;
    uint16_t i2 = 0b10101010, r2 = 0;
    uint32_t i3 = 0b10101010;

    printf("i1 = %d | ", i1);
    printBits(&i1, sizeof(i1));

    r1 = i1;
    BITSET(r1, 6);
    BITSET(r1, 5);
    BITSET(r1, 4);
    printf("r1 = %d | ", r1);
    printBits(&r1, sizeof(r1));
    
    r1 = i1;
    //uint8_t tmp = 0;
    //printf ("tm = "); printBits(&tmp, sizeof(tmp)); printf ("r1 = "); printBits(&r1, sizeof(r1));
    //tmp = 1 << 5;
    //printf ("tm = "); printBits(&tmp, sizeof(tmp)); printf ("r1 = "); printBits(&r1, sizeof(r1));
    //tmp = ~tmp;
    //printf ("tm = "); printBits(&tmp, sizeof(tmp)); printf ("r1 = "); printBits(&r1, sizeof(r1));
    //r1 = r1 & tmp;
    //printf ("tm = "); printBits(&tmp, sizeof(tmp)); printf ("r1 = "); printBits(&r1, sizeof(r1));
    BITCLEAR(r1, 6);
    BITCLEAR(r1, 5);
    BITCLEAR(r1, 4);
    printf("r1 = %d | ", r1);
    printBits(&r1, sizeof(r1));
    
    r1 = ~i1;
    printf("r1 = %d | ", r1);
    printBits(&r1, sizeof(r1));

    printf("i2 = %d | ", i2);
    printBits(&i2, sizeof(i2));
    
    r2 = i2;
    BITSET(r2, 9);
    BITSET(r2, 8);
    printf("r2 = %d | ", r2);
    printBits(&r2, sizeof(r2));

    printf("i3 = %d | ", i3);
    printBits(&i3, sizeof(i3));
    
    uint32_t rgb = 0xC4332211;
    
    printf("rgb = %x | ", rgb);
    printBits(&rgb, sizeof(rgb));
    
    RGB_to_GRB(&rgb);
   
    printf("grb = %x | ", rgb);
    printBits(&rgb, sizeof(rgb));
    return 0;
}
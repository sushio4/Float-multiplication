#include <stdio.h>
#include <inttypes.h>

float multiply(float a, float b)
{
    uint32_t ai = *(int32_t*)&a;
    uint32_t bi = *(int32_t*)&b;

    uint8_t exp = (((ai & 0x7F800000) + (bi & 0x7F800000)) >> 23) - 0x80;
    uint64_t mant = ((ai & 0x7FFFFF) + 0x800000) * (uint64_t)((bi & 0x7FFFFF) + 0x800000) >> 22;
    
    mant += 0x2 * (mant & 0x1);

    exp += (mant > 0x2000000);
    mant = mant >> (1 + (mant > 0x2000000));

    uint32_t res = (mant & 0x7FFFFF) | (++exp << 23) | ((ai ^ bi) & 0x80000000);
    return *(float*)&res;
}

int main()
{
    //while(1)
    {
        float a, b;
        printf("a = ");
        scanf("%f", &a);
        printf("b = ");
        scanf("%f", &b);
        float act = a*b, comp = multiply(a,b);
        printf(" actual  a * b = %f  \ncomputed a * b = %f  \n", act, comp);
        printf("\nHexadecimal:\n actual  = %08x\ncomputed = %08x\n", *(int32_t*)&act, *(int32_t*)&comp);
    }
}
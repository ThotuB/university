#include <stdio.h>

int g_int1 = 1;
int g_int2 = 0;
int g_int3;

float g_float1 = 1.0;
float g_float2 = 0.0;
float g_float3;

int function(int fp_int1, float fp_float, int fp_int2) {
    int fv_int1 = 1;
    float fv_float = 1.0;
    int fv_int2 = 0;

    printf("FUNCTION PARAMETERS\n");
    printf("\tint1: %p - %x\n", &fp_int1, fp_int1);
    printf("\tfloat: %p - %x\n", &fp_float, *(int*)&fp_float);
    printf("\tint2: %p - %x\n", &fp_int2, fp_int2);

    printf("FUNCTION VARIABLES\n");
    printf("\tint1: %p - %x\n", &fv_int1, fv_int1);
    printf("\tfloat: %p - %x\n", &fv_float, *(int*)&fv_float);
    printf("\tint2: %p - %x\n", &fv_int2, fv_int2);

    register void *ip asm ("si");
    printf("%p\n", ip);

    return 0;
}

int main() {
    int l_int1 = 1;
    int l_int2 = 0;
    int l_int3;

    float l_float1 = 1.0;
    float l_float2 = 0.0;
    float l_float3;

    printf("GLOBAL VARIABLES\n");

    printf("\tINTEGERS\n");
    printf("\t\tinitialized non-zero: 0x%p - %x\n", &g_int1, g_int1);
    printf("\t\tinitialized zero: 0x%p - %x\n", &g_int2, g_int2);
    printf("\t\tuninitialized: 0x%p - %x\n", &g_int3, g_int3);

    printf("\tFLOATS\n");
    printf("\t\tinitialized non-zero: 0x%p - %x\n", &g_float1, *(int*)&g_float1);
    printf("\t\tinitialized zero: 0x%p - %x\n", &g_float2, *(int*)&g_float2);
    printf("\t\tuninitialized: 0x%p - %x\n", &g_float3, *(int*)&g_float3);

    printf("LOCAL VARIABLES\n");

    printf("\tINTEGERS\n");
    printf("\t\tinitialized non-zero: 0x%p - %x\n", &l_int1, l_int1);
    printf("\t\tinitialized zero: 0x%p - %x\n", &l_int2, l_int2);
    printf("\t\tuninitialized: 0x%p - %x\n", &l_int3, l_int3);

    printf("\tFLOATS\n");
    printf("\t\tinitialized non-zero: 0x%p - %x\n", &l_float1, *(int*)&l_float1);
    printf("\t\tinitialized zero: 0x%p - %x\n", &l_float2, *(int*)&l_float2);
    printf("\t\tuninitialized: 0x%p - %x\n", &l_float3, *(int*)&l_float3);

    function(3, 4.0, 'a');
}
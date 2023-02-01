/**
 * MIPS SIMD Architecture(MSA)
 *  Branch
 *  related MSA intrinsics demo codes
 */
#include <msa.h>
#include "utils.c"


void testIfNotZero() {
    __uint8_t a[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    __uint8_t b[16] = {0,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    /* Immediate Branch If All Elements Are Not Zero
        i32 __builtin_msa_bnz_b (v16u8);
        i32 __builtin_msa_bnz_h (v8u16);
        i32 __builtin_msa_bnz_w (v4u32);
        i32 __builtin_msa_bnz_d (v2u64);

       Immediate Branch If Not Zero
        i32 __builtin_msa_bnz_v (v16u8);
    */

    // PC-relative branch if all elements in 'a' are not zero.
    int r1 = __builtin_msa_bnz_b((v16u8)__builtin_msa_ld_b((void*)a, 0));
    int r0 = __builtin_msa_bnz_b((v16u8)__builtin_msa_ld_b((void*)b, 0));
    printf("Immediate Branch If All Elements Are Not Zero: \n");
    printf(" [%d] [%d] \n", r1, r0);

    // At Least One Element of Any Format Is Not Zero
    r0 = __builtin_msa_bnz_v((v16u8)__builtin_msa_ld_b((void*)b, 0));
    printf("Immediate Branch If Not Zero: \n");
    printf(" [%d] \n", r0);
}

void testIfZero() {
    __int8_t a[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    __int8_t b[16] = {0,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    /* Immediate Branch If At Least One Element Is Zero
        i32 __builtin_msa_bz_b (v16u8);
        i32 __builtin_msa_bz_h (v8u16);
        i32 __builtin_msa_bz_w (v4u32);
        i32 __builtin_msa_bz_d (v2u64);

       Immediate Branch If Zero
        i32 __builtin_msa_bz_v (v16u8);
    */

    // PC-relative branch if at least on element in 'a' is zero.
    int r1 = __builtin_msa_bz_b((v16u8)__builtin_msa_ld_b((void*)a, 0));
    int r0 = __builtin_msa_bz_b((v16u8)__builtin_msa_ld_b((void*)b, 0));
    printf("Immediate Branch If At Least One Element Is Zero: \n");
    printf(" [%d] [%d] \n", r1, r0);

    // At Least One Element of Any Format Is Zero
    r0 = __builtin_msa_bz_v((v16u8)__builtin_msa_ld_b((void*)b, 0));
    printf("Immediate Branch If Zero: \n");
    printf(" [%d] \n", r0);
}


int main() {
    printf("------------------ Branch Operation Tests ------------------------ \n");

    testIfNotZero();
    testIfZero();

    return 0;
}

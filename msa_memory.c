/**
 * MIPS SIMD Architecture(MSA)
 *  Memory
 *  related MSA intrinsics demo codes
 */
#include <msa.h>
#include "utils.c"


void testCopy() {
    __int8_t a[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    v16i8 v_a = __builtin_msa_ld_b((void*)a, 0);


    /**
     * Element Copy to GPR Signed
        i32 __builtin_msa_copy_s_b (v16i8, imm0_15);
        i32 __builtin_msa_copy_s_h (v8i16, imm0_7);
        i32 __builtin_msa_copy_s_w (v4i32, imm0_3);
        i64 __builtin_msa_copy_s_d (v2i64, imm0_1);
       Element Copy to GPR Unsigned
        u32 __builtin_msa_copy_u_b (v16i8, imm0_15);
        u32 __builtin_msa_copy_u_h (v8i16, imm0_7);
        u32 __builtin_msa_copy_u_w (v4i32, imm0_3);
        u64 __builtin_msa_copy_u_d (v2i64, imm0_1);
    */

    // Sign-extend element imm4 of vector 'a' and copy the result to GPR rd
    // should be the same with vector[imm]
    // r1 == r2
    printf("Element Copy to GPR Signed: \n");
    int r1 = __builtin_msa_copy_s_b(v_a, 5);
    int r2 = v_a[5];
    printf("%d %d \n",r1, r2);

    /**
      GPR Copy from MSA Control Register
      The sign extended content of MSA control register cs is copied to GPRrd.
        i32 __builtin_msa_cfcmsa (imm0_31);
      GPR Copy to MSA Control Register
      The content of the least significant 31 bits of GPR imm1 is copied to MSA control register cd
        void __builtin_msa_ctcmsa (imm0_31, i32);
    */
    // Both can not be tested in user mode
    // printf("MSA control register: \n");
    // printf(" %d \n",__builtin_msa_cfcmsa(0));

}



int main() {
    printf("------------------ Memory Operation Tests ------------------------ \n");

    testCopy();

    return 0;
}

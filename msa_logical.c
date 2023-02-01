/**
 * MIPS SIMD Architecture(MSA)
 *  Logical
 *  related MSA intrinsics demo codes
 */
#include <msa.h>
#include "utils.c"


void testAnd() {
    v16u8 v_true, v_false, v_dst;

    v_true = (v16u8)__builtin_msa_fill_b(1);
    v_false = (v16u8)__builtin_msa_fill_b(0);

    /* Vector Logical And
        v16u8 __builtin_msa_and_v (v16u8, v16u8);
    */
    v_dst = __builtin_msa_and_v(v_true, v_false);
    printf("Vector Logical And: \n");
    // [0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0]
    dump_u8_vector(v_dst);

    /* Immediate Logical And
        v16u8 __builtin_msa_andi_b  (v16u8, imm0_255);
    */
    v_dst = __builtin_msa_andi_b (v_true, 1);
    printf("Immediate Logical And: \n");
    // [1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1]
    dump_u8_vector(v_dst);
}



int main() {
    printf("------------------ Logical Operation Tests ----------------------- \n");

    testAnd();

    return 0;
}

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


void testOrNor() {
    v16u8 v_true, v_false;
    v_true = (v16u8)__builtin_msa_fill_b(1);
    v_false = (v16u8)__builtin_msa_fill_b(0);

    /* Vector Logical Or
        v16u8 __builtin_msa_or_v (v16u8, v16u8);
       Vector Logical Negated Or
        v16u8 __builtin_msa_nor_v (v16u8, v16u8);
       Immediate Logical Or
        v16u8 __builtin_msa_ori_b (v16u8, imm0_255);
       Immediate Logical Negated Or
        v16u8 __builtin_msa_nori_b (v16u8, imm0_255);
    */
    printf("Vector Logical Or: \n");
    // [1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1]
    dump_u8_vector(__builtin_msa_or_v(v_true, v_false));

    printf("Vector Logical Negated Or: \n");
    // or then negative
    // [254 254 254 254 254 254 254 254 254 254 254 254 254 254 254 254]
    dump_u8_vector(__builtin_msa_nor_v(v_true, v_false));

    printf("Immediate Logical Or: \n");
    // [1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1]
    dump_u8_vector(__builtin_msa_ori_b(v_true, 0));

    printf("Immediate Logical Negated Or: \n");
    // or then negative
    // [254 254 254 254 254 254 254 254 254 254 254 254 254 254 254 254]
    dump_u8_vector(__builtin_msa_nori_b(v_true, 0));
}


void testXor() {
    v16u8 v_true, v_false;
    v_true = (v16u8)__builtin_msa_fill_b(1);
    v_false = (v16u8)__builtin_msa_fill_b(0);

    /* Vector Logical Exclusive Or
        v16u8 __builtin_msa_xor_v (v16u8, v16u8);
       Immediate Logical Exclusive Or
        v16u8 __builtin_msa_xori_b (v16u8, imm0_255);
    */
    printf("Vector Logical Exclusive Or: \n");
    // ¬: not
    // ∧: and
    // ∨: or
    // ⊕: xor : (¬ a ∧ b) ∨ (a ∧¬b)
    // [1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1]
    dump_u8_vector(__builtin_msa_xor_v(v_true, v_false));

    printf("Immediate Logical Exclusive Or: \n");
    // [1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1]
    dump_u8_vector(__builtin_msa_xori_b(v_true, 0));
}


int main() {
    printf("------------------ Logical Operation Tests ----------------------- \n");

    testAnd();
    testOrNor();
    testXor();

    return 0;
}

/**
 * MIPS SIMD Architecture(MSA)
 *  Bit operation
 *  related MSA intrinsics demo codes
 */
#include <msa.h>
#include "utils.c"


void testBitClear() {
    v16u8 v_true, v_false, v_dst;
    v_true = (v16u8)__builtin_msa_fill_b(1);
    v_false = (v16u8)__builtin_msa_fill_b(0);

/**
    -- Vector Bit Clear
     - Clear (set to 0) one bit in each element of vector a,
     - The bit position is given by the elements in b.

        v16u8 __builtin_msa_bclr_b (v16u8, v16u8);
        v8u16 __builtin_msa_bclr_h (v8u16, v8u16);
        v4u32 __builtin_msa_bclr_w (v4u32, v4u32);
        v2u64 __builtin_msa_bclr_d (v2u64, v2u64);

    -- Immediate Bit Clear
        v16u8 __builtin_msa_bclri_b (v16u8, imm0_7);
        v8u16 __builtin_msa_bclri_h (v8u16, imm0_15);
        v4u32 __builtin_msa_bclri_w (v4u32, imm0_31);
        v2u64 __builtin_msa_bclri_d (v2u64, imm0_63);
*/
    v_dst = __builtin_msa_bclr_b(v_true, v_false);
    printf("Vector Bit Clear: \n");
    // [0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0]
    dump_u8_vector(v_dst);

    v_dst = __builtin_msa_bclri_b(v_true, 0);
    printf("Immediate Bit Clear: \n");
    // [0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0]
    dump_u8_vector(v_dst);
}

void testBitInsert() {
    v16u8 v_a, v_b, v_c, v_dst;
    v_a = (v16u8)__builtin_msa_fill_b(1);
    v_b = (v16u8)__builtin_msa_fill_b(175);
    v_c = (v16u8)__builtin_msa_fill_b(10);
/**
    Vector Bit Insert Left
     - Copy most significant (left) bits in each element of vector b 
     - to elements in vector 'a' while preserving the least sig-nificant (right) bits.
     - The number of bits to copy is given by the elements in vector 'c' modulo the size of the element inbits plus 1.
        v16u8 __builtin_msa_binsl_b (v16u8, v16u8, v16u8);
        v8u16 __builtin_msa_binsl_h (v8u16, v8u16, v8u16);
        v4u32 __builtin_msa_binsl_w (v4u32, v4u32, v4u32);
        v2u64 __builtin_msa_binsl_d (v2u64, v2u64, v2u64);

   Immediate Bit Insert Left
        v16u8 __builtin_msa_binsli_b (v16u8, v16u8, imm0_7);
        v8u16 __builtin_msa_binsli_h (v8u16, v8u16, imm0_15);
        v4u32 __builtin_msa_binsli_w (v4u32, v4u32, imm0_31);
        v2u64 __builtin_msa_binsli_d (v2u64, v2u64, imm0_63);

    Vector Bit Insert Right
        v16u8 __builtin_msa_binsr_b (v16u8, v16u8, v16u8);
        v8u16 __builtin_msa_binsr_h (v8u16, v8u16, v8u16);
        v4u32 __builtin_msa_binsr_w (v4u32, v4u32, v4u32);
        v2u64 __builtin_msa_binsr_d (v2u64, v2u64, v2u64);

    Immediate Bit Insert Right
        v16u8 __builtin_msa_binsri_b (v16u8, v16u8, imm0_7);
        v8u16 __builtin_msa_binsri_h (v8u16, v8u16, imm0_15);
        v4u32 __builtin_msa_binsri_w (v4u32, v4u32, imm0_31);
        v2u64 __builtin_msa_binsri_d (v2u64, v2u64, imm0_63);
**/
    v_dst = __builtin_msa_binsl_b(v_a, v_b, v_c);
    printf("Vector Bit Insert Left: \n");
    // a: 0000 0001
    // b: 1010 1111
    // c: 0000 1010  -> (10 % 8 + 1) = 3
    // -- copy 3 left bits in b to the left of a, and preserve right bits of a, so
    // dst = 1010 0001 = 161
    // [161 161 161 161 161 161 161 161 161 161 161 161 161 161 161 161]
    dump_u8_vector(v_dst);

    // a: 0000 0001
    // b: 1010 1111
    // imm: 5 % 8 + 1 -> 6
    // dst = 1010 1101 -> 173
    v_dst = __builtin_msa_binsli_b(v_a, v_b, 5);
    printf("Immediate Bit Insert Left: \n");
    dump_u8_vector(v_dst);

        v_dst = __builtin_msa_binsl_b(v_a, v_b, v_c);
    printf("Vector Bit Insert Left: \n");
    // a: 0000 0001
    // b: 1010 1111
    // c: 0000 1010  -> (10 % 8 + 1) = 3
    // -- copy 3 left bits in b to the left of a, and preserve right bits of a, so
    // dst = 1010 0001 = 161
    // [161 161 161 161 161 161 161 161 161 161 161 161 161 161 161 161]
    dump_u8_vector(v_dst);


}




int main() {

    printf("------------------ Bit Operation Tests --------------------------- \n");

    testBitClear();
    testBitInsert();

    return 0;
}

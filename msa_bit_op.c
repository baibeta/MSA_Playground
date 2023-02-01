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


    // a: 0000 0001
    // b: 1010 1111
    // c: 0000 1010  -> (10 % 8 + 1) = 3
    // -- copy 3 right bits in b to the right of a, and preserve left bits of a, so
    // dst = 0000 0111 = 7
    // [7 7 7 7 7 7 7 7 7 7 7 7 7 7 7 7]
    v_dst = __builtin_msa_binsr_b(v_a, v_b, v_c);
    printf("Vector Bit Insert Right: \n");
    dump_u8_vector(v_dst);

    // a: 0000 0001
    // b: 1010 1111
    // imm: 5 % 8 + 1 -> 6
    // dst = 00101111 -> 47
    v_dst = __builtin_msa_binsri_b(v_a, v_b, 5);
    printf("Immediate Bit Insert Right: \n");
    dump_u8_vector(v_dst);
}


void testBitMove() {
    v16u8 v_a, v_b, v_c, v_dst;
    v_a = (v16u8)__builtin_msa_fill_b(1);
    v_b = (v16u8)__builtin_msa_fill_b(175);
    v_c = (v16u8)__builtin_msa_fill_b(10);
    /**
    Vector Bit Move If Not Zero
        v16u8 __builtin_msa_bmnz_v (v16u8, v16u8, v16u8);
    Immediate Bit Move If Not Zero
        v16u8 __builtin_msa_bmnzi_b (v16u8, v16u8, imm0_255);
    Vector Bit Move If Zero
        v16u8 __builtin_msa_bmz_v (v16u8, v16u8, v16u8);
    Immediate Bit Move If Zero
        v16u8 __builtin_msa_bmzi_b (v16u8, v16u8, imm0_255);
    */

    /**
     * Vector Bit Move If Not Zero
     * Copy to destination vector 'a' all bits from source vector 'b'
     * for which the corresponding bits from target vector 'c' are 1
     * and leaves unchanged all destination bits for which the corresponding target bits are 0.
     * */
    // a: 0000 0001
    // b: 1010 1111
    // c: 0000 1010
    // dst = 0000 1011 -> [11]
    v_dst = __builtin_msa_bmnz_v(v_a, v_b, v_c);
    printf("Vector Bit Move If Not Zero: \n");
    dump_u8_vector(v_dst);

    // a: 0000 0001
    // b: 1010 1111
    // imm: 1111 0000
    // dst = 1010 0001 -> [161]
    v_dst = __builtin_msa_bmnzi_b(v_a, v_b, 240);
    printf("Immediate Bit Move If Not Zero: \n");
    dump_u8_vector(v_dst);

    // a: 0000 0001
    // b: 1010 1111
    // c: 0000 1010
    // dst = 1010 0101 -> [165]
    v_dst = __builtin_msa_bmz_v(v_a, v_b, v_c);
    printf("Vector Bit Move If Zero: \n");
    dump_u8_vector(v_dst);

    // a: 0000 0001
    // b: 1010 1111
    // imm: 1111 0000
    // dst = 0000 1111 -> [15]
    v_dst = __builtin_msa_bmzi_b(v_a, v_b, 240);
    printf("Immediate Bit Move If Zero: \n");
    dump_u8_vector(v_dst);

}


void testBitNegtive() {
    v16u8 v_a, v_b, v_dst;
    v_a = (v16u8)__builtin_msa_fill_b(1);
    v_b = (v16u8)__builtin_msa_fill_b(14);

    /**
    Vector Bit Negate
        v16u8 __builtin_msa_bneg_b (v16u8, v16u8);
        v8u16 __builtin_msa_bneg_h (v8u16, v8u16);
        v4u32 __builtin_msa_bneg_w (v4u32, v4u32);
        v2u64 __builtin_msa_bneg_d (v2u64, v2u64);
    Immediate Bit Negate
        v16u8 __builtin_msa_bnegi_b (v16u8, imm0_7);
        v8u16 __builtin_msa_bnegi_h (v8u16, imm0_15);
        v4u32 __builtin_msa_bnegi_w (v4u32, imm0_31);
        v2u64 __builtin_msa_bnegi_d (v2u64, imm0_63);
    */

    // Negate (complement) one bit in each element of vector a
    // The bit position is given by the elements in vector 'b'modulo the size of the element in bits.
    // a: 0000 0001   -> position [7, 6, 5, 4, 3, 2, 1, 0]
    // b: 14 --------> 14 % 8 = 6 ----↑
    // dst = 0100 0001 => [65]
    v_dst = __builtin_msa_bneg_b(v_a, v_b);
    printf("Vector Bit Negate: \n");
    dump_u8_vector(v_dst);

    // imm range [0,7]
    v_dst = __builtin_msa_bnegi_b(v_a, 6);
    printf("Immediate Bit Negate: \n");
    dump_u8_vector(v_dst);
}


void testBitSelect() {
    v16u8 v_a, v_b, v_c, v_dst;
    v_a = (v16u8)__builtin_msa_fill_b(170);
    v_b = (v16u8)__builtin_msa_fill_b(255);
    v_c = (v16u8)__builtin_msa_fill_b(0);
    /**
    Vector Bit Select
        v16u8 __builtin_msa_bsel_v (v16u8, v16u8, v16u8);
    Immediate Bit Select
        v16u8 __builtin_msa_bseli_b (v16u8, v16u8, imm0_255);
    */

    // Selectively copy bits from the source vectors 'b' and 'c'
    // into destination vector 'a' based on the corresponding bit in a:
    // if 0 copies the bit from 'b', if 1 copies the bit from 'c'.
    //   a: 1010 1010
    //   b: 1111 1111
    //   c: 0000 0000
    //   dst => 0101 0101 => [85]
    v_dst = __builtin_msa_bsel_v(v_a, v_b, v_c);
    printf("Vector Bit Select: \n");
    dump_u8_vector(v_dst);

    // based on the corresponding bit in a:
    // if 0 copies the bit from 'b', if 1 copies the bit from 'imm'.
    //   a: 1010 1010
    //   b: 1111 1111
    //   c: 0000 1111
    //   dst => 0101 1111 => [95]
    v_dst = __builtin_msa_bseli_b(v_a, v_b, 15);
    printf("Immediate Bit Select: \n");
    dump_u8_vector(v_dst);
}


void testBitSet() {
    v16u8 v_a, v_b, v_dst;
    v_a = (v16u8)__builtin_msa_fill_b(170);
    v_b = (v16u8)__builtin_msa_fill_b(6);
    /**
    Vector Bit Set
        v16u8 __builtin_msa_bset_b (v16u8, v16u8);
        v8u16 __builtin_msa_bset_h (v8u16, v8u16);
        v4u32 __builtin_msa_bset_w (v4u32, v4u32);
        v2u64 __builtin_msa_bset_d (v2u64, v2u64);
    Immediate Bit Set
        v16u8 __builtin_msa_bseti_b (v16u8, imm0_7);
        v8u16 __builtin_msa_bseti_h (v8u16, imm0_15);
        v4u32 __builtin_msa_bseti_w (v4u32, imm0_31);
        v2u64 __builtin_msa_bseti_d (v2u64, imm0_63);
    */

    // Set to 1 one bit in each element of vector 'a', the bit position
    // is given by the elements in vector 'b' modulo the size of the element in bits.
    //   a: 1010 1010
    //   b: 6 % 8 => 6
    //   dst => 1110 1010 => [234]
    v_dst = __builtin_msa_bset_b(v_a, v_b);
    printf("Vector Bit Select: \n");
    dump_u8_vector(v_dst);

    // The bit position is given by immediate imm3 [0,7].
    v_dst = __builtin_msa_bseti_b(v_a, 6);
    printf("Immediate Bit Select: \n");
    dump_u8_vector(v_dst);
}



int main() {
    printf("------------------ Bit Operation Tests --------------------------- \n");

    testBitClear();
    testBitInsert();
    testBitMove();
    testBitNegtive();
    testBitSelect();
    testBitSet();

    return 0;
}

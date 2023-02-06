/**
 * MIPS SIMD Architecture(MSA)
 *  Other
 *  related MSA intrinsics demo codes
 */
#include <msa.h>
#include "utils.c"

const int a[4] = {1,2,3,4};
const int b[4] = {5,6,7,8};

void testInterleave() {
    v4i32 v_a = __builtin_msa_ld_w((void*)a, 0);
    v4i32 v_b = __builtin_msa_ld_w((void*)b, 0);

    /**
    Vector Interleave Even
        v16i8 __builtin_msa_ilvev_b (v16i8, v16i8);
        v8i16 __builtin_msa_ilvev_h (v8i16, v8i16);
        v4i32 __builtin_msa_ilvev_w (v4i32, v4i32);
        v2i64 __builtin_msa_ilvev_d (v2i64, v2i64);
    Vector Interleave Left
        v16i8 __builtin_msa_ilvl_b (v16i8, v16i8);
        v8i16 __builtin_msa_ilvl_h (v8i16, v8i16);
        v4i32 __builtin_msa_ilvl_w (v4i32, v4i32);
        v2i64 __builtin_msa_ilvl_d (v2i64, v2i64);
    Vector Interleave Odd
        v16i8 __builtin_msa_ilvod_b (v16i8, v16i8);
        v8i16 __builtin_msa_ilvod_h (v8i16, v8i16);
        v4i32 __builtin_msa_ilvod_w (v4i32, v4i32);
        v2i64 __builtin_msa_ilvod_d (v2i64, v2i64);
    Vector Interleave Right
        v16i8 __builtin_msa_ilvr_b (v16i8, v16i8);
        v8i16 __builtin_msa_ilvr_h (v8i16, v8i16);
        v4i32 __builtin_msa_ilvr_w (v4i32, v4i32);
        v2i64 __builtin_msa_ilvr_d (v2i64, v2i64);
    */

    // Interleave Even returns:
    // b[0] ... a[0] ... b[0 + 2] ... a[0 + 2]
    printf("Vector Interleave Even: \n");
    dump_i32_vector(__builtin_msa_ilvev_w(v_a, v_b));

    // Interleave Odd returns:
    // b[0 + 1] ... a[0 + 1] ... b[0 + 3] ... a[0 + 3]
    printf("Vector Interleave Odd: \n");
    dump_i32_vector(__builtin_msa_ilvod_w(v_a, v_b));

    // Interleave Left returns:
    // b[2] ... a[2] ... b[3] ... a[3]
    printf("Vector Interleave Left: \n");
    dump_i32_vector(__builtin_msa_ilvl_w(v_a, v_b));

    // Interleave Right returns:
    // b[0] ... a[0] ... b[1] ... a[1]
    printf("Vector Interleave Right: \n");
    dump_i32_vector(__builtin_msa_ilvr_w(v_a, v_b));
}


void testInsert() {
    v4i32 v_a = __builtin_msa_ld_w((void*)a, 0);
    v4i32 v_b = __builtin_msa_ld_w((void*)b, 0);

    /**
    GPR Insert Element
        v16i8 __builtin_msa_insert_b (v16i8, imm0_15, i32);
        v8i16 __builtin_msa_insert_h (v8i16, imm0_7, i32);
        v4i32 __builtin_msa_insert_w (v4i32, imm0_3, i32);
        v2i64 __builtin_msa_insert_d (v2i64, imm0_1, i64);
    Element Insert Element
        v16i8 __builtin_msa_insve_b (v16i8, imm0_15, v16i8);
        v8i16 __builtin_msa_insve_h (v8i16, imm0_7, v8i16);
        v4i32 __builtin_msa_insve_w (v4i32, imm0_3, v4i32);
        v2i64 __builtin_msa_insve_d (v2i64, imm0_1, v2i64);
    */

    // [vecter, index, insert_value]
    printf("GPR Insert Element: \n");
    dump_i32_vector(__builtin_msa_insert_w(v_a, 2, 33));

    // [vecter, index, v_b[0]]
    printf("Element Insert Element: \n");
    dump_i32_vector(__builtin_msa_insve_w(v_a, 2, v_b));
}


void testMinMax() {
    /**
    Vector Maximum Based on Absolute Values
        v16i8 __builtin_msa_max_a_b (v16i8, v16i8);
        v8i16 __builtin_msa_max_a_h (v8i16, v8i16);
        v4i32 __builtin_msa_max_a_w (v4i32, v4i32);
        v2i64 __builtin_msa_max_a_d (v2i64, v2i64);
    Vector Minimum Based on Absolute Value
        v16i8 __builtin_msa_min_a_b (v16i8, v16i8);
        v8i16 __builtin_msa_min_a_h (v8i16, v8i16);
        v4i32 __builtin_msa_min_a_w (v4i32, v4i32);
        v2i64 __builtin_msa_min_a_d (v2i64, v2i64);
    Vector Signed Maximum
        v16i8 __builtin_msa_max_s_b (v16i8, v16i8);
        v8i16 __builtin_msa_max_s_h (v8i16, v8i16);
        v4i32 __builtin_msa_max_s_w (v4i32, v4i32);
        v2i64 __builtin_msa_max_s_d (v2i64, v2i64);
    Vector Signed Minimum
        v16i8 __builtin_msa_min_s_b (v16i8, v16i8);
        v8i16 __builtin_msa_min_s_h (v8i16, v8i16);
        v4i32 __builtin_msa_min_s_w (v4i32, v4i32);
        v2i64 __builtin_msa_min_s_d (v2i64, v2i64);
    Vector Unsigned Maximum
        v16u8 __builtin_msa_max_u_b (v16u8, v16u8);
        v8u16 __builtin_msa_max_u_h (v8u16, v8u16);
        v4u32 __builtin_msa_max_u_w (v4u32, v4u32);
        v2u64 __builtin_msa_max_u_d (v2u64, v2u64);
    Vector Unsigned Minimum
        v16i8 __builtin_msa_min_u_b (v16i8, v16i8);
        v8i16 __builtin_msa_min_u_h (v8i16, v8i16);
        v4i32 __builtin_msa_min_u_w (v4i32, v4i32);
        v2i64 __builtin_msa_min_u_d (v2i64, v2i64);
    Immediate Signed Maximum
        v16i8 __builtin_msa_maxi_s_b (v16i8, imm_n16_15);
        v8i16 __builtin_msa_maxi_s_h (v8i16, imm_n16_15);
        v4i32 __builtin_msa_maxi_s_w (v4i32, imm_n16_15);
        v2i64 __builtin_msa_maxi_s_d (v2i64, imm_n16_15);
    Immediate Unsigned Maximum
        v16u8 __builtin_msa_maxi_u_b (v16u8, imm0_31);
        v8u16 __builtin_msa_maxi_u_h (v8u16, imm0_31);
        v4u32 __builtin_msa_maxi_u_w (v4u32, imm0_31);
        v2u64 __builtin_msa_maxi_u_d (v2u64, imm0_31);
    Immediate Signed Minimum
        v16i8 __builtin_msa_mini_s_b (v16i8, imm_n16_15);
        v8i16 __builtin_msa_mini_s_h (v8i16, imm_n16_15);
        v4i32 __builtin_msa_mini_s_w (v4i32, imm_n16_15);
        v2i64 __builtin_msa_mini_s_d (v2i64, imm_n16_15);
    Immediate Unsigned Minimum
        v16u8 __builtin_msa_mini_u_b (v16u8, imm0_31);
        v8u16 __builtin_msa_mini_u_h (v8u16, imm0_31);
        v4u32 __builtin_msa_mini_u_w (v4u32, imm0_31);
        v2u64 __builtin_msa_mini_u_d (v2u64, imm0_31);
    */
    v4i32 v_a = __builtin_msa_ld_w((void*)a, 0);
    v4i32 v_b = __builtin_msa_ld_w((void*)b, 0);
    printf("Vector Maximum Based on Absolute Values: \n");
    dump_i32_vector(__builtin_msa_max_a_w(v_a, v_b));
    printf("Immediate Signed Minimum: \n");
    dump_i32_vector(__builtin_msa_mini_s_w(v_b, 6));
}


void testLeadingCount() {
    /**
    Vector Leading Ones Count
        v16i8 __builtin_msa_nloc_b (v16i8);
        v8i16 __builtin_msa_nloc_h (v8i16);
        v4i32 __builtin_msa_nloc_w (v4i32);
        v2i64 __builtin_msa_nloc_d (v2i64);
    Vector Leading Zeros Count
        v16i8 __builtin_msa_nlzc_b (v16i8);
        v8i16 __builtin_msa_nlzc_h (v8i16);
        v4i32 __builtin_msa_nlzc_w (v4i32);
        v2i64 __builtin_msa_nlzc_d (v2i64);
    */
    v4i32 v_a = __builtin_msa_ld_w((void*)a, 0);
    printf("Vector Leading Ones Count: \n");
    dump_i32_vector(__builtin_msa_nloc_w(v_a));
    dump_i32_vector(__builtin_msa_nloc_w(__builtin_msa_fill_w(-1)));

    printf("Vector Leading Zeros Count: \n");
    dump_i32_vector(__builtin_msa_nlzc_w(v_a));


}



int main() {
    printf("------------------ All Other MSA Tests ------------------------ \n");

    testInterleave();
    testInsert();
    testMinMax();
    testLeadingCount();

    return 0;
}

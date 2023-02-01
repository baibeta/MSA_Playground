/**
 * MIPS SIMD Architecture(MSA)
 *  Compare
 *  related MSA intrinsics demo codes
 */
#include <msa.h>
#include "utils.c"


void testFixPointCompare() {
    __int8_t a[17] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};
    __int8_t b[17] = {0,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};
    v16i8 v_a = __builtin_msa_ld_b((void*)a, 0);
    v16i8 v_b = __builtin_msa_ld_b((void*)b, 0);

    v16i8 v_c = __builtin_msa_ld_b((void*)a, 1);
    v16i8 v_d = __builtin_msa_ld_b((void*)b, 1);


    /* Vector Compare Equal
        v16i8 __builtin_msa_ceq_b (v16i8, v16i8);
        v8i16 __builtin_msa_ceq_h (v8i16, v8i16);
        v4i32 __builtin_msa_ceq_w (v4i32, v4i32);
        v2i64 __builtin_msa_ceq_d (v2i64, v2i64);
    */

    // Set all bits to 1 in vector elements if the corresponding 'a' and 'b'
    // elements are equal, otherwise set all bits to 0.
    printf("Vector Compare Equal: \n");
    // [0 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255]
    dump_u8_vector((v16u8)__builtin_msa_ceq_b(v_a, v_b));
    // [255 255 255 255 255 255 255 255 255 255 255 255 255 255 255 255]
    dump_u8_vector((v16u8)__builtin_msa_ceq_b(v_c, v_d));

    /* Immediate Compare Equal
        v16i8 __builtin_msa_ceqi_b (v16i8, imm_n16_15);
        v8i16 __builtin_msa_ceqi_h (v8i16, imm_n16_15);
        v4i32 __builtin_msa_ceqi_w (v4i32, imm_n16_15);
        v2i64 __builtin_msa_ceqi_d (v2i64, imm_n16_15);
    */
    printf("Immediate Compare Equal: \n");
    // [0 255 0 0 0 0 0 0 0 0 0 0 0 0 0 0]
    dump_u8_vector((v16u8)__builtin_msa_ceqi_b(v_a, 2));
    // [255 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0]
    dump_u8_vector((v16u8)__builtin_msa_ceqi_b(v_c, 2));


    /**
      Vector Compare Signed Less Than or Equal
        v16i8 __builtin_msa_cle_s_b (v16i8, v16i8);
        v8i16 __builtin_msa_cle_s_h (v8i16, v8i16);
        v4i32 __builtin_msa_cle_s_w (v4i32, v4i32);
        v2i64 __builtin_msa_cle_s_d (v2i64, v2i64);
      Vector Compare Unsigned Less Than or Equal
        v16i8 __builtin_msa_cle_u_b (v16u8, v16u8);
        v8i16 __builtin_msa_cle_u_h (v8u16, v8u16);
        v4i32 __builtin_msa_cle_u_w (v4u32, v4u32);
        v2i64 __builtin_msa_cle_u_d (v2u64, v2u64);
    */
    printf("Vector Compare Signed Less Than or Equal: \n");
    // [255 255 255 255 255 255 255 255 255 0 0 0 0 0 0 0]
    dump_u8_vector((v16u8)__builtin_msa_cle_s_b(v_a, __builtin_msa_fill_b(9)));
    printf("Vector Compare Unsigned Less Than or Equal: \n");
    // [255 255 255 255 255 255 255 255 255 0 0 0 0 0 0 0]
    dump_u8_vector((v16u8)__builtin_msa_cle_u_b((v16u8)v_a, (v16u8)__builtin_msa_fill_b(9)));


    /**
      Immediate Compare Signed Less Than or Equal
        v16i8 __builtin_msa_clei_s_b (v16i8, imm_n16_15);
        v8i16 __builtin_msa_clei_s_h (v8i16, imm_n16_15);
        v4i32 __builtin_msa_clei_s_w (v4i32, imm_n16_15);
        v2i64 __builtin_msa_clei_s_d (v2i64, imm_n16_15);
      Immediate Compare Unsigned Less Than or Equal
        v16i8 __builtin_msa_clei_u_b (v16u8, imm0_31);
        v8i16 __builtin_msa_clei_u_h (v8u16, imm0_31);
        v4i32 __builtin_msa_clei_u_w (v4u32, imm0_31);
        v2i64 __builtin_msa_clei_u_d (v2u64, imm0_31);
    */
    printf("Immediate Compare Signed Less Than or Equal: \n");
    // [255 255 255 255 255 255 255 255 0 0 0 0 0 0 0 0]
    dump_u8_vector((v16u8)__builtin_msa_clei_s_b(v_a, 8));

    /**
     * Vector Compare Signed Less Than
        v16i8 __builtin_msa_clt_s_b (v16i8, v16i8);
        v8i16 __builtin_msa_clt_s_h (v8i16, v8i16);
        v4i32 __builtin_msa_clt_s_w (v4i32, v4i32);
        v2i64 __builtin_msa_clt_s_d (v2i64, v2i64);
       Vector Compare Unsigned Less Than
        v16i8 __builtin_msa_clt_u_b (v16u8, v16u8);
        v8i16 __builtin_msa_clt_u_h (v8u16, v8u16);
        v4i32 __builtin_msa_clt_u_w (v4u32, v4u32);
        v2i64 __builtin_msa_clt_u_d (v2u64, v2u64);
    */
    printf("Vector Compare Signed Less Than: \n");
    // [255 255 255 255 255 255 255 255 0 0 0 0 0 0 0 0]
    dump_u8_vector((v16u8)__builtin_msa_clt_s_b(v_a, __builtin_msa_fill_b(9)));


    /**
     * Immediate Compare Signed Less Than
        v16i8 __builtin_msa_clti_s_b (v16i8, imm_n16_15);
        v8i16 __builtin_msa_clti_s_h (v8i16, imm_n16_15);
        v4i32 __builtin_msa_clti_s_w (v4i32, imm_n16_15);
        v2i64 __builtin_msa_clti_s_d (v2i64, imm_n16_15);
       Immediate Compare Unsigned Less Than
        v16i8 __builtin_msa_clti_u_b (v16u8, imm0_31);
        v8i16 __builtin_msa_clti_u_h (v8u16, imm0_31);
        v4i32 __builtin_msa_clti_u_w (v4u32, imm0_31);
        v2i64 __builtin_msa_clti_u_d (v2u64, imm0_31);
    */
    printf("Immediate Compare Signed Less Than: \n");
    // [255 255 255 255 255 255 255 0 0 0 0 0 0 0 0 0]
    dump_u8_vector((v16u8)__builtin_msa_clti_s_b(v_a, 8));

}


int main() {
    printf("------------------ Compare Operation Tests ----------------------- \n");

    testFixPointCompare();

    return 0;
}

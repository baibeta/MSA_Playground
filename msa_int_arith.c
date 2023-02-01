/**
 * MIPS SIMD Architecture(MSA)
 *  Integer Arithmetic
 *  related MSA intrinsics demo codes
 */
#include <msa.h>
#include "utils.c"

const int src1[] = {1,2,3,4};
const int src2[] = {-1,-2,-3,-4};
const int src_max_int[] = {2147483647, 2147483647, 2147483647, 2147483647};


/** At begining, I write this function to call built-in and dump result
    then I got this error:
    "error: built-in function '__builtin_msa_add_a_w' must be directly called"

void test_builtin_2_in_1_out_v4i32(v4i32 (* builtin_name)(v4i32, v4i32),
    v4i32 v1, v4i32 v2, v4i32 dst) {
        dst = builtin_name(v1, v2);
        dump_i32_vector(dst);
}
**/

void testAdd() {
    v4i32 v_src1, v_src2, v_max, v_dst;
    v_src1 = (v4i32)__builtin_msa_ld_w((void*)src1, 0);
    v_src2 = (v4i32)__builtin_msa_ld_w((void*)src2, 0);
    v_max = (v4i32)__builtin_msa_ld_w((void*)src_max_int, 0);


    /* Vector Add Absolute Values
        v16i8 __builtin_msa_add_a_b (v16i8, v16i8);
        v8i16 __builtin_msa_add_a_h (v8i16, v8i16);
        v4i32 __builtin_msa_add_a_w (v4i32, v4i32);
        v2i64 __builtin_msa_add_a_d (v2i64, v2i64);
    */
    v_dst = __builtin_msa_add_a_w(v_src1, v_src2);
    printf("Vector Add Absolute Values: \n");
    // [2 4 6 8]
    dump_i32_vector(v_dst);

    /* Vector Saturated Add of Absolute Values
        v16i8 __builtin_msa_adds_a_b (v16i8, v16i8);
        v8i16 __builtin_msa_adds_a_h (v8i16, v8i16);
        v4i32 __builtin_msa_adds_a_w (v4i32, v4i32);
        v2i64 __builtin_msa_adds_a_d (v2i64, v2i64);
    */
    v_dst = __builtin_msa_adds_a_w(v_src1, v_max);
    printf("Vector Saturated Add of Absolute Values: \n");
    // [2147483647 2147483647 2147483647 2147483647]
    dump_i32_vector(v_dst);

    /* Vector Signed Saturated Add of Signed Values
        v16i8 __builtin_msa_adds_s_b (v16i8, v16i8);
        v8i16 __builtin_msa_adds_s_h (v8i16, v8i16);
        v4i32 __builtin_msa_adds_s_w (v4i32, v4i32);
        v2i64 __builtin_msa_adds_s_d (v2i64, v2i64);
    */
    v_dst = __builtin_msa_adds_s_w(v_src1, v_src2);
    printf("Vector Signed Saturated Add of Signed Values: \n");
    // [0 0 0 0]
    dump_i32_vector(v_dst);

    /* Vector Unsigned Saturated Add of Unsigned Values
        v16u8 __builtin_msa_adds_u_b (v16u8, v16u8);
        v8u16 __builtin_msa_adds_u_h (v8u16, v8u16);
        v4u32 __builtin_msa_adds_u_w (v4u32, v4u32);
        v2u64 __builtin_msa_adds_u_d (v2u64, v2u64);
    */
    v_dst = (v4i32)__builtin_msa_adds_u_w((v4u32)v_src1, (v4u32)v_src1);
    printf("Vector Unsigned Saturated Add of Unsigned Values: \n");
    // [2 4 6 8]
    dump_i32_vector(v_dst);

    /* Vector Add
        v16i8 __builtin_msa_addv_b (v16i8, v16i8);
        v8i16 __builtin_msa_addv_h (v8i16, v8i16);
        v4i32 __builtin_msa_addv_w (v4i32, v4i32);
        v2i64 __builtin_msa_addv_d (v2i64, v2i64);
    */
    v_dst = __builtin_msa_addv_w(v_src1, v_src2);
    printf("Vector Add: \n");
    // [0 0 0 0]
    dump_i32_vector(v_dst);

    /* Vector Immediate Add
        v16i8 __builtin_msa_addvi_b (v16i8, imm0_31);
        v8i16 __builtin_msa_addvi_h (v8i16, imm0_31);
        v4i32 __builtin_msa_addvi_w (v4i32, imm0_31);
        v2i64 __builtin_msa_addvi_d (v2i64, imm0_31);
    */
    v_dst = __builtin_msa_addvi_w(v_src1, 1);
    printf("Vector Immediate Add: \n");
    // [2 3 4 5]
    dump_i32_vector(v_dst);

}


void testSubtract() {
    v4i32 v_src1, v_src2, v_dst;
    v_src1 = (v4i32)__builtin_msa_ld_w((void*)src1, 0);
    v_src2 = (v4i32)__builtin_msa_ld_w((void*)src2, 0);

    /* Vector Absolute Values of Signed Subtract
        v16i8 __builtin_msa_asub_s_b (v16i8, v16i8);
        v8i16 __builtin_msa_asub_s_h (v8i16, v8i16);
        v4i32 __builtin_msa_asub_s_w (v4i32, v4i32);
        v2i64 __builtin_msa_asub_s_d (v2i64, v2i64);
    */
    v_dst = __builtin_msa_asub_s_w(v_src1, v_src2);
    printf("Vector Absolute Values of Signed Subtract\n");
    // v_dst = |v_src1 - v_src2|
    // [2 4 6 8]
    dump_i32_vector(v_dst);

    /* Vector Absolute Values of Unsigned Subtract
        v16u8 __builtin_msa_asub_u_b (v16u8, v16u8);
        v8u16 __builtin_msa_asub_u_h (v8u16, v8u16);
        v4u32 __builtin_msa_asub_u_w (v4u32, v4u32);
        v2u64 __builtin_msa_asub_u_d (v2u64, v2u64);
    */
    v_dst = (v4i32)__builtin_msa_asub_u_w((v4u32)v_src1, (v4u32)v_src2);
    printf("Vector Absolute Values of Unsigned Subtract\n");
    // [-2 -4 -6 -8]
    dump_i32_vector(v_dst);

}


void testAverage() {
    v4i32 v_src1, v_src2, v_dst;
    v_src1 = (v4i32)__builtin_msa_ld_w((void*)src1, 0);
    v_src2 = (v4i32)__builtin_msa_ld_w((void*)src2, 0);

    /* Vector Signed Average
        v16i8 __builtin_msa_ave_s_b (v16i8, v16i8);
        v8i16 __builtin_msa_ave_s_h (v8i16, v8i16);
        v4i32 __builtin_msa_ave_s_w (v4i32, v4i32);
        v2i64 __builtin_msa_ave_s_d (v2i64, v2i64);
    */
    v_dst = __builtin_msa_ave_s_w(v_src1, v_src2);
    printf("Vector Signed Average\n");
    // [0 0 0 0]
    dump_i32_vector(v_dst);

    
    /* Vector Unsigned Average
        v16u8 __builtin_msa_ave_u_b (v16u8, v16u8);
        v8u16 __builtin_msa_ave_u_h (v8u16, v8u16);
        v4u32 __builtin_msa_ave_u_w (v4u32, v4u32);
        v2u64 __builtin_msa_ave_u_d (v2u64, v2u64);
    */
    // TODO

    /* Vector Signed Average Rounded
        v16i8 __builtin_msa_aver_s_b (v16i8, v16i8);
        v8i16 __builtin_msa_aver_s_h (v8i16, v8i16);
        v4i32 __builtin_msa_aver_s_w (v4i32, v4i32);
        v2i64 __builtin_msa_aver_s_d (v2i64, v2i64);
    */
    // round((a+b)/2)
    v_dst = __builtin_msa_aver_s_w(v_src1, __builtin_msa_fill_w(1));
    printf("Vector Signed Average Rounded\n");
    // [0 0 0 0]
    dump_i32_vector(v_dst);


    /* Vector Unsigned  Average Rounded
        v16u8 __builtin_msa_aver_u_b (v16u8, v16u8);
        v8u16 __builtin_msa_aver_u_h (v8u16, v8u16);
        v4u32 __builtin_msa_aver_u_w (v4u32, v4u32);
        v2u64 __builtin_msa_aver_u_d (v2u64, v2u64);
    */
    // TODO 

}

int main() {
    printf("------------------ Integer Arithmetic Tests ---------------------- \n");

    testAdd();
    testSubtract();
    testAverage();

    return 0;
}

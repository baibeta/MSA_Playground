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
       Vector Unsigned Average
        v16u8 __builtin_msa_ave_u_b (v16u8, v16u8);
        v8u16 __builtin_msa_ave_u_h (v8u16, v8u16);
        v4u32 __builtin_msa_ave_u_w (v4u32, v4u32);
        v2u64 __builtin_msa_ave_u_d (v2u64, v2u64);
    */
    v_dst = __builtin_msa_ave_s_w(v_src1, v_src2);
    printf("Vector Signed Average\n");
    // [0 0 0 0]
    dump_i32_vector(v_dst);

    /* Vector Signed Average Rounded
        v16i8 __builtin_msa_aver_s_b (v16i8, v16i8);
        v8i16 __builtin_msa_aver_s_h (v8i16, v8i16);
        v4i32 __builtin_msa_aver_s_w (v4i32, v4i32);
        v2i64 __builtin_msa_aver_s_d (v2i64, v2i64);
       Vector Unsigned Average Rounded
        v16u8 __builtin_msa_aver_u_b (v16u8, v16u8);
        v8u16 __builtin_msa_aver_u_h (v8u16, v8u16);
        v4u32 __builtin_msa_aver_u_w (v4u32, v4u32);
        v2u64 __builtin_msa_aver_u_d (v2u64, v2u64);
    */
    // round((a+b)/2)
    v_dst = __builtin_msa_aver_s_w(v_src1, __builtin_msa_fill_w(1));
    printf("Vector Signed Average Rounded\n");
    // [0 0 0 0]
    dump_i32_vector(v_dst);
}


void testDivide() {
    __int8_t a[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    __int8_t b[16] = {16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1};
    v16i8 v_a, v_b, v_dst;
    v_a = __builtin_msa_ld_b((void*)a, 0);
    v_b = __builtin_msa_ld_b((void*)b, 0);

    /* Vector Signed Divide
        v16i8 __builtin_msa_div_s_b (v16i8, v16i8);
        v8i16 __builtin_msa_div_s_h (v8i16, v8i16);
        v4i32 __builtin_msa_div_s_w (v4i32, v4i32);
        v2i64 __builtin_msa_div_s_d (v2i64, v2i64);
      Vector Unsigned Divide
        v16u8 __builtin_msa_div_u_b (v16u8, v16u8);
        v8u16 __builtin_msa_div_u_h (v8u16, v8u16);
        v4u32 __builtin_msa_div_u_w (v4u32, v4u32);
        v2u64 __builtin_msa_div_u_d (v2u64, v2u64);
    */

    // The signed integer elements in vector 'a'
    //  are divided by signed integer elements in vector 'b'

    v_dst = __builtin_msa_div_s_b(v_a, v_b);
    printf("Vector Signed Divide\n");
    // [0 0 0 0 0 0 0 0 1 1 1 2 3 4 7 16]
    dump_u8_vector((v16u8)v_dst);
}

void testDotProduct() {
    short a[8] = {1,2,3,4,5,6,7,8};
    short b[8] = {1,2,3,1,2,3,1,2};
    v8i16 v_a, v_b;
    v4i32 v_c, v_dst;
    v_a = __builtin_msa_ld_h((void*)a, 0);
    v_b = __builtin_msa_ld_h((void*)b, 0);
    v_c = __builtin_msa_fill_w(3);

    /* Vector Signed Dot Product
        v8i16 __builtin_msa_dotp_s_h (v16i8, v16i8);
        v4i32 __builtin_msa_dotp_s_w (v8i16, v8i16);
        v2i64 __builtin_msa_dotp_s_d (v4i32, v4i32);
       Vector Unsigned Dot Product
        v8u16 __builtin_msa_dotp_u_h (v16u8, v16u8);
        v4u32 __builtin_msa_dotp_u_w (v8u16, v8u16);
        v2u64 __builtin_msa_dotp_u_d (v4u32, v4u32);
    */
    // a : 1,2,3,4,5,6,7,8,9
    // b ：9,8,7,6,5,4,3,2,1
    // dst = [1*1 + 2*2], [3*3 + 4*1], [5*2 + 6*3], [7*1 + 8*2]
    //     = [5, 13, 28, 23]
    v_dst = __builtin_msa_dotp_s_w(v_a, v_b);
    printf("Vector Signed Dot Product\n");
    dump_i32_vector(v_dst);

    /* Vector Signed Dot Product and Add
        v8i16 __builtin_msa_dpadd_s_h (v8i16, v16i8, v16i8);
        v4i32 __builtin_msa_dpadd_s_w (v4i32, v8i16, v8i16);
        v2i64 __builtin_msa_dpadd_s_d (v2i64, v4i32, v4i32);
       Vector Unsigned Dot Product and Add
        v8u16 __builtin_msa_dpadd_u_h (v8u16, v16u8, v16u8);
        v4u32 __builtin_msa_dpadd_u_w (v4u32, v8u16, v8u16);
        v2u64 __builtin_msa_dpadd_u_d (v2u64, v4u32, v4u32);
    */
    // a : 1,2,3,4,5,6,7,8,9
    // b ：9,8,7,6,5,4,3,2,1
    // dst = [1*1 + 2*2]+3, [3*3 + 4*1]+3 , [5*2 + 6*3]+3, [7*1 + 8*2]+3
    //     = [8 16 31 26]
    v_dst = __builtin_msa_dpadd_s_w(v_c, v_a, v_b);
    printf("Vector Signed Dot Product and Add\n");
    dump_i32_vector(v_dst);

    /* Vector Signed Dot Product and Subtract
        v8i16 __builtin_msa_dpsub_s_h (v8i16, v16i8, v16i8);
        v4i32 __builtin_msa_dpsub_s_w (v4i32, v8i16, v8i16);
        v2i64 __builtin_msa_dpsub_s_d (v2i64, v4i32, v4i32);
       Vector Unsigned Dot Product and Subtract
        v8i16 __builtin_msa_dpsub_u_h (v8i16, v16u8, v16u8);
        v4i32 __builtin_msa_dpsub_u_w (v4i32, v8u16, v8u16);
        v2i64 __builtin_msa_dpsub_u_d (v2i64, v4u32, v4u32);
    */
    // a : 1,2,3,4,5,6,7,8,9
    // b ：9,8,7,6,5,4,3,2,1
    // dst = 3-[1*1 + 2*2]， 3-[3*3 + 4*1], 3-[5*2 + 6*3], 3-[7*1 + 8*2]
    //     = [-2 -10 -25 -20]
    v_dst = __builtin_msa_dpsub_s_w(v_c, v_a, v_b);
    printf("Vector Signed Dot Product and Subtract\n");
    dump_i32_vector(v_dst);
}


int main() {
    printf("------------------ Integer Arithmetic Tests ---------------------- \n");

    testAdd();
    testSubtract();
    testAverage();
    testDivide();
    testDotProduct();

    return 0;
}

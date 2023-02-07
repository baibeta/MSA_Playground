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


    /* Vector Subtract
        v16i8 __builtin_msa_subv_b (v16i8, v16i8);
        v8i16 __builtin_msa_subv_h (v8i16, v8i16);
        v4i32 __builtin_msa_subv_w (v4i32, v4i32);
        v2i64 __builtin_msa_subv_d (v2i64, v2i64);
       Immediate Subtract
        v16i8 __builtin_msa_subvi_b (v16i8, imm0_31);
        v8i16 __builtin_msa_subvi_h (v8i16, imm0_31);
        v4i32 __builtin_msa_subvi_w (v4i32, imm0_31);
        v2i64 __builtin_msa_subvi_d (v2i64, imm0_31);
    */
    printf("Vector Subtract\n");
    // v_dst = v_src1 - v_src2
    // [2 4 6 8]
    dump_i32_vector(__builtin_msa_subv_w(v_src1, v_src2));

    printf("Immediate Subtract\n");
    // v_dst = v_src1 - imm
    // [-1 0 1 2]
    dump_i32_vector(__builtin_msa_subvi_w(v_src1, 2));

    // subv is not saturate
    // 2147483647 - (-1) = sat (2147483647)
    // not sat = (-2147483648)
    v4i32 v_max = (v4i32)__builtin_msa_ld_w((void*)src_max_int, 0);
    dump_i32_vector(__builtin_msa_subv_w(v_max, v_src2));

    /* Vector Signed Saturated Subtract of Signed Values
        v16i8 __builtin_msa_subs_s_b (v16i8, v16i8);
        v8i16 __builtin_msa_subs_s_h (v8i16, v8i16);
        v4i32 __builtin_msa_subs_s_w (v4i32, v4i32);
        v2i64 __builtin_msa_subs_s_d (v2i64, v2i64);
       Vector Unsigned Saturated Subtract of Unsigned Values
        v16u8 __builtin_msa_subs_u_b (v16u8, v16u8);
        v8u16 __builtin_msa_subs_u_h (v8u16, v8u16);
        v4u32 __builtin_msa_subs_u_w (v4u32, v4u32);
        v2u64 __builtin_msa_subs_u_d (v2u64, v2u64);
    */
    // subs is saturate
    // 2147483647 - (-1) = sat (2147483647)
    printf("Vector Signed Saturated Subtract of Signed Values\n");
    dump_i32_vector(__builtin_msa_subs_s_w(v_max, v_src2));


    /* Vector Unsigned Saturated Subtract of Signed Values
        v16u8 __builtin_msa_subsus_u_b (v16u8, v16i8);
        v8u16 __builtin_msa_subsus_u_h (v8u16, v8i16);
        v4u32 __builtin_msa_subsus_u_w (v4u32, v4i32);
        v2u64 __builtin_msa_subsus_u_d (v2u64, v2i64);
       Vector Signed Saturated Subtract of Unsigned Values
        v16i8 __builtin_msa_subsuu_s_b (v16u8, v16u8);
        v8i16 __builtin_msa_subsuu_s_h (v8u16, v8u16);
        v4i32 __builtin_msa_subsuu_s_w (v4u32, v4u32);
        v2i64 __builtin_msa_subsuu_s_d (v2u64, v2u64);
    */
    // unsigned = sat(signed - unsigned)
    printf("Vector Unsigned Saturated Subtract of Signed Values\n");
    dump_u32_vector(__builtin_msa_subsus_u_w((v4u32)v_max, v_src2));
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


void testModulo() {
    __int8_t a[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    __int8_t b[16] = {16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1};
    v16i8 v_a, v_b, v_dst;
    v_a = __builtin_msa_ld_b((void*)a, 0);
    v_b = __builtin_msa_ld_b((void*)b, 0);

    /* Vector Signed Modulo
        v16i8 __builtin_msa_mod_s_b (v16i8, v16i8);
        v8i16 __builtin_msa_mod_s_h (v8i16, v8i16);
        v4i32 __builtin_msa_mod_s_w (v4i32, v4i32);
        v2i64 __builtin_msa_mod_s_d (v2i64, v2i64);
      Vector Unsigned Modulo
        v16u8 __builtin_msa_mod_u_b (v16u8, v16u8);
        v8u16 __builtin_msa_mod_u_h (v8u16, v8u16);
        v4u32 __builtin_msa_mod_u_w (v4u32, v4u32);
        v2u64 __builtin_msa_mod_u_d (v2u64, v2u64);
    */

    // a % b
    v_dst = __builtin_msa_mod_s_b(v_a, v_b);
    printf("Vector Signed Modulo\n");
    // [1 2 3 4 5 6 7 8 1 3 5 2 1 2 1 0]
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


void testHorizontal() {
    short a[8] = {1,2,3,4,5,6,7,8};
    short b[8] = {1,2,3,1,2,3,1,2};
    v8i16 v_a = __builtin_msa_ld_h((void*)a, 0);
    v8i16 v_b = __builtin_msa_ld_h((void*)b, 0);

    /**
    Vector Signed Horizontal Add
        v8i16 __builtin_msa_hadd_s_h (v16i8, v16i8);
        v4i32 __builtin_msa_hadd_s_w (v8i16, v8i16);
        v2i64 __builtin_msa_hadd_s_d (v4i32, v4i32);
    Vector Unsigned Horizontal Add
        v8u16 __builtin_msa_hadd_u_h (v16u8, v16u8);
        v4u32 __builtin_msa_hadd_u_w (v8u16, v8u16);
        v2u64 __builtin_msa_hadd_u_d (v4u32, v4u32);
    Vector Signed Horizontal Subtract
        v8i16 __builtin_msa_hsub_s_h (v16i8, v16i8);
        v4i32 __builtin_msa_hsub_s_w (v8i16, v8i16);
        v2i64 __builtin_msa_hsub_s_d (v4i32, v4i32);
    Vector Unsigned Horizontal Subtract
        v8i16 __builtin_msa_hsub_u_h (v16u8, v16u8);
        v4i32 __builtin_msa_hsub_u_w (v8u16, v8u16);
        v2i64 __builtin_msa_hsub_u_d (v4u32, v4u32);
    */

    // The odd elements in vector 'a' are added to the even elements in vector 'b'
    // producing a result twice the size of the input operands. 
    printf("Vector Signed Horizontal Add: \n");
    dump_i16_vector(v_a);
    dump_i16_vector(v_b);
    printf("a[1] + b[0], a[3] + b[2], a[5] + b[4], a[7] + b[6] =");
    printf(" [%hd %hd %hd %hd] \n", v_a[1] + v_b[0], v_a[3] + v_b[2], v_a[5] + v_b[4], v_a[7] + v_b[6]);
    dump_i32_vector(__builtin_msa_hadd_s_w(v_a, v_b));

    // a[1] - b[0], a[3] - b[2], a[5] - b[4], a[7] - b[6]
    // [1 1 4 7]
    printf("Vector Signed Horizontal Subtract: \n");
    dump_i32_vector(__builtin_msa_hsub_s_w(v_a, v_b));


    printf("Test SUM(v8i16 a, v8i16 b):\n");
    // sum (v8i16 a, v8i16 b) = 51
    // without MSA:
    //    to sum two v8i16 vectors, you need 15 scaler `ADD` ins
    // with MSA:
    //    5 `SIMD` ins + 1 scaler `ADD` ins
    v4i32 sum_1 = __builtin_msa_hadd_s_w(v_a, v_b);
    v4i32 sum_2 = __builtin_msa_hadd_s_w(v_b, v_a);
    v2i64 sum_12 = __builtin_msa_hadd_s_d(sum_1,sum_2);
    v2i64 sum_21 = __builtin_msa_hadd_s_d(sum_2,sum_1);
    v2i64 sum_1221 = __builtin_msa_add_a_d(sum_12, sum_21);
    int64_t sum = sum_1221[0] + sum_1221[1];
    printf("SUM(v_a, v_b) = %"PRId64"\n", sum);
}


void testMul() {
    int a[4] = {1,2,3,4};
    int b[4] = {5,6,7,8};
    v4i32 v_src1 = (v4i32)__builtin_msa_ld_w((void*)a, 0);
    v4i32 v_src2 = (v4i32)__builtin_msa_ld_w((void*)b, 0);
    /**
    Vector Multiply
        v16i8 __builtin_msa_mulv_b (v16i8, v16i8);
        v8i16 __builtin_msa_mulv_h (v8i16, v8i16);
        v4i32 __builtin_msa_mulv_w (v4i32, v4i32);
        v2i64 __builtin_msa_mulv_d (v2i64, v2i64);
    */
    printf("Vector Multiply: \n");
    // [5 12 21 32]
    dump_i32_vector(__builtin_msa_mulv_w(v_src1, v_src2));
}


void testMulAdd() {
    int a[4] = {1,2,3,4};
    int b[4] = {5,6,7,8};
    v4i32 v_src1 = (v4i32)__builtin_msa_ld_w((void*)a, 0);
    v4i32 v_src2 = (v4i32)__builtin_msa_ld_w((void*)b, 0);
    v4i32 v_src3 = (v4i32)__builtin_msa_ldi_w(3);
    /**
    Vector Multiply and Add
        v16i8 __builtin_msa_maddv_b (v16i8, v16i8, v16i8);
        v8i16 __builtin_msa_maddv_h (v8i16, v8i16, v8i16);
        v4i32 __builtin_msa_maddv_w (v4i32, v4i32, v4i32);
        v2i64 __builtin_msa_maddv_d (v2i64, v2i64, v2i64);
    */
    printf("Vector Multiply and Add: \n");
    // v_src3 + v_src2 * v_src1
    // [8 15 24 35]
    dump_i32_vector(__builtin_msa_maddv_w(v_src1, v_src2, v_src3));

    // test saturate
    // if saturate result should be (2147483647)
    // however, result is [-1651507197]
    v4i32 v_src4 = (v4i32)__builtin_msa_fill_w(2000000000);
    dump_i32_vector(__builtin_msa_maddv_w(v_src4, v_src4, v_src3));

    /**
    Vector Multiply and Subtract
        v16i8 __builtin_msa_msubv_b (v16i8, v16i8, v16i8);
        v8i16 __builtin_msa_msubv_h (v8i16, v8i16, v8i16);
        v4i32 __builtin_msa_msubv_w (v4i32, v4i32, v4i32);
        v2i64 __builtin_msa_msubv_d (v2i64, v2i64, v2i64);
    */
    printf("Vector Multiply and Subtract: \n");
    // v_src1 - v_src2 * v_src3
    // [8 15 24 35]
    dump_i32_vector(__builtin_msa_msubv_w(v_src1, v_src2, v_src3));
}


void testFixedPoint() {
    int a[4] = {1,2,3,4};
    int b[4] = {5,6,7,8};
    v4i32 v_src1 = (v4i32)__builtin_msa_ld_w((void*)a, 0);
    v4i32 v_src2 = (v4i32)__builtin_msa_ld_w((void*)b, 0);

    printf("Vector Fixed-Point Multiply: \n");
    /**
    Vector Fixed-Point Multiply
        v8i16 __builtin_msa_mul_q_h (v8i16, v8i16);
        v4i32 __builtin_msa_mul_q_w (v4i32, v4i32);
    Vector Fixed-Point Multiply Rounded
        v8i16 __builtin_msa_mulr_q_h (v8i16, v8i16);
        v4i32 __builtin_msa_mulr_q_w (v4i32, v4i32);
    */

    // a*b = [5 12 21 32]
    // but here is fixed-point, the result need to / 2^31
    // [0 0 0 0]
    dump_i32_vector(__builtin_msa_mul_q_w(v_src1, v_src2));

    float f_a[4] = {0.001, 0.002, 0.003, 0.004};
    int q_a[4] = {0};
    // MSA ...
    for (int i = 0; i < 4; i++) {
        q_a[i] = f_a[i] * 2147483647; // 2^31
    }
    v4i32 v_src_q1 = (v4i32)__builtin_msa_ld_w((void*)q_a, 0);
    //  [2147483 4294967 6442451 8589935]
    dump_i32_vector(v_src_q1);
    // f: 0.001 * 0.001 = 0.000001
    // q: 2147
    // q back to f: 2147 / 2147483647 ~= 0.000001
    // [2147 8589 19327 34359]
    v4i32 q_result = __builtin_msa_mul_q_w(v_src_q1, v_src_q1);
    dump_i32_vector(q_result);
    printf("Convert Fixed-Point result to floating-point: \n");
    dump_f64_vector(__builtin_msa_ffqr_d(q_result));
    dump_f64_vector(__builtin_msa_ffql_d(q_result));

    printf("Vector Fixed-Point Multiply Rounded: \n");
    // The rounding is done by adding 1 to the most significant bit
    // that is going to be discarded prior to shifting left the full
    // multiplication result.
    q_result = __builtin_msa_mulr_q_w(v_src_q1, v_src_q1);
    dump_i32_vector(q_result);
    printf("Convert Fixed-Point result to floating-point: \n");
    dump_f64_vector(__builtin_msa_ffqr_d(q_result));
    dump_f64_vector(__builtin_msa_ffql_d(q_result));

    /**
    Vector Fixed-Point Multiply and Add
        v8i16 __builtin_msa_madd_q_h (v8i16, v8i16, v8i16);
        v4i32 __builtin_msa_madd_q_w (v4i32, v4i32, v4i32);
    Vector Fixed-Point Multiply and Add Rounded
        v8i16 __builtin_msa_maddr_q_h (v8i16, v8i16, v8i16);
        v4i32 __builtin_msa_maddr_q_w (v4i32, v4i32, v4i32);
    */
    // a = saturate(v2*v3 + v1)
    printf("Vector Fixed-Point Multiply and Add: \n");
    // f: 0.001001
    // q: (2147 + 2147483) = 2149630
    // q back to f = 2149630 / 2147483647 ~= 0.001001
    q_result = __builtin_msa_madd_q_w(v_src_q1, v_src_q1, v_src_q1);
    dump_i32_vector(q_result);
    printf("Convert Fixed-Point result to floating-point: \n");
    dump_f64_vector(__builtin_msa_ffqr_d(q_result));
    dump_f64_vector(__builtin_msa_ffql_d(q_result));

    printf("Vector Fixed-Point Multiply and Add Rounded: \n");
    q_result = __builtin_msa_maddr_q_w(v_src_q1, v_src_q1, v_src_q1);
    dump_i32_vector(q_result);
    printf("Convert Fixed-Point result to floating-point: \n");
    dump_f64_vector(__builtin_msa_ffqr_d(q_result));
    dump_f64_vector(__builtin_msa_ffql_d(q_result));

    /**
    Vector Fixed-Point Multiply and Subtract
        v8i16 __builtin_msa_msub_q_h (v8i16, v8i16, v8i16);
        v4i32 __builtin_msa_msub_q_w (v4i32, v4i32, v4i32);
    Vector Fixed-Point Multiply and Subtract Rounded
        v8i16 __builtin_msa_msubr_q_h (v8i16, v8i16, v8i16);
        v4i32 __builtin_msa_msubr_q_w (v4i32, v4i32, v4i32);
    */
    printf("Vector Fixed-Point Multiply and Subtract: \n");
    q_result = __builtin_msa_msub_q_w(v_src_q1, v_src_q1, v_src_q1);
    dump_i32_vector(q_result);
    printf("Convert Fixed-Point result to floating-point: \n");
    dump_f64_vector(__builtin_msa_ffqr_d(q_result));
    dump_f64_vector(__builtin_msa_ffql_d(q_result));

    printf("Vector Fixed-Point Multiply and Subtract Rounded: \n");
    q_result = __builtin_msa_msubr_q_w(v_src_q1, v_src_q1, v_src_q1);
    dump_i32_vector(q_result);
    printf("Convert Fixed-Point result to floating-point: \n");
    dump_f64_vector(__builtin_msa_ffqr_d(q_result));
    dump_f64_vector(__builtin_msa_ffql_d(q_result));

}


void testSaturate() {
    /**
    Immediate Signed Saturate
        v16i8 __builtin_msa_sat_s_b (v16i8, imm0_7);
        v8i16 __builtin_msa_sat_s_h (v8i16, imm0_15);
        v4i32 __builtin_msa_sat_s_w (v4i32, imm0_31);
        v2i64 __builtin_msa_sat_s_d (v2i64, imm0_63);
    Immediate Unsigned Saturate
        v16u8 __builtin_msa_sat_u_b (v16u8, imm0_7);
        v8u16 __builtin_msa_sat_u_h (v8u16, imm0_15);
        v4u32 __builtin_msa_sat_u_w (v4u32, imm0_31);
        v2u64 __builtin_msa_sat_u_d (v2u64, imm0_63);
    */
    v4i32 v_max = __builtin_msa_ld_w((void*)src_max_int, 0);
    printf("Immediate Signed Saturate: \n");
    // saturate vector to imm+1 bits
    // [127 127 127 127]
    dump_i32_vector(__builtin_msa_sat_s_w(v_max, 7));
    // [2147483647 2147483647 2147483647 2147483647]
    dump_i32_vector(__builtin_msa_sat_s_w(v_max, 31));

    printf("Immediate Unsigned Saturate: \n");
    // saturate unsigned vector to imm+1 bits
    // [255 255 255 255]
    dump_u32_vector(__builtin_msa_sat_u_w((v4u32)v_max, 7));
}



int main() {
    printf("------------------ Integer Arithmetic Tests ---------------------- \n");

    testAdd();
    testSubtract();
    testAverage();
    testMul();
    testDivide();
    testModulo();
    testMulAdd();
    testDotProduct();
    testHorizontal();
    testFixedPoint();
    testSaturate();

    return 0;
}

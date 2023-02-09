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


void testCount() {
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

    /**
    Vector Population Count
        v16i8 __builtin_msa_pcnt_b (v16i8);
        v8i16 __builtin_msa_pcnt_h (v8i16);
        v4i32 __builtin_msa_pcnt_w (v4i32);
        v2i64 __builtin_msa_pcnt_d (v2i64);
    */
    // counting number of "1"
    printf("Vector Population Count: \n");
    // a = [1,2,3,4] = 00000001, 00000010, 00000011, 00000100
    // pcnt(a) = [1,1,2,1]
    dump_i32_vector(__builtin_msa_pcnt_w(v_a));
    // b = [5,6,7,8] = 0101, 0110, 0111, 1000
    // pcnt(b) = [2,2,3,1]
    dump_i32_vector(__builtin_msa_pcnt_w(__builtin_msa_ld_w((void*)b, 0)));
}


void testPack() {
    /**
    Vector Pack Even
        v16i8 __builtin_msa_pckev_b (v16i8, v16i8);
        v8i16 __builtin_msa_pckev_h (v8i16, v8i16);
        v4i32 __builtin_msa_pckev_w (v4i32, v4i32);
        v2i64 __builtin_msa_pckev_d (v2i64, v2i64);
    Vector Pack Odd
        v16i8 __builtin_msa_pckod_b (v16i8, v16i8);
        v8i16 __builtin_msa_pckod_h (v8i16, v8i16);
        v4i32 __builtin_msa_pckod_w (v4i32, v4i32);
        v2i64 __builtin_msa_pckod_d (v2i64, v2i64);
    */
    // a = [1,2,3,4]
    // b = [5,6,7,8]
    // pack even = b[0] b[2] a[0] a[2]
    // pack odd  = b[1] b[3] a[1] a[3]
    v4i32 v_a = __builtin_msa_ld_w((void*)a, 0);
    v4i32 v_b = __builtin_msa_ld_w((void*)b, 0);

    printf("Vector Pack Even: \n");
    dump_i32_vector(__builtin_msa_pckev_w(v_a, v_b));

    printf("Vector Pack Odd: \n");
    dump_i32_vector(__builtin_msa_pckod_w(v_a, v_b));


    printf("Pack two vectors into one: \n");
    // Try pack a(v4i32) and b(v4i32) into one vector(v8i16),
    //  watch out a and b should be less than i16_max.
    // Firstly convert a(v4i32) to a(v8i16), so the leading zero of a will be treat as odd elements,
    //  then we can use pack even.
    v8i16 v_dst = __builtin_msa_pckev_h((v8i16)v_b, (v8i16)v_a);
    // [1 2 3 4 5 6 7 8]
    dump_i16_vector(v_dst);
}


void testElement() {
    /**
    GPR Element Splat
        v16i8 __builtin_msa_splat_b (v16i8, i32);
        v8i16 __builtin_msa_splat_h (v8i16, i32);
        v4i32 __builtin_msa_splat_w (v4i32, i32);
        v2i64 __builtin_msa_splat_d (v2i64, i32);
    Immediate Element Splat
        v16i8 __builtin_msa_splati_b (v16i8, imm0_15);
        v8i16 __builtin_msa_splati_h (v8i16, imm0_7);
        v4i32 __builtin_msa_splati_w (v4i32, imm0_3);
        v2i64 __builtin_msa_splati_d (v2i64, imm0_1);
    */
    // a = [1,2,3,4]
    v4i32 v_1 = __builtin_msa_ld_w((void*)a, 0);
    v4i32 v_2 = __builtin_msa_ld_w((void*)b, 0);
    printf("GPR Element Splat: \n");
    // splat v_1[i32 % 32] to output vector
    // [2 2 2 2]
    dump_i32_vector(__builtin_msa_splat_w(v_1,1));
    dump_i32_vector(__builtin_msa_splat_w(v_1,33));
    printf("Immediate Element Splat: \n");
    // splat v_1[imm] to output vector
    // [2 2 2 2]
    dump_i32_vector(__builtin_msa_splati_w(v_1,1));

    /**
    Immediate Set Shuffle Elements
        v16i8 __builtin_msa_shf_b (v16i8, imm0_255);
        v8i16 __builtin_msa_shf_h (v8i16, imm0_255);
        v4i32 __builtin_msa_shf_w (v4i32, imm0_255);
    */
    __int8_t i8[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    v16i8 v_a = __builtin_msa_ld_b((void*)i8, 0);
    printf("Immediate Set Shuffle Elements: \n");
    // shuffle each 4-elements
    // imm(0-255) control the element to copy
    //
    // imm = 1 = 00 00 00 01 -> a[1], a[0], a[0], a[0]
    // -- [2 1 1 1 6 5 5 5 10 9 9 9 14 13 13 13]
    dump_i8_vector(__builtin_msa_shf_b(v_a,1));
    // imm = 7 = 00 00 01 11 -> a[3], a[1], a[0], a[0]
    // -- [4 2 1 1 8 6 5 5 12 10 9 9 16 14 13 13]
    dump_i8_vector(__builtin_msa_shf_b(v_a,7));
    // imm = 33 = 00 10 00 01 -> a[1], a[0], a[2], a[0]
    // -- [2 1 3 1 6 5 7 5 10 9 11 9 14 13 15 13]
    dump_i8_vector(__builtin_msa_shf_b(v_a,33));
    // imm = 222 = 11 01 11 10 -> a[2], a[3], a[1], a[3]
    // -- [3 4 2 4 7 8 6 8 11 12 10 12 15 16 14 16]
    dump_i8_vector(__builtin_msa_shf_b(v_a,222));
    // if you want 4,3,2,1 you need to set imm to 00 01 10 11
    // which is 27
    // -- [4 3 2 1 8 7 6 5 12 11 10 9 16 15 14 13]
    dump_i8_vector(__builtin_msa_shf_b(v_a,27));


    /**
    GPR Columns Slide
        v16i8 __builtin_msa_sld_b (v16i8, v16i8, i32);
        v8i16 __builtin_msa_sld_h (v8i16, v8i16, i32);
        v4i32 __builtin_msa_sld_w (v4i32, v4i32, i32);
        v2i64 __builtin_msa_sld_d (v2i64, v2i64, i32);
    Immediate Columns Slide
        v16i8 __builtin_msa_sldi_b (v16i8, v16i8, imm0_15);
        v8i16 __builtin_msa_sldi_h (v8i16, v8i16, imm0_7);
        v4i32 __builtin_msa_sldi_w (v4i32, v4i32, imm0_3);
        v2i64 __builtin_msa_sldi_d (v2i64, v2i64, imm0_1);
    */
    printf("GPR Columns Slide: \n");
    // TODO -- It's too hard to understand.
    //
    // Vector registers 'a' and 'b' contain 2-dimensional byte arrays stored row-wise.
    // The two source rectangles 'b' and 'a' are concatenated horizontally in the order
    //  they appear in the syntax, i.e. first 'a' and then 'b'.
    // Place a new destination rectangle over 'b' and then slide it to the left over
    //  the concatenation of 'a' and 'b' by the number of columns given in GPR 'c'.
    // The result is written to vector.
    // GPR 'c' value is interpreted modulo the number of columns in destination rectangle,
    // or equivalently, the number of data format df elements in the destination vector.

    // a = [[1],[2],[3],[4]]
    // b = [[5],[6],[7],[8]]
    // c = c % [number of elements]
    // if colums slide = 0, the result is b

    // [0x00000005 0x00000006 0x00000007 0x00000008]
    dump_i32_vector_hex(__builtin_msa_sld_w(v_1, v_2, 0));
    // [0x01000000 0x02000000 0x03000000 0x04000000]
    dump_i32_vector_hex(__builtin_msa_sld_w(v_1, v_2, 1));
    // [0x00010000 0x00020000 0x00030000 0x00040000]
    dump_i32_vector_hex(__builtin_msa_sld_w(v_1, v_2, 2));
    // [0x00000100 0x00000200 0x00000300 0x00000400]
    dump_i32_vector_hex(__builtin_msa_sld_w(v_1, v_2, 3));


    int aa[4] = {0x1f1f1f1f,0x2f2f2f2f,0x3f3f3f3f,0x4f4f4f4f};
    int bb[4] = {0x1aaaaaaa,0x1bbbbbbb,0x1ccccccc,0x1ddddddd};
    v4i32 v_11 = __builtin_msa_ld_w((void*)aa, 0);
    v4i32 v_22 = __builtin_msa_ld_w((void*)bb, 0);
    // [0x1aaaaaaa 0x1bbbbbbb 0x1ccccccc 0x1ddddddd]
    dump_i32_vector_hex(__builtin_msa_sld_w(v_11, v_22, 0));
    // [0x1f1aaaaa 0x2f1bbbbb 0x3f1ccccc 0x4f1ddddd]
    dump_i32_vector_hex(__builtin_msa_sld_w(v_11, v_22, 1));
    // [0x1f1f1aaa 0x2f2f1bbb 0x3f3f1ccc 0x4f4f1ddd]
    dump_i32_vector_hex(__builtin_msa_sld_w(v_11, v_22, 2));
    // [0x1f1f1f1a 0x2f2f2f1b 0x3f3f3f1c 0x4f4f4f1d]
    dump_i32_vector_hex(__builtin_msa_sld_w(v_11, v_22, 3));
    // so it looks like:
    // first concatenate a and b:
    // then if no slide, return right half
    // if slide then shift left.
    // ------------------------------------
    // cat(a,b) [1f 1f 1f 1f 1a aa aa aa]
    // slide=3     [1f 1f 1f 1a]
    // slide=2        [1f 1f 1a aa]
    // slide=1           [1f 1a aa aa]
    // slide=0              [1a aa aa aa]




    __int16_t aa16[8] = {0x1f1f,0x2f2f,0x3f3f,0x4f4f,0x5f5f,0x6f6f,0x7f7f,0x8f8f};
    __int16_t bb16[8] = {0x1aaa,0x1bbb,0x1ccc,0x1ddd,0x1eee,0x1fff,0x2aaa,0x2bbb};
    v8i16 v_aa16 = __builtin_msa_ld_h((void*)aa16, 0);
    v8i16 v_bb16 = __builtin_msa_ld_h((void*)bb16, 0);
    /**
    concatanate a(64bit) and b(64bit)
       a[3] a[2] a[1] a[0] b[3] b[2] b[1] b[0]
       4f4f 3f3f 2f2f 1f1f 1ddd 1ccc 1bbb 1aaa
    0                                     1aaa
    1                                  bb 1a
    2                                1bbb
    3                             cc 1b
    4                           1ccc
    5                        dd 1c
    6                      1ddd
    7                    1f1d
    */
    /**
        v8i16 vector = [0x1aaa 0x1bbb 0x1ccc 0x1ddd 0x1eee 0x1fff 0x2aaa 0x2bbb]
        v8i16 vector = [0xbb1a 0xcc1b 0xdd1c 0x1f1d 0xff1e 0xaa1f 0xbb2a 0x5f2b]
        v8i16 vector = [0x1bbb 0x1ccc 0x1ddd 0x1f1f 0x1fff 0x2aaa 0x2bbb 0x5f5f]
        v8i16 vector = [0xcc1b 0xdd1c 0x1f1d 0x2f1f 0xaa1f 0xbb2a 0x5f2b 0x6f5f]
        v8i16 vector = [0x1ccc 0x1ddd 0x1f1f 0x2f2f 0x2aaa 0x2bbb 0x5f5f 0x6f6f]
        v8i16 vector = [0xdd1c 0x1f1d 0x2f1f 0x3f2f 0xbb2a 0x5f2b 0x6f5f 0x7f6f]
        v8i16 vector = [0x1ddd 0x1f1f 0x2f2f 0x3f3f 0x2bbb 0x5f5f 0x6f6f 0x7f7f]
        v8i16 vector = [0x1f1d 0x2f1f 0x3f2f 0x4f3f 0x5f2b 0x6f5f 0x7f6f 0x8f7f] 
    */
    dump_i16_vector_hex(__builtin_msa_sld_h(v_aa16, v_bb16, 0));
    dump_i16_vector_hex(__builtin_msa_sld_h(v_aa16, v_bb16, 1));
    dump_i16_vector_hex(__builtin_msa_sld_h(v_aa16, v_bb16, 2));
    dump_i16_vector_hex(__builtin_msa_sld_h(v_aa16, v_bb16, 3));
    dump_i16_vector_hex(__builtin_msa_sld_h(v_aa16, v_bb16, 4));
    dump_i16_vector_hex(__builtin_msa_sld_h(v_aa16, v_bb16, 5));
    dump_i16_vector_hex(__builtin_msa_sld_h(v_aa16, v_bb16, 6));
    dump_i16_vector_hex(__builtin_msa_sld_h(v_aa16, v_bb16, 7));




    __int8_t a8[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    __int8_t b8[16] = {16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1};
    v16i8 v_a8 = __builtin_msa_ld_b((void*)a8, 0);
    v16i8 v_b8 = __builtin_msa_ld_b((void*)b8, 0);
    /**
        v16i8 vector = [16 15 14 13 12 11 10  9  8  7  6  5  4  3  2  1]
        v16i8 vector = [15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  1]
        v16i8 vector = [14 13 12 11 10  9  8  7  6  5  4  3  2  1  1  2]
        v16i8 vector = [13 12 11 10  9  8  7  6  5  4  3  2  1  1  2  3]
        v16i8 vector = [12 11 10  9  8  7  6  5  4  3  2  1  1  2  3  4]
        v16i8 vector = [11 10  9  8  7  6  5  4  3  2  1  1  2  3  4  5]
        v16i8 vector = [10  9  8  7  6  5  4  3  2  1  1  2  3  4  5  6]
        v16i8 vector = [ 9  8  7  6  5  4  3  2  1  1  2  3  4  5  6  7]
        v16i8 vector = [ 8  7  6  5  4  3  2  1  1  2  3  4  5  6  7  8]
        v16i8 vector = [ 7  6  5  4  3  2  1  1  2  3  4  5  6  7  8  9]
        v16i8 vector = [ 6  5  4  3  2  1  1  2  3  4  5  6  7  8  9 10]
        v16i8 vector = [ 5  4  3  2  1  1  2  3  4  5  6  7  8  9 10 11]
        v16i8 vector = [ 4  3  2  1  1  2  3  4  5  6  7  8  9 10 11 12]
        v16i8 vector = [ 3  2  1  1  2  3  4  5  6  7  8  9 10 11 12 13]
        v16i8 vector = [ 2  1  1  2  3  4  5  6  7  8  9 10 11 12 13 14]
        v16i8 vector = [ 1  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15]
    */
    dump_i8_vector(__builtin_msa_sld_b(v_a8, v_b8, 0));
    dump_i8_vector(__builtin_msa_sld_b(v_a8, v_b8, 1));
    dump_i8_vector(__builtin_msa_sld_b(v_a8, v_b8, 2));
    dump_i8_vector(__builtin_msa_sld_b(v_a8, v_b8, 3));
    dump_i8_vector(__builtin_msa_sld_b(v_a8, v_b8, 4));
    dump_i8_vector(__builtin_msa_sld_b(v_a8, v_b8, 5));
    dump_i8_vector(__builtin_msa_sld_b(v_a8, v_b8, 6));
    dump_i8_vector(__builtin_msa_sld_b(v_a8, v_b8, 7));
    dump_i8_vector(__builtin_msa_sld_b(v_a8, v_b8, 8));
    dump_i8_vector(__builtin_msa_sld_b(v_a8, v_b8, 9));
    dump_i8_vector(__builtin_msa_sld_b(v_a8, v_b8, 10));
    dump_i8_vector(__builtin_msa_sld_b(v_a8, v_b8, 11));
    dump_i8_vector(__builtin_msa_sld_b(v_a8, v_b8, 12));
    dump_i8_vector(__builtin_msa_sld_b(v_a8, v_b8, 13));
    dump_i8_vector(__builtin_msa_sld_b(v_a8, v_b8, 14));
    dump_i8_vector(__builtin_msa_sld_b(v_a8, v_b8, 15));



    /**
     Vector Floating-Point Class Mask
        v4i32 __builtin_msa_fclass_w (v4f32);
        v2i64 __builtin_msa_fclass_d (v2f64);
    */
    // result has 10 bit
    // bit 0 -- signaling NaN
    // bit 1 -- quiet NaN
    //
    // bit 2,3,4,5 classify negative values:
    // bit 2 -- infinity
    // bit 3 -- normal
    // bit 4 -- subnormal
    // bit 5 -- zero
    //
    // bit 6,7,8,9 classify positive values
    // bit 6 -- infinity
    // bit 7 -- normal
    // bit 8 -- subnormal
    // bit 9 -- zero
    float f[4] = {0.001, 0.002, 0.003, 0.004};
    v4f32 v_f = (v4f32)__builtin_msa_ld_w((void*)f, 0);
    printf("Vector Floating-Point Class Mask: \n");
    dump_i32_vector(__builtin_msa_fclass_w(v_f));
    // [128 128 128 128]
    // 128 = 00 10 00 00 00  -- bit 7 -- normal

    float z[4] = {0.0, 0.0, 0.0, 0.0};
    v4f32 v_z = (v4f32)__builtin_msa_ld_w((void*)z, 0);
    printf("Vector Floating-Point Class Mask: \n");
    dump_i32_vector(__builtin_msa_fclass_w(v_z));
    // [512 512 512 512]
    // 512 = 10 00 00 00 00 -- bit 9 -- zero


    /**
     Vector Data Preserving Shuffle
        v16i8 __builtin_msa_vshf_b (v16i8, v16i8, v16i8);
        v8i16 __builtin_msa_vshf_h (v8i16, v8i16, v8i16);
        v4i32 __builtin_msa_vshf_w (v4i32, v4i32, v4i32);
        v2i64 __builtin_msa_vshf_d (v2i64, v2i64, v2i64);
    */
    printf("Vector Data Preserving Shuffle: \n");

    // v_1 = 1234
    // v_2 = 5678
    // concatanate (a,b)
    // c's lsb 000001 % 8 = 1 specify the index of source element to copy
    // if c's bit 6 and 7 are 0, then do copy, if 1 no copy and set dst to 0
    // [2 3 4 5]
    dump_i32_vector( __builtin_msa_vshf_w(v_1, v_2, v_1));
}


void testShift() {
    /**
    Vector Shift Left
        v16i8 __builtin_msa_sll_b (v16i8, v16i8);
        v8i16 __builtin_msa_sll_h (v8i16, v8i16);
        v4i32 __builtin_msa_sll_w (v4i32, v4i32);
        v2i64 __builtin_msa_sll_d (v2i64, v2i64);
    Immediate Shift Left
        v16i8 __builtin_msa_slli_b (v16i8, imm0_7);
        v8i16 __builtin_msa_slli_h (v8i16, imm0_15);
        v4i32 __builtin_msa_slli_w (v4i32, imm0_31);
        v2i64 __builtin_msa_slli_d (v2i64, imm0_63);
    */
    // a = [1,2,3,4]
    // b = [5,6,7,8]
    v4i32 v_a = __builtin_msa_ld_w((void*)a, 0);
    v4i32 v_b = __builtin_msa_ld_w((void*)b, 0);
    printf("Vector Shift Left: \n");
    // [1 << 5 % 32], [2 << 6 % 32], [3 << 7 % 32], [4 << 8 % 32]
    // [32 128 384 1024]
    dump_i32_vector(__builtin_msa_sll_w(v_a, v_b));
    // c = [5,6,7,8]+32
    int c[4] = {37, 38, 39, 40};
    v4i32 v_c = __builtin_msa_ld_w((void*)c, 0);
    dump_i32_vector(__builtin_msa_sll_w(v_a, v_c));

    printf("Immediate Shift Left: \n");
    // [1 << 5], [2 << 5], [3 << 5], [4 << 5]
    dump_i32_vector(__builtin_msa_slli_w(v_a, 5));

    /**
    Vector Shift Right Arithmetic
        v16i8 __builtin_msa_sra_b (v16i8, v16i8);
        v8i16 __builtin_msa_sra_h (v8i16, v8i16);
        v4i32 __builtin_msa_sra_w (v4i32, v4i32);
        v2i64 __builtin_msa_sra_d (v2i64, v2i64);
    Immediate Shift Right Arithmetic
        v16i8 __builtin_msa_srai_b (v16i8, imm0_7);
        v8i16 __builtin_msa_srai_h (v8i16, imm0_15);
        v4i32 __builtin_msa_srai_w (v4i32, imm0_31);
        v2i64 __builtin_msa_srai_d (v2i64, imm0_63);
    */
    printf("Vector Shift Right Arithmetic: \n");
    // [5 >> 1 % 32], [6 >> 2 % 32], [7 >> 3 % 32], [8 >> 4 % 32]
    // [2 1 0 0]
    dump_i32_vector(__builtin_msa_sra_w(v_b, v_a));
    printf("Immediate Shift Right Arithmetic: \n");
    // [5 >> 1], [6 >> 1], [7 >> 1], [8 >> 1]
    // [2 3 3 4]
    dump_i32_vector(__builtin_msa_srai_w(v_b, 1));

    /**
    Vector Shift Right Arithmetic Rounded
        v16i8 __builtin_msa_srar_b (v16i8, v16i8);
        v8i16 __builtin_msa_srar_h (v8i16, v8i16);
        v4i32 __builtin_msa_srar_w (v4i32, v4i32);
        v2i64 __builtin_msa_srar_d (v2i64, v2i64);
    Immediate Shift Right Arithmetic Rounded
        v16i8 __builtin_msa_srari_b (v16i8, imm0_7);
        v8i16 __builtin_msa_srari_h (v8i16, imm0_15);
        v4i32 __builtin_msa_srari_w (v4i32, imm0_31);
        v2i64 __builtin_msa_srari_d (v2i64, imm0_63);
    */
    printf("Vector Shift Right Arithmetic Rounded: \n");
    // [round(5 >> (1 % 32))], [round(6 >> (2 % 32))],
    //  [round(7 >> (3 % 32))], [round(8 >> (4 % 32))]
    // [3 2 1 1]
    dump_i32_vector(__builtin_msa_srar_w(v_b, v_a));
    printf("Immediate Shift Right Arithmetic Rounded: \n");
    // round ([5 >> 1], [6 >> 1], [7 >> 1], [8 >> 1])
    // [2 3 3 4]
    dump_i32_vector(__builtin_msa_srari_w(v_b, 1));

    /**
    Vector Shift Right Logical
        v16i8 __builtin_msa_srl_b (v16i8, v16i8);
        v8i16 __builtin_msa_srl_h (v8i16, v8i16);
        v4i32 __builtin_msa_srl_w (v4i32, v4i32);
        v2i64 __builtin_msa_srl_d (v2i64, v2i64);
    Immediate Shift Right Logical
        v16i8 __builtin_msa_srli_b (v16i8, imm0_7);
        v8i16 __builtin_msa_srli_h (v8i16, imm0_15);
        v4i32 __builtin_msa_srli_w (v4i32, imm0_31);
        v2i64 __builtin_msa_srli_d (v2i64, imm0_63);
    */
    printf("Vector Shift Right Logical: \n");
    // [5 >> 1 % 32], [6 >> 2 % 32], [7 >> 3 % 32], [8 >> 4 % 32]
    // [2 1 0 0]
    dump_i32_vector(__builtin_msa_srl_w(v_b, v_a));
    printf("Immediate Shift Right Logical: \n");
    // [5 >> 1], [6 >> 1], [7 >> 1], [8 >> 1]
    // [2 3 3 4]
    dump_i32_vector(__builtin_msa_srli_w(v_b, 1));

    /**
    Vector Shift Right Logical Rounded
        v16i8 __builtin_msa_srlr_b (v16i8, v16i8);
        v8i16 __builtin_msa_srlr_h (v8i16, v8i16);
        v4i32 __builtin_msa_srlr_w (v4i32, v4i32);
        v2i64 __builtin_msa_srlr_d (v2i64, v2i64);
    Immediate Shift Right Logical Rounded
        v16i8 __builtin_msa_srlri_b (v16i8, imm0_7);
        v8i16 __builtin_msa_srlri_h (v8i16, imm0_15);
        v4i32 __builtin_msa_srlri_w (v4i32, imm0_31);
        v2i64 __builtin_msa_srlri_d (v2i64, imm0_63);
    */
    printf("Vector Shift Right Logical Rounded: \n");
    // [round(5 >> (1 % 32))], [round(6 >> (2 % 32))],
    //  [round(7 >> (3 % 32))], [round(8 >> (4 % 32))]
    // [3 2 1 1]
    dump_i32_vector(__builtin_msa_srlr_w(v_b, v_a));
    printf("Immediate Shift Right Logical Rounded: \n");
    // round ([5 >> 1], [6 >> 1], [7 >> 1], [8 >> 1])
    // [2 3 3 4]
    dump_i32_vector(__builtin_msa_srlri_w(v_b, 1));
}



int main() {
    printf("------------------ All Other MSA Tests ------------------------ \n");

    testInterleave();
    testInsert();
    testMinMax();
    testCount();
    testPack();
    testElement();
    testShift();

    return 0;
}

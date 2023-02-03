/**
 * MIPS SIMD Architecture(MSA)
 *  Floating-point Arithmetic, Compare, Conversions
 *  related MSA intrinsics demo codes
 */
#include <msa.h>
#include "utils.c"
#include <math.h>

const float src1[] = {1.1, 2.2, 3.3, 4.4};
const float src2[] = {5.5, 6.6, 7.7, 8.8};


void testArithmetic() {
    v4f32 v_a,v_b,v_c;
    v2f64 v_d;

    v_a = (v4f32)__builtin_msa_ld_w((void*)src1, 0);
    v_b = (v4f32)__builtin_msa_ld_w((void*)src2, 0);

    /* Vector Floating-Point Addition
        v4f32 __builtin_msa_fadd_w (v4f32, v4f32);
        v2f64 __builtin_msa_fadd_d (v2f64, v2f64);
    */
    v_c = __builtin_msa_fadd_w(v_a, v_b);
    printf("Vector Floating-Point Addition: \n");
    // [6.600000 8.800000 11.000000 13.200000]
    dump_f32_vector(v_c);

    /* Vector Floating-Point Subtraction
        v4f32 __builtin_msa_fsub_w (v4f32, v4f32);
        v2f64 __builtin_msa_fsub_d (v2f64, v2f64);
    */
    printf("Vector Floating-Point Subtraction: \n");
    // [-4.400000 -4.400000 -4.400000 -4.400000]
    dump_f32_vector(__builtin_msa_fsub_w(v_a, v_b));

    /* Vector Floating-Point Multiplication
        v4f32 __builtin_msa_fmul_w (v4f32, v4f32);
        v2f64 __builtin_msa_fmul_d (v2f64, v2f64);
    */
    v_c = __builtin_msa_fmul_w(v_a, v_b);
    printf("Vector Floating-Point Multiplication: \n");
    // [6.050000 14.520000 25.410000 38.720001]
    dump_f32_vector(v_c);

    /* Vector Floating-Point Division
        v4f32 __builtin_msa_fdiv_w (v4f32, v4f32);
        v2f64 __builtin_msa_fdiv_d (v2f64, v2f64);
    */
    v_c = __builtin_msa_fdiv_w(v_a, v_b);
    printf("Vector Floating-Point Division: \n");
    // [0.200000 0.333333 0.428571 0.500000]
    dump_f32_vector(v_c);


    /* Vector Floating-Point Base 2 Exponentiation
        v4f32 __builtin_msa_fexp2_w (v4f32, v4i32);
        v2f64 __builtin_msa_fexp2_d (v2f64, v2i64);
    */
    // result = float_input_a * 2^(int_input_b)
    printf("Vector Floating-Point Base 2 Exponentiation: \n");
    // [4.400000 8.800000 13.200000 17.600000]
    dump_f32_vector(
        __builtin_msa_fexp2_w(v_a, __builtin_msa_fill_w(2))
    );

    /* Vector Floating-Point Base 2 Logarithm
        v4f32 __builtin_msa_flog2_w (v4f32);
        v2f64 __builtin_msa_flog2_d (v2f64);
    */
    printf("Vector Floating-Point Base 2 Logarithm: \n");
    // v_a = [1.1, 2.2, 3.3, 4.4]
    // Log2(v_a) should be: [0.1375, 1.1375, 1.7224, 2.1375]
    // But here is floored: [0.0000, 1.0000, 1.0000, 2.0000]
    dump_f32_vector(__builtin_msa_flog2_w(v_a));

    /* Vector Floating-Point Multiply-Add
        v4f32 __builtin_msa_fmadd_w (v4f32, v4f32, v4f32);
        v2f64 __builtin_msa_fmadd_d (v2f64, v2f64, v2f64);
    */
    // v_c + v_a * v_b
    // [9.050000 17.520000 28.410000 41.720001]
    printf("Vector Floating-Point Multiply-Add: \n");
    v_c = __builtin_msa_ffint_s_w(__builtin_msa_fill_w(3));
    dump_f32_vector(__builtin_msa_fmadd_w(v_a, v_b, v_c));

    /* Vector Floating-Point Multiply-Sub
        v4f32 __builtin_msa_fmsub_w (v4f32, v4f32, v4f32);
        v2f64 __builtin_msa_fmsub_d (v2f64, v2f64, v2f64);
    */
    // v_c - v_a * v_b
    // [-3.050000 -11.520000 -22.410000 -35.720001]
    printf("Vector Floating-Point Multiply-Sub: \n");
    v_c = __builtin_msa_ffint_s_w(__builtin_msa_fill_w(3));
    dump_f32_vector(__builtin_msa_fmsub_w(v_a, v_b, v_c));


    /* Vector Floating-Point Maximum Based on Absolute Values
        v4f32 __builtin_msa_fmax_a_w (v4f32, v4f32);
        v2f64 __builtin_msa_fmax_a_d (v2f64, v2f64);
       Vector Floating-Point Maximum
        v4f32 __builtin_msa_fmax_w (v4f32, v4f32);
        v2f64 __builtin_msa_fmax_d (v2f64, v2f64);
       Vector Floating-Point Minimum Based on Absolute Values
        v4f32 __builtin_msa_fmin_a_w (v4f32, v4f32);
        v2f64 __builtin_msa_fmin_a_d (v2f64, v2f64);
       Vector Floating-Point Minimum
        v4f32 __builtin_msa_fmin_w (v4f32, v4f32);
        v2f64 __builtin_msa_fmin_d (v2f64, v2f64);
    */
    printf("Vector Floating-Point Maximum Based on Absolute Values: \n");
    v_c = __builtin_msa_ffint_s_w(__builtin_msa_fill_w(-3));
    // [-3.000000 -3.000000 3.300000 4.400000]
    dump_f32_vector(__builtin_msa_fmax_a_w(v_a, v_c));


    /* Vector Approximate Floating-Point Reciprocal
        v4f32 __builtin_msa_frcp_w (v4f32);
        v2f64 __builtin_msa_frcp_d (v2f64);
    */
    printf("Vector Approximate Floating-Point Reciprocal: \n");
    // Reciprocal  1 / v_a
    // [0.909091 0.454545 0.303030 0.227273]
    dump_f32_vector(__builtin_msa_frcp_w(v_a));

    /* Vector Approximate Floating-Point Reciprocal
        v4f32 __builtin_msa_frsqrt_w (v4f32);
        v2f64 __builtin_msa_frsqrt_d (v2f64);
    */
    printf("Vector Approximate Floating-Point Reciprocal of Square Root: \n");
    // Reciprocal  1 / square_root(v_a)
    // [0.909091 0.454545 0.303030 0.227273]
    dump_f32_vector(__builtin_msa_frsqrt_w(v_a));

    /* Vector Floating-Point Square Root
        v4f32 __builtin_msa_fsqrt_w (v4f32);
        v2f64 __builtin_msa_fsqrt_d (v2f64);
    */
    printf("Vector Floating-Point Square Root: \n");
    // Reciprocal  square_root(v_a)
    // [1.048809 1.483240 1.816590 2.097618]
    dump_f32_vector(__builtin_msa_fsqrt_w(v_a));


}


void testCompare() {
    v4f32 v_a,v_b,v_c;
    v2f64 v_d;

    v_a = (v4f32)__builtin_msa_ld_w((void*)src1, 0);
    v_b = (v4f32)__builtin_msa_ld_w((void*)src2, 0);
    /* Vector Floating-Point Quiet Compare Always False
        v4i32 __builtin_msa_fcaf_w (v4f32, v4f32);
        v2i64 __builtin_msa_fcaf_d (v2f64, v2f64);
    
        function QuietFALSE(tt, ts, n)
            // Implementation defined signaling NaN(Not a Number) test
            return 0
        endfunction QuietFALSE

        // https://en.wikipedia.org/wiki/NaN
        // Signaling NaNs can support advanced features such as mixing numerical 
        // and symbolic computation or other extensions to basic floating-point arithmetic.

        // The quiet compare operation is defined by the IEEE Standard for Floating-Point Arithmetic 754TM-2008.
        //  A quiet comparison predicate signals no exception on a quiet NaN operand.
            A signaling comparison predicate signals invalid operand exception on a
            quiet NaN operand.

        // https://grouper.ieee.org/groups/msc/ANSI_IEEE-Std-754-2019/background/predicates.txt
            IEEE 754 floating-point data comparisons can have four possible outcomes - 
                = E Equal
                < L Less than
                > G Greater than
                ? U Unordered
    */
    printf("Vector Floating-Point Quiet Compare Always False: \n");
    dump_i32_vector_hex(
        __builtin_msa_fcaf_w(
            (v4f32)__builtin_msa_fill_w(NAN),
            (v4f32)__builtin_msa_fill_w(NAN)
            )
        );
    dump_i32_vector_hex( __builtin_msa_fcaf_w(v_a, v_a) );


    /* Vector Floating-Point Quiet Compare Equal
        v4i32 __builtin_msa_fceq_w (v4f32, v4f32);
        v2i64 __builtin_msa_fceq_d (v2f64, v2f64);
    */
    // -- Set all bits to 1 in vector elements if the corresponding in 'a'
    //  and 'b' elementsare ordered and equal, otherwise set all bits to 0.
    printf("Vector Floating-Point Quiet Compare Equal: \n");
    v4i32 v_equal = __builtin_msa_fceq_w(v_a, v_a);
    // [0xffffffff 0xffffffff 0xffffffff 0xffffffff]
    dump_i32_vector_hex(v_equal);
    dump_i32_vector_hex(
        __builtin_msa_fceq_w(
            (v4f32)__builtin_msa_fill_w(NAN),
            (v4f32)__builtin_msa_fill_w(NAN)
            )
        );

    /** 
    Vector Floating-Point Quiet Compare Less or Equal
        v4i32 __builtin_msa_fcle_w (v4f32, v4f32);
        v2i64 __builtin_msa_fcle_d (v2f64, v2f64);
    Vector Floating-Point Quiet Compare Less Than
        v4i32 __builtin_msa_fclt_w (v4f32, v4f32);
        v2i64 __builtin_msa_fclt_d (v2f64, v2f64);
    Vector Floating-Point Quiet Compare Not Equal
        v4i32 __builtin_msa_fcne_w (v4f32, v4f32);
        v2i64 __builtin_msa_fcne_d (v2f64, v2f64);
    */
    const float src3[] = {3.3, 3.3, 3.3, 3.3};
    v4f32 v_e = (v4f32)__builtin_msa_ld_w((void*)src3, 0);

    printf("Vector Floating-Point Quiet Compare Less Than: \n");
    // [0xffffffff 0xffffffff 0x0 0x0]
    dump_i32_vector_hex(__builtin_msa_fclt_w(v_a,  v_e));

    printf("Vector Floating-Point Quiet Compare Not Equal: \n");
    // [0xffffffff 0xffffffff 0x0 0xffffffff]
    dump_i32_vector_hex(__builtin_msa_fcne_w(v_a, v_e));


    /** 
    Vector Floating-Point Quiet Compare Ordered
        v4i32 __builtin_msa_fcor_w (v4f32, v4f32);
        v2i64 __builtin_msa_fcor_d (v2f64, v2f64);
    Vector Floating-Point Quiet Compare Unordered
        v4i32 __builtin_msa_fcun_w (v4f32, v4f32);
        v2i64 __builtin_msa_fcun_d (v2f64, v2f64);
    */
    // Ordered:  both elements are not NaN values, otherwise set all bits to 0.
    printf("Vector Floating-Point Quiet Compare Ordered: \n");
    dump_i32_vector_hex(__builtin_msa_fcor_w(v_a, v_b));
    dump_i32_vector_hex(__builtin_msa_fcor_w(
        (v4f32)__builtin_msa_fill_w(0.0/0.0),
        (v4f32)__builtin_msa_fill_w(0.0/0.0))
    );
    printf("Vector Floating-Point Quiet Compare Unordered: \n");
    dump_i32_vector_hex(__builtin_msa_fcun_w(v_a, v_b));
    dump_i32_vector_hex(__builtin_msa_fcun_w(
        (v4f32)__builtin_msa_fill_w(0.0/0.0),
        (v4f32)__builtin_msa_fill_w(0.0/0.0))
    );


    /** 
    Vector Floating-Point Quiet Compare Unordered or Equal
        v4i32 __builtin_msa_fcueq_w (v4f32, v4f32);
        v2i64 __builtin_msa_fcueq_d (v2f64, v2f64);
    Vector Floating-Point Quiet Compare Unordered or Less or Equal
        v4i32 __builtin_msa_fcule_w (v4f32, v4f32);
        v2i64 __builtin_msa_fcule_d (v2f64, v2f64);
    Vector Floating-Point Quiet Compare Unordered or Less Than
        v4i32 __builtin_msa_fcult_w (v4f32, v4f32);
        v2i64 __builtin_msa_fcult_d (v2f64, v2f64);
    Vector Floating-Point Quiet Compare Unordered or Not Equal
        v4i32 __builtin_msa_fcune_w (v4f32, v4f32);
        v2i64 __builtin_msa_fcune_d (v2f64, v2f64);
    */

   /**
    Vector Floating-Point Signaling Compare Always False
        v4i32 __builtin_msa_fsaf_w (v4f32, v4f32);
        v2i64 __builtin_msa_fsaf_d (v2f64, v2f64);
    Vector Floating-Point Signaling Compare Equal
        v4i32 __builtin_msa_fseq_w (v4f32, v4f32);
        v2i64 __builtin_msa_fseq_d (v2f64, v2f64);
    Vector Floating-Point Signaling Compare Less or Equal
        v4i32 __builtin_msa_fsle_w (v4f32, v4f32);
        v2i64 __builtin_msa_fsle_d (v2f64, v2f64);
    Vector Floating-Point Signaling Compare Less Than
        v4i32 __builtin_msa_fslt_w (v4f32, v4f32);
        v2i64 __builtin_msa_fslt_d (v2f64, v2f64);
    Vector Floating-Point Signaling Compare Not Equal
        v4i32 __builtin_msa_fsne_w (v4f32, v4f32);
        v2i64 __builtin_msa_fsne_d (v2f64, v2f64);
    Vector Floating-Point Signaling Compare Ordered
        v4i32 __builtin_msa_fsor_w (v4f32, v4f32);
        v2i64 __builtin_msa_fsor_d (v2f64, v2f64);
    */
    printf("Vector Floating-Point Signaling Compare Always False: \n");
    dump_i32_vector_hex(
        __builtin_msa_fsaf_w(
            (v4f32)__builtin_msa_fill_w(0.0/0.0),
            (v4f32)__builtin_msa_fill_w(0.0/0.0)
            )
        );
    dump_i32_vector_hex( __builtin_msa_fsaf_w(v_a, v_a) );

   /**
    Vector Floating-Point Signaling Compare Ordered
        v4i32 __builtin_msa_fsueq_w (v4f32, v4f32);
        v2i64 __builtin_msa_fsueq_d (v2f64, v2f64);
    Vector Floating-Point Signaling Compare Unordered or Less or Equal
        v4i32 __builtin_msa_fsule_w (v4f32, v4f32);
        v2i64 __builtin_msa_fsule_d (v2f64, v2f64);
    Vector Floating-Point Signaling Compare Unordered or Less Than
        v4i32 __builtin_msa_fsult_w (v4f32, v4f32);
        v2i64 __builtin_msa_fsult_d (v2f64, v2f64);
    Vector Floating-Point Signaling Compare Unordered
        v4i32 __builtin_msa_fsun_w (v4f32, v4f32);
        v2i64 __builtin_msa_fsun_d (v2f64, v2f64);
    Vector Floating-Point Signaling Compare Unordered or Not Equal
        v4i32 __builtin_msa_fsune_w (v4f32, v4f32);
        v2i64 __builtin_msa_fsune_d (v2f64, v2f64);
    */

    printf("More compare quiet and signaling: \n");
    v4f32 v_0 = __builtin_msa_ffint_s_w(__builtin_msa_fill_w(0));
    dump_i32_vector_hex(
        __builtin_msa_fsult_w(
            __builtin_msa_fdiv_w(v_0, v_0),
            __builtin_msa_fdiv_w(v_0, v_0)
            )
    );

    dump_i32_vector_hex(
        __builtin_msa_fcult_w(
            __builtin_msa_fdiv_w(v_0, v_0),
            __builtin_msa_fdiv_w(v_0, v_0)
            )
    );

    //uncaught target signal 8 (Floating point exception) - core dumped
    // v4i32 v_00 = __builtin_msa_fill_w(0);
    // dump_i32_vector_hex(
    //     __builtin_msa_fcult_w(
    //        (v4f32) __builtin_msa_div_s_w(v_00, v_00),
    //        (v4f32) __builtin_msa_div_s_w(v_00, v_00)
    //         )
    // );
}


void testConversion() {
    v2f64 v_a, v_b;
    double a[] = {1.1, 2.2, 3.3, 4.4};
    double b[] = {5.5, 6.6, 7.7, 8.8};
    v_a = (v2f64)__builtin_msa_ld_d((void*)a, 0);
    v_b = (v2f64)__builtin_msa_ld_d((void*)b, 0);

    v4f32 v_c = (v4f32)__builtin_msa_ld_w((void*)a, 0);


    /**
    Vector Floating-Point Down-Convert Interchange Format
        v8i16 __builtin_msa_fexdo_h (v4f32, v4f32);
        v4f32 __builtin_msa_fexdo_w (v2f64, v2f64);
    */
    // [1.100000 2.200000 5.500000 6.600000]
    printf("Vector Floating-Point Down-Convert Interchange Format: \n");
    dump_f32_vector(__builtin_msa_fexdo_w(v_a, v_b));

    // fp32 => fp16
    // fp16 to hex
    // https://evanw.github.io/float-toy/
    // 0.225 => 0x3333
    float f[] = {0.224976,0.224976,0.224976,0.224976};
    v4f32 v_f = (v4f32)__builtin_msa_ld_w((void*)f, 0);
    v8i16 v_d = __builtin_msa_fexdo_h(v_f, v_f);
    __uint16_t d = v_d[0]; // 0x3333
    printf("fp32 0.224976 => fp16 => hex = 0x%x\n", d);


    /**
    Vector Floating-Point Up-Convert Interchange Format Left
        v4f32 __builtin_msa_fexupl_w (v8i16);
        v2f64 __builtin_msa_fexupl_d (v4f32);
    Vector Floating-Point Up-Convert Interchange Format right
        v4f32 __builtin_msa_fexupr_w (v8i16);
        v2f64 __builtin_msa_fexupr_d (v4f32);
    */
    printf("Vector Floating-Point up-Convert Interchange Format Left: \n");
    // src1 = [1.1, 2.2, 3.3, 4.4] -> Right to Left
    dump_f64_vector(__builtin_msa_fexupl_d((v4f32)__builtin_msa_ld_w((void*)src1, 0)));
    dump_f64_vector(__builtin_msa_fexupr_d((v4f32)__builtin_msa_ld_w((void*)src1, 0)));

    // fp16 to hex
    // https://evanw.github.io/float-toy/
    // 0.225 => 0x3333
    v8i16 hex = (v8i16)__builtin_msa_fill_h(0x3333);
    // fp16 => fp32
    // [0.224976 0.224976 0.224976 0.224976]
    dump_f32_vector(__builtin_msa_fexupl_w(hex));



    /**
    Vector Floating-Point Round and Convert from Signed Integer
        v4f32 __builtin_msa_ffint_s_w (v4i32);
        v2f64 __builtin_msa_ffint_s_d (v2i64);
    Vector Floating-Point Round and Convert from Unsigned Integer
        v4f32 __builtin_msa_ffint_u_w (v4u32);
        v2f64 __builtin_msa_ffint_u_d (v2u64);
    */
    printf("Vector Floating-Point Round and Convert from Signed Integer: \n");
    dump_f32_vector(__builtin_msa_ffint_s_w(__builtin_msa_fill_w(5)));

    /**
    Vector Floating-Point Round to Integer
        v4f32 __builtin_msa_frint_w (v4f32);
        v2f64 __builtin_msa_frint_d (v2f64);
    */
    printf("Vector Floating-Point Round to Integer: \n");
    // 1.1 2.2 round 1 2
    // 5.5 6.6 round 6 7
    dump_f64_vector(__builtin_msa_frint_d(v_a));
    dump_f64_vector(__builtin_msa_frint_d(v_b));

    /**
    Vector Floating-Point Convert from Fixed-Point Left
        v4f32 __builtin_msa_ffql_w (v8i16);
        v2f64 __builtin_msa_ffql_d (v4i32);
    Vector Floating-Point Convert from Fixed-Point Right
        v4f32 __builtin_msa_ffqr_w (v8i16);
        v2f64 __builtin_msa_ffqr_d (v4i32);
    */
    printf("Vector Floating-Point Convert from Fixed-Point Left: \n");
    // v8i16[3] and v8i16[4] up-converted to floating-point data format.
    // from 16-bit Q15 to 32-bit floating-point.
    // Q / 2^15 = F
    // Q / 2^31 = D
    short q[16] = {4000, 8000, 12000, 16000, 20000, 24000, 28000, 32000};
    // [0.610352 0.732422 0.854492 0.976562]
    dump_f32_vector(__builtin_msa_ffql_w(__builtin_msa_ld_h((void*)q, 0)));

    printf("Vector Floating-Point Convert from Fixed-Point Right: \n");
    // [0.122070 0.244141 0.366211 0.488281]
    dump_f32_vector(__builtin_msa_ffqr_w(__builtin_msa_ld_h((void*)q, 0)));


    /**
    Vector Floating-Point Convert to Signed Integer
        v4i32 __builtin_msa_ftint_s_w (v4f32);
        v2i64 __builtin_msa_ftint_s_d (v2f64);
    Vector Floating-Point Convert to Unsigned Integer
        v4u32 __builtin_msa_ftint_u_w (v4f32);
        v2u64 __builtin_msa_ftint_u_d (v2f64);
    Vector Floating-Point Convert to Fixed-Point
        v8i16 __builtin_msa_ftq_h (v4f32, v4f32);
        v4i32 __builtin_msa_ftq_w (v2f64, v2f64);
    */
    printf("Vector Floating-Point Convert to Signed Integer: \n");
    float ff[] = {2.354, 234.1, 3.12, 55.0};
    v4f32 v_ff = (v4f32)__builtin_msa_ld_w((void*)ff, 0);
    dump_i32_vector(__builtin_msa_ftint_s_w(v_ff));
    dump_f64_vector(v_a);
    dump_i64_vector(__builtin_msa_ftint_s_d(v_a));

    printf("Vector Floating-Point Convert to Fixed-Point: \n");
    // v_f = {0.224976,0.224976,0.224976,0.224976};
    // q_r = v_f * 2^15 = 7372
    v8i16 q_r = __builtin_msa_ftq_h(v_f, v_f);
    dump_i16_vector(q_r);

    // v_a = {1.1 2.2}
    // [0x7fffffff 0x7fffffff 0x7fffffff 0x7fffffff]
    // Saturated?
    // must be < 1.0?
    dump_i32_vector_hex(__builtin_msa_ftq_w(v_a, v_a));

    /**
    Vector Floating-Point Truncate and Convert to Signed Integer
        v4i32 __builtin_msa_ftrunc_s_w (v4f32);
        v2i64 __builtin_msa_ftrunc_s_d (v2f64);
    Vector Floating-Point Truncate and Convert to Unsigned Integer
        v4u32 __builtin_msa_ftrunc_u_w (v4f32);
        v2u64 __builtin_msa_ftrunc_u_d (v2f64);
    */
    // x > 0 truncate = floor
    // x < 0 trancate = ceil
    printf("Vector Floating-Point Truncate and Convert to Signed Integer: \n");
    dump_i64_vector(__builtin_msa_ftrunc_s_d(v_a));

}


/**
        Scaler implementation takes:
        - 4 Float MUL
        - 3 Float ADD
        FIXED-POINT MSA implementation takes:
        - 1 SIMD QUANT
        - 1 SIMD DOTP
        - 1 SIMD DEQUANT
        - 1 Float Add
        - 1 Float MUL
            and a lot of extra memory operation.
        FLOATING-POINT MSA takes:
        - 1 SIMD FMUL
        - 2 SIMD Up-Convert
        - 1 SIMD ADD
        - 1 Float Add
*/
void testDotProduct() {
    // There is no floating-point dot product MSA ins.
    // Here implement with fixed-point MSA

    float a[4] = {0.1, 0.2, 0.3, 0.4};
    float b[4] = {0.5, 0.6, 0.7, 0.8};

    float reference_result = a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
    printf("Test Floating Point Dot Product:\n");
    printf("Reference result = %f \n", reference_result);

    // Now implement with fixed-point MSA
    int16_t array_fixed[8] = {0};
    int32_t array_fixed_a[4] = {0};
    int32_t array_fixed_b[4] = {0};
    v4f32 v_f_a = (v4f32)__builtin_msa_ld_w((void*)a, 0);
    v4f32 v_f_b = (v4f32)__builtin_msa_ld_w((void*)b, 0);

    // v_f_a * 2^15, v_f_b * 2^15, so a*b scale = 2^30
    v8i16 v_i_ba = __builtin_msa_ftq_h(v_f_a, v_f_b);

    __builtin_msa_st_h(v_i_ba, array_fixed, 0);
    array_fixed_a[0] = (int32_t)array_fixed[4];
    array_fixed_a[1] = (int32_t)array_fixed[5];
    array_fixed_a[2] = (int32_t)array_fixed[6];
    array_fixed_a[3] = (int32_t)array_fixed[7];
    array_fixed_b[0] = (int32_t)array_fixed[0];
    array_fixed_b[1] = (int32_t)array_fixed[1];
    array_fixed_b[2] = (int32_t)array_fixed[2];
    array_fixed_b[3] = (int32_t)array_fixed[3];

    v4i32 v_i_a = (v4i32)__builtin_msa_ld_w((void*)array_fixed_a, 0);
    v4i32 v_i_b = (v4i32)__builtin_msa_ld_w((void*)array_fixed_b, 0);

    v2i64 v_result_fixed = __builtin_msa_dotp_s_d(v_i_a,v_i_b);

    int32_t result_i32[4] = {0};
    result_i32[0] = (int32_t)__msa_copy_s_d(v_result_fixed,0);
    result_i32[1] = (int32_t)__msa_copy_s_d(v_result_fixed,1);
    v4i32 v_result_i32 = (v4i32)__builtin_msa_ld_w((void*)result_i32, 0);

    // Dequant right half(first 2 elements) of v_result_i32
    // v_result_i32[0..1] / 2^31 = dequant_result
    v2f64 dequant_result = __builtin_msa_ffqr_d(v_result_i32);

    // the scale is different to ftq (2^30)
    // so need to * 2^1
    float fixed_point_result = ((float)dequant_result[0] + (float)dequant_result[1]) * 2;

    printf("Fixed-point MSA result = %f, acuracy loss = %f\n",
            fixed_point_result, fabs(fixed_point_result - reference_result));


    // Now implement with floating-point MSA (MUL and ADD)
    v4f32 v_mul = __builtin_msa_fmul_w(v_f_a, v_f_b);
    v2f64 v_mul_l = __builtin_msa_fexupl_d(v_mul);
    v2f64 v_mul_r = __builtin_msa_fexupr_d(v_mul);
    v2f64 v_sum = __builtin_msa_fadd_d(v_mul_l, v_mul_r);
    float floating_point_result = v_sum[0] + v_sum[1];
    printf("Floating_point MSA result = %f \n", floating_point_result);
}




int main() {
    printf("------------------ Floating-point Tests -------------------------- \n");

    testArithmetic();
    testCompare();
    testConversion();

    // There is no direct MSA floating-point dotp
    testDotProduct();

    return 0;
}

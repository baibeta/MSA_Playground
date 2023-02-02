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
        (v4f32)__builtin_msa_fill_w(NAN),
        (v4f32)__builtin_msa_fill_w(NAN))
    );
    printf("Vector Floating-Point Quiet Compare Unordered: \n");
    dump_i32_vector_hex(__builtin_msa_fcun_w(v_a, v_b));
    dump_i32_vector_hex(__builtin_msa_fcun_w(
        (v4f32)__builtin_msa_fill_w(NAN),
        (v4f32)__builtin_msa_fill_w(NAN))
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
}


void testConversion() {
    v2f64 v_a, v_b;
    double a[] = {1.1, 2.2, 3.3, 4.4};
    double b[] = {5.5, 6.6, 7.7, 8.8};
    v_a = (v2f64)__builtin_msa_ld_w((void*)a, 0);
    v_b = (v2f64)__builtin_msa_ld_w((void*)b, 0);

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

}

int main() {
    printf("------------------ Floating-point Tests -------------------------- \n");

    testArithmetic();
    testCompare();
    testConversion();

    return 0;
}

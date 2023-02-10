#include <msa.h>
#include "utils.c"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateRandomArray(int n, float *array)
{
    srand(time(NULL));
    // range (-10, 10)
    for (int i = 0; i < n; i++)
    {
        array[i] = ((float)rand() / RAND_MAX) * 20 - 10;
    }
}


void testReLU(int n, float *array) {
    printf("ReLU inputs = ");
    dump_f32_array(n, array);

    v4f32 _zero = (v4f32)__msa_fill_w(0);
    for (int i = 0; i + 3 < n; i += 4)
    {
        // prefetch next batch of data into CPU cache
        __builtin_prefetch(array + (4 * sizeof(float)));

        v4f32 _p = (v4f32)__msa_ld_w(array, 0);
        _p = __msa_fmax_w(_p, _zero);
        __msa_st_w((v4i32)_p, array, 0);
        array +=4;
    }

    printf("ReLU outputs = ");
    dump_f32_array(n, array-n);
}



void testAbs(int n, float *array) {
    printf("ABS inputs = ");
    dump_f32_array(n, array);

    v4f32 _zero = (v4f32)__msa_fill_w(0);
    for (int i = 0; i + 3 < n; i += 4)
    {
        __builtin_prefetch(array + (4 * sizeof(float)));
        v4f32 _p = (v4f32)__msa_ld_w(array, 0);
        // clear sign bit
        v4u32 _out_p = __msa_bclri_w((v4u32)_p, 31);
        __msa_st_w((v4i32)_out_p, array, 0);
        array +=4;
    }

    printf("ABS outputs = ");
    dump_f32_array(n, array-n);
}


void sgemm_msa_K4(int M, int N, float *A, float *B, float *C)
{
    int i, j;
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; j++)
        {
            v4f32 sum = {0, 0, 0, 0};
            v4f32 a = {A[i*4+0], A[i*4+1], A[i*4+2], A[i*4+3]};
            v4f32 b = {B[0*N+j], B[1*N+j], B[2*N+j], B[3*N+j]};
            sum = __msa_fmul_w(a,b);
            C[i*N+j] = sum[0] + sum[1] + sum[2] + sum[3];
        }
    }
}

void sgemm(int M, int N, int K, float *A, float *B, float *C)
{
    int i, j, k;
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; j++)
        {
            float sum = 0;
            for (k = 0; k < K; k++)
            {
                sum += A[i*K+k] * B[k*N+j];
            }
            C[i*N+j] = sum;
        }
    }
}

void testSgemm() {
    int M = 4, N = 4, K = 4;
    float A[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    float B[16] = {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    float C[16];

    // Matrix A = MxK
    // Matrix B = KxN

    sgemm(M, N, K, A, B, C);
    printf("SGEMM result:\n");
    dump_f32_array(16, C);

    sgemm_msa_K4(M, N, A, B, C);
    dump_f32_array(16, C);
}



int main() {
    printf("------------------ NN Operation Tests --------------------------- \n");

    // Make 16 random inputs
    int n = 16;
    float *array = (float *)malloc(n * sizeof(float));

    generateRandomArray(n, array);
    testReLU(n, array);

    generateRandomArray(n, array);
    testAbs(n, array);

    testSgemm();

    free(array);
    return 0;
}

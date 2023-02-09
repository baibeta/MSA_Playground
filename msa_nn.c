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
    for (int i = 0; i < n; i++)
    {
        printf("%f ", array[i]);
    }
    printf("\n");

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
    array -=n;
    for (int i = 0; i < n; i++)
    {
        printf("%f ", array[i]);
    }
    printf("\n");
}




int main() {
    printf("------------------ NN Operation Tests --------------------------- \n");

    // Make 16 random inputs
    int n = 16;
    float *array = (float *)malloc(n * sizeof(float));
    generateRandomArray(n, array);


    testReLU(n, array);


    free(array);
    return 0;
}

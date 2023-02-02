#include "stdio.h"

void dump_i32_vector(v4i32 vector) {
    printf("v4i32 vector = [%d %d %d %d]\n",
        vector[0], vector[1], vector[2], vector[3]);
}

void dump_i32_vector_hex(v4i32 vector) {
    printf("v4i32 vector = [0x%x 0x%x 0x%x 0x%x]\n",
        vector[0], vector[1], vector[2], vector[3]);
}


void dump_u8_vector(v16u8 vector) {
    printf("v16u8 vector = [%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d]\n",
        vector[0], vector[1], vector[2], vector[3],
        vector[4], vector[5], vector[6], vector[7],
        vector[8], vector[9], vector[10], vector[11],
        vector[12], vector[13], vector[14], vector[15]);
}

void dump_f32_vector(v4f32 vector) {
    printf("v4f32 vector = [%f %f %f %f]\n",
        vector[0], vector[1], vector[2], vector[3]);
}

void dump_f64_vector(v2f64 vector) {
    printf("v4f32 vector = [%f %f]\n",vector[0], vector[1]);
}
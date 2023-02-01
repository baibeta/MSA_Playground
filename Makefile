all: clean msa_int_arith msa_logical msa_bit_op run

CROSS_COMPILE ?= /data/home/yifan.bai/code/x2000/prebuilts/toolchains/mips-gcc720-glibc229/bin/mips-linux-gnu-
CC=$(CROSS_COMPILE)gcc
CXXFLAGS= -mmsa -static

msa_int_arith: msa_int_arith.c
	${CC} $^ -o $@ ${CXXFLAGS}

msa_logical: msa_logical.c
	${CC} $^ -o $@ ${CXXFLAGS}

msa_bit_op: msa_bit_op.c
	${CC} $^ -o $@ ${CXXFLAGS}

clean:
	-rm msa_int_arith
	-rm msa_logical
	-rm msa_bit_op

run:
	-qemu-mipsel -cpu P5600 msa_int_arith
	-qemu-mipsel -cpu P5600 msa_logical
	-qemu-mipsel -cpu P5600 msa_bit_op

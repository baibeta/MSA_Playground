all: clean msa_int_arith msa_logical msa_bit_op msa_branch msa_compare msa_memory run

CROSS_COMPILE ?= /data/home/yifan.bai/code/x2000/prebuilts/toolchains/mips-gcc720-glibc229/bin/mips-linux-gnu-
CC=$(CROSS_COMPILE)gcc
CXXFLAGS= -mmsa -static

msa_int_arith: msa_int_arith.c
	${CC} $^ -o $@ ${CXXFLAGS}

msa_logical: msa_logical.c
	${CC} $^ -o $@ ${CXXFLAGS}

msa_bit_op: msa_bit_op.c
	${CC} $^ -o $@ ${CXXFLAGS}

msa_branch: msa_branch.c
	${CC} $^ -o $@ ${CXXFLAGS}

msa_compare: msa_compare.c
	${CC} $^ -o $@ ${CXXFLAGS}

msa_memory: msa_memory.c
	${CC} $^ -o $@ ${CXXFLAGS}

run:
	-qemu-mipsel -cpu P5600 msa_int_arith
	-qemu-mipsel -cpu P5600 msa_logical
	-qemu-mipsel -cpu P5600 msa_bit_op
	-qemu-mipsel -cpu P5600 msa_branch
	-qemu-mipsel -cpu P5600 msa_compare
	-qemu-mipsel -cpu P5600 msa_memory

clean:
	-rm msa_int_arith
	-rm msa_logical
	-rm msa_bit_op
	-rm msa_branch
	-rm msa_compare
	-rm msa_memory

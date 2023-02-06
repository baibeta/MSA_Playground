all: count clean test_bins qemu_tests

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

msa_floating_point: msa_floating_point.c
	${CC} $^ -o $@ ${CXXFLAGS}

msa_other: msa_other.c
	${CC} $^ -o $@ ${CXXFLAGS}

bins = msa_int_arith msa_logical msa_bit_op msa_branch msa_compare msa_memory msa_floating_point msa_other
test_bins: ${bins}
qemu_tests:
	for x in $(foreach n,$(bins), $(n)); do \
		qemu-mipsel -cpu P5600 $$x; \
	done

count:
	-find . -name '*.c' | xargs wc -l

clean:
	-find . -type f -name 'msa_*' -and -not -name '*.c' -delete

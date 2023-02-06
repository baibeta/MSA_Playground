# MSA_Playground
MIPS SIMD Architecture intrinsics

# Prerequisites
* MIPS GCC Toolchains
* MIPS QEMU

# Build and Test
Build and Run on QEMU
```
make
```
Only run on QEMU
```
make qemu_tests
```


## Referece:
* MIPS64 SIMD Manual:
>https://s3-eu-west-1.amazonaws.com/downloads-mips/documents/MD00868-1D-MSA64-AFP-01.12.pdf

* GCC MSA Intrinsics with params:
>https://gcc.gnu.org/onlinedocs/gcc/MIPS-SIMD-Architecture-Built-in-Functions.html

* GCC Add MSA git commit
>https://github.com/MIPS/gcc/commit/6cf538daaead38a5bc09a79bfb26c34c83fec91e

* A useful documentation website
>https://docs.rs/core_arch/latest/core_arch/mips64/

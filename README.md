# kman

#### *- kernel management and monitor -*


## overview

kman, cross platform text-based kernel/sysmsg monitor and management application

## build instructions

linux on pc :

```sh
mkdir -p build
make CC=gcc CXX=g++ 
```

cross compile :

```sh
mkdir -p build
make CC=<cross_platform_c_toolchain> CXX=<cross_platform_cpp_toolchain>
```
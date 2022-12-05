# README

This is a simple demonstration of an infinite loop between two
functions. With a new enough clang version, even when not optimized,
this does not "blow out the  stack".

     [tailcalls]$ clang --version
     clang version 14.0.6
     Target: x86_64-pc-linux-gnu
     Thread model: posix
     InstalledDir: /usr/bin

Here is an example of an unoptimized gcc build blowing out the stack:

     [tailcalls]$ ./gcc-build-c
     bblock_1 0
     bblock_2 0
     bblock_1 0
     bblock_1 0
     bblock_2 0
     Segmentation fault (core dumped)

gcc with -O2 does however work properly.

     [tailcalls]$ ./gcc-build-c-opt 
     bblock_1 0
     bblock_2 0
     bblock_1 0
     bblock_1 0
     bblock_2 0
     bblock_2 10000
     bblock_1 0
     bblock_1 0
     bblock_1 65536
     ...



# CI-server

## Compiling

This is one way to compile the project on a linux/debian based machine while in the project dir.

First running cmake to construct a Makefile
```
ci_test$ cmake -B./build -H.
```
Secondly run the make file to create exicutables
```
ci_test$ make -C ./build
```
There are now exicutables in the build folder one of them should be unittest, example of a exicutable being ran.
```
ci_test$ ./build/unittest
```

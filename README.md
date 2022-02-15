### Requirements

- LLVM 12+

### Building

```
$ mkdir build
$ cd build
$ cmake -DLLVM_DIR=</path/to/LLVM/build>/lib/cmake/llvm/ ..
$ make
```

### Running

```
$ clang -fplugin=lib/libfunction-printer-plugin.so -c ../test/functions.c
```

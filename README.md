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
$ clang -fplugin=</path/to/build>/lib/libprintfunc.so \
    -c </path/to/source> 
```

### Additional Remarks

- Change `printfunc` in `lib/CMakeLists.txt` to your plugin name.
  `libprintfunc.so` will change to `lib<your-plugin-name>.so`. Set the library
  name accordingly when running.

### Requirements

- LLVM 12+ (https://github.com/llvm/llvm-project)

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
  `libprintfunc.so` will be renamed to `lib<your-plugin-name>.so`.

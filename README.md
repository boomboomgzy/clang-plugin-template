## Building

### (Prerequisite) LLVM

0. Instal prerequisites.

```
$ sudo apt install git
$ sudo apt install cmake
```

1. Make a work drectory and move into it.

```
$ mkdir my-project
$ cd my-project
```

2. Clone LLVM 15.

```
$ git clone -b llvmorg-15.0.0 https://github.com/llvm/llvm-project
```

3. Make a build directory and move into it.

```
$ cd llvm-project
$ mkdir build
$ cd build
```

4. build llvm (c.f., this will generate Makefile here).

llvm build目录下:
1、cmake -DLLVM_TARGETS_TO_BUILD=X86 -DCMAKE_BUILD_TYPE=Release     -DCMAKE_INSTALL_PREFIX=$(pwd)/../install     -DLLVM_ENABLE_PROJECTS="clang"     -G "Unix Makefiles"(or -G Ninja)  -DLLVM_ENABLE_ASSERTIONS=ON     -DCMAKE_CXX_FLAGS=${CMAKE_CLANG_FLAGS}     -DBUILD_SHARED_LIBS=ON  -DCLANG_ENABLE_STATIC_ANALYZER=ON -DLLVM_ENABLE_PLUGINS=ON ../llvm
2、make install -j8  (8是线程数) 或  ninja clang -j8

5. Set environment variables.

```
$ export LLVM_BUILD_DIR=<...>/my-project/llvm-project/build
$ export LLVM_INSTALL_DIR=<...>/my-project/llvm-project/install
$ export PATH=$PATH:$LLVM_INSTALL_DIR/bin
```

Please replace `<...>` to a proper absolute path to the directory `my-project`.
You may want to add those commands at the end of your `.bashrc` file to let your
terminal automatically recognize them whenever it starts up.  The default
`.bashrc` file is at your home directory. (e.g., `/home/<your_id>/.bashrc`)

### Plugins (Checker & AST Visitor)

```
$ cd <this/repo/dir>
$ mkdir build
$ cd build
$ cmake -DLLVM_DIR=$LLVM_BUILD_DIR/lib/cmake/llvm/ ..  && make
```

## Running

### AST Visitor (PrintFunction)

```
clang -fplugin=<this/repo/dir>/build/lib/libPrintFunc.so \
    -c <this/repo/dir>/test/functions.c
```
### gzy_verison: clang -fplugin=/home/gzy/gzy_work/cpp/clang_plugins/clang-plugin-template/build/lib/libPrintFunction.so -c /home/gzy/gzy_work/cpp/clang_plugins/clang-plugin-template/test/functions.c

### AST Matcher (explicit cast)

### gzy_version:matcher.exe   testfile  -- ${MY_INCLUDES}

### Checker (StreamChecker)

```
clang -fsyntax-only -fplugin=<this/repo/dir>/build/lib/libSimpleStreamChecker.so \
    -Xclang -analyze -Xclang -analyzer-checker=demo.SimpleStreamChecker \
    <this/repo/dir>/test/files.c
```
### gzy_version 
### simplestream: clang -fsyntax-only -fplugin=/home/gzy/gzy_work/cpp/clang_plugins/clang-plugin-template/build/lib/libSimpleStreamChecker.so -Xclang -analyze -Xclang -analyzer-checker=demo.SimpleStreamChecker /home/gzy/gzy_work/cpp/clang_plugins/clang-plugin-template/test/files.c
###  maincall: clang -fsyntax-only -fplugin=/home/gzy/gzy_work/cpp/clang_plugins/clang-plugin-template/build/lib/libMainCallChecker.so -Xclang -analyze -Xclang -analyzer-checker=demo.MainCallChecker /home/gzy/gzy_work/cpp/clang_plugins/clang-plugin-template/test/maincall.c



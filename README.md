### Requirements

- LLVM 15+ (https://github.com/llvm/llvm-project)

### (Prerequisite) Building LLVM

0. Instal prerequisites.

$ sudo apt install git
$ sudo apt install cmake

1. Make a work drectory and move into it.

$ mkdir my-project
$ cd my-project

2. Clone LLVM 15.

$ git clone -b llvmorg-15.0.0 https://github.com/llvm/llvm-project

3. Make a build directory and move into it.

$ cd llvm-project
$ mkdir build
$ cd build

4. Configure with CMake (c.f., this will generate Makefile here).

$ cmake -DLLVM_TARGETS_TO_BUILD=X86 -DCMAKE_BUILD_TYPE=RelWithDebInfo \
    -DCMAKE_INSTALL_PREFIX=$(pwd)/../install \
    -DLLVM_ENABLE_PROJECTS="clang;compiler-rt" \
    -G "Unix Makefiles" -DLLVM_ENABLE_ASSERTIONS=ON \
    -DCMAKE_CXX_FLAGS=${CMAKE_CLANG_FLAGS} ../llvm

5. Build and install LLVM. (c.f., control # of cpus to use with "-j" option).

$ make install -j4

6. Set environment variables.

$ cd .. # now we're at "my-project/llvm-project"
$ export LLVM_BUILD_DIR=$(pwd)/build
$ export LLVM_INSTALL_DIR=$(pwd)/install
$ export PATH=$PATH:$LLVM_INSTALL_DIR/bin

You may want to add those three `export` commands at the end of your `.bashrc`
file to let your terminal automatically recognize them whenever it starts up.
The default `.bashrc` file is at your home directory. (e.g.,
`/home/<your_id>/.bashrc`)

### Building Examples (Checker & AST Visitor)

```
$ cd <this/repo/dir>
$ mkdir build
$ cd build
$ cmake -DLLVM_DIR=$LLVM_BUILD_DIR/lib/cmake/llvm/ ..
$ make
```

### Running

## AST Visitor (PrintFunction)

```
$ clang -fplugin=</path/to/build>/lib/libprintfunc.so \
    -c </path/to/source> 
```

## Checker (StreamChecker)

```
$ clang -fsyntax-only -fplugin=lib/libSimpleStreamChecker.so \
    -Xclang -analyze -Xclang -analyzer-checker=demo.SimpleStreamChecker \
    <this/repo/dir>/test/files.c
```


### Additional Remarks

- Change `printfunc` in `lib/CMakeLists.txt` to your plugin name.
  `libprintfunc.so` will be renamed to `lib<your-plugin-name>.so`.

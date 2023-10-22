## Building

### (Prerequisite) LLVM

0. Instal prerequisites.

```
 sudo apt install git
 sudo apt install cmake
```

1. Make a new drectory and move into it.

```
 mkdir llvm
 cd llvm
```

2. Clone LLVM 15.

```
 git clone -b llvmorg-15.0.7 https://github.com/llvm/llvm-project
```
### if it is too slow to dowload from github , you can dowload from gitee
 ```
 git clone -b llvmorg-15.0.7 https://gitee.com/mirrors/LLVM.git
 ```
### also you can dowload the zip file
```
链接：https://pan.baidu.com/s/1pOyKoTCfEq-SzBMgH1K_ww?pwd=9999 
提取码：9999 
```
3. Make a build directory and move into it.

```
$ cd <llvm_dir>
$ mkdir build
$ cd build
```

4. build llvm (c.f., this will generate Makefile here).

llvm build目录下:
1、cmake -DLLVM_TARGETS_TO_BUILD=X86 -DCMAKE_BUILD_TYPE=Release     -DCMAKE_INSTALL_PREFIX=$(pwd)/../install     -DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra"     -G "Unix Makefiles"  -DLLVM_ENABLE_ASSERTIONS=ON     -DCMAKE_CXX_FLAGS=${CMAKE_CLANG_FLAGS}     -DBUILD_SHARED_LIBS=ON  -DCLANG_ENABLE_STATIC_ANALYZER=ON -DLLVM_ENABLE_PLUGINS=ON ../llvm
2、 make install -j8  (8是线程数) 
### 注意自己的线程数小于等于逻辑cpu个数  不要太多 不然可能会卡死


5. Set environment variables.
### add this to .bashrc file
```
 export PATH=$PATH:$LLVM_BUILD_DIR/bin
```
### 例子:export PATH=$PATH:/home/gzy/gzy_work_second/cpp/llvm/LLVM/build/bin

### check llvm version:  llvm-config --version  看到15.0.7就是安装好了



### Plugins

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
### example: clang -fplugin=/home/gzy/gzy_work/cpp/clang_plugins/clang-plugin-template/build/lib/libPrintFunction.so -c /home/gzy/gzy_work/cpp/clang_plugins/clang-plugin-template/test/functions.c

### AST Matcher (explicit cast)
```
    <this/repo/dir>/build/bin/cast-match <this/repo/dir>/test/is_cast.c  
```
### 注意  此处可能会出现找不到头文件的情况，解决方法如下：
1、clang -E -x c - -v < /dev/null
2、将#include <...> 中的查找路径都加入到.bashrc文件中，如下:
查找路径：
#include <...> search starts here:
 /home/gzy/gzy_work_second/cpp/llvm/LLVM/build/lib/clang/15.0.7/include
 /usr/local/include
 /usr/include/x86_64-linux-gnu
 /usr/include
End of search list.
添加示例：
export MY_INCLUDES="-I/home/gzy/gzy_work_second/cpp/llvm/LLVM/build/lib/clang/15.0.7/include -I/usr/local/include -I/usr/include/x86_64-linux-gnu -I/usr/include"
### 此时命令如下:  
```
    <this/repo/dir>/build/bin/cast-match <this/repo/dir>/test/is_cast.c  -- ${MY_INCLUDES}
```
### example: /home/gzy/gzy_work/cpp/clang_plugins/clang-plugin-template/build/bin/cast-match /home/gzy/gzy_work/cpp/clang_plugins/clang-plugin-template/test/is_cast.c -- ${MY_INCLUDES}

### Checker (MainCallChecker)

```
clang -fsyntax-only -fplugin=<this/repo/dir>/build/lib/libMainCallChecker.so \
    -Xclang -analyze -Xclang -analyzer-checker=demo.MainCallChecker \
    <this/repo/dir>/test/maincall.c
```
### example:  clang -fsyntax-only -fplugin=/home/gzy/gzy_work/cpp/clang_plugins/clang-plugin-template/build/lib/libMainCallChecker.so -Xclang -analyze -Xclang -analyzer-checker=demo.MainCallChecker /home/gzy/gzy_work/cpp/clang_plugins/clang-plugin-template/test/maincall.c



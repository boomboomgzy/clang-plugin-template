#include<stdio.h>
typedef int (*main_t)(int, char **);
int main(int argc, char **argv) {
  main_t foo = main;
  int exit_code = foo(argc, argv);   // actually calls main()!
  return exit_code;
}


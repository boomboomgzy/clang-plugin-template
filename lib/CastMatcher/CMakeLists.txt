set(LLVM_LINK_COMPONENTS support)

add_executable(cast-match
  castmatch.cpp
  )
target_link_libraries(cast-match
  PRIVATE
  clangAST
  clangASTMatchers
  clangBasic
  clangFrontend
  clangSerialization
  clangTooling
  clangParse
  LLVMSupport
  LLVMCore
  LLVMFrontendOpenMP
  )
if (NOT LLVM_INCLUDE_DIRS OR NOT LLVM_LIBRARY_DIRS)
   message(FATAL_ERROR "No LLVM and Clang support requires LLVM")
else (NOT LLVM_INCLUDE_DIRS OR NOT LLVM_LIBRARY_DIRS)

function(add_suffix oldlist suffix newlist)
   set(locallist "")
   foreach(element ${${oldlist}})
      list(APPEND locallist "${element}${suffix}")
   endforeach(element)
   set(${newlist} "${locallist}" PARENT_SCOPE)
endfunction(add_suffix)

function(set_clang_include_dirs)
  add_suffix(LLVM_INCLUDE_DIRS "/../../clang/include/" SEARCH_HINTS_STATIC)
  find_path(STATIC_INCLUDES clang/Basic/Version.h
            HINTS ${LLVM_INCLUDE_DIRS} ${SEARCH_HINTS_STATIC})
  add_suffix(LLVM_INCLUDE_DIRS "/../tools/clang/include/" SEARCH_HINTS_DYNAMIC)
  find_path(DYNAMIC_INCLUDES clang/Config/config.h
            HINTS ${LLVM_INCLUDE_DIRS} ${SEARCH_HINTS_DYNAMIC})
  string(COMPARE NOTEQUAL ${STATIC_INCLUDES} ${DYNAMIC_INCLUDES} DIFFERENT)
  if (DIFFERENT)
    list(APPEND STATIC_INCLUDES ${DYNAMIC_INCLUDES})
  endif (DIFFERENT)
  set(CLANG_INCLUDE_DIRS ${STATIC_INCLUDES} PARENT_SCOPE)
endfunction(set_clang_include_dirs)

set_clang_include_dirs()

endif (NOT LLVM_INCLUDE_DIRS OR NOT LLVM_LIBRARY_DIRS)

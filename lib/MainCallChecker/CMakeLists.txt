add_library(MainCallChecker MODULE
  MainCallChecker.cpp
)

target_include_directories(MainCallChecker
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

install(TARGETS MainCallChecker DESTINATION lib)

#set_target_properties(MainCallChecker PROPERTIES
#  CXX_VISIBILITY_PRESET hidden
#)
#
#target_link_libraries(MainCallChecker
#  PRIVATE
#    clang-cpp
#)

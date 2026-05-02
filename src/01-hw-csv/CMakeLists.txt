add_library(Output STATIC output.c)
add_library(DynamicTable STATIC dynamicTable.c)

target_include_directories(Output PUBLIC .)
target_include_directories(DynamicTable PUBLIC .)

add_compile_definitions(_GNU_SOURCE)

add_executable(pretty-printer main.c)
target_link_libraries(pretty-printer PRIVATE Output DynamicTable)

add_executable(tests tests.c)

target_link_libraries(tests PRIVATE DynamicTable)

add_test(NAME AllUnitTests COMMAND tests)
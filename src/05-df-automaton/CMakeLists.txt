add_library(DFA STATIC dfa.c)

target_link_directories(DFA PUBLIC .)

add_executable(checkNumber main.c)
target_link_libraries(checkNumber DFA)

add_executable(tests test.c)
target_link_libraries(tests PRIVATE DFA)
add_test(NAME tests COMMAND tests)
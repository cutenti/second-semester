add_library(DFA STATIC dfa.c)

target_link_directories(DFA PUBLIC .)

add_executable(checkNumber main.c)
target_link_libraries(checkNumber DFA)
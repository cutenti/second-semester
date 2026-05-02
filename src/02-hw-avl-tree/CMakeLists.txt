add_library(Dictionary STATIC dictionary.c)

target_include_directories(Dictionary PUBLIC .)

add_executable(aerosoft main.c)
target_link_libraries(aerosoft Dictionary)
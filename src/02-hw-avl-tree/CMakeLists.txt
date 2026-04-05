add_library(AVLTree STATIC AVLTree.c)

target_include_directories(AVLTree PUBLIC .)

add_executable(aerosoft main.c)
target_link_libraries(aerosoft AVLTree)
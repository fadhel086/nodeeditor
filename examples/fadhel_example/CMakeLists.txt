file(GLOB_RECURSE CPPS ./*.cpp)

add_executable(fadhel_example ${CPPS})

target_link_libraries(fadhel_example nodes)

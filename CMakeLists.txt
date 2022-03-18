cmake_minimum_required(VERSION 3.0.0)
project(fib)

add_subdirectory(lib)

add_executable(${PROJECT_NAME} main.c)

option(fsanitizer "Run with fnsanitizerr" OFF)
if(fsanitizer)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address,undefined -fno-sanitize-recover=all -fsanitize-undefined-trap-on-error" )
else()
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )
endif(fsanitizer)
unset(fsanitizer CACHE)


target_include_directories(${PROJECT_NAME} PUBLIC ${FIB_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${FIB_LIB_LIBRARIES})

add_subdirectory(tests)
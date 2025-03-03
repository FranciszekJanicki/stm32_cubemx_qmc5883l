add_library(qmc5883l STATIC)

target_sources(qmc5883l PRIVATE 
    "qmc5883l.cpp"
)

target_include_directories(qmc5883l PUBLIC 
    "."
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(qmc5883l PRIVATE
    utility
    stm32cubemx
)

target_compile_options(qmc5883l PUBLIC
    -std=c++23
    -Wall
    -Wextra
    -Wconversion
    -Wshadow
    -Wpedantic
    -Wnarrowing
    -Waddress
    -pedantic
    -Wdeprecated
    -Wsign-conversion
    -Wduplicated-cond
    -Wduplicated-branches
    -Wlogical-op
    -Wnull-dereference
    -Wdouble-promotion
    -Wimplicit-fallthrough
    -Wcast-align
    -fconcepts
)

add_library(qmc5883l STATIC)

target_sources(qmc5883l PRIVATE 
    "qmc5883l.c"
)

target_include_directories(qmc5883l PUBLIC
)

target_link_libraries(qmc5883l PRIVATE
)

target_compile_options(qmc5883l PUBLIC
    -std=c23
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
)

cmake_minimum_required(VERSION 3.9.6)

project(brainscrawl)

set(SOURCES
    src/main.cc
   )

add_executable(brainscrawl ${SOURCES})

target_include_directories(brainscrawl
                           PRIVATE
                           ${PROJECT_SOURCE_DIR}/include
                           ${PROJECT_SOURCE_DIR}/include/lexer
                           ${PROJECT_SOURCE_DIR}/include/parser
                          )

cmake_minimum_required(VERSION 3.8)

project(vtoml LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(vlex
    GIT_REPOSITORY https://github.com/viper-org/vlex
    GIT_TAG master)
FetchContent_MakeAvailable(vlex)

set(SOURCES
    "source/Value.cpp"

    "source/parser/Parser.cpp"
)

set(HEADERS
    "include/vtoml/Value.h"

    "include/vtoml/parser/Parser.h"
)

source_group(TREE ${PROJECT_SOURCE_DIR} FILES ${SOURCES} ${HEADERS})

add_library(vtoml ${SOURCES} ${HEADERS})

target_include_directories(vtoml PUBLIC include)
target_compile_features(vtoml PUBLIC cxx_std_20)

vlex_generate(vtoml source/lexer/Lexer.vlex source/lexer include/vtoml/lexer)
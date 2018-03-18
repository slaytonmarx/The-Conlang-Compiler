cmake_minimum_required(VERSION 3.8)
project(TheConlangCompiler)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp headers.h Menu.h Menu.cpp Codex.h Codex.cpp Grammar.cpp Grammar.h Scrivener.cpp Scrivener.h)
add_executable(TheConlangCompiler ${SOURCE_FILES})
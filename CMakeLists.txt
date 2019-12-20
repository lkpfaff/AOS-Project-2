cmake_minimum_required(VERSION 3.14)
project(Project_1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_COMPILER "/usr/bin/clang++")

add_executable(Project_1 main.cpp RBTree.cpp RBTree.h splay.cpp splay.h Trie.cpp Trie.h RedBlackC.cpp RedBlackC.h Tests.cpp Tests.h SplayMain.cpp SplayTree.h)
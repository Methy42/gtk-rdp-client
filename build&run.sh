#!/bin/bash

# 删除当前目录中的build目录
rm -rf build

# 创建一个新的build目录并进入
mkdir build && cd build

# 使用CMake生成Makefile
cmake ..

# 使用Make编译程序
make

# 运行程序
./rdp-client